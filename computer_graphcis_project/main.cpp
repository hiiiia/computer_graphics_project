
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <glad/glad.h>

#include <vector>


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <iostream>
using namespace glm;
using namespace std;

# define M_PI 3.14159265358979323846 /* pi */

//define camera class
class camera {

public:
    //variables for opengl
    vec3 eye; //center position
    vec3 at; //point where this camera is pointing out
    vec3 up; // up direction (normalized)

    //other variables
    vec3 forward; //vector pointing forward direction
    float distance = 1; //distance from eye to at
    vec3 right; //vector indicating right direction from the point of camera

    void InitCamera(vec3 _center, vec3 _at, vec3 _up)
    {
        //set three variables and update others
        eye = _center;
        at = _at;
        up = _up;
        UpdateCamera();
    }

    void MoveCamera(vec3 move)
    {
        eye += move;
        at += move;
    }

    void RotateCamera(vec3 axis, float angle)
    {
        //rotate direc and up vector
        vec4 tempForward = vec4(forward, 0);
        vec4 tempUp = vec4(up, 0);
        mat4 rot = rotate(mat4(1), radians(angle), axis);
        forward = rot * tempForward;
        up = rot * tempUp;

        //update at vector accordingly
        at = eye + forward * distance;

        UpdateCamera();
    }

    //update variables accordingly
    void UpdateCamera()
    {
        up = normalize(up);
        distance = length(at - eye);
        forward = normalize(at - eye);
        right = normalize(cross(forward, up));
    }
};

camera myCamera;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;

static int SpinAngle = 0;
static int Ground_spin = 0;

GLuint textures[6];

void InitLight() {
    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     //조명 특성
    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    /// <summary>
    /// 
    glShadeModel(GL_SMOOTH);//구로 셰이딩
    //glShadeModel(GL_FLAT); // 삼각형 셰이딩
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);


    /// </summary>
}

//void loadTexture(const char* filename, GLuint textureID) {
//    int width, height, channels;
//    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb);
//
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//
//    stbi_image_free(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//
//void skybox_init() {
//    glEnable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//    glGenTextures(6, textures);
//
//    // Load textures for each face (front, back, left, right, top, bottom)
//    loadTexture("./skybox/front.jpg", textures[0]);
//    loadTexture("./skybox/back.jpg", textures[1]);
//    loadTexture("./skybox/left.jpg", textures[2]);
//    loadTexture("./skybox/right.jpg", textures[3]);
//    loadTexture("./skybox/top.jpg", textures[4]);
//    loadTexture("./skybox/bottom.jpg", textures[5]);
//
//    // Set texture coordinates for each face (assuming you have a unit cube)
//}



void draw_cube(float cubeSize) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mat_diffuse[3] = 0.5;  // 알파 값을 0.5로 설정 (반투명)

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };

    // 각 면의 재질 색상 배열
    GLfloat ambientColors[][4] = {
        {1.0f, 0.0f, 0.0f, 1.0f},  // Front face (Red)
        {0.0f, 1.0f, 0.0f, 1.0f},  // Back face (Green)
        {0.0f, 0.0f, 1.0f, 1.0f},  // Right face (Blue)
        {1.0f, 1.0f, 0.0f, 1.0f},  // Left face (Yellow)
        {0.0f, 1.0f, 1.0f, 1.0f},  // Top face (Cyan)
        {1.0f, 0.0f, 1.0f, 1.0f}   // Bottom face (Magenta)
    };


    for (int i = 0; i < 6; ++i) {

        // 재질 설정
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColors[i]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

        glBegin(GL_QUADS);
        switch (i)
        {
        //case(0):    
        //    //Front 
        //    
        //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
        //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
        //    break;
        //case(1):
        //    //Back

        //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
        //    break;
        //case(2):
        //    //Right 

        //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
        //    break;
        //case(3):
        //    //Left  

        //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
        //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
        //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
        //    break;
        case(4):
            //Top  

            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
            break;
        case(5):
            //Bottom  

            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
            break;
        }

        glEnd();

    }

    glDisable(GL_BLEND);
}

