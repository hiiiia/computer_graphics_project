#define _CRT_SECURE_NO_WARNINGS

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

int sphere_num =1500;
camera myCamera;

vec2 preMouse, currentMouse;
int windowHeight, windowWidth;

vec3 tmp_loc;

static int skybox_size = 20;

static int SpinAngle = 0;
static int weatherTime = 0;

static float Spin_sun_moon = 0;

static float Spin_star = 0;

static bool Ray_flag = false;
LoadTex loadTex;
Sea sea;



//OakCask oak3;
Skybox skybox;
Night_sphere night_sphere;

void initLight() {
    glEnable(GL_LIGHTING);  // ì¡°ëª… í™œì„±í™”

    // ê´‘ì› í™œì„±í™”
    glEnable(GL_LIGHT0);

    // ê´‘ì› ìœ„ì¹˜ ì„¤ì •
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0 };  // (x, y, z, w) - wëŠ” ê´‘ì›ì´ ë°©í–¥ ê´‘ì›ì¸ì§€ ìœ„ì¹˜ ê´‘ì›ì¸ì§€ë¥¼ ë‚˜íƒ€ëƒ„

    // ê´‘ì› ìƒ‰ìƒ ì„¤ì •
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    // ê´‘ì› ì„¤ì • ì ìš©
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

    // ì¬ì§ˆ ì„¤ì • í™œì„±í™”
    //GL_COLOR_MATERIALì„ í™œì„±í™”í•˜ë©´ glColor ëª…ë ¹ì–´ë¡œ ì„¤ì •í•œ ìƒ‰ìƒì´ ë¬¼ì²´ì˜ ì¬ì§ˆì— ì ìš©
    //glEnable(GL_COLOR_MATERIAL);
}


struct SphereInfo {
    float x, y, z;  // ìœ„ì¹˜
    float r, g, b, a;  // ìƒ‰ìƒ ë° íˆ¬ëª…ë„
};

std::vector<SphereInfo> spheres;

void initSpheres(int numSpheres) {
    spheres.clear();  // ë²¡í„° ì´ˆê¸°í™”

    for (int i = 0; i < numSpheres; ++i) {
        SphereInfo sphere;
        float innerRadius = skybox_size * 4;
        float outerRadius = skybox_size * 4 - 5;

        sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;

        while (sqrt(sphere.x * sphere.x + sphere.y * sphere.y + sphere.z * sphere.z) < innerRadius) {
            // ë°˜ì§€ë¦„ì´ innerRadius ì´ìƒì¸ì§€ í™•ì¸í•˜ê³ , ì•„ë‹ˆë©´ ë‹¤ì‹œ ë¬´ì‘ìœ„ ì¢Œí‘œ ìƒì„±
            sphere.x = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.y = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
            sphere.z = static_cast<float>(rand()) / RAND_MAX * 2.0 * outerRadius - outerRadius;
        }

        sphere.r = static_cast<float>(rand()) / RAND_MAX;
        sphere.g = static_cast<float>(rand()) / RAND_MAX;
        sphere.b = static_cast<float>(rand()) / RAND_MAX;
        sphere.a = 1;

        spheres.push_back(sphere);  // ë²¡í„°ì— ì¶”ê°€

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


//obj ÆÄÀÏ ¹Ş¾Æ¿À±â 
std::vector < glm::vec3 > vertices;
std::vector < glm::ivec3 > faces;
std::vector < glm::vec2 > uvs;
std::vector < glm::vec3 > normals;


//3D °ñ·½ obj load
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
    //movingÀ» ³Ö¾î¼­ °ñ·ë À§Ä¡ º¯°æ
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


//ì¬ì§ˆ ì„¤ì •
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

    glTranslated(0, 0, -50);
    glRotatef(Spin_star, 0.0, 1.0, 0.0);

    int count = 0;
    for (const auto& sphere : spheres) {
        count += 1;
        glColor4f(sphere.r, sphere.g, sphere.b, sphere.a);  // íˆ¬ëª…ë„ ì ìš©


        //if (tmp_loc.x == sphere.x && tmp_loc.y == sphere.y && tmp_loc.z == sphere.z) {
        //    printf_s("%d", count);
        //}

        //glBindTexture(GL_TEXTURE_2D, LoadTex::MyTextureObject[10]);
            // ì¬ì§ˆ ì„¤ì •
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);


        glPushMatrix();
        glTranslatef(sphere.x, sphere.y, sphere.z);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
    }

    glPopMatrix();
    glColor4f(1, 1, 1, 1);

}


