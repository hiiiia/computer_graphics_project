//
//
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
////#include <glad/glad.h>
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
//#include <iostream>
//using namespace glm;
//using namespace std;
//
//
//GLuint cubemapTexture;
//
//# define M_PI 3.14159265358979323846 /* pi */
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
//    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     
//    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
//    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//
//    /// <summary>
//    /// 
//    glShadeModel(GL_SMOOTH);//���� ���̵�
//    //glShadeModel(GL_FLAT); // �ﰢ�� ���̵�
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
//GLuint loadCubemap(std::vector<std::string> faces) {
//    GLuint textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    int width, height, nrChannels;
//    for (GLuint i = 0; i < faces.size(); i++) {
//        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//        if (data) {
//            GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//            stbi_image_free(data);
//            printf("Loaded image %s: width = %d, height = %d, channels = %d\n", faces[i].c_str(), width, height, nrChannels);
//        }
//        else {
//            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//            stbi_image_free(data);
//        }
//    }
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    return textureID;
//}
//
//void drawSkybox(float size) {
//    glDisable(GL_LIGHTING);
//    glEnable(GL_TEXTURE_CUBE_MAP);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//    glPushMatrix();
//    //glScalef(size, size, size);
//
//    // Enable automatic texture coordinate generation
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//    glEnable(GL_TEXTURE_GEN_R);
//
//    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
//    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
//    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
//
//    //glBegin(GL_QUADS);
//
//    //// Front Face
//    //glVertex3f(-1.0, -1.0, 1.0);
//    //glVertex3f(1.0, -1.0, 1.0);
//    //glVertex3f(1.0, 1.0, 1.0);
//    //glVertex3f(-1.0, 1.0, 1.0);
//
//    //// Back Face
//    //glVertex3f(-1.0, -1.0, -1.0);
//    //glVertex3f(1.0, -1.0, -1.0);
//    //glVertex3f(1.0, 1.0, -1.0);
//    //glVertex3f(-1.0, 1.0, -1.0);
//
//    //// Left Face
//    //glVertex3f(-1.0, -1.0, -1.0);
//    //glVertex3f(-1.0, -1.0, 1.0);
//    //glVertex3f(-1.0, 1.0, 1.0);
//    //glVertex3f(-1.0, 1.0, -1.0);
//
//    //// Right Face
//    //glVertex3f(1.0, -1.0, -1.0);
//    //glVertex3f(1.0, -1.0, 1.0);
//    //glVertex3f(1.0, 1.0, 1.0);
//    //glVertex3f(1.0, 1.0, -1.0);
//
//    //// Top Face
//    //glVertex3f(-1.0, 1.0, -1.0);
//    //glVertex3f(-1.0, 1.0, 1.0);
//    //glVertex3f(1.0, 1.0, 1.0);
//    //glVertex3f(1.0, 1.0, -1.0);
//
//    //// Bottom Face
//    //glVertex3f(-1.0, -1.0, -1.0);
//    //glVertex3f(1.0, -1.0, -1.0);
//    //glVertex3f(1.0, -1.0, 1.0);
//    //glVertex3f(-1.0, -1.0, 1.0);
//
//    //glEnd();
//
//    //glPopMatrix();
//
//    // Disable automatic texture coordinate generation
//    glDisable(GL_TEXTURE_GEN_S);
//    glDisable(GL_TEXTURE_GEN_T);
//    glDisable(GL_TEXTURE_GEN_R);
//
//    glDisable(GL_TEXTURE_CUBE_MAP);
//    glEnable(GL_LIGHTING);
//}
//
//
//void draw_cube(float cubeSize) {
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    mat_diffuse[3] = 0.5; 
//
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat high_shininess[] = { 100.0 };
//
//    // 
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
//        // ���� ����
//        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColors[i]);
//        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
//
//        glBegin(GL_QUADS);
//        switch (i)
//        {
//            //case(0):    
//            //    //Front 
//            //    
//            //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            //    break;
//            //case(1):
//            //    //Back
//
//            //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            //    break;
//            //case(2):
//            //    //Right 
//
//            //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            //    break;
//            //case(3):
//            //    //Left  
//
//            //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, 0.5f * cubeSize);
//            //    glVertex3f(-0.5f * cubeSize, -0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            //    glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            //    break;
//        case(4):
//            //Top  
//
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize);
//            glVertex3f(0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            glVertex3f(-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize);
//            break;
//        case(5):
//            //Bottom  
//
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
//
//    glDisable(GL_BLEND);
//}
//
//void setFrustum(float fov, float aspect, float nearPlane, float farPlane) {
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
//
//
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
//    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
//    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat no_shininess[] = { 0.0 };
//    GLfloat low_shininess[] = { 5.0 };
//    GLfloat high_shininess[] = { 100.0 };
//    GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
//    // emission <<--- �߱�ü ����
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
//
//    glLoadIdentity();
//
//
//    ////
//    //setFrustum(40.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 20.0f);
//    gluPerspective(40.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 20.0);
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
//    //drawSkybox(1.0f);
//
//    ///
//
//    glPushMatrix();
//
//
//    glTranslatef(0.0, 0.0, -5.0);
//
//    glRotatef(Ground_spin, 1.0, 0.0, 0.0);
//
//    draw_cube(5);
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
//    glutSolidSphere(1.0, 100, 100);
//
//    glPopMatrix();
//    glFlush();
//    /// 
//
//
//}
//
//
//
//void MyReshape(int w, int h) {
//    windowHeight = h;
//    windowWidth = w;
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//}
//
//
//void MyTimer(int Value) {
//    SpinAngle = (SpinAngle + 10) % 360;
//    Ground_spin = (Ground_spin + 1) % 360;
//    //printf_s("x:%f / y:%f / z:%f/ \n", myCamera.eye[0], myCamera.eye[1], myCamera.eye[2]);
//    glutPostRedisplay();
//    glutTimerFunc(40, MyTimer, 1);
//}
//
//void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
//    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
//        preMouse = vec2(X, Y);
//        currentMouse = preMouse;
//    }
//}
//
//void MyMouseMove(GLint X, GLint Y)
//{
//    currentMouse = vec2(X, Y);
//    glutPostRedisplay();
//}
//
//void MyKeyboard(unsigned char key, int x, int y) {
//    float scale = 0.5;
//    switch (key) {
//    case 'w':
//        myCamera.MoveCamera(myCamera.forward * scale);
//        break;
//    case 's':
//        myCamera.MoveCamera(myCamera.forward * -scale);
//        break;
//    case 'a':
//        myCamera.MoveCamera(myCamera.right * -scale);
//        break;
//    case 'd':
//        myCamera.MoveCamera(myCamera.right * scale);
//        break;
//    case 'q':
//        myCamera.MoveCamera(myCamera.up * scale);
//        break;
//    case 'z':
//        myCamera.MoveCamera(myCamera.up * -scale);
//        break;
//
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv) {
//
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(1200, 1200);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("openGL Sample Drawing");
//
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err) << std::endl;
//        return -1;
//    }
//
//    GLenum error = glGetError();
//    if (error != GL_NO_ERROR) {
//        // Print or log the error message
//        std::cerr << "OpenGL Error: " << gluErrorString(error) << std::endl;
//    }
//
//
//    //Init camera
//    vec3 eye(8, 0, 10);
//    vec3 at(0, 0, -5);
//    vec3 up(1, 0, 0);
//    up = normalize(up);
//    myCamera.InitCamera(eye, at, up);
//
//
//    std::vector<std::string> faces{
//        "./skybox/right.jpg", "./skybox/left.jpg",
//        "./skybox/top.jpg", "./skybox/bottom.jpg",
//        "./skybox/front.jpg", "./skybox/back.jpg"
//    };
//
//    cubemapTexture = loadCubemap(faces);  // 전역 변수 초기화
//    //printf_s("%d", cubemapTexture);
//    InitLight();
//    //skybox_init();
//    glutDisplayFunc(MyDisplay);
//    glutReshapeFunc(MyReshape);
//    glutMouseFunc(MyMouseClick);
//    glutMotionFunc(MyMouseMove);
//    glutKeyboardFunc(MyKeyboard);
//    glutTimerFunc(40, MyTimer, 1);
//
//
//    glEnable(GL_DEPTH_TEST);
//
//    glutMainLoop();
//    return 0;
//}
//
//
//
////
////#define STB_IMAGE_IMPLEMENTATION
////#include "stb_image.h"
////
////#include <GL/glew.h>
////#include <GL/glut.h>
////#include <iostream>
////#include <vector>
////
////GLuint cubemapTexture;
////
////
////GLuint loadCubemap(std::vector<std::string> faces) {
////    GLuint textureID;
////    glGenTextures(1, &textureID);
////    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
////
////    int width, height, nrChannels;
////    for (GLuint i = 0; i < faces.size(); i++) {
////        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
////        if (data) {
////            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
////            stbi_image_free(data);
////            printf_s("OK\n");
////        }
////        else {
////            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
////            stbi_image_free(data);
////        }
////    }
////    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
////    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
////    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
////    return textureID;
////}
////
////void drawCube() {
////    glutSolidCube(1.0);
////}
////
////void display() {
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    glLoadIdentity();
////
////    // Draw Skybox
////    glDisable(GL_DEPTH_TEST);
////
////    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
////
////    glMatrixMode(GL_MODELVIEW);
////    glPushMatrix();
////    glLoadIdentity();
////
////    // Draw the skybox cube without depth testing
////    drawCube();
////
////    glPopMatrix();
////    glEnable(GL_DEPTH_TEST);
////
////    // Draw the rest of the scene (cube)
////    glMatrixMode(GL_MODELVIEW);
////    glPushMatrix();
////    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
////    drawCube();
////    glPopMatrix();
////
////    glutSwapBuffers();
////}
////
////void reshape(int w, int h) {
////    glViewport(0, 0, w, h);
////    glMatrixMode(GL_PROJECTION);
////    glLoadIdentity();
////    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity();
////    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
////}
////
////int main(int argc, char** argv) {
////    glutInit(&argc, argv);
////    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
////    glutInitWindowSize(800, 600);
////    glutCreateWindow("Skybox Cube Example");
////
////    GLenum err = glewInit();
////    if (GLEW_OK != err) {
////        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err) << std::endl;
////        return -1;
////    }
////
////    std::vector<std::string> faces{
////        "./skybox/right.jpg", "./skybox/left.jpg",
////        "./skybox/top.jpg", "./skybox/bottom.jpg",
////        "./skybox/front.jpg", "./skybox/back.jpg"
////    };
////
////    cubemapTexture = loadCubemap(faces);
////
////    glutDisplayFunc(display);
////    glutReshapeFunc(reshape);
////    glEnable(GL_DEPTH_TEST);
////
////    glutMainLoop();
////
////    return 0;
////}