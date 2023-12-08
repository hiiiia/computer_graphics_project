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

#define PI 3.1415926
#define TEXTURE_NUM 1

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

public:
	OakCask() {

	}

	void Move() override {

	}

	void Destroy() override {

	}

	inline void DrawObj(float x, float y, float z) override {
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

		pos_x = x;
		pos_y = y;
		pos_z = z;

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
		glPopMatrix();
		cout << "��ũ�� ������";
	}

};

class Sea {
public:
	unsigned int MyTextureObject[1];
	AUX_RGBImageRec* pTextureImage[1];

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

	void DrawSea(int seaSize, float time) {
		// 1. �� ����
		// 2. �� ��ġ �̵�
		// 3. �� �׸���

		//����
		GLfloat sea_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat sea_mat_diff[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat sea_mat_specular[] = { 0.5, 0.5, 1.0, 1.0 };

		GLfloat seaLightpos[] = { 1,1,1,1 };
		const int SeaSize = seaSize;



		float stime = 0.5f * sin(time * PI / 180.0f);
		float ctime = sin(time * PI / 180.0f);

		// 1. 3D Array Init
		float vertices[100][100][100];
		/*float*** vertices = new float** [SeaSize];
		for (int i = 0; i < SeaSize; i++) {
			vertices[i] = new float* [SeaSize];
			for (int j = 0; j < SeaSize; j++) {
				vertices[i][j] = new float[3];
			}
		}*/

		// 2. move vertexPos

		float timeTmp = 0.0f;

		for (int i = 0; i < SeaSize; i++) {
			for (int j = 0; j < SeaSize; j++) {
				vertices[i][j][0] = i - (int)( SeaSize / 2 );
				vertices[i][j][1] = j - (int)( SeaSize / 2 );
				vertices[i][j][2] = 0.25f * sin(2.0f * (time + timeTmp) * PI / 180.0f);
			}
			timeTmp += 30;



		}
		for (int i = 0; i < SeaSize; i++) {

			for (int j = 0; j < SeaSize; j++) {
				vertices[j][i][2] = +0.25f * -sin(2.0f * (time + timeTmp) * PI / 180.0f);
				vertices[j][i][2] /= 2;
			}
			timeTmp += 30;

		}


		// 3. draw Sea
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
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


				glBegin(GL_TRIANGLES);
				vec3 p1(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
				vec3 p2(vertices[i][j + 1][0], vertices[i][j + 1][1], vertices[i][j + 1][2]);
				vec3 p3(vertices[i + 1][j][0], vertices[i + 1][j][1], vertices[i + 1][j][2]);
				vec3 p4(vertices[i + 1][j + 1][0], vertices[i + 1][j + 1][1], vertices[i + 1][j + 1][2]);


				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(p1.x, p1.y, p1.z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(p2.x, p2.y, p2.z);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(p3.x, p3.y, p3.z);

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