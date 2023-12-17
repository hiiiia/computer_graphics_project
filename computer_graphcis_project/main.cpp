
#define _CRT_SECURE_NO_WARNINGS



#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <GLAUX/glaux.h>
#include <stdio.h> 
#include <iostream>


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

int sphere_num = 1500;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;

vec3 tmp_loc;

static int skybox_size = 20;
static float star_size = 0.05;
static int SpinAngle = 0;
static int weatherTime = 0;

static float Spin_sun_moon = 0;

static float Spin_star = 0;

static bool Ray_flag = false;


vec3 moving(0.0f, 0.0f, 0.0f);
glm::vec3 cubeWorldPosition(0.0f);

float g_fSpinX = 0.0f;
float g_fSpinY = 0.0f;

float g_fDistance = -50.5f;
float g_fCameraX = 0.0f;
float g_fCameraY = 0.0f;
float g_fCameraSpeed = 0.1f;



vec3 at_(0, 0, 0);



vec3 gol_position;
vec3 gol_forward;

bool moveCamera = false;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

int Width, Height;
bool viewport = false;


std::vector < glm::vec3 > vertices;
std::vector < glm::ivec3 > faces;
std::vector < glm::vec2 > uvs;
std::vector < glm::vec3 > normals;



LoadTex loadTex;
Sea sea;
camera myCamera;


Skybox skybox;
Night_sphere night_sphere;

using namespace std;
using namespace glm;








void initLight() {
    glEnable(GL_LIGHTING);  // 조명 활성화

    // 광원 활성화
    glEnable(GL_LIGHT0);

    // 광원 위치 설정
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };  // (x, y, z, w) - w는 광원이 방향 광원인지 위치 광원인지를 나타냄

    // 광원 색상 설정
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    // 광원 설정 적용
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    glDisable(GL_LIGHT0);

    glEnable(GL_LIGHT1);


    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    glDisable(GL_LIGHT1);


    glEnable(GL_LIGHT2);


    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

    glDisable(GL_LIGHT2);

    // 재질 설정 활성화
    //GL_COLOR_MATERIAL을 활성화하면 glColor 명령어로 설정한 색상이 물체의 재질에 적용
    //glEnable(GL_COLOR_MATERIAL);
}


void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST); // 깊이버퍼
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_FRONT);
}


struct SphereInfo {
    float x, y, z;  // 위치
    float r, g, b, a;  // 색상 및 투명도
};

std::vector<SphereInfo> spheres;

void initSpheres(int numSpheres) {
    spheres.clear();  // 벡터 초기화

    for (int i = 0; i < numSpheres; ++i) {
        SphereInfo sphere;
        float innerRadius = skybox_size * 4;
        float outerRadius = skybox_size * 4 + 5;

        sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;

        while (sqrt(sphere.x * sphere.x + sphere.y * sphere.y + sphere.z * sphere.z) < innerRadius) {
            // 반지름이 innerRadius 이상인지 확인하고, 아니면 다시 무작위 좌표 생성
            sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        }

        sphere.r = static_cast<float>(rand()) / RAND_MAX;
        sphere.g = static_cast<float>(rand()) / RAND_MAX;
        sphere.b = static_cast<float>(rand()) / RAND_MAX;
        sphere.a = 1;

        spheres.push_back(sphere);  // 벡터에 추가
    }
}


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


GLfloat sun_mat_amb[] = { 0.2, 0 , 0, 1.0 };
GLfloat sun_mat_diffuse[] = { 1, 0.5, 0.5, 1.0 };
GLfloat sun_mat_specular[] = { 0, 0, 0, 1 };
GLfloat sun_mat_emission[] = { 0.3, 0.1, 0.1, 0.0 };


GLfloat sea_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat sea_mat_diff[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat sea_mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };
GLfloat sea_mat_shininess[] = { 50.0 };
GLfloat seaLightpos[] = { 1,1,1,1 };