//
//struct StarInfo {
//    float x, y, z;  // í˜„ì¬ ìœ„ì¹˜
//    float targetX, targetY, targetZ;  // ëª©í‘œ ìœ„ì¹˜
//    float speed;  // ì´ë™ ì†ë„
//};
//
//std::vector<StarInfo> stars;
//
//void initStars(int numStars) {
//    stars.clear();  // ë²¡í„° ì´ˆê¸°í™”
//
//    for (int i = 0; i < numStars; ++i) {
//        StarInfo star;
//        star.x = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.y = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.z = 40.0;  // ê³ ì •ëœ Z ì¢Œí‘œ
//
//        star.targetX = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.targetY = static_cast<float>(rand()) / RAND_MAX * 80.0 - 40.0;
//        star.targetZ = 30.0;  // ê³ ì •ëœ Z ì¢Œí‘œ
//
//        star.speed = 0.1;
//
//        stars.push_back(star);  // ë²¡í„°ì— ì¶”ê°€
//    }
//}
//
//
//
//void moveStars() {
//    for (auto& star : stars) {
//        // í˜„ì¬ ìœ„ì¹˜ì—ì„œ ëª©í‘œ ìœ„ì¹˜ë¡œ ì´ë™
//        float dx = star.targetX - star.x;
//        float dy = star.targetY - star.y;
//        float dz = star.targetZ - star.z;
//        float distance = sqrt(dx * dx + dy * dy + dz * dz);
//
//        if (distance > 0.1) {  // ì´ë™ì´ ëœ ëœ ê²½ìš°ì—ë§Œ ì´ë™
//            float factor = star.speed / distance;
//            star.x += dx * factor;
//            star.y += dy * factor;
//            star.z += dz * factor;
//        }
//        else {  // ëª©í‘œ ìœ„ì¹˜ì— ë„ë‹¬í•˜ë©´ ìƒˆë¡œìš´ ëª©í‘œ ìœ„ì¹˜ ì„¤ì •
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
//        glColor3f(1.0, 1.0, 1.0);  // í°ìƒ‰
//        glutSolidSphere(0.5, 10, 10);
//        glPopMatrix();
//    }
//}

struct FallingStar {
    float x, y, z;  // í˜„ì¬ ìœ„ì¹˜
    float speedX, speedY, speedZ;  // ì´ë™ ì†ë„
    float size;     // í¬ê¸°
    bool active;    // í™œì„± ì—¬ë¶€
};

std::vector<FallingStar> fallingStars;

void initFallingStars(int numStars) {
    fallingStars.clear();  // ë²¡í„° ì´ˆê¸°í™”

    for (int i = 0; i < numStars; ++i) {
        FallingStar star;
        star.x = 20.0;
        star.y = static_cast<float>(rand()) / RAND_MAX * 40.0 - 20.0;
        star.z = 20.0;

        star.speedX = static_cast<float>(rand()) / RAND_MAX * 5.0*0.1;  // X ë°©í–¥ ì†ë„: 0ì—ì„œ 5.0 ì‚¬ì´
        star.speedY = static_cast<float>(rand()) / RAND_MAX * 5.0*0.1;  // Y ë°©í–¥ ì†ë„: 0ì—ì„œ 5.0 ì‚¬ì´
        star.speedZ = static_cast<float>(rand()) / RAND_MAX * 2.0*0.1;  // Z ë°©í–¥ ì†ë„: 0ì—ì„œ 2.0 ì‚¬ì´
        star.size = 5;
        star.active = false;

        fallingStars.push_back(star);  // ë²¡í„°ì— ì¶”ê°€
    }
}

