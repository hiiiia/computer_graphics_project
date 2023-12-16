#pragma once
#include <windows.h>		
#include <stdlib.h>
#include <math.h>
#include "glaux.h"	
#include <gl/glut.h>	
#include <gl/glu.h>	

struct particle {
	vec3 pos;
	vec3 d;
	vec3 vel;
	vec3 force;
};

vec3 camEye;
vec3 camAt;

GLfloat GetParticleRotate() {

	GLfloat normal[] = { 0.0f, 1.0f, 0.0f };
	vec3  camVec = camAt - camEye;
	GLfloat dot_product = camVec[0] * normal[0] + camVec[1] * normal[1] + camVec[2] * normal[2];
	GLfloat magnitude_vector = sqrt(camVec[0] * camVec[0] + camVec[1] * camVec[1] + camVec[2] * camVec[2]);
	GLfloat magnitude_normal = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	GLfloat cosine_angle = dot_product / (magnitude_vector * magnitude_normal);
	GLfloat angle_degrees = acos(cosine_angle) * 180.0 / 3.141592; // 라디안 값을 각도로 변환

	return angle_degrees;
}

class Weather_Spring {
public:
#define Sakura_Amount 3333
#define Map_Size 7.0f
	particle p[Sakura_Amount];

	void SetParticle(int i) {

		p[i].pos.x = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.y = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.z = 3.f;

		//p[i].vel = vec3((rand() % 50) - 25.0f, (rand() % 50) - 25.0f, -(rand() % 25) );
		p[i].d.x = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.y = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.z = -(rand() / 32767.0f ) / 100.0f;
	}

	void Draw() {
		
		glPushMatrix();
			glRotatef( GetParticleRotate(), 0.0 , 0.0, 1.0 );
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, 1);

			for (int i = 0; i < Sakura_Amount; i++) {
				p[i].pos.x += cos(45 * .0174532925f) * 0.0005f;
				p[i].pos.y += sin(45 * .0174532925f)* 0.0005f;
				p[i].pos.z += p[i].d.z;

				if (p[i].pos.z <= -0.25f) {
					SetParticle(i);
				}
			}

			for (int i = 0; i < Sakura_Amount; i++) {
				float dif = 0.0;
				float mul = 3.0f;
				if (i % 3 == 0)		dif = 0.01 * mul;
				else if (i % 3 == 1)	dif = 0.02 * mul;
				else				dif = 0.03 * mul;

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[(i % 2)+10]);
				glPushMatrix();
				glTranslatef(p[i].pos.x, p[i].pos.y, p[i].pos.z);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(dif, 0, 0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(dif, 0, dif);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, dif);
					glEnd();
				glPopMatrix();
			}

			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		//cout << "웨더 업데이트 실행중인 ㅋㅋ" << endl;
	}

	void Update() {
		Draw();
	}

	void Init() {
		cout << "웨더 이닛 실행된 ㅋㅋ" << endl;
		for (int i = 0; i < Sakura_Amount; i++) {
			SetParticle(i);
		}
	}
};

class Weather_Winter {
public:

#define Snow_Amount 3333
#define Map_Size 7.0f
	particle p[Snow_Amount];

	void SetParticle(int i) {

		p[i].pos.x = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.y = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.z = 3.f;

		//p[i].vel = vec3((rand() % 50) - 25.0f, (rand() % 50) - 25.0f, -(rand() % 25) );
		p[i].d.x = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.y = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.z = -(rand() / 32767.0f) / 100.0f;
	}

	void Draw() {

		glPushMatrix();
		glRotatef(GetParticleRotate(), 0.0, 0.0, 1.0);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, 1);

		for (int i = 0; i < Snow_Amount; i++) {
			p[i].pos.x += cos(45 * .0174532925f) * 0.0005f;
			p[i].pos.y += sin(45 * .0174532925f) * 0.0005f;
			p[i].pos.z += p[i].d.z;

			if (p[i].pos.z <= -0.25f) {
				SetParticle(i);
			}
		}

		for (int i = 0; i < Snow_Amount; i++) {
			float dif = 0.0;
			float mul = 3.0f;
			if (i % 3 == 0)		dif = 0.01 * mul;
			else if (i % 3 == 1)	dif = 0.02 * mul;
			else				dif = 0.03 * mul;

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[(i % 3) + 12]);
			glPushMatrix();
			glTranslatef(p[i].pos.x, p[i].pos.y, p[i].pos.z);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(dif, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(dif, 0, dif);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, dif);
			glEnd();
			glPopMatrix();
		}

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		//cout << "웨더 업데이트 실행중인 ㅋㅋ" << endl;
	}

	void Update() {
		Draw();
	}

	void Init() {
		cout << "웨더 이닛 실행된 ㅋㅋ" << endl;
		for (int i = 0; i < Snow_Amount; i++) {
			SetParticle(i);
		}
	}
};