void drawSpheres() {

    glPushMatrix();

    glTranslated(0, 0, -skybox_size*2-1);
    glRotatef(Spin_star, 0.0, 1.0, 0.0);

    int count = 0;
    for (const auto& sphere : spheres) {
        count += 1;
        //glColor4f(sphere.r, sphere.g, sphere.b, sphere.a);  // 투명도 적용


        if (tmp_loc.x == sphere.x && tmp_loc.y == sphere.y && tmp_loc.z == sphere.z) {
            //printf_s("%d", count);
        }

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);


        glPushMatrix();
        glTranslatef(sphere.x, sphere.y, sphere.z);
        glutSolidSphere(star_size, 20, 20);
        glPopMatrix();
    }

    glPopMatrix();
    glColor4f(1, 1, 1, 1);

}



void draw_with_Texture2(float radius, int slices) {


    GLUquadric* obj = gluNewQuadric();
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricNormals(obj, GLU_SMOOTH);
    gluSphere(obj, radius, slices, slices);
    gluDeleteQuadric(obj);

}


void draw_sun_moon() {
    glPushMatrix();

    GLfloat sub_ligth_pos[] = { skybox_size * 3, 0.0 ,-skybox_size ,1 };
    GLfloat moon_ligth_pos[] = { -skybox_size * 3, 0.0 ,-skybox_size ,1 };
    GLfloat radius = skybox_size * 3;
    float planets_rad = 1;
    glTranslated(0, 0, -22);


    glEnable(GL_TEXTURE_2D);

    glRotatef(Spin_sun_moon, 0, 1, 0);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[23]);

    glTranslated(radius, 0, 0);

    draw_with_Texture2(planets_rad, 100);

    glLightfv(GL_LIGHT1, GL_POSITION, sub_ligth_pos);
    glEnable(GL_LIGHT1);


    glPopMatrix();




    glPushMatrix();


    glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[24]);


    glTranslated(-radius, 0, 0);

    draw_with_Texture2(planets_rad, 100);



    glLightfv(GL_LIGHT2, GL_POSITION, moon_ligth_pos);
    glEnable(GL_LIGHT2);




    glPopMatrix();


    glPopMatrix();


    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

};


bool rayBoxIntersection(const vec3& origin, const vec3& direction, const vec3& boxMin, const vec3& boxMax, float& tMin, float& tMax) {
    vec3 invDirection = 1.0f / direction;

    float t1 = (boxMin.x - origin.x) * invDirection.x;
    float t2 = (boxMax.x - origin.x) * invDirection.x;
    float t3 = (boxMin.y - origin.y) * invDirection.y;
    float t4 = (boxMax.y - origin.y) * invDirection.y;
    float t5 = (boxMin.z - origin.z) * invDirection.z;
    float t6 = (boxMax.z - origin.z) * invDirection.z;

    tMin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    tMax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    return tMax >= tMin && tMax >= 0;
}



