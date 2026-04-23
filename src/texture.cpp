#include "texture.hpp"

Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	type = texType;

	// stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    if (!bytes)
    {
        std::cerr << "Failed to load texture: " << stbi_failure_reason() << "\n";
    }

	// generates an opengl texture object
	glGenTextures(1, &ID);
	// assigns the texture to a texture unit
	glActiveTexture(unit + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// extra lines in case you choose to use gl_clamp_to_border
	// float flatcolor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// gltexparameterfv(gl_texture_2d, gl_texture_border_color, flatcolor);

	// automatically assign color data without using input params
	if (numColCh == 4)
	{
	    glTexImage2D
		(
		    GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 3)
	{
	    glTexImage2D
		(
		    GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 1)
	{
    	glTexImage2D
    	(
    		GL_TEXTURE_2D,
    		0,
    		GL_RGBA,
    		widthImg,
    		heightImg,
    		0,
    		GL_RED,
    		GL_UNSIGNED_BYTE,
    		bytes
    	);
	}
	else
	{
	    throw std::invalid_argument("Automatic Texture type recognition failed.");
	}

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// deletes the image data as it is already in the opengl texture object
	stbi_image_free(bytes);

	// unbinds the opengl texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.shaderProgram, uniform);
	// shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
