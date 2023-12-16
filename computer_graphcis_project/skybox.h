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


class Skybox {
public:
	unsigned int MyTextureObject[TEXTURE_NUM];
	GLint g_textureID[1];


	int LoadGLTextures(const char* szFilePath, int number) {       //������ �ε��ϰ� �ؽ��ķ� ��ȯ
		int width, height, nrChannels;
		unsigned char* data = stbi_load(szFilePath, &width, &height, &nrChannels, 0);
		if (data) {
			glGenTextures(1, MyTextureObject + number);
			glBindTexture(GL_TEXTURE_2D, *(MyTextureObject + number));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			printf_s("\n%s %d %d %d\n", szFilePath, width, height, nrChannels);
			stbi_image_free(data);
			//cout << "텍스쳐 번호 : " << number << " 텍스처 내용 : " << MyTextureObject[number] << endl;
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


		glEnable(GL_TEXTURE_2D);
	}

	void MakeSky(int skybox_size) {

		glEnable(GL_TEXTURE_2D);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);

		glPushMatrix();

		glRotated(90, 1, 0, 0);

		//printf_s("%d %d", MyTextureObject[0], MyTextureObject[1]);
		// Front face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[0]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);

		//glEnd();

		//// Back face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[1]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		//glEnd();

		//// Top face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[2]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		//glEnd();

		//// Bottom face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[3]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		//glEnd();

		//// Right face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[4]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);

		//glEnd();

		//// Left face
		//glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[5]);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		//glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		//glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		//glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		//glEnd();


		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[17]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);

		glEnd();

		// Back face
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[18]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glEnd();

		// Top face
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[19]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glEnd();

		// Bottom face
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[20]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glEnd();

		// Right face
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[21]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);

		glEnd();

		// Left face
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[22]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
		glEnd();
		glEnable(GL_DEPTH_TEST);

		glPopMatrix();

	}

};