void drawRay() {

    vec3 eye = myCamera.eye;
    vec3 direction = normalize(myCamera.eye - myCamera.at);

    // Skybox의 경계 상자 (예: -40, -40, -40에서 40, 40, 40)
    //vec3 boxMin(-skybox_size * 4, -skybox_size * 4, -skybox_size * 4);
    //vec3 boxMax(skybox_size * 4, skybox_size * 4, skybox_size * 4);

    vec3 boxMin(-skybox_size * 2, -skybox_size * 2, -skybox_size * 2);
    vec3 boxMax(skybox_size * 2, skybox_size * 2, skybox_size * 2);



    // 레이 시각화 및 정보 출력

    if (Ray_flag) {

        float tMin, tMax;
        bool hit = rayBoxIntersection(eye, direction, boxMin, boxMax, tMin, tMax);

        if (hit) {

            printf_s("Hit\n");
            // 충돌 지점 계산
            tmp_loc = eye + tMin * direction;

            glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslatef(tmp_loc.x, tmp_loc.y, tmp_loc.z);


            SphereInfo sphere;

            sphere.x = tmp_loc.x;
            sphere.y = tmp_loc.y;
            sphere.z = tmp_loc.z;

            sphere.r = 1;
            sphere.g = 1;
            sphere.b = 1;
            sphere.a = 1;

            spheres.push_back(sphere);

            glColor3f(1.0, 0, 0);
            glutSolidCube(0.5);
            glColor3f(1.0, 1.0, 1.0);

            glPopMatrix();

            printf_s("Sphere size: %d \n", spheres.size());
            printf_s("Eye: (%.2f, %.2f, %.2f)\n", eye.x, eye.y, eye.z);
            printf_s("At: (%.2f, %.2f, %.2f)\n", direction.x, direction.y, direction.z);
            printf_s("Ray: (%.2f, %.2f, %.2f)\n", tmp_loc.x, tmp_loc.y, tmp_loc.z);

            Ray_flag = false;

        }


    }

    else {
        glPushMatrix();


        glColor3f(1.0, 0, 0.0);

        glTranslatef(tmp_loc.x, tmp_loc.y, tmp_loc.z);

        glutSolidCube(0.5);


        glColor3f(1.0, 1.0, 1.0);


        glPopMatrix();

    }

}




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


//
//void CalculateAndPrintCubeWorldCoordinates() {
//    glm::vec3 cubeLocalPosition = glm::vec3(0, 8.7, 1.1);
//    glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), moving) *
//        glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f)) *
//        glm::translate(glm::mat4(1.0f), cubeLocalPosition);
//
//    cubeWorldPosition = glm::vec3(cubeModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//    //std::cout << "Cube World Coordinates: (" << cubeWorldPosition.x << ", " << cubeWorldPosition.y << ", " << cubeWorldPosition.z << ")" << std::endl;
//}



struct Star {
    float x, y, z;   // 현재 위치
    float destX, destZ;  // 목적지 위치
    float size;      // 크기
};

std::vector<Star> stars;  // 별들의 목록

void drawStar(float x, float y, float z, float size) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[25]);

    draw_with_Texture2(size, 100);
    glPopMatrix();
}


void moveStars() {
    // 이동 속도 및 방향 설정 (예: 일정한 속도로 이동)
    float speed = 0.1;

    for (auto& star : stars) {
        float deltaX = (star.destX - star.x) * speed;
        float deltaZ = (star.destZ - star.z) * speed;

        // 현재 위치 및 크기 업데이트
        star.x += deltaX;
        star.z += deltaZ;
        star.size *= 0.8;  // 크기를 줄여나감
    }
}



void MyDisplay() {





    GLfloat sea_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat sea_mat_diff[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat sea_mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat sea_mat_shininess[] = { 50.0 };
    GLfloat seaLightpos[] = { 1,1,1,1 };

    float x_move = -30.f * (currentMouse[0] - preMouse[0]) / windowWidth;
    float y_move = -30.f * (currentMouse[1] - preMouse[1]) / windowHeight;

    myCamera.RotateCamera(myCamera.right, (float)y_move);
    myCamera.RotateCamera(myCamera.up, (float)x_move);
    preMouse = currentMouse;


    vec3 eye = myCamera.eye;
    vec3 at = myCamera.at;
    vec3 up = myCamera.up;




    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();





    gluPerspective(40.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0,50);

    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




    glDisable(GL_LIGHTING);

    glClear(GL_COLOR_BUFFER_BIT);



    skybox.MakeSky(skybox_size);


    glPushMatrix();


        glScaled(0.1, 0.1, 0.1);

        glRotated(180, 0, 1, 0);
        glRotated(-90, 1, 0, 0);

        glTranslatef(moving.x, moving.z, moving.y);
        glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f); 

        //printf_s("%f /%f / %f\n", moving.x, moving.y, moving.z);

        DrawWireSurface(vertices, faces);
        glutSolidSphere(0.5, 100, 100);


    glPopMatrix();


    sea.Update(SpinAngle, myCamera.eye, myCamera.at);


    glPushMatrix();

    for (const auto& star : stars) {
        drawStar(star.x, star.y, star.z, star.size);
    }
    glPopMatrix();




    drawRay();

    draw_sun_moon();


    drawSpheres();

    


    glPopMatrix();



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
    Spin_star = (Spin_star + 0.05);
    Spin_sun_moon = (Spin_sun_moon + 0.01);
    glutPostRedisplay();
    glutTimerFunc(10, MyTimer, 1);
}

