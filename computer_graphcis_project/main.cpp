

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
#include <time.h>

#include "skybox.h"
#include "night_sphere.h"
camera myCamera;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;

static int SpinAngle = 0;

Sea sea;
Skybox skybox;
Night_sphere night_sphere;

void InitLight() {
    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     //���� Ư��
    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glShadeModel(GL_SMOOTH); //���� ���̵�
    glEnable(GL_DEPTH_TEST); //���� ���� Ȱ��ȭ
    glEnable(GL_LIGHTING); //���� Ȱ��ȭ
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); //�ֺ��� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); //Ȯ�걤 ����
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    /// <summary>
    /// 
    /// </summary>
}

void MyDisplay() {

    

    //���� ����
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
    /// skybox�� night_spehre�� �׸��� �ؽ��İ� �ϳ��� �и�. ���� �����ΰ���?
    glEnable(GL_LIGHTING); 
    sea.DrawSea(100, SpinAngle);

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

    
    sea.init();
    skybox.init();
    night_sphere.init();

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



/////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h> 
#include <iostream>
#include "Camera.h"
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>


using namespace std;
using namespace glm;

//static int Day = 0, Time = 0;

int windowHeight, windowWidth;
vec2 preMouse, currentMouse;
vec3 moving(0.0f, 0.0f, 0.0f);
glm::vec3 cubeWorldPosition(0.0f);

float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;

float g_fDistance = -50.5f;
float g_fCameraX = 0.0f;
float g_fCameraY = 0.0f;
float g_fCameraSpeed = 1.0f;

bool moveCamera = false;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

int Width, Height;
bool viewport = false;


//obj ���� �޾ƿ��� 
std::vector < glm::vec3 > vertices;
std::vector < glm::ivec3 > faces;
std::vector < glm::vec2 > uvs;
std::vector < glm::vec3 > normals;

camera myCamera;

//3D �� obj load
bool LoadObj(const char* path,
    std::vector < glm::vec3 >& out_vertices,
    std::vector < glm::ivec3 >& out_faces,
    std::vector < glm::vec2 >& out_uvs,
    std::vector < glm::vec3 >& out_normals)
{
    //init variables
    out_vertices.clear();
    out_faces.clear();
    out_uvs.clear();
    out_normals.clear();

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == -1)
            break;

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            out_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f %f\n", &uv.x, &uv.y);
            out_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            out_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matchs = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            out_faces.push_back(glm::ivec3(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1));

        }
    }

}


void DrawWireSurface(std::vector < glm::vec3 >& vectices,
    std::vector < glm::ivec3 >& faces)
{
    //moving�� �־ ��� ��ġ ����
    for (int i = 0; i < faces.size(); i++) {

        glColor3f(0.5, 0.6, 0.7);

        glBegin(GL_LINES);

        glVertex3f(vectices[faces[i].x].x, vectices[faces[i].x].y, vectices[faces[i].x].z);
        glVertex3f(vectices[faces[i].y].x, vectices[faces[i].y].y, vectices[faces[i].y].z);

        glVertex3f(vectices[faces[i].y].x, vectices[faces[i].y].y, vectices[faces[i].y].z);
        glVertex3f(vectices[faces[i].z].x, vectices[faces[i].z].y, vectices[faces[i].z].z);

        glVertex3f(vectices[faces[i].z].x, vectices[faces[i].z].y, vectices[faces[i].z].z);
        glVertex3f(vectices[faces[i].x].x, vectices[faces[i].x].y, vectices[faces[i].x].z);
        glEnd();
    }
}



void MyMouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            ptLastMousePosit.x = ptCurrentMousePosit.x = x;
            ptLastMousePosit.y = ptCurrentMousePosit.y = y;
            bMousing = true;
        }
        else
            bMousing = false;
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void MyMotion(int x, int y) {
    ptCurrentMousePosit.x = x;
    ptCurrentMousePosit.y = y;

    if (bMousing)
    {
        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);//���ڸ� ȸ�� //������� �����ϸ� �ɵ�
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST); // ���̹���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
}



void CalculateAndPrintCubeWorldCoordinates() {
    glm::vec3 cubeLocalPosition = glm::vec3(0, 8.7, 1.1);
    glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), moving) *
        glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0f), cubeLocalPosition);

    cubeWorldPosition = glm::vec3(cubeModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    std::cout << "Cube World Coordinates: (" << cubeWorldPosition.x << ", " << cubeWorldPosition.y << ", " << cubeWorldPosition.z << ")" << std::endl;
}