void moveFallingStars() {
    for (auto& star : fallingStars) {
        if (star.active) {
            star.x += star.speedX;
            star.y += star.speedY;
            star.z -= star.speedZ;
            star.size -= 0.02;  // í¬ê¸°ë¥¼ ê°ì†Œì‹œì¼œ ì‚¬ë¼ì§€ëŠ” íš¨ê³¼

            // í¬ê¸°ê°€ 0ë³´ë‹¤ ì‘ì•„ì§€ë©´ ë¹„í™œì„±í™”
            if (star.size < 0.0) {
                star.active = false;
                star.size = 0.0;  // í¬ê¸°ê°€ ìŒìˆ˜ê°€ ë˜ì§€ ì•Šë„ë¡ ë³´ì •
            }
        }
        else {
            // ì¼ì • ê°„ê²©ìœ¼ë¡œ ë–¨ì–´ì§€ëŠ” ë³„ë˜¥ë³„ì´ ë‚˜íƒ€ë‚˜ë„ë¡ ì„¤ì •
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
            glColor3f(1.0, 1.0, 1.0);  // í°ìƒ‰
            glutSolidSphere(star.size, 10, 10);
            glPopMatrix();
        }
    }
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

    GLfloat sub_ligth_pos[] = { skybox_size*3, 0.0 ,-skybox_size ,1 };
    GLfloat moon_ligth_pos[] = { -skybox_size*3, 0.0 ,-skybox_size ,1 };
    GLfloat radius = skybox_size*3;
    float planets_rad = 1;
    glTranslated(0, 0, -22);

    //glColor3f(1, 0, 0);


    glEnable(GL_TEXTURE_2D);


    //glutSolidSphere(1, 10, 10);

    glRotatef(Spin_sun_moon*10,0, 1, 0);
    //glRotated(90, 0, 0, 1);

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

        //glLightfv(GL_LIGHT1, GL_POSITION, sub_ligth_pos);
        //glEnable(GL_LIGHT1);



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

    // Skyboxì˜ ê²½ê³„ ìƒì (ì˜ˆ: -40, -40, -40ì—ì„œ 40, 40, 40)
    vec3 boxMin(-skybox_size*4, -skybox_size*4, -skybox_size*4);
    vec3 boxMax(skybox_size*4, skybox_size*4, skybox_size*4);




    // ë ˆì´ ì‹œê°í™” ë° ì •ë³´ ì¶œë ¥

    if (Ray_flag) {

        float tMin, tMax;
        bool hit = rayBoxIntersection(eye, direction, boxMin, boxMax, tMin, tMax);

        if (hit) {

            printf_s("Hit\n");
            // ì¶©ëŒ ì§€ì  ê³„ì‚°
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
                //glutSolidCube(100);
                //glColor3f(1.0, 1.0, 1.0);
            glPopMatrix();

            printf_s("Sphere size: %d \n",spheres.size());
            printf_s("Eye: (%.2f, %.2f, %.2f)\n", eye.x, eye.y, eye.z);
            printf_s("At: (%.2f, %.2f, %.2f)\n", direction.x, direction.y, direction.z);
            printf_s("Ray: (%.2f, %.2f, %.2f)\n", tmp_loc.x, tmp_loc.y, tmp_loc.z);

            Ray_flag = false;

        }


    }

    else {
        glPushMatrix();


        //glColor3f(1.0, 1.0, 0.0);

        //glTranslatef(tmp_loc.x, tmp_loc.y, tmp_loc.z);

        //glutSolidCube(0.2);


        //glColor3f(1.0, 1.0, 1.0);


        glPopMatrix();

    }

}





void CalculateAndPrintCubeWorldCoordinates() {
    glm::vec3 cubeLocalPosition = glm::vec3(0, 8.7, 1.1);
    glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), moving) *
        glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0f), cubeLocalPosition);

    cubeWorldPosition = glm::vec3(cubeModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    std::cout << "Cube World Coordinates: (" << cubeWorldPosition.x << ", " << cubeWorldPosition.y << ", " << cubeWorldPosition.z << ")" << std::endl;
}


