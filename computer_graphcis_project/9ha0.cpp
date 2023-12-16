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


//obj 파일 받아오기 
std::vector < glm::vec3 > vertices;
std::vector < glm::ivec3 > faces;
std::vector < glm::vec2 > uvs;
std::vector < glm::vec3 > normals;

camera myCamera;

//3D 골렘 obj load
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
    //moving을 넣어서 골룸 위치 변경
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
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);//제자리 회전 //각도라고 생각하면 될듯
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
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

    switch (key) { //오브젝트 위치 이동
    case 'w': // 위로 이동
        translate_obj += forward * g_fCameraSpeed;
        at_ -= forward;
        break;
    case 's': // 아래로 이동
        translate_obj -= forward * g_fCameraSpeed;
        at_ += forward;

        break;
    case 'a': // 왼쪽으로 이동
        translate_obj -= right * g_fCameraSpeed;
        at_ += right;

        break;
    case 'd': // 오른쪽으로 이동
        translate_obj += right * g_fCameraSpeed;
        at_ -= right;

        break;
    case 't': // 카메라 시점 변경
        if (!viewport) {//분할중에는 시점변경 안되게 하기
            moveCamera = !moveCamera;
        }
        break;
    case 'm':
        // 추가된 코드: 키 'm'을 누를 때마다 큰 화면과 작은 화면을 전환
        viewport = !viewport;
        break;
    }


    // 회전된 이동 벡터를 구해서 오브젝트를 이동시킴
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f));
    translate_obj = glm::vec3(rotationMatrix * glm::vec4(translate_obj, 0.0f));
    moving += translate_obj;

    glutPostRedisplay();
}

void modelmove() {
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // 회전 각도 적용

    //draw solar system
    glColor3f(0.5, 0.6, 0.7);
    glPushMatrix();
    glTranslatef(moving.x, moving.y, moving.z); // head
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f); //이거를 하면 오브젝트만 회전
    DrawWireSurface(vertices, faces);
    glPushMatrix();
    glTranslatef(0, 8.7, 1.1); //머리 자리
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

        // 전체 창에 그릴 내용 (큐브 등)
        glPushMatrix();
        gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glColor3f(0.7, 0.7, 0.7);
        glutWireCube(1.0);
        glPopMatrix();

        glViewport(Width - Width / 2, 0, Width / 2, Height / 2);
        //골렘 따라가게 하기
        if (moveCamera) {
            at = myCamera.at - moving;
            gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
                at[0], at[1], at[2],
                up[0], up[1], up[2]);
            //glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // 회전 각도 적용
            glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
        }

        else {//3인칭 시점
            gluLookAt(eye[0] - moving.x, eye[1] + 11.0f - moving.y, eye[2] - moving.z,
                at[0], at[1], at[2], up[0], up[1], up[2]);
            modelmove();

        }
    }

    //골렘 따라가게 하기
    if (moveCamera && !viewport) { //일인칭
        vec3 at = myCamera.at;
        glViewport(0, 0, Width, Height);

        gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
            at_[0] + cubeWorldPosition.x, at_[1] + cubeWorldPosition.y, at_[2] + cubeWorldPosition.z,
            up[0], up[1], up[2]);


        glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // 회전 각도 적용
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

    //마우스 클릭할 때만 회전하도록 bool 값 넣기
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