vec3 at_(0, 0, 0);
void MyKeyboard(unsigned char key, int x, int y) {
    glm::vec3 right = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 translate_obj = glm::vec3(0.0f);

    switch (key) { //������Ʈ ��ġ �̵�
    case 'w': // ���� �̵�
        translate_obj += forward * g_fCameraSpeed;
        at_ -= forward;
        break;
    case 's': // �Ʒ��� �̵�
        translate_obj -= forward * g_fCameraSpeed;
        at_ += forward;

        break;
    case 'a': // �������� �̵�
        translate_obj -= right * g_fCameraSpeed;
        at_ += right;

        break;
    case 'd': // ���������� �̵�
        translate_obj += right * g_fCameraSpeed;
        at_ -= right;

        break;
    case 't': // ī�޶� ���� ����
        if (!viewport) {//�����߿��� �������� �ȵǰ� �ϱ�
            moveCamera = !moveCamera;
        }
        break;
    case 'm':
        // �߰��� �ڵ�: Ű 'm'�� ���� ������ ū ȭ��� ���� ȭ���� ��ȯ
        viewport = !viewport;
        break;
    }


    // ȸ���� �̵� ���͸� ���ؼ� ������Ʈ�� �̵���Ŵ
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f));
    translate_obj = glm::vec3(rotationMatrix * glm::vec4(translate_obj, 0.0f));
    moving += translate_obj;

    glutPostRedisplay();
}

void modelmove() {
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // ȸ�� ���� ����

    //draw solar system
    glColor3f(0.5, 0.6, 0.7);
    glPushMatrix();
    glTranslatef(moving.x, moving.y, moving.z); // head
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f); //�̰Ÿ� �ϸ� ������Ʈ�� ȸ��
    DrawWireSurface(vertices, faces);
    glPushMatrix();
    glTranslatef(0, 8.7, 1.1); //�Ӹ� �ڸ�
    //glutWireCube(2.0);
    glPopMatrix();
    glPopMatrix();
}

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set projection;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)800 / (GLfloat)600, 1.0, 100.0);


    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(20.0, 0.0, 20.0);
    glVertex3f(20.0, 0.0, -20.0);
    glVertex3f(-20.0, 0.0, -20.0);
    glVertex3f(-20.0, 0.0, 20.0);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0); //test
    glColor3f(1.0, 0.3, 0.3);
    glutSolidCube(5.0);
    glPopMatrix();

    //Draw Scene
   //get camera variables from camera class
    vec3 eye = myCamera.eye;
    vec3 at = myCamera.at - moving;
    vec3 up = myCamera.up;

    glMatrixMode(GL_MODELVIEW); //set matrix mode
    glLoadIdentity(); //set Identity 

    if (viewport) {
        glViewport(0, 0, Width, Height);

        // ��ü â�� �׸� ���� (ť�� ��)
        glPushMatrix();
        gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glColor3f(0.7, 0.7, 0.7);
        glutWireCube(1.0);
        glPopMatrix();

        glViewport(Width - Width / 2, 0, Width / 2, Height / 2);
        //�� ���󰡰� �ϱ�
        if (moveCamera) {
            at = myCamera.at - moving;
            gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
                at[0], at[1], at[2],
                up[0], up[1], up[2]);
            //glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // ȸ�� ���� ����
            glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
        }

        else {//3��Ī ����
            gluLookAt(eye[0] - moving.x, eye[1] + 11.0f - moving.y, eye[2] - moving.z,
                at[0], at[1], at[2], up[0], up[1], up[2]);
            modelmove();

        }
    }

    //�� ���󰡰� �ϱ�
    if (moveCamera && !viewport) { //����Ī
        vec3 at = myCamera.at;
        glViewport(0, 0, Width, Height);

        gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
            at_[0] + cubeWorldPosition.x, at_[1] + cubeWorldPosition.y, at_[2] + cubeWorldPosition.z,
            up[0], up[1], up[2]);


        glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // ȸ�� ���� ����
        glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
    }

    else if (!viewport) {
        glViewport(0, 0, Width, Height);

        gluLookAt(eye[0] - moving.x, eye[1] + 11.0f - moving.y, eye[2] - moving.z,
            at[0], at[1], at[2], up[0], up[1], up[2]);
        modelmove();
    }

    CalculateAndPrintCubeWorldCoordinates();

    //Send it to buffer
    glutSwapBuffers();

}


void MyReshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;

    //Set viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


void MyTimer(int Value) {
    //Day = (Day + 2) % 360;
    //Time = (Time + 1) % 360;

    //���콺 Ŭ���� ���� ȸ���ϵ��� bool �� �ֱ�
    mat4 rot = rotate(mat4(1.f), radians(0.0f), vec3(0, 0, 1));

    vec3 rotatedDirec = rot * vec4((myCamera.eye - myCamera.at), 0);
    vec3 rotatedUp = rot * vec4(myCamera.up, 0);
    myCamera.eye = myCamera.at + rotatedDirec;
    myCamera.up = rotatedUp;
    myCamera.UpdateCamera();
    glutPostRedisplay();
    //glutTimerFunc(40, MyTimer, 1);
}


void main(int argc, char** argv) {
    Width = 800;
    Height = 600;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("stone_move");
    init();

    //get window variables
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    LoadObj("Data/stone/Stone.obj", vertices, faces, uvs, normals);

    //Init camera
    vec3 center(0, 0, 40);
    vec3 at(0, 0, 0);
    vec3 up = cross(vec3(1, 0, 0), at - center);
    up = normalize(up);
    myCamera.InitCamera(center, at, up);

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutMouseFunc(MyMouse);
    glutMotionFunc(MyMotion);
    //glutReshapeFunc(MyReshape);

    glutMainLoop();

}