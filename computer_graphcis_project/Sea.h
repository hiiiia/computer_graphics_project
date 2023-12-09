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

class raft {

};

class MovingObj {
public:
	float pos_x;
	float pos_y;
	float pos_z;


	virtual void Move() = 0;
	virtual void Destroy() = 0;
	virtual inline void DrawObj(float x, float y, float z) = 0;

};

class OakCask : public MovingObj {
	static int Total_OakCask_Count;
public:
	
	LoadObj4 obj;

	OakCask() {
		Total_OakCask_Count += 1;
		obj.Load("Images/objs/Wooden_Barrel/Wooden Barrel.obj");
		obj.printInfo();
		cout << "\n\n오크통 객체 생성 완료 :: 총 개수 - " << Total_OakCask_Count << endl;
		
	}

	void Move() override {

	}

	void Destroy() override {

	}

	void DrawObj(float x, float y, float z) override {

		GLfloat oak_amb[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat oak_dif[] = { 0.1, 0.1, 0.8, 1.0 };
		GLfloat oak_spe[] = { 0.5, 0.5, 1.0, 1.0 };



		glPushMatrix();

			glTranslatef(x,y,z);
			glRotatef(90.0f, 1, 0, 0);
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT, oak_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, oak_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, oak_spe);

				for (int j = 0; j < obj.objInfo[1].faces_vertices.size(); j++) {
					
					vec3 no(0,0,0);
					for (int k = 0; k < 4; k++) {
						vec3 p = obj.objInfo[1].normals[obj.objInfo[1].faces_normals[j][k]];

						no.x += p.x;
						no.y += p.y;
						no.z += p.z;
					}

					no.x /= 4;
					no.y /= 4;
					no.z /= 4;

					
					glBegin(GL_QUADS);
					glNormal3f(no.x, no.y, no.z);
					for (int k = 0; k < 4; k++) {
						vec3 p = obj.objInfo[1].vertices[obj.objInfo[1].faces_vertices[j][k]];

						glVertex3f(p[0] / 15, p[1] / 15, p[2] / 15);
					}
					glEnd();

				}
				
				/*for (int j = 0; j < obj.objInfo[1].faces_vertices.size(); j++) {


						cout << "노말 정보 : [ ";
						for (int k = 0; k < 4; k++) {
							if (obj.objInfo[1].faces_normals[j][k] > obj.objInfo[1].normals.size() - 1) {
								cout << "\n\n\n 큰 값 있음 \n\n\n" << endl;
							}
							else if (obj.objInfo[1].faces_normals[j][k] < 0) {
								cout << "\n\n\n 작은 값 있음 \n\n\n" << endl;
							}
							cout << obj.objInfo[1].faces_normals[j][k] << " " ; 

						}
						cout << " ]" << endl;



					}*/

				//for (int i = 0; i < obj.objInfo.size(); i++) {
				//	glBegin(GL_QUADS);
				//	for (int j = 0; j < obj.objInfo[i].faces_vertices.size(); j++) {
				//		cout << "면 정보 : [ ";
				//		for (int k = 0; k < 4; k++) {
				//			if (obj.objInfo[i].faces_vertices[j][k] > obj.objInfo[i].vertices.size()-1) {
				//				cout << "\n\n\n 큰 값 있음 \n\n\n" << endl;
				//			}
				//			else if (obj.objInfo[i].faces_vertices[j][k] < 0) {
				//				cout << "\n\n\n 작은 값 있음 \n\n\n" << endl;
				//			}
				//			//vec3 p = obj.objInfo[i].vertices[obj.objInfo[i].faces_vertices[j][k]];
				//			cout << obj.objInfo[i].faces_vertices[j][k] << " ";
				//			//glVertex3f(p[0], p[1], p[2]);
				//		}
				//		cout << " ]" << endl;
				//	}
				//	glEnd();
				//}
			
			glPopMatrix();
		glPopMatrix();

		/*
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
		GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat no_shininess[] = { 0.0 };
		GLfloat low_shininess[] = { 5.0 };
		GLfloat high_shininess[] = { 100.0 };
		GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
		GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };

		glPushMatrix();
		glTranslatef(0.0, 0.0, 5);
		glLightfv(GL_LIGHT0, GL_POSITION,
			LightPosition);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x, y, z);
		glMaterialfv(GL_FRONT, GL_AMBIENT,
			mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,
			mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,
			mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS,
			high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION,
			no_mat);

		glutSolidSphere(1.0, 100, 100);
		glPopMatrix();*/

	}

};
int OakCask::Total_OakCask_Count = 0;

class Sea {
public:
	unsigned int MyTextureObject[1];
	AUX_RGBImageRec* pTextureImage[1];
	float vertices[SeaSize][SeaSize][SeaSize];

	AUX_RGBImageRec* LoadBMP(const char* Filename) {
		FILE* File = NULL;
		if (!Filename) return NULL;
		//File = fopen(Filename, "r");
		if (fopen_s(&File, Filename, "r") == 0) {
			fclose(File);
			return auxDIBImageLoad(Filename);	     // ���Ϸκ��� �޸𸮷�
		}
		return NULL;
	}

	int LoadGLTextures(const char* szFilePath) {       //������ �ε��ϰ� �ؽ��ķ� ��ȯ
		int Status = FALSE;
		glClearColor(0.0, 0.0, 0.0, 0.5);
		memset(pTextureImage, 0, sizeof(void*) * 1);    //�����͸� �η�

		if (pTextureImage[0] = LoadBMP(szFilePath)) {   //��Ʈ���� �ε��ϰ� ����Ȯ��
			Status = TRUE;                              //���� �÷��� True��
			glGenTextures(1, &MyTextureObject[0]);      //�ؽ��� ����
			glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3,
				pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
		}

		if (pTextureImage[0]) {                 //�ؽ��İ� �����ϸ�
			if (pTextureImage[0]->data) {       //�ؽ��� ������ �����ϸ�
				free(pTextureImage[0]->data);   //�ؽ��� ������� �ݳ�
			}
			free(pTextureImage[0]);             //�ؽ��� �ݳ�
		}
		return Status;
	}

