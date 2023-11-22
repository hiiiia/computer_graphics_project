#pragma once
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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
		cout << "오크통 생성됨";
	}

};