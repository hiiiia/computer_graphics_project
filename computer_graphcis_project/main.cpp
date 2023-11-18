#include <gl/glew.h>
#include <gl/freeglut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}