void drawSkybox(float size) {
    glPushMatrix();
    glScalef(size, size, size);

    // Draw the front face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Draw the back face
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Draw the left face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Draw the right face
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    // Draw the top face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Draw the bottom face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
}
void setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    // Calculate the parameters for glFrustum
    float top = nearPlane * tan(0.5f * M_PI / 180.0f * fov);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    // Set the projection matrix using glFrustum
    glFrustum(left, right, bottom, top, nearPlane, farPlane);
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
    // emission <<--- 발광체 구성



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


    ////
    setPerspective(40.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 20.0f);
    //gluPerspective(40.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 20.0);
    ////


    //set modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);


    GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///
    //put your code here

    glPushMatrix();


    glTranslatef(0.0, 0.0, -5.0);

    glRotatef(Ground_spin, 1.0, 0.0, 0.0);
    draw_cube(5);
    //drawSkybox(50.0);



    glPushMatrix();
    glRotatef(SpinAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 1.5);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glDisable(GL_LIGHTING);
    glColor3f(0.9, 0.9, 0.9);
    glutWireSphere(0.06, 10, 10);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    //glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, 100, 100);
    // 2,3번째 변수는 해상도. 낮을수록 삼각형이 잘보임
    glPopMatrix();
    glFlush();
    /// 



    glFlush();
}



