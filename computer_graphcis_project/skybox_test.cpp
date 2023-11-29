//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
////#include <glad/glad.h>
//
//#include <vector>
//#include <GLAUX/glaux.h>
//
//#include <glm/glm.hpp> 
//#include <glm/gtc/matrix_transform.hpp> 
//#include <glm/gtc/type_ptr.hpp>
//
//
//
//#include <iostream>
//using namespace glm;
//using namespace std;
//
//
//GLfloat xrot = 1.0f, yrot = 1.0f, zrot = 1.0f;
//unsigned int MyTextureObject[6];
//AUX_RGBImageRec* pTextureImage[1];  //텍스쳐 저장 공간을 가리키는 포인터
//
//void MyReshape(int w, int h) {
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//}
//
//void MyDisplay() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	float skybox_size = 50.0f;
//
//
//	// Front face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
//
//	glEnd();
//
//	// Back face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
//	glEnd();
//
//	// Top face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[2]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
//	glEnd();
//
//	// Bottom face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[3]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
//	glEnd();
//
//	// Right face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[4]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, -skybox_size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(skybox_size, skybox_size, -skybox_size);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(skybox_size, skybox_size, skybox_size);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(skybox_size, -skybox_size, skybox_size);
//
//	glEnd();
//
//	// Left face
//	glBindTexture(GL_TEXTURE_2D, MyTextureObject[5]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, -skybox_size);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skybox_size, -skybox_size, skybox_size);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, skybox_size);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skybox_size, skybox_size, -skybox_size);
//	glEnd();
//
//
//	glEnable(GL_DEPTH_TEST);
//	glutSwapBuffers();
//}
//
//void MyTimer(int Value) {
//	//glRotatef(xrot, 1.0f, 0.0f, 0.0f);
//	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
//	//glRotatef(zrot, 0.0f, 0.0f, 1.0f);
//	glutPostRedisplay();
//	glutTimerFunc(50, MyTimer, 1);
//}
//
//AUX_RGBImageRec* LoadBMP(const char* szFilename) {
//	FILE* pFile = NULL;
//	if (!szFilename) {
//		return NULL;
//	}
//
//	pFile = fopen(szFilename, "r");
//	if (pFile) {
//		fclose(pFile);
//		return auxDIBImageLoad(szFilename);     //파일로부터 메모리로
//	}
//	return NULL;
//}
//
//bool LoadTextureFromFile(const char* filePath, GLuint* texture, int number) {
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
//	if (data) {
//		glGenTextures(1, texture + number);
//		glBindTexture(GL_TEXTURE_2D, *(texture + number));
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		stbi_image_free(data);
//		return true;
//	}
//	else {
//		std::cerr << "Failed to load texture: " << filePath << std::endl;
//		stbi_image_free(data);
//		return false;
//	}
//}
//
//void main(int argc, char** argv) {
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Skybox Cube Example");
//
//	glutDisplayFunc(MyDisplay);
//	glutReshapeFunc(MyReshape);
//	glutTimerFunc(500, MyTimer, 1);
//
//	glDisable(GL_DEPTH_TEST);
//	if (LoadTextureFromFile("snow_terrian/front.bmp", MyTextureObject, 0) &&
//		LoadTextureFromFile("snow_terrian/back.bmp", MyTextureObject, 1) &&
//		LoadTextureFromFile("snow_terrian/top.bmp", MyTextureObject, 2) &&
//		LoadTextureFromFile("snow_terrian/bottom.bmp", MyTextureObject, 3) &&
//		LoadTextureFromFile("snow_terrian/right.bmp", MyTextureObject, 4) &&
//		LoadTextureFromFile("snow_terrian/left.bmp", MyTextureObject, 5)
//		) {
//
//		glEnable(GL_TEXTURE_2D);
//		glShadeModel(GL_SMOOTH);
//		glClearDepth(1.0);
//
//		glDepthFunc(GL_LEQUAL);
//		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//		glutMainLoop();
//	}
//
//
//}