class Weather_Fall {
public:

#define Snow_Amount 3333
#define Map_Size 7.0f
	particle p[Snow_Amount];

	void SetParticle(int i) {

		p[i].pos.x = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.y = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.z = 3.f;

		//p[i].vel = vec3((rand() % 50) - 25.0f, (rand() % 50) - 25.0f, -(rand() % 25) );
		p[i].d.x = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.y = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.z = -(rand() / 32767.0f) / 100.0f;
	}

	void Draw() {

		glPushMatrix();
		glRotatef(GetParticleRotate(), 0.0, 0.0, 1.0);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, 1);

		for (int i = 0; i < Snow_Amount; i++) {
			p[i].pos.x += cos(45 * .0174532925f) * 0.0005f;
			p[i].pos.y += sin(45 * .0174532925f) * 0.0005f;
			p[i].pos.z += p[i].d.z;

			if (p[i].pos.z <= -0.25f) {
				SetParticle(i);
			}
		}

		for (int i = 0; i < Snow_Amount; i++) {
			float dif = 0.0;
			float mul = 3.0f;
			if (i % 3 == 0)		dif = 0.01 * mul;
			else if (i % 3 == 1)	dif = 0.02 * mul;
			else				dif = 0.03 * mul;

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[(i % 2) + 15]);
			glPushMatrix();
			glTranslatef(p[i].pos.x, p[i].pos.y, p[i].pos.z);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(dif, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(dif, 0, dif);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, dif);
			glEnd();
			glPopMatrix();
		}

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		//cout << "웨더 업데이트 실행중인 ㅋㅋ" << endl;
		
	}

	void Update() {
		Draw();
	}

	void Init() {
		cout << "웨더 이닛 실행된 ㅋㅋ" << endl;
		for (int i = 0; i < Snow_Amount; i++) {
			SetParticle(i);
		}
	}
};

class Weather_Summer {
public:

#define Snow_Amount 3333
#define Map_Size 7.0f
	particle p[Snow_Amount];

	void SetParticle(int i) {

		p[i].pos.x = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.y = (rand() / 32767.0f - 0.5f) * Map_Size;
		p[i].pos.z = 3.f;

		//p[i].vel = vec3((rand() % 50) - 25.0f, (rand() % 50) - 25.0f, -(rand() % 25) );
		p[i].d.x = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.y = -(rand() / 32767.0f - 0.5f) / 200.0f;
		p[i].d.z = -(rand() / 32767.0f) / 50.0f;
	}

	void Draw() {

		glPushMatrix();
		glRotatef(GetParticleRotate(), 0.0, 0.0, 1.0);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, 1);

		for (int i = 0; i < Snow_Amount; i++) {
			p[i].pos.x += cos(45 * .0174532925f) * 0.0005f;
			p[i].pos.y += sin(45 * .0174532925f) * 0.0005f;
			p[i].pos.z += p[i].d.z;

			if (p[i].pos.z <= -0.25f) {
				SetParticle(i);
			}
		}

		for (int i = 0; i < Snow_Amount; i++) {
			float difx = 0.0, dify = 0.0;
			if (i % 3 == 0) {
				difx = 0.005;
				dify = 0.01;
			}
			else if (i % 3 == 1) {
				difx = 0.005;
				dify = 0.03;
			}
			else {
				difx = 0.005;
				dify = 0.05;
			}

			glDisable(GL_TEXTURE_2D);
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(p[i].pos.x - difx, p[i].pos.y , p[i].pos.z - dify);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(p[i].pos.x, p[i].pos.y , p[i].pos.z - dify);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(p[i].pos.x, p[i].pos.y, p[i].pos.z);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(p[i].pos.x - difx, p[i].pos.y, p[i].pos.z);
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
			
		}

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		//cout << "웨더 업데이트 실행중인 ㅋㅋ" << endl;

	}

	void Update() {
		Draw();
	}

	void Init() {
		cout << "웨더 이닛 실행된 ㅋㅋ" << endl;
		for (int i = 0; i < Snow_Amount; i++) {
			SetParticle(i);
		}
	}
};


class Weather {
public:
	Weather_Spring weather_Spring;
	Weather_Winter weather_Winter;
	Weather_Fall weather_Fall;
	Weather_Summer weather_Summer;
	
	static int weatherCount;
	
	void Update(vec3 eye, vec3 at) {
		camEye = eye;
		camEye = at;

		switch (weatherCount) {
		case 0 :
			weather_Summer.Update();
			break;
		case 1 : 
			weather_Fall.Update();
			break;
		case 2 :
			weather_Winter.Update();
			break;
		case 3 :
			weather_Spring.Update();
			break;
		}
	}

	void init() {
		weather_Spring.Init();
		weather_Winter.Init();
		weather_Fall.Init();
		weather_Summer.Init();
	}

	static void ChangeWeather() {
		weatherCount = (weatherCount + 1 ) % 4;
	}
};
int Weather::weatherCount = 0;