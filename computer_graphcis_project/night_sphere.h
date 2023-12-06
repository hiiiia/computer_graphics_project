#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#pragma once
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


class Night_sphere {
public:
	unsigned int MyTextureObject[TEXTURE_NUM];
	GLint g_textureID[1];

	AUX_RGBImageRec* pTextureImage[1];

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

	int LoadGLTextures(const char* szFilePath, int number) {       //파일을 로드하고 텍스쳐로 변환
		int width, height, nrChannels;
		memset(pTextureImage, 0, sizeof(void*) * 1);
		unsigned char* data = stbi_load(szFilePath, &width, &height, &nrChannels, 0);
		if (data) {
			glGenTextures(1, MyTextureObject + number);
			glBindTexture(GL_TEXTURE_2D, *(MyTextureObject + number));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			printf_s("\n%s %d %d %d\n", szFilePath, width, height, nrChannels);
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
			//LoadGLTextures("snow_terrian/front.bmp", 0) &&
			//LoadGLTextures("snow_terrian/back.bmp", 1) &&
			//LoadGLTextures("snow_terrian/top.bmp", 2) &&
			////LoadGLTextures("./Data/top.bmp", 2) &&
			//LoadGLTextures("snow_terrian/bottom.bmp", 3) &&
			//LoadGLTextures("snow_terrian/right.bmp", 4) &&
			//LoadGLTextures("snow_terrian/left.bmp", 5)&&
			LoadGLTextures("./Data/Earth.bmp", 0)

			) {
			printf_s("\nsky Image Load success\n");
		}
		else {
			printf_s("\nsky Image Load error\n");
		}

		glEnable(GL_TEXTURE_2D);
	}

	void Draw_night_sphere(int skybox_size) {

		glDisable(GL_TEXTURE_2D);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, *(MyTextureObject + 0));

		glEnable(GL_TEXTURE_2D);

		GLUquadric* obj = gluNewQuadric();
		gluQuadricTexture(obj, GL_TRUE);
		gluQuadricNormals(obj, GLU_SMOOTH);
		gluSphere(obj, skybox_size, 100, 100);
		gluDeleteQuadric(obj);


	}

};

