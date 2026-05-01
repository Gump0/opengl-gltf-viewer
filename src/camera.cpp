#include "camera.hpp"

Camera::Camera(glm::vec3 position, uint width, uint height)
{
    Camera::position = position;
    Camera::width = width;
    Camera::height = height;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // initialize matrices since otherwise they will be a null matrix
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width/(float)height, nearPlane, farPlane);

    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	// handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS ||
	    glfwGetKey(window, GLFW_KEY_LEFT_ALT == GLFW_PRESS))
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = shiftSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = releasedSpeed;
	}

	// handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
	    glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// stores the coordinates of the cursor
		double mouseX, mouseY;
		// fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if(firstClick)
		{
		    lastMouseX = mouseX;
			lastMouseY = mouseY;
			firstClick = false;
		}

		// rotate only by how much the mouse has moved by :)
		float rotX = sensitivity * (float)(mouseY - lastMouseY) / height;
		float rotY = sensitivity * (float)(mouseX - lastMouseX) / width;

		lastMouseX = mouseX;
		lastMouseY = mouseY;

        // vertical rotation (pitch) with clamping
        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX),
                                            glm::normalize(glm::cross(orientation, up)));
        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            orientation = newOrientation;

        // horizontal rotation (yaw)
        orientation = glm::rotate(orientation, glm::radians(-rotY), up);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;  // reset so next click doesn't jump
    }
}