void modelmove() {
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // È¸Àü °¢µµ Àû¿ë

    //draw solar system
    glColor3f(0.5, 0.6, 0.7);
    glPushMatrix();
    glTranslatef(moving.x, moving.y, moving.z); // head
    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f); //ÀÌ°Å¸¦ ÇÏ¸é ¿ÀºêÁ§Æ®¸¸ È¸Àü
    DrawWireSurface(vertices, faces);
    glPushMatrix();
    glTranslatef(0, 8.7, 1.1); //¸Ó¸® ÀÚ¸®
    //glutWireCube(2.0);
    glPopMatrix();
    glPopMatrix();
}



void MyDisplay() {


    moveFallingStars();
    drawFallingStars();




    GLfloat sea_mat_amb[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat sea_mat_diff[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat sea_mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat sea_mat_shininess[] = { 50.0 };
    GLfloat seaLightpos[] = { 1,1,1,1 };

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




    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    vec3 eye = myCamera.eye;
    vec3 at = myCamera.at - moving;
    vec3 up = myCamera.up;

    glMatrixMode(GL_MODELVIEW); //set matrix mode
    glLoadIdentity(); //set Identity 

    if (viewport) {
        glViewport(0, 0, Width, Height);

        // ÀüÃ¼ Ã¢¿¡ ±×¸± ³»¿ë (Å¥ºê µî)
        glPushMatrix();
        gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glColor3f(0.7, 0.7, 0.7);
        glutWireCube(1.0);
        glPopMatrix();

        glViewport(Width - Width / 2, 0, Width / 2, Height / 2);
        //°ñ·½ µû¶ó°¡°Ô ÇÏ±â
        if (moveCamera) {
            at = myCamera.at - moving;
            gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
                at[0], at[1], at[2],
                up[0], up[1], up[2]);
            //glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // È¸Àü °¢µµ Àû¿ë
            glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
        }

        else {//3ÀÎÄª ½ÃÁ¡
            gluLookAt(eye[0] - moving.x, eye[1] + 11.0f - moving.y, eye[2] - moving.z,
                at[0], at[1], at[2], up[0], up[1], up[2]);
            modelmove();

        }
    }

    //°ñ·½ µû¶ó°¡°Ô ÇÏ±â
    if (moveCamera && !viewport) { //ÀÏÀÎÄª
        vec3 at = myCamera.at;
        glViewport(0, 0, Width, Height);

        gluLookAt(cubeWorldPosition.x, cubeWorldPosition.y, cubeWorldPosition.z,
            at_[0] + cubeWorldPosition.x, at_[1] + cubeWorldPosition.y, at_[2] + cubeWorldPosition.z,
            up[0], up[1], up[2]);


        glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // È¸Àü °¢µµ Àû¿ë
        glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
    }

    else if (!viewport) {
        glViewport(0, 0, Width, Height);

        gluLookAt(eye[0] - moving.x, eye[1] + 11.0f - moving.y, eye[2] - moving.z,
            at[0], at[1], at[2], up[0], up[1], up[2]);
        modelmove();
    }

    CalculateAndPrintCubeWorldCoordinates();

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////


    //GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///
    //put your code here


    glDisable(GL_LIGHTING);

    //glClear(GL_COLOR_BUFFER_BIT);


    skybox.MakeSky(skybox_size);




    glEnable(GL_LIGHTING);


    // ì•½ê°„ í•¸ë“œí°ìœ¼ë¡œ ë³´ëŠ”ê²ƒ ì²˜ëŸ¼ ë¨
    //glPushMatrix();

    //glLoadIdentity();
    //glTranslated(0, 3, -3);
    //glutSolidSphere(2, 10, 10);

    //glPopMatrix();



    drawRay();

    draw_sun_moon();


    drawSpheres();


    //moveStars();
    //drawStars();

    //night_sphere.Make_night_sky(1);
    /// skyboxë‘ night_spehreë¥¼ ê·¸ë¦¬ë©´ í…ìŠ¤ì³ê°€ í•˜ë‚˜ì”© ë°€ë¦¼. ë­ê°€ ë¬¸ì œì¸ê±°ì§€?

    //glLightfv(GL_LIGHT0, GL_POSITION , testlightPosition);

    glPopMatrix();

    sea.Update(SpinAngle, myCamera.eye, myCamera.at);


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
    Spin_sun_moon = (Spin_sun_moon + 0.01);
    glutPostRedisplay();
    glutTimerFunc(10, MyTimer, 1);
}

void MyTimer2(int Value) {
    weatherTime += 1;

    if (weatherTime >= 10) {
        weatherTime = 0;
        cout << " ï¿½ë¼®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ä±ï¿½ ï¿½Ïµï¿½ " << endl;
        Weather::ChangeWeather();
    }

    cout << weatherTime << endl;
    glutPostRedisplay();
    glutTimerFunc(1000, MyTimer2, 1);
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        preMouse = vec2(X, Y);
        currentMouse = preMouse;
    }

    if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {
        Ray_flag = true;
    }


    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
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
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////


    glutPostRedisplay();

}

