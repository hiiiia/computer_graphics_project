

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <GLAUX/glaux.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Camera2.h"
#include "Sea.h"
#include "LoadObj.h"
#include <time.h>

#include "skybox.h"
#include "LoadTex.h"
#include "night_sphere.h"
camera myCamera;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;

static int SpinAngle = 0;

LoadTex loadTex;
Sea sea;



//OakCask oak3;
Skybox skybox;
Night_sphere night_sphere;

void InitLight() {
    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     //조명 특성
    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_position[] = { 1.0, 1.0, 5.0, 1.0 };

    glShadeModel(GL_SMOOTH); //구로 셰이딩
    glEnable(GL_DEPTH_TEST); //깊이 버퍼 활성화
    glEnable(GL_LIGHTING); //조명 활성화
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); //주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); //확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    /// <summary>
    /// 
    /// </summary>
}

void MyDisplay() {

    

    //재질 설정
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

    //Rotate camera
    float x_move = -30.f * (currentMouse[0] - preMouse[0]) / windowWidth;
    float y_move = -30.f * (currentMouse[1] - preMouse[1]) / windowHeight;

    myCamera.RotateCamera(myCamera.right, (float)y_move);
    myCamera.RotateCamera(myCamera.up, (float)x_move);
    preMouse = currentMouse;

    //get camera variables from camera class
    
    vec3 eye = myCamera.eye;
    vec3 at = myCamera.at;
    vec3 up = myCamera.up;

   

    //set projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 41.0);

    //set modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);


    GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///
    //put your code here
    glDisable(GL_LIGHTING);


    skybox.MakeSky(10);
    //night_sphere.Make_night_sky(1);
    /// skybox랑 night_spehre를 그리면 텍스쳐가 하나씩 밀림. 뭐가 문제인거지?
    glEnable(GL_LIGHTING); 

    GLfloat testlightPosition[] = { 0.f, 0.f, 5.f, 1.f};
    //glLightfv(GL_LIGHT0, GL_POSITION , testlightPosition);

    
    sea.Update(SpinAngle);

    //oak2.DrawObj(1.f, -1.f, 0.f);
    //oak3.DrawObj(-1.f, -1.f, 0.f);

    glutSwapBuffers();

}

void MyReshape(int w, int h) {
    windowHeight = h;
    windowWidth = w;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


void MyTimer(int Value) {
    SpinAngle = (SpinAngle + 3) % 360;
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        preMouse = vec2(X, Y);
        currentMouse = preMouse;
    }
}

void MyMouseMove(GLint X, GLint Y)
{
    currentMouse = vec2(X, Y);
    glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
    float scale = 0.1;
    switch (key) {
    case 'w':
        myCamera.MoveCamera(myCamera.forward * scale);
        break;
    case 's':
        myCamera.MoveCamera(myCamera.forward * -scale);
        break;
    case 'a':
        myCamera.MoveCamera(myCamera.right * -scale);
        break;
    case 'd':
        myCamera.MoveCamera(myCamera.right * scale);
        break;
    case 'q':
        myCamera.MoveCamera(myCamera.up * scale);
        break;
    case 'z':
        myCamera.MoveCamera(myCamera.up * -scale);
        break;

    default:
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("openGL Sample Drawing");

    //Init camera
    vec3 eye(0, 1, 0);
    vec3 at(0, 3, 0);
    vec3 up(0, 0, 1);
    up = normalize(up);
    myCamera.InitCamera(eye, at, up);

    srand((unsigned int)time(NULL));
    
    loadTex.init();
    skybox.init();
    sea.init();
    
    //night_sphere.init();

    

    InitLight();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutMainLoop();
    return 0;
}
