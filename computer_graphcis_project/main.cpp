//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//
//static int SpinAngle = 0;
//
//void InitLight() {
//    GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };     //조명 특성
//    GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
//    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//
//    GLfloat material_ambient[] = { 0.4, 0.4, 0.4, 1.0 };  //물체 특성
//    GLfloat material_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
//    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat material_shininess[] = { 25.0 };
//
//    glShadeModel(GL_SMOOTH);    //구로 셰이딩
//    glEnable(GL_DEPTH_TEST);    //깊이 버퍼 활성화
//    glEnable(GL_LIGHTING);      //조명 활성화
//    glEnable(GL_LIGHT0);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
//}
//
//void MyDisplay() {
//    GLfloat LightPosition[] = { 0.0, 0.0, 1.5, 1.0 };
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glPushMatrix();
//    glTranslatef(0.0, 0.0, -5.0);
//    glPushMatrix();
//    glRotatef(SpinAngle, 1.0, 0.0, 0.0);
//    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
//    glTranslatef(0.0, 0.0, 1.5);
//    glDisable(GL_LIGHTING);
//    glColor3f(0.9, 0.9, 0.9);
//    glutWireSphere(0.06, 10, 10);
//    glEnable(GL_LIGHTING);
//    glPopMatrix();
//    glutSolidSphere(1.0, 400, 400);
//    glPopMatrix();
//    glFlush();
//}
//
//void MyReshape(int w, int h) {
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//void MyMouse(int button, int state, int x, int y) {
//    switch (button) {
//    case GLUT_LEFT_BUTTON:
//        if (state == GLUT_DOWN) {
//            SpinAngle = (SpinAngle + 15) % 360;
//            glutPostRedisplay();
//        }
//        break;
//    default:
//        break;
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("openGL Sample Drawing");
//    InitLight();
//    glutDisplayFunc(MyDisplay);
//    glutReshapeFunc(MyReshape);
//    glutMouseFunc(MyMouse);
//    glutMainLoop();
//    return 0;
//}

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define GLEW_STATIC
#include <GL/glew.h>


#define WIDTH   4
#define HEIGHT  4

GLubyte MyTexture[WIDTH][HEIGHT][3];

void FillMyTexture() {
    int s, t;
    for (s = 0; s < WIDTH; s++) {
        for (t = 0; t < HEIGHT; t++) {
            GLubyte Intensity = ((s + t) % 2) * 255;    //0는 흑색, 255는 백색
            MyTexture[s][t][0] = Intensity;             //Red 값에 할당
            MyTexture[s][t][1] = Intensity;             //Green 값에 할당
            MyTexture[s][t][2] = Intensity;             //Blue 값에 할당
        }
    }
}

void MyInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    FillMyTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, WIDTH, HEIGHT, 0, GL_RGB,
        GL_UNSIGNED_BYTE, &MyTexture[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 3.0); glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(3.0, 3.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(3.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("openGL Sample Program");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