void MyTimer2(int Value) {
    weatherTime += 1;

    if (weatherTime >= 10) {
        weatherTime = 0;
        cout << " �뼮�� ���� ���� : �ı� �ϵ� " << endl;
        Weather::ChangeWeather();
    }

    cout << weatherTime << endl;
    glutPostRedisplay();
    glutTimerFunc(1000, MyTimer2, 1);
}



void MyTimer3(int value) {
    // 별똥별을 생성
    Star newStar;
    newStar.x = static_cast<float>(rand()) / RAND_MAX * 40.0 - 20.0;
    newStar.y = 20.0;
    newStar.z = 20.0;
    newStar.size = star_size * 3;
    newStar.destX = static_cast<float>(rand()) / RAND_MAX * 40.0 - 20.0;
    newStar.destZ = 10.0;
    stars.push_back(newStar);

    // 다음 생성 타이밍을 10초 후로 설정
    glutTimerFunc(10000, MyTimer3, 0);
}

void MyTimer4(int value) {
    moveStars();
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer4, 0);

    auto it = std::remove_if(stars.begin(), stars.end(), [](const Star& star) {
        return fabs(star.x - star.destX) < 0.1 && fabs(star.z - star.destZ) < 0.1;
        });

    stars.erase(it, stars.end());
}


void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        preMouse = vec2(X, Y);


        currentMouse = preMouse;



        ptLastMousePosit.x = ptCurrentMousePosit.x = X;
        ptLastMousePosit.y = ptCurrentMousePosit.y = Y;
        bMousing = true;


    }

    else if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {

        bMousing = false;
    }


    if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {
        Ray_flag = true;
    }




}

void MyMouseMove(GLint X, GLint Y)
{

    currentMouse = vec2(X, Y);


    ptCurrentMousePosit.x = X;
    ptCurrentMousePosit.y = Y;

    if (bMousing)
    {
        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);//제자리 회전 //각도라고 생각하면 될듯
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;


    glutPostRedisplay();
}


void MyKeyboard(unsigned char key, int x, int y) {
    float scale = 0.1;


    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 translate_obj = glm::vec3(0.0f);


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

    case '8':
        translate_obj += forward * g_fCameraSpeed;
        break;
    case '5':
        translate_obj -= forward * g_fCameraSpeed;
        break;
    case '4':
        translate_obj += right * g_fCameraSpeed;
        break;
    case '6':
        translate_obj -= right * g_fCameraSpeed;
        break;

    default:
        break;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(g_fSpinX), glm::vec3(0.0f, 0.0f, 1.0f));
    translate_obj = glm::vec3(rotationMatrix * glm::vec4(translate_obj, 0.0f));
    moving += translate_obj;
    /// //////////////////////////////////////////////////////////////////////////////


    glutPostRedisplay();
}






int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1300, 1300);
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
    sea.init();
    skybox.init();
    loadTex.init();

    // 구체 초기화
    initSpheres(sphere_num);  // 10개의 구체를 초기화합니다.

    LoadObj("Data/stone/Stone.obj", vertices, faces, uvs, normals);
    //night_sphere.init();


    initLight();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutTimerFunc(1000, MyTimer2, 1);

    MyTimer3(0);
    glutTimerFunc(40, MyTimer4, 0);

    glutMainLoop();
    return 0;
}