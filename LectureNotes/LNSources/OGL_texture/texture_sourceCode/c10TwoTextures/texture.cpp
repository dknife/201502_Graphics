#include "texture.h"
#include "STBImage.h"

GLuint setTexture(char *filename) {
	GLuint texture;
	int width, height, bitsPerPixel;
	unsigned char *data = 
	stbi_load(filename, &width, 
			  &height, &bitsPerPixel, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				 width, height, 0, GL_RGB, 
				 GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	return texture;
}

void setTwoTextures(char *filename1, char *filename2, GLuint *tex1, GLuint *tex2) {
	GLuint texture[2];
	int width, height, bitsPerPixel;
	unsigned char *data1 = 
	stbi_load(filename1, &width, 
			  &height, &bitsPerPixel, 0);
	
	glGenTextures(2, &texture[0]);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				 width, height, 0, GL_RGB, 
				 GL_UNSIGNED_BYTE, data1);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	unsigned char *data2 = 
	stbi_load(filename2, &width, 
			  &height, &bitsPerPixel, 0);
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				 width, height, 0, GL_RGB, 
				 GL_UNSIGNED_BYTE, data2);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	*tex1 = texture[0];
	*tex2 = texture[1];
	
	glEnable(GL_TEXTURE_2D);
}