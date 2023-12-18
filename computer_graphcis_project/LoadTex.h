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
#define TEXTURE_NUM 30


using namespace glm;
using namespace std;

class LoadTex {
public:
	static unsigned int MyTextureObject[TEXTURE_NUM];

	int LoadGLTextures(const char* szFilePath, int number) {     
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
			cout << "Texture : " << number << " Texture Number: " << MyTextureObject[number] << endl;
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




		LoadGLTextures("Data/Sakura1.bmp", 10);
		LoadGLTextures("Data/Sakura2.bmp", 11);
		LoadGLTextures("Data/SnowSmall.bmp", 12);
		LoadGLTextures("Data/SnowMiddle.bmp", 13);
		LoadGLTextures("Data/SnowLarge.bmp", 14);
		LoadGLTextures("Data/FallenLeaf.bmp", 15);
		LoadGLTextures("Data/FallenLeaf2.bmp", 16);
		

		LoadGLTextures("Data/skybox2/front.bmp", 17);
		LoadGLTextures("Data/skybox2/back.bmp", 18);
		LoadGLTextures("Data/skybox2/top.bmp", 19);
		LoadGLTextures("Data/skybox2/bottom.bmp", 20);
		LoadGLTextures("Data/skybox2/right.bmp", 21);
		LoadGLTextures("Data/skybox2/left.bmp", 22);


		LoadGLTextures("Data/Planets/Sun.bmp", 23);
		LoadGLTextures("Data/Planets/Moon.bmp", 24);
		LoadGLTextures("Data/Planets/Pluto.bmp", 25);

		LoadGLTextures("Data/stone/birdd.png", 26);

	}

};
unsigned int LoadTex::MyTextureObject[TEXTURE_NUM] = { 0 };