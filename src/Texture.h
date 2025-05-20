#ifndef  TEXTURE
#define TEXTURE

#include <glad/glad.h>

#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::string, std::cout, std::endl;

class Texture {
	unsigned int textureID;
public:
	Texture() = default;
	Texture(const string& path) {

		glGenTextures(1, &textureID);
		
		int w, h, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &w, &h, &nrChannels, 0);
		if (data) {
			
			glBindTexture(GL_TEXTURE_2D, textureID);

			GLenum format{};
			if (nrChannels == 1) format = GL_RED;
			else if (nrChannels == 3) format = GL_RGB;
			else if (nrChannels == 4) format = GL_RGBA;
			
			glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


			stbi_image_free(data);
		}
		else {
			cout << " Texture Failed to load at path: " << path << endl;
			stbi_image_free(data);
		}

	}

	Texture* operator() (const string& path) {
		return this;
	}

	unsigned int getTextureID() const {
		return textureID;
	}

	void bindTexture(const unsigned int texSlot = 0) const {
		glActiveTexture(GL_TEXTURE0 + texSlot);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void unBindTexture() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}


};


#endif // ! TEXTURE

