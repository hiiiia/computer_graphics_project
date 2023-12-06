#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#pragma once
#include "stb_image.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include "glaux.h"
#include <gl/glut.h>

#define TEXTURE_NUM 6

using namespace glm;
using namespace std;


class Skybox {
public:
	unsigned int MyTextureObject[TEXTURE_NUM];
	GLint g_textureID[1];

	AUX_RGBImageRec* pTextureImage = NULL;

	AUX_RGBImageRec* LoadBMP(const char* Filename) {
		FILE* File = NULL;
		if (!Filename) return NULL;
		//File = fopen(Filename, "r");
		if (fopen_s(&File, Filename, "r") == 0) {
			fclose(File);
			return auxDIBImageLoad(Filename);	     // 파일로부터 메모리로
		}
		return NULL;
	}

	int LoadGLTextures(const char* szFilePath,int number) {       //파일을 로드하고 텍스쳐로 변환
		int width, height, nrChannels;
		unsigned char* data = stbi_load(szFilePath, &width, &height, &nrChannels, 0);
		if (data) {
			glGenTextures(1, MyTextureObject + number);
			glBindTexture(GL_TEXTURE_2D, *(MyTextureObject + number));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			printf_s("\n%s %d %d %d\n", szFilePath, width, height, nrChannels );
			stbi_image_free(data);
			return true;
		}
		else {
			std::cerr << "Failed to load texture: " << szFilePath << std::endl;
			stbi_image_free(data);
			return false;
		}
	}

	void init() {
		int Status = FALSE;

		if (
			LoadGLTextures("snow_terrian/front.bmp", 0) &&
			LoadGLTextures("snow_terrian/back.bmp", 1) &&
			LoadGLTextures("snow_terrian/top.bmp", 2) &&
			LoadGLTextures("snow_terrian/bottom.bmp", 3) &&
			LoadGLTextures("snow_terrian/right.bmp", 4) &&
			LoadGLTextures("snow_terrian/left.bmp", 5)
			) {
			printf_s("\nsky Image Load success\n");
		}
		else {
			printf_s("\nsky Image Load error\n");
		}

		glEnable(GL_TEXTURE_2D);
	}

	void MakeSky(int skybox_size) {

		glEnable(GL_TEXTURE_2D);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);


		//printf_s("%d %d", MyTextureObject[0], MyTextureObject[1]);
		// Front face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);

		glEnd();

		// Back face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glEnd();

		// Top face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glEnd();

		// Bottom face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glEnd();

		// Right face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[4]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);

		glEnd();

		// Left face
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glEnd();

		glEnable(GL_DEPTH_TEST);
	}

};

