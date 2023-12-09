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

#define PI 3.1415926
#define TEXTURE_NUM 1
#define SeaSize 150
#define SeaSize_Dense 10.0

using namespace glm;
using namespace std;

class LoadTex {
public:
	static unsigned int MyTextureObject[20];
	AUX_RGBImageRec* pTextureImage[20];

	int count = 0;

	AUX_RGBImageRec* LoadBMP(const char* Filename) {
		FILE* File = NULL;
		if (!Filename) return NULL;
		//File = fopen(Filename, "r");
		if (fopen_s(&File, Filename, "r") == 0) {
			fclose(File);
			return auxDIBImageLoad(Filename);	     // ????リ??? ?????
		}
		return NULL;
	}

	int LoadGLTextures(const char* szFilePath) {       //?????? ?ュ???? ?????? ???
		int Status = FALSE;
		glClearColor(0.0, 0.0, 0.0, 0.5);
		//memset(pTextureImage, 0, sizeof(void*) * 20);    //??????? ?ョ?

		if (pTextureImage[count] = LoadBMP(szFilePath)) {   //??????? ?ュ???? ???????
			Status = TRUE;                              //???? ?＼??? True??
			glGenTextures(1, &MyTextureObject[count]);      //????? ????
			glBindTexture(GL_TEXTURE_2D, MyTextureObject[count]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3,
				pTextureImage[count]->sizeX, pTextureImage[count]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[count]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);

			count++;
		}

		if (pTextureImage[count]) {                 //?????? ???????
			if (pTextureImage[count]->data) {       //????? ?????? ???????
				free(pTextureImage[count]->data);   //????? ??????? ???
			}
			free(pTextureImage[count]);             //????? ???
		}
		return Status;
	}

	void Load(const char* FilePath) {

		if (LoadGLTextures(FilePath)) {
			cout << FilePath << " : Load Success :)" << endl;
		}
		else {
			cout << FilePath << " : Load Failed :(" << endl;
		}

		glEnable(GL_TEXTURE_2D);
	}

	LoadTex() {
		
		Load("snow_terrian/front.bmp");
		Load("snow_terrian/top.bmp");
		Load("snow_terrian/bottom.bmp");
		Load("snow_terrian/back.bmp");
		Load("snow_terrian/right.bmp");
		Load("snow_terrian/left.bmp");
		Load("Images/water.bmp");
		Load("Images/wood2.bmp");
	}


};
unsigned int LoadTex::MyTextureObject[20] = { 0 };