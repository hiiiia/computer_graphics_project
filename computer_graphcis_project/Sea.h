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
#include "LoadTex.h"
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


	virtual void Move(float time) = 0;
	virtual void Destroy() = 0;
	virtual void DrawObj(float x, float y, float z, float rot) = 0;

};

class OakCask : public MovingObj {
	static int Total_OakCask_Count;
public:
	
	LoadObj4 obj;
	vec3 position;


	float DownOakSize = 30.f;
	float speed = 1.0f;

	float minY = -7.f;
	float minX = -7.f;
	float maxY = 7.f;
	float maxX = 7.f;
	OakCask(float x, float y, float z , float speed) {
		Total_OakCask_Count += 1;
		obj.Load("Images/objs/Wooden_Barrel/wood_barrel3.obj");
		position.x = x;
		position.y = y;
		position.z = z;
		this->speed = speed;
	}

	void DrawObj(float x, float y, float z, float rot) override {

		GLfloat oak_amb[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat oak_dif[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat oak_spe[] = { 1.0, 1.0 , 1.0, 1.0 };

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[7]);


		glPushMatrix();

		glTranslatef(x, y, z - 0.1);

		glRotatef(rot * 30.0, 1, 0, 0);
		glRotatef(rot * 15.0, 0, 1, 0);
		glPushMatrix();



		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, oak_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, oak_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, oak_spe);

		for (int j = 0; j < obj.objInfo.faces_vertices.size(); j++) {

			vec3 no(0, 0, 0);
			for (int k = 0; k < 4; k++) {
				vec3 p = obj.objInfo.normals[obj.objInfo.faces_normals[j][k]];

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
				vec3 p = obj.objInfo.vertices[obj.objInfo.faces_vertices[j][k]];
				vec2 uv = obj.objInfo.uvs[obj.objInfo.faces_uvs[j][k]];
				glTexCoord2f(uv.x, uv.y);
				glVertex3f(p[0] / DownOakSize, p[1] / DownOakSize, p[2] / DownOakSize);
			}
			glEnd();

		}

		/*for (int j = 0; j < obj.objInfo.faces_vertices.size(); j++) {


				cout << "노말 번호 정보 : [ ";
				for (int k = 0; k < 4; k++) {
					if (obj.objInfo.faces_normals[j][k] > obj.objInfo.normals.size() - 1) {
						cout << "\n\n\n 노말 큰 값 있음 : " << obj.objInfo.faces_normals[j][k] <<"\n\n\n" << endl;
					}
					else if (obj.objInfo.faces_normals[j][k] < 0) {
						cout << "\n\n\n 작은 값 있음 : "<< obj.objInfo.faces_normals[j][k] << "\n\n\n" << endl;
					}
					else {
						cout << obj.objInfo.faces_normals[j][k] << " ";
					}


				}
				cout << " ]" << endl;



			}*/

			//
			//	
			//	for (int j = 0; j < obj.objInfo.faces_vertices.size(); j++) {
			//		cout << "정점 번호 정보 : [ ";
			//		for (int k = 0; k < 4; k++) {
			//			if (obj.objInfo.faces_vertices[j][k] > obj.objInfo.vertices.size()-1) {
			//				cout << "\n\n\n 큰 값 있음 \n\n\n" << endl;
			//			}
			//			else if (obj.objInfo.faces_vertices[j][k] < 0) {
			//				cout << "\n\n\n 작은 값 있음 \n\n\n" << endl;
			//			}
			//			//vec3 p = obj.objInfo[i].vertices[obj.objInfo[i].faces_vertices[j][k]];
			//			cout << obj.objInfo.faces_vertices[j][k] << " ";
			//			//glVertex3f(p[0], p[1], p[2]);
			//		}
			//		cout << " ]" << endl;
			//	}



		glPopMatrix();
		glPopMatrix();

		

		glPopMatrix();

	}

	void Move(float time) override {
		
		if (position.y < minY) {
			
			position.y = maxY;
		}
		else if (position.x < minX) {
			position.x = maxX;
		}

		float dx = -(cos(2.0f * (time)*PI / 180.0f)+1)*speed / 200.0;
		float dy = -(sin(4.0f * (time)*PI / 180.0f) ) / 200.0;
		float dz = (sin(2.0f * (time)*PI / 180.0f) / 100.0 ) ;

		position.x += dx;
		position.y += dy;
		position.z = dz;

		//cout << position.x << " " << position.y << " " << position.z << endl;

		DrawObj(position.x, position.y, position.z , sin(2.0f * (time)*PI / 180.0f) );
		
	}

	void Destroy() override {
	}



};
int OakCask::Total_OakCask_Count = 0;

class Sea {
public:
	//LoadTexture _loadTexture;
	float vertices[SeaSize][SeaSize][SeaSize];
	vector <OakCask> Oaks;

	void init() {

		//_loadTexture.Load("Images/water.bmp");
		//cout << "zzzzz : " << _loadTexture.MyTextureObject[0] << endl;
		//glEnable(GL_TEXTURE_2D);
		OakCask oak1(4, -6, 0, 1);
		OakCask oak2(5, -3.5, 0, 2);
		OakCask oak3(4, -1.5, 0, 1.2);
		OakCask oak4(5, 1.5, 0, 1.7);
		OakCask oak5(4, 3.5, 0, 1.5);
		OakCask oak6(5, 6, 0, 2.2);
		OakCask oak7(4, 2.5, 0, 2.4);
		OakCask oak8(5, -2.5, 0, 2.7);

		Oaks.push_back(oak1);
		Oaks.push_back(oak2);
		Oaks.push_back(oak3);
		Oaks.push_back(oak4);
		Oaks.push_back(oak5);
		Oaks.push_back(oak6);
		Oaks.push_back(oak7);
		Oaks.push_back(oak8);
		
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


		//cout << LoadTex::MyTextureObject[6];
		glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[6]);
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
	
	void Update(float time) {

		DrawSea(time, 1, 20, 25);

		for (int i = 0; i < 8; i++) {
			Oaks[i].Move(time);
		}
	}
};
