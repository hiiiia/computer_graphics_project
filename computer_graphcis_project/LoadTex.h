#define _CRT_SECURE_NO_WARNINGS
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
#include "LoadObj.h"
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define PI 3.1415926
#define TEXTURE_NUM 20


using namespace glm;
using namespace std;

class LoadTex {
public:
	static unsigned int MyTextureObject[TEXTURE_NUM];

	int LoadGLTextures(const char* szFilePath, int number) {       //?????? ?ε???? ?????? ???
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
			cout << "텍스쳐 번호 : " << number << " 텍스처 내용 : " << MyTextureObject[number] << endl;
			return true;
		}
		else {
			std::cerr << "Failed to load texture: " << szFilePath << std::endl;
			stbi_image_free(data);
			return false;
		}
	}

	LoadTex() {

		
		/*LoadTexture2("snow_terrian/front.bmp");
		LoadTexture2("snow_terrian/top.bmp");
		LoadTexture2("snow_terrian/bottom.bmp");
		LoadTexture2("snow_terrian/back.bmp");
		LoadTexture2("snow_terrian/right.bmp");
		LoadTexture2("snow_terrian/left.bmp");
		LoadTexture2("Images/water.bmp");
		LoadTexture2("Images/wood2.bmp");*/
	}

	void init() {
		LoadGLTextures("snow_terrian/front.bmp", 0);
		LoadGLTextures("snow_terrian/back.bmp", 1);
		LoadGLTextures("snow_terrian/top.bmp", 2);
		LoadGLTextures("snow_terrian/bottom.bmp", 3);
		LoadGLTextures("snow_terrian/right.bmp", 4);
		LoadGLTextures("snow_terrian/left.bmp", 5);
		LoadGLTextures("Images/water.bmp", 6);
		LoadGLTextures("Images/wood2.bmp", 7);
		LoadGLTextures("Images/wood3.jpg", 8);
		LoadGLTextures("Images/raft.png", 9);
	}

};
unsigned int LoadTex::MyTextureObject[TEXTURE_NUM] = { 0 };