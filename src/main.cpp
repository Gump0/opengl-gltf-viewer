#include "model.hpp"
#include "gui.hpp"

const uint wWidth = 1920;
const uint wHeight = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "openGL gltf viewer", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // initialize imgui
    GUI gui;
    gui.InitializeImGUI(window);

    // generate shader object using shaders default.vert and default.frag
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	// light data n stuff
	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(0.5f, 5.0f, 10.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.shaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.shaderProgram, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

    // prevent faces from rendering on-top of one-another
    glEnable(GL_DEPTH_TEST);

    // opengl face-culling optimization
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), wWidth, wHeight);

    // load 3d gltf model
    std::string modelLocation;
    try
    {
        modelLocation = Model::SelectModel();
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR : " << e.what() << '\n';
        return -1;
    }
    Model model(modelLocation.c_str());


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // queue and hadle glfw events
        glfwPollEvents();

        // clear the screen
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // buffer new gui frame
        gui.NewFrameImGUI();

        // handle camera inputs and matrices
        camera.Inputs(window);
        camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);
        camera.Matrix(shaderProgram, "camMatrix");
        // draw model
        model.Draw(shaderProgram, camera);

        // render ImGUI before glfw scene
        gui.RenderImGUI();

        // swap back buffer with front buffer
        glfwSwapBuffers(window);
    }

    // cleanup
    gui.CleanUpImGUI();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