	void init() {
		int Status = FALSE;

		if (LoadGLTextures("Images/water.bmp")) {
			printf_s("Sea Image Load success");
		}
		else {
			printf_s("Sea Image Load error");
		}

		glEnable(GL_TEXTURE_2D);
	}

	void DrawSea(float time, float height = 1.0f , float waveSpeedH = 30.0f , float waveSpeedV = 30.0f) {

		GLfloat sea_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat sea_mat_diff[] = { 0.8, 0.8, 0.8, 1.0 };
		GLfloat sea_mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };
		GLfloat sea_mat_shininess[] = { 50.0 };
		GLfloat seaLightpos[] = { 1,1,1,1 };



		// 1. 3D Array Init
		//float vertices[SeaSize][SeaSize][SeaSize];


		// 2. move vertexPos


		
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		float timeTmp = 0.0f;

		for (int i = 0; i < SeaSize; i++) {
			for (int j = 0; j < SeaSize; j++) {
				
				vertices[i][j][0] = ( ( i - (int)( SeaSize / 2 ) ) / SeaSize_Dense);
				vertices[i][j][1] = ( ( j - (int)( SeaSize / 2 ) ) / SeaSize_Dense);
				vertices[i][j][2] = height * ( 0.25*( sin(2.0f * (time + timeTmp) * PI / 180.0) ) ) / SeaSize_Dense;
				//cout << "바다 버텍스 위치  : "<< vertices[i][j][0] << " " << vertices[i][j][1] << " " << vertices[i][j][2] << " "<< endl;
			}
			timeTmp += waveSpeedH;



		}
		for (int i = 0; i < SeaSize; i++) {

			for (int j = 0; j < SeaSize; j++) {
				vertices[j][i][2] += height * ( 0.25f * -cos(2.0f * (time + timeTmp) * PI / 180.0f) ) / SeaSize_Dense;
				vertices[j][i][2] /= 2;
			}
			timeTmp += waveSpeedV;

		}


		// 3. draw Sea

		for (int i = 0; i < SeaSize - 1; i++) {


			for (int j = 0; j < SeaSize - 1; j++) {
				/*glBegin(GL_LINES);
				glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
				glVertex3f(vertices[i][j + 1][0], vertices[i][j + 1][1], vertices[i][j + 1][2]);

				glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
				glVertex3f(vertices[i+1][j][0], vertices[i+1][j][1], vertices[i+1][j][2]);

				glVertex3f(vertices[i][j + 1][0], vertices[i][j + 1][1], vertices[i][j + 1][2]);
				glVertex3f(vertices[i + 1][j][0], vertices[i + 1][j][1], vertices[i + 1][j][2]);

				glVertex3f(vertices[i][j + 1][0], vertices[i][j + 1][1], vertices[i][j + 1][2]);
				glVertex3f(vertices[i + 1][j + 1][0], vertices[i + 1][j + 1][1], vertices[i + 1][j + 1][2]);

				glVertex3f(vertices[i + 1][j][0], vertices[i + 1][j][1], vertices[i + 1][j][2]);
				glVertex3f(vertices[i + 1][j+1][0], vertices[i + 1][j+1][1], vertices[i + 1][j+1][2]);
				glEnd();*/
				glLightfv(GL_LIGHT0, GL_POSITION, seaLightpos);
				glMaterialfv(GL_FRONT, GL_AMBIENT, sea_mat_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, sea_mat_diff);
				glMaterialfv(GL_FRONT, GL_SPECULAR, sea_mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, sea_mat_shininess);


				glBegin(GL_TRIANGLES);
				vec3 p1(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
				vec3 p2(vertices[i][j + 1][0], vertices[i][j + 1][1], vertices[i][j + 1][2]);
				vec3 p3(vertices[i + 1][j][0], vertices[i + 1][j][1], vertices[i + 1][j][2]);
				vec3 p4(vertices[i + 1][j + 1][0], vertices[i + 1][j + 1][1], vertices[i + 1][j + 1][2]);

				vec3 nomal1(0, 0, 0);
				vec3 nomal2(0, 0, 0);

				nomal1 = cross(p3 - p1, p2 - p1);
				nomal1 = normalize(nomal1);

				nomal2 = cross(p4 - p3, p2 - p3);
				nomal2 = normalize(nomal2);

				glNormal3f(nomal1.x, nomal1.y, nomal1.z);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(p1.x, p1.y, p1.z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(p2.x, p2.y, p2.z);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(p3.x, p3.y, p3.z);

				glNormal3f(nomal2.x, nomal2.y, nomal2.z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(p2.x, p2.y, p2.z);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(p3.x, p3.y, p3.z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(p4.x, p4.y, p4.z);
				glEnd();


			}

		}
	}

};

class Test_SeaLight {
public:
	static void Init() {
		GLfloat sun_light_amb[] = { 0.5, 0, 0, 1.0 };
		GLfloat sun_light_diffuse[] = { 1, 0.5, 0.5, 1.0 };
		GLfloat sun_light_specular[] = { 1, 1, 1, 1.0 };

		glShadeModel(GL_SMOOTH); //���� ���̵�
		glEnable(GL_DEPTH_TEST);//���� ���� Ȱ��ȭ
		glEnable(GL_LIGHTING); //���� Ȱ��ȭ

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_amb); //�ֺ��� ����
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //Ȯ�걤 ����
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular); //���ݻ籤 ����
	}
};