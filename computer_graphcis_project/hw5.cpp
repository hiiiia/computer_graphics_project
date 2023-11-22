//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <GL/GL.h>
//#include <GL/GLU.h>
//#include <GL/glut.h>
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//
//
//
//using namespace std;
//using namespace glm;
//
//static int Day = 0, Time = 0;
//vec2 preMouse, currentMouse;
//int windowHeight, windowWidth;
//mat4 rotation;
//
////define camera class
//class camera {
//public:
//    vec3 eye; //center position
//    vec3 at; //point where this camera is pointing out
//    vec3 up; // up direction (normalized)
//
//    vec3 forward; //vector pointing forward direction
//    float distance = 1; //distance from eye to at
//    vec3 right; //vector indicating right direction from the point of camera
//    mat4 viewMat = mat4(1); //set initial view matrix as identity
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
//    //void RotateCamera(vec3 axis, float angle)
//    //{
//    //    //rotate direc and up vector
//    //    vec4 tempForward = vec4(forward[0], forward[1], forward[2], 0);
//    //    vec4 tempUp = vec4(up[0], up[1], up[2], 0);
//    //    mat4 rot = rotate(mat4(1), radians(angle), axis);
//    //    rotation = rot;
//    //    forward = rot * tempForward;
//    //    up = rot * tempUp;
//
//    //    //update at vector accordingly
//    //    at = eye + forward * distance;
//
//    //    UpdateCamera();
//    //}
//
//
//    //update variables accordingly
//    void UpdateCamera()
//    {
//        up = normalize(up);
//        distance = length(at - eye);
//        forward = normalize(at - eye);
//        right = normalize(cross(forward, up));
//    }
//
//    void ComputeViewMatrix()
//    {
//        viewMat = mat4(1);
//        for (int i = 0; i < 3; i++)
//        {
//            viewMat[0][i] = right[i];
//            viewMat[1][i] = up[i];
//            viewMat[2][i] = -forward[i];
//            viewMat[i][3] = -eye[i];
//        }
//    }
//
//};
//
//camera myCamera;
//
//void init() {
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK); // 후면 면 제거
//    glFrontFace(GL_CCW); // 전면 면은 반시계 방향
//    // 나머지 초기화 코드...
//}
//
//
//void DrawSolarSystem() {
//
//    //get camera variables from camera class
//    vec3 eye = myCamera.eye;
//    vec3 at = myCamera.at;
//    vec3 up = myCamera.up;
//
//
//
//    // 태양 조명
//    GLfloat sun_light_amb[] = { 0.5, 0, 0, 1.0 };
//    GLfloat sun_light_diffuse[] = { 1, 0.5, 0.5, 1.0 };
//    GLfloat sun_light_specular[] = { 1, 1, 1, 1.0 };
//    // 달 조명
//    GLfloat moon_light_amb[] = { 0.5, 0.5, 0, 1.0 };
//    GLfloat moon_light_diffuse[] = { 1, 1, 0.5, 1.0 };
//    GLfloat moon_light_specular[] = { 1, 1, 1, 1.0 };
//
//    //재질 설정
//    //태양
//    GLfloat sun_mat_amb[] = { 0.2, 0 , 0, 1.0 };
//    GLfloat sun_mat_diffuse[] = { 1, 0.5, 0.5, 1.0 };
//    GLfloat sun_mat_specular[] = { 0, 0, 0, 1 };
//    GLfloat sun_mat_emission[] = { 0.3, 0.1, 0.1, 0.0 };
//    //달
//    GLfloat moon_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
//    GLfloat moon_mat_diff[] = { 0.5, 0.5, 0.1, 1.0 };
//    GLfloat moon_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat moon_shininess[] = { 100.0 };
//    GLfloat moon_mat_emission[] = { 0.3, 0.3, 0.1, 0.0 };
//    //지구
//    GLfloat earth_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
//    GLfloat earth_mat_diff[] = { 0.1, 0.1, 0.8, 1.0 };
//    GLfloat earth_mat_specular[] = { 0.5, 0.5, 1.0, 1.0 };
//    GLfloat earth_shininess[] = { 80.0 };
//
//
//    //glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_SMOOTH);
//
//    glEnable(GL_LIGHTING);
//
//
//    //===============
//    glEnable(GL_LIGHT0);
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_amb);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
//
//    GLfloat sunPosition[] = { 0.0, 0.0, 0.0, 1.0 };
//
//    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
//
//    glDisable(GL_LIGHT0);
//    //===============
//    glEnable(GL_LIGHT1);
//
//    glLightfv(GL_LIGHT1, GL_AMBIENT, moon_light_amb);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, moon_light_diffuse);
//    glLightfv(GL_LIGHT1, GL_SPECULAR, moon_light_specular);
//
//    GLfloat moonPosition[] = { 0.0, 0.0, 0.0, 1.0 };
//
//
//
//    //===============
//
//
//    //glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_amb);
//    //glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
//    //glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
//    ////glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    //glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
//
//
//
//
//
//    glMatrixMode(GL_MODELVIEW); //set matrix mode
//    glLoadIdentity(); //set Identity 
//    //set view transform matrix
//    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
//
//    //========================================
//    //========================================
//    //glEnable(GL_DEPTH_TEST);
//    //draw solar system
//    //glEnable(GL_LIGHTING);
//    //glColor3f(0, 1, 0);
//
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_amb);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
//    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
//
//    glutSolidSphere(0.2, 100, 100);
//    //glutWireSphere(0.2, 100, 100);
//
//    glEnable(GL_LIGHT0);
//    //glDisable(GL_LIGHTING);
//    //glDisable(GL_LIGHT0);
//    //glDisable(GL_COLOR_MATERIAL);
//    //glDisable(GL_DEPTH_TEST);
//    // 
//    //========================================
//    //========================================
//    glPushMatrix();
//
//    // Apply transformations
//    //glLoadIdentity();
//    glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
//    glTranslatef(0.7, 0.0, 0.0);
//    // Get the current modelview matrix
//    GLfloat modelviewMatrix[16];
//    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
//
//    // Extract the translation part
//    moonPosition[0] = modelviewMatrix[12];
//    moonPosition[1] = modelviewMatrix[13];
//    moonPosition[2] = modelviewMatrix[14];
//    moonPosition[3] = modelviewMatrix[15];
//
//    // Restore the previous modelview matrix
//    glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
//    glDisable(GL_LIGHT1);
//
// 
//    printf_s("%f / %f / %f /%f \n", moonPosition[0], moonPosition[1], moonPosition[2], moonPosition[3]);
//    glPopMatrix();
//
//    //========================================
//    //========================================
//    glPushMatrix();
//    glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
//    glTranslatef(0.7, 0.0, 0.0);
//
//
//
//
//
//    //========================================
//    //========================================
//    glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
//    //glEnable(GL_BLEND);
//    //glEnable(GL_COLOR_MATERIAL);
//    //glColor3f(0, 1, 0);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_amb);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diff);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, earth_shininess);
//    //glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
//    glutSolidSphere(0.1, 100, 100);
//    glEnable(GL_LIGHT1);
//    glPushMatrix();
//
//    //glDisable(GL_BLEND);
//    //glDisable(GL_COLOR_MATERIAL);
//    //========================================
//    //========================================
//
//    glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
//    glTranslatef(-0.2, 0.0, 0.0);
//
//    //glEnable(GL_LIGHTING);
//    //glEnable(GL_BLEND);
//    //glEnable(GL_COLOR_MATERIAL);
//
//
//    //glColor3f(0, 0, 1);
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_amb);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diff);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, moon_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
//
//    glutSolidSphere(0.04, 100, 100);
//
//
//
//    //glDisable(GL_LIGHTING);
//    //glDisable(GL_LIGHT0);
//    //glDisable(GL_LIGHT1);
//    //glDisable(GL_BLEND);
//    //glDisable(GL_COLOR_MATERIAL);
//    //========================================
//    //========================================
//    glPopMatrix();
//    glPopMatrix();
//
//}
//
//void MyDisplay() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    init();
//    //Rotate camera
//    float x_move = -30.f * (currentMouse[0] - preMouse[0]) / windowWidth;
//    float y_move = -30.f * (currentMouse[1] - preMouse[1]) / windowHeight;
//
//    //myCamera.RotateCamera(myCamera.right, (float)y_move);
//    //myCamera.RotateCamera(myCamera.up, (float)x_move);
//    //preMouse = currentMouse;
//
//    //Set projection;
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(20, (float)windowWidth / (float)windowHeight, 0, 10);
//
//    //Draw Scene
//    DrawSolarSystem();
//
//    //Send it to buffer
//    glFlush();
//}
//
//
//void MyReshape(int w, int h) {
//    windowWidth = w;
//    windowHeight = h;
//
//    //Set viewport
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//}
//
//void MyKeyboard(unsigned char key, int x, int y) {
//    float scale = 0.1;
//    switch (key) {
//    case 'w':
//        //myCamera.RotateCamera(myCamera.right, 1);
//        myCamera.MoveCamera(myCamera.forward * scale);
//        glutPostRedisplay();
//        break;
//    case 's':
//        //myCamera.RotateCamera(myCamera.right, -1);
//        myCamera.MoveCamera(myCamera.forward * -scale);
//        glutPostRedisplay();
//        break;
//    case 'a':
//        myCamera.MoveCamera(myCamera.right * -scale);
//        glutPostRedisplay();
//        break;
//    case 'd':
//        myCamera.MoveCamera(myCamera.right * scale);
//        glutPostRedisplay();
//        break;
//    default:
//        break;
//    }
//}
//
//void MyTimer(int Value) {
//    Day = (Day + 2) % 360;
//    Time = (Time + 1) % 360;
//
//
//
//
//
//
//    vec4 relativeEye = vec4(myCamera.eye[0], myCamera.eye[1], myCamera.eye[2], 1);
//    float deg = 1;
//    mat4 rotationMatrix = mat4(
//        cos(radians(deg)), -sin(radians(deg)), 0.0, myCamera.at[0],
//        sin(radians(deg)), cos(radians(deg)), 0.0, myCamera.at[1],
//        0.0, 0.0, 1.0, myCamera.at[2],
//
//        0.0, 0.0, 0.0, 1
//    );
//    relativeEye = rotationMatrix * relativeEye;
//    myCamera.eye = relativeEye;
//
//
//    vec4 tmp_up = vec4(myCamera.up[0], myCamera.up[1], myCamera.up[2], 1);
//    mat4 rotationMatrix_1 = mat4(
//        cos(radians(deg)), -sin(radians(deg)), 0.0, myCamera.up[0],
//        sin(radians(deg)), cos(radians(deg)), 0.0, myCamera.up[1],
//        0.0, 0.0, 1.0, myCamera.up[2],
//        0.0, 0.0, 0.0, 1
//    );
//    tmp_up = rotationMatrix_1 * tmp_up;
//    myCamera.up = tmp_up;
//
//
//    //myCamera.RotateCamera(vec3(0,0,1), (float)1);
//    //vec4 tempeye = vec4(myCamera.eye[0], myCamera.eye[1], myCamera.eye[2], 0);
//    //myCamera.eye = rotation * tempeye;
//
//
//    //cout << "At : " << myCamera.at.x << "," << myCamera.at.y << "," << myCamera.at.z << "\n";
//
//    glutPostRedisplay();
//    glutTimerFunc(40, MyTimer, 1);
//}
//
//
//void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
//    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
//        preMouse = vec2(X, Y);
//        currentMouse = preMouse;
//    }
//
//
//
//}
//
//void MyMouseMove(GLint X, GLint Y) {
//    currentMouse = vec2(X, Y);
//    glutPostRedisplay();
//}
//
//int main(int argc, char** argv) {
//    //Create window
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(500, 300);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("195837 / 용한빛");
//
//    //Clear and set background color;
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//
//    //get window variables
//    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
//    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
//
//
//
//    //Init camera
//    vec3 eye(0, 2, 4);
//    vec3 at(0.2, 0, 0);
//    vec3 up = cross(vec3(1, 0, 0), eye - at);
//    cout << "Before normal up vector : " << "(" << up.x << ", " << up.y << ", " << up.z << ")\n";
//    up = normalize(up);
//    cout << "After normal up vector : " << "(" << up.x << ", " << up.y << ", " << up.z << ")";
//    myCamera.InitCamera(eye, at, up);
//
//    //set callback functions
//    glutDisplayFunc(MyDisplay);
//    glutKeyboardFunc(MyKeyboard);
//    glutTimerFunc(40, MyTimer, 1);
//    glutMouseFunc(MyMouseClick);
//    glutMotionFunc(MyMouseMove);
//    glutReshapeFunc(MyReshape);
//
//    glFrustum(-1, 1, -1, 1, -1, 100);
//
//    //start mainloop
//    glutMainLoop();
//    return 0;
//}