void MyMouseMove(GLint X, GLint Y)
{
    
    //currentMouse = vec2(X, Y);


        ptCurrentMousePosit.x = x;
    ptCurrentMousePosit.y = y;

    if (bMousing)
    {
        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);//Á¦ÀÚ¸® È¸Àü //°¢µµ¶ó°í »ı°¢ÇÏ¸é µÉµí
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();

    glutPostRedisplay();
}

vec3 at_(0, 0, 0);
void MyKeyboard(unsigned char key, int x, int y) {
    glm::vec3 right = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 translate_obj = glm::vec3(0.0f);

    switch (key) { //¿ÀºêÁ§Æ® À§Ä¡ ÀÌµ¿
    case 'w': // À§·Î ÀÌµ¿
        translate_obj += forward * g_fCameraSpeed;
        at_ -= forward;
        break;
    case 's': // ¾Æ·¡·Î ÀÌµ¿
        translate_obj -= forward * g_fCameraSpeed;
        at_ += forward;

        break;
    case 'a': // ¿ŞÂÊÀ¸·Î ÀÌµ¿
        translate_obj -= right * g_fCameraSpeed;
        at_ += right;

        break;
    case 'd': // ¿À¸¥ÂÊÀ¸·Î ÀÌµ¿
        translate_obj += right * g_fCameraSpeed;
        at_ -= right;

        break;
    case 't': // Ä«¸Ş¶ó ½ÃÁ¡ º¯°æ
        if (!viewport) {//ºĞÇÒÁß¿¡´Â ½ÃÁ¡º¯°æ ¾ÈµÇ°Ô ÇÏ±â
            moveCamera = !moveCamera;
        }
        break;
    case 'm':
        // Ãß°¡µÈ ÄÚµå: Å° 'm'À» ´©¸¦ ¶§¸¶´Ù Å« È­¸é°ú ÀÛÀº È­¸éÀ» ÀüÈ¯
        viewport = !viewport;
        break;
    }


    // È¸ÀüµÈ ÀÌµ¿ º¤ÅÍ¸¦ ±¸ÇØ¼­ ¿ÀºêÁ§Æ®¸¦ ÀÌµ¿½ÃÅ´
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-g_fSpinX), glm::vec3(0.0f, 1.0f, 0.0f));
    translate_obj = glm::vec3(rotationMatrix * glm::vec4(translate_obj, 0.0f));
    moving += translate_obj;

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



   LoadObj("Data/stone/Stone.obj", vertices, faces, uvs, normals);

//     //Init camera
//     vec3 center(0, 0, 40);
//     vec3 at(0, 0, 0);
//     vec3 up = cross(vec3(1, 0, 0), at - center);
//     up = normalize(up);
//     myCamera.InitCamera(center, at, up);

    srand((unsigned int)time(NULL));

    loadTex.init();
    sea.init();
    skybox.init();
    loadTex.init();

    // êµ¬ì²´ ì´ˆê¸°í™”
    initSpheres(sphere_num);  // 10ê°œì˜ êµ¬ì²´ë¥¼ ì´ˆê¸°í™”í•©ë‹ˆë‹¤.
    initFallingStars(100);
    //night_sphere.init();
    

    initLight();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutTimerFunc(1000, MyTimer2, 1);
    glutMainLoop();
    return 0;
}
