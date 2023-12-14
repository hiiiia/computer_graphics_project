

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

int sphere_num =1000;
camera myCamera;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;



static int SpinAngle = 0;

static float Spin_star = 0;
LoadTex loadTex;
Sea sea;



//OakCask oak3;
Skybox skybox;
Night_sphere night_sphere;

void InitLight() {
    GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };     //���� Ư��
    GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_position[] = { 1.0, 1.0, 5.0, 1.0 };

    glShadeModel(GL_SMOOTH); //���� ���̵�
    glEnable(GL_DEPTH_TEST); //���� ���� Ȱ��ȭ
    glEnable(GL_LIGHTING); //���� Ȱ��ȭ
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); //�ֺ��� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); //Ȯ�걤 ����
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    /// <summary>
    /// 
    /// </summary>
}


struct SphereInfo {
    float x, y, z;  // ��ġ
    float r, g, b, a;  // ���� �� ����
};

std::vector<SphereInfo> spheres;

void initSpheres(int numSpheres) {
    spheres.clear();  // ���� �ʱ�ȭ

    for (int i = 0; i < numSpheres; ++i) {
        SphereInfo sphere;
        const float innerRadius = 80.0;
        const float outerRadius = 85.0;

        sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;

        while (sqrt(sphere.x * sphere.x + sphere.y * sphere.y + sphere.z * sphere.z) < innerRadius) {
            // �������� innerRadius �̻����� Ȯ���ϰ�, �ƴϸ� �ٽ� ������ ��ǥ ����
            sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        }

        sphere.r = static_cast<float>(rand()) / RAND_MAX;
        sphere.g = static_cast<float>(rand()) / RAND_MAX;
        sphere.b = static_cast<float>(rand()) / RAND_MAX;
        sphere.a = static_cast<float>(rand()) / RAND_MAX;

        spheres.push_back(sphere);  // ���Ϳ� �߰�
    }
}

void drawSpheres() {

    glPushMatrix();

    glTranslated(0,0,-50);
    glRotatef(Spin_star, 0.0, 1.0, 0.0);

    for (const auto& sphere : spheres) {
        glColor4f(sphere.r, sphere.g, sphere.b, sphere.a);  // ���� ����
        glPushMatrix();
        glTranslatef(sphere.x, sphere.y, sphere.z);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
    }

    glPopMatrix();
    glColor4f(1,1,1,1);

}



//
//struct StarInfo {
//    float x, y, z;  // ���� ��ġ
//    float targetX, targetY, targetZ;  // ��ǥ ��ġ
//    float speed;  // �̵� �ӵ�
//};
//
//std::vector<StarInfo> stars;
//
//void initStars(int numStars) {
//    stars.clear();  // ���� �ʱ�ȭ
//
//    for (int i = 0; i < numStars; ++i) {
//        StarInfo star;
//        star.x = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.y = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.z = 40.0;  // ������ Z ��ǥ
//
//        star.targetX = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.targetY = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.targetZ = 30.0;  // ������ Z ��ǥ
//
//        star.speed = 0.1;
//
//        stars.push_back(star);  // ���Ϳ� �߰�
//    }
//}
//
//
//
//void moveStars() {
//    for (auto& star : stars) {
//        // ���� ��ġ���� ��ǥ ��ġ�� �̵�
//        float dx = star.targetX - star.x;
//        float dy = star.targetY - star.y;
//        float dz = star.targetZ - star.z;
//        float distance = sqrt(dx * dx + dy * dy + dz * dz);
//
//        if (distance > 0.1) {  // �̵��� �� �� ��쿡�� �̵�
//            float factor = star.speed / distance;
//            star.x += dx * factor;
//            star.y += dy * factor;
//            star.z += dz * factor;
//        }
//        else {  // ��ǥ ��ġ�� �����ϸ� ���ο� ��ǥ ��ġ ����
//            star.targetX = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//            star.targetY = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        }
//    }
//}
//
//void drawStars() {
//    for (const auto& star : stars) {
//        glPushMatrix();
//        glTranslatef(star.x, star.y, star.z);
//        glColor3f(1.0, 1.0, 1.0);  // ���
//        glutSolidSphere(0.5, 10, 10);
//        glPopMatrix();
//    }
//}

struct FallingStar {
    float x, y, z;  // ���� ��ġ
    float speedX, speedY, speedZ;  // �̵� �ӵ�
    float size;     // ũ��
    bool active;    // Ȱ�� ����
};

std::vector<FallingStar> fallingStars;

void initFallingStars(int numStars) {
    fallingStars.clear();  // ���� �ʱ�ȭ

    for (int i = 0; i < numStars; ++i) {
        FallingStar star;
        star.x = 20.0;
        star.y = static_cast<float>(rand()) / RAND_MAX * 40.0 - 20.0;
        star.z = 20.0;

        star.speedX = static_cast<float>(rand()) / RAND_MAX * 5.0*0.1;  // X ���� �ӵ�: 0���� 5.0 ����
        star.speedY = static_cast<float>(rand()) / RAND_MAX * 5.0*0.1;  // Y ���� �ӵ�: 0���� 5.0 ����
        star.speedZ = static_cast<float>(rand()) / RAND_MAX * 2.0*0.1;  // Z ���� �ӵ�: 0���� 2.0 ����
        star.size = 0.1;
        star.active = false;

        fallingStars.push_back(star);  // ���Ϳ� �߰�
    }
}

void moveFallingStars() {
    for (auto& star : fallingStars) {
        if (star.active) {
            star.x += star.speedX;
            star.y += star.speedY;
            star.z -= star.speedZ;
            star.size -= 0.02;  // ũ�⸦ ���ҽ��� ������� ȿ��

            // ũ�Ⱑ 0���� �۾����� ��Ȱ��ȭ
            if (star.size < 0.0) {
                star.active = false;
                star.size = 0.0;  // ũ�Ⱑ ������ ���� �ʵ��� ����
            }
        }
        else {
            // ���� �������� �������� ���˺��� ��Ÿ������ ����
            if (rand() % 100 == 0) {
                star.active = true;
                star.x = 20.0;
                star.y = static_cast<float>(rand()) / RAND_MAX * 40.0 - 20.0;
                star.z = 20.0;
                star.size = static_cast<float>(rand()) / RAND_MAX * 2.0 + 1.0;
            }
        }
    }
}

void drawFallingStars() {
    for (const auto& star : fallingStars) {
        if (star.active) {
            glPushMatrix();
            glTranslatef(star.x, star.y, star.z);
            glColor3f(1.0, 1.0, 1.0);  // ���
            glutSolidSphere(star.size, 10, 10);
            glPopMatrix();
        }
    }
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
    ///
    //put your code here
    glDisable(GL_LIGHTING);

    glClear(GL_COLOR_BUFFER_BIT);


    skybox.MakeSky(20);


    drawSpheres();


    moveFallingStars();
    drawFallingStars();

    //moveStars();
    //drawStars();

    //night_sphere.Make_night_sky(1);
    /// skybox�� night_spehre�� �׸��� �ؽ��İ� �ϳ��� �и�. ���� �����ΰ���?
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
    Spin_star = (Spin_star + 0.05) ;
    glutPostRedisplay();
    glutTimerFunc(10, MyTimer, 1);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
    
    sea.init();
    skybox.init();
    loadTex.init();

    // ��ü �ʱ�ȭ
    initSpheres(sphere_num);  // 10���� ��ü�� �ʱ�ȭ�մϴ�.
    initFallingStars(10);
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