void MyReshape(int w, int h) {
    windowHeight = h;
    windowWidth = w;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


void MyTimer(int Value) {
    SpinAngle = (SpinAngle + 10) % 360;
    Ground_spin = (Ground_spin + 1) % 360;
    printf_s("x:%f / y:%f / z:%f/ \n", myCamera.eye[0], myCamera.eye[1], myCamera.eye[2]);
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
    float scale = 0.5;
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

    //if (!glfwInit()) {
    //    // Handle initialization failure
    //    cout << "glfw Error";
    //    return -1;
    //}

    //// Create a GLFW window and context

    //// Initialize Glad
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 1200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("openGL Sample Drawing");

    //Init camera
    vec3 eye(8, 0, 10);
    vec3 at(0, 0, -5);
    vec3 up(1, 0, 0);
    up = normalize(up);
    myCamera.InitCamera(eye, at, up);

    InitLight();
    //skybox_init();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutMainLoop();
    return 0;
}













//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <glad/glad.h>
//
//#include <vector>
//
//
//#include <glm/glm.hpp> 
//#include <glm/gtc/matrix_transform.hpp> 
//#include <glm/gtc/type_ptr.hpp>
//
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <GLFW/glfw3.h>
//#include <iostream>
//# define M_PI 3.14159265358979323846 /* pi */
//
//using namespace glm;
//using namespace std;
//
//
//
////define camera class
//class camera {
//
//public:
//    //variables for opengl
//    vec3 eye; //center position
//    vec3 at; //point where this camera is pointing out
//    vec3 up; // up direction (normalized)
//
//    //other variables
//    vec3 forward; //vector pointing forward direction
//    float distance = 1; //distance from eye to at
//    vec3 right; //vector indicating right direction from the point of camera
//
//    void InitCamera(vec3 _center, vec3 _at, vec3 _up)
//    {
//        //set three variables and update others
//        eye = _center;
//        at = _at;
//        up = _up;
//        UpdateCamera();
//    }
//
//    void MoveCamera(vec3 move)
//    {
//        eye += move;
//        at += move;
//    }
//
//    void RotateCamera(vec3 axis, float angle)
//    {
//        //rotate direc and up vector
//        vec4 tempForward = vec4(forward, 0);
//        vec4 tempUp = vec4(up, 0);
//        mat4 rot = rotate(mat4(1), radians(angle), axis);
//        forward = rot * tempForward;
//        up = rot * tempUp;
//
//        //update at vector accordingly
//        at = eye + forward * distance;
//
//        UpdateCamera();
//    }
//
//    //update variables accordingly
//    void UpdateCamera()
//    {
//        up = normalize(up);
//        distance = length(at - eye);
//        forward = normalize(at - eye);
//        right = normalize(cross(forward, up));
//    }
//};
//
//camera myCamera;
//
//vec2 preMouse, currentMouse;
//int windowHeight, windowWidth;
//
//static int SpinAngle = 0;
//static int Ground_spin = 0;
//
//GLuint textures[6];
//
//void InitLight() {
//    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     //조명 특성
//    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
//    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//
//    /// <summary>
//    /// 
//    //glShadeModel(GL_SMOOTH);//구로 셰이딩
//    //glShadeModel(GL_FLAT); // 삼각형 셰이딩
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
//
//
//    /// </summary>
//}
//
//void loadTexture(const char* filename, GLuint textureID) {
//    int width, height, channels;
//    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb);
//
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//
//    stbi_image_free(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//
//void skybox_init() {
//    glEnable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//    glGenTextures(6, textures);
//
//    // Load textures for each face (front, back, left, right, top, bottom)
//    loadTexture("./skybox/front.jpg", textures[0]);
//    loadTexture("./skybox/back.jpg", textures[1]);
//    loadTexture("./skybox/left.jpg", textures[2]);
//    loadTexture("./skybox/right.jpg", textures[3]);
//    loadTexture("./skybox/top.jpg", textures[4]);
//    loadTexture("./skybox/bottom.jpg", textures[5]);
//
//    // Set texture coordinates for each face (assuming you have a unit cube)
//}
//
//
//
//void draw_cube(float cubeSize) {
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat high_shininess[] = { 100.0 };
//
//    // 각 면의 재질 색상 배열
//    GLfloat ambientColors[][4] = {
//        {1.0f, 0.0f, 0.0f, 1.0f},  // Front face (Red)
//        {0.0f, 1.0f, 0.0f, 1.0f},  // Back face (Green)
//        {0.0f, 0.0f, 1.0f, 1.0f},  // Right face (Blue)
//        {1.0f, 1.0f, 0.0f, 1.0f},  // Left face (Yellow)
//        {0.0f, 1.0f, 1.0f, 1.0f},  // Top face (Cyan)
//        {1.0f, 0.0f, 1.0f, 1.0f}   // Bottom face (Magenta)
//    };
//
//
//    for (int i = 0; i < 6; ++i) {
//
//        // 재질 설정
//        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColors[i]);
//        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
//
//        glBegin(GL_QUADS);
//        switch (i)
//        {
//        case(0):
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            break;
//        case(1):
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            break;
//        case(2):
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            break;
//        case(3):
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            break;
//        case(4):
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            break;
//        case(5):
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            break;
//        }
//
//        glEnd();
//
//    }
//}
//
//void drawSkybox(float size) {
//    glPushMatrix();
//    glScalef(size, size, size);
//
//    // Draw the front face
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
//    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
//    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
//    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
//    glEnd();
//
//    // Draw the back face
//    glBegin(GL_QUADS);
//    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
//    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
//    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, 0.5);
//    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, 0.5);
//    glEnd();
//
//    // Draw the left face
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
//    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, -0.5);
//    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
//    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
//    glEnd();
//
//    // Draw the right face
//    glBegin(GL_QUADS);
//    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
//    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
//    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, 0.5);
//    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
//    glEnd();
//
//    // Draw the top face
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
//    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, -0.5);
//    glTexCoord2f(1, 0); glVertex3f(0.5, 0.5, 0.5);
//    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, 0.5);
//    glEnd();
//
//    // Draw the bottom face
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
//    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
//    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, 0.5);
//    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
//    glEnd();
//
//    glPopMatrix();
//}
//void setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
//    // Calculate the parameters for glFrustum
//    float top = nearPlane * tan(0.5f * M_PI / 180.0f * fov);
//    float bottom = -top;
//    float right = top * aspect;
//    float left = -right;
//
//    // Set the projection matrix using glFrustum
//    glFrustum(left, right, bottom, top, nearPlane, farPlane);
//}
//void MyDisplay() {
//
//    //재질 설정
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
//    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
//    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat no_shininess[] = { 0.0 };
//    GLfloat low_shininess[] = { 5.0 };
//    GLfloat high_shininess[] = { 100.0 };
//    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
//    // emission <<--- 발광체 구성
//
//
//
//    //Rotate camera
//    float x_move = -30.f * (currentMouse[0] - preMouse[0]) / windowWidth;
//    float y_move = -30.f * (currentMouse[1] - preMouse[1]) / windowHeight;
//
//    myCamera.RotateCamera(myCamera.right, (float)y_move);
//    myCamera.RotateCamera(myCamera.up, (float)x_move);
//    preMouse = currentMouse;
//
//    //get camera variables from camera class
//    vec3 eye = myCamera.eye;
//    vec3 at = myCamera.at;
//    vec3 up = myCamera.up;
//
//    //set projection
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//
//    ////
//    setPerspective(40.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 20.0f);
//    //gluPerspective(40.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 20.0);
//    ////
//
//
//    //set modelview matrix
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
//
//
//    GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    ///
//    //put your code here
//
//    glPushMatrix();
//
//
//    glTranslatef(0.0, 0.0, -5.0);
//
//    glRotatef(Ground_spin, 1.0, 0.0, 0.0);
//    //draw_cube(5);
//    drawSkybox(50.0);
//
//
//
//    glPushMatrix();
//    glRotatef(SpinAngle, 1.0, 0.0, 0.0);
//    glTranslatef(0.0, 0.0, 1.5);
//    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
//    glDisable(GL_LIGHTING);
//    glColor3f(0.9, 0.9, 0.9);
//    glutWireSphere(0.06, 10, 10);
//    glEnable(GL_LIGHTING);
//
//    glPopMatrix();
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
//    //glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
//
//    glutSolidSphere(1.0, 10, 10);
//    // 2,3번째 변수는 해상도. 낮을수록 삼각형이 잘보임
//    glPopMatrix();
//    glFlush();
//    /// 
//
//
//
//    glFlush();
//}
//
//
//
//void MyReshape(GLFWwindow* window, int w, int h) {
//    windowHeight = h;
//    windowWidth = w;
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//}
//
//
//void MyTimer(int Value) {
//    SpinAngle = (SpinAngle + 3) % 360;
//    Ground_spin = (Ground_spin + 1) % 360;
//    glutPostRedisplay();
//    glutTimerFunc(40, MyTimer, 1);
//}
//
//void MyMouseClick(GLFWwindow* window, GLint Button, GLint State, GLint mods) {
//    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
//        double x, y;
//        glfwGetCursorPos(window, &x, &y);
//        preMouse = vec2(x, y);
//        currentMouse = preMouse;
//    }
//}
//
//void MyMouseMove(GLFWwindow* window, GLdouble X, GLdouble Y)
//{
//    currentMouse = vec2(X, Y);
//    glutPostRedisplay();
//}
//
//void MyKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    float scale = 0.1;
//
//    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
//        switch (key) {
//        case GLFW_KEY_W:
//            myCamera.MoveCamera(myCamera.forward * scale);
//            break;
//        case GLFW_KEY_S:
//            myCamera.MoveCamera(myCamera.forward * -scale);
//            break;
//        case GLFW_KEY_A:
//            myCamera.MoveCamera(myCamera.right * -scale);
//            break;
//        case GLFW_KEY_D:
//            myCamera.MoveCamera(myCamera.right * scale);
//            break;
//        case GLFW_KEY_Q:
//            myCamera.MoveCamera(myCamera.up * scale);
//            break;
//        case GLFW_KEY_Z:
//            myCamera.MoveCamera(myCamera.up * -scale);
//            break;
//        default:
//            break;
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//
//
//int main(int argc, char** argv) {
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//
//    if (!glfwInit()) {
//        std::cout << "GLFW initialization failed" << std::endl;
//        return -1;
//    }
//
//    // Use GLFW to create a window and OpenGL context
//    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL Sample Drawing", NULL, NULL);
//    if (!window) {
//        std::cout << "Window creation failed" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // Init camera
//    vec3 eye(0, 0, 0);
//    vec3 at(0, 0, -5);
//    vec3 up(1, 0, 0);
//    up = normalize(up);
//    myCamera.InitCamera(eye, at, up);
//
//    InitLight();
//    //skybox_init();
//
//    glfwSetFramebufferSizeCallback(window, MyReshape);
//    glfwSetMouseButtonCallback(window, MyMouseClick);
//    glfwSetCursorPosCallback(window, MyMouseMove);
//    glfwSetKeyCallback(window, MyKeyboard);
//
//    while (!glfwWindowShouldClose(window)) {
//        MyDisplay();
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}




//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//// DESC :> window 크기 변경 시마다 callback 함수 호출
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//// DESC :> Input 이벤트
//void processInput(GLFWwindow* window);
//
//int main()
//{
//	// DESC :> glfw initialize
//	glfwInit();
//
//	GLFWwindow* window = glfwCreateWindow(800, 500, "LearnOpenGL", NULL, NULL);
//
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// DESC :> glad initialize
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// DESC :> rendering infinity loop
//	while (!glfwWindowShouldClose(window))
//	{
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// DESC :> 할당된 모든 메모리 삭제
//	glfwTerminate();
//
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}