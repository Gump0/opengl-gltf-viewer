#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.hpp>
#include "mesh.hpp"

using json = nlohmann::json;

class Model
{
public:
    Model(const char* file);

    void Draw(Shader& shader, Camera& camera);

private:
    const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// all the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// gets the binary data from a file
	std::vector<unsigned char> getData();
	// interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();             // <-- will need refining as specular implementation is not ideal
	                                                // also the way we check if a texture is already in-use kinda sucks (based off yt video)

	// assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	// helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

	// helper method to read file.
    std::string readFile(const char* filename);
};
#endif
