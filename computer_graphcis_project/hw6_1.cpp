 //
//#define STB_IMAGE_IMPLEMENTATION    
//#include "stb_image.h"
//
//#include <windows.h>
//#include <stdlib.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//#include <GLAUX/glaux.h>
//#include <math.h>
//
//#include <stdio.h>
//#include <iostream>
//
//GLuint g_textureID = -1;
//
//
//float g_fDistance = -4.5f;
//float g_fSpinX = 0.0f;
//float g_fSpinY = 0.0f;
//
//
//static POINT ptLastMousePosit;
//static POINT ptCurrentMousePosit;
//static bool bMousing;
//
////void convertJpgToBmp(const char* jpgPath, const char* bmpPath) {
////
////    FIBITMAP* dib = FreeImage_Load(FIF_JPEG, jpgPath, JPEG_DEFAULT);
////    if (!dib) {
////        fprintf(stderr, "Error loading JPG file\n");
////        return;
////    }
////
////    FreeImage_Save(FIF_BMP, dib, bmpPath, BMP_DEFAULT);
////
////    FreeImage_Unload(dib);
////}
////
////void convertPngToBmp(const char* pngPath, const char* bmpPath) {
////    FIBITMAP* dib = FreeImage_Load(FIF_PNG, pngPath, PNG_DEFAULT);
////    if (!dib) {
////        fprintf(stderr, "Error loading PNG file\n");
////        return;
////    }
////
////    FreeImage_Save(FIF_BMP, dib, bmpPath, BMP_DEFAULT);
////
////    FreeImage_Unload(dib);
////}
//
//void MyMouse(int button, int state, int x, int y) {
//    switch (button) {
//    case GLUT_LEFT_BUTTON:
//        if (state == GLUT_DOWN) {
//            ptLastMousePosit.x = ptCurrentMousePosit.x = x;
//            ptLastMousePosit.y = ptCurrentMousePosit.y = y;
//            bMousing = true;
//        }
//        else
//            bMousing = false;
//        break;
//    case GLUT_MIDDLE_BUTTON:
//    case GLUT_RIGHT_BUTTON:
//        break;
//    default:
//        break;
//    }
//
//    glutPostRedisplay();
//}
//
//void MyMotion(int x, int y) {
//    ptCurrentMousePosit.x = x;
//    ptCurrentMousePosit.y = y;
//
//    if (bMousing)
//    {
//        g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
//        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
//    }
//
//    ptLastMousePosit.x = ptCurrentMousePosit.x;
//    ptLastMousePosit.y = ptCurrentMousePosit.y;
//
//    glutPostRedisplay();
//}
//
//
//void load_image_Texture(void) {
//
//
//    // load and generate the texture
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load("Data/hw6.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        printf_s("%d %d", width, height);
//
//        glGenTextures(1, &g_textureID);
//        glBindTexture(GL_TEXTURE_2D, g_textureID);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        // 
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//
//
//        ///////////
//        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//}
//
//
//void load_bmp_Texture(void) {
//    AUX_RGBImageRec* pTextureImage = auxDIBImageLoad("Data/apple.bmp");
//    if (pTextureImage != NULL) {
//        glGenTextures(1, &g_textureID);
//
//        glBindTexture(GL_TEXTURE_2D, g_textureID);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        // 
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//
//
//        ///////////
//        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//        ///////////
//
//        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
//            GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
//    }
//
//    if (pTextureImage) {
//        if (pTextureImage->data)
//            free(pTextureImage->data);
//
//        free(pTextureImage);
//    }
//}
//
//void init(void) {
//    //load_bmp_Texture();
//    load_image_Texture();
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_DEPTH_TEST);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
//}
//
//
//
//
//void draw_with_Texture1(float size) {
//    GLUquadric* obj = gluNewQuadric();
//    gluQuadricTexture(obj, GL_TRUE);
//    gluQuadricNormals(obj, GLU_SMOOTH);
//
//    glPushMatrix();
//
//        gluCylinder(obj, 0.7, 0.7, 1.5, 50, 50);
//        gluDisk(obj, 0.0, 0.7, 50, 1);
//        glTranslatef(0.0, 0.0, 1.5);
//        gluDisk(obj, 0.0,0.7, 50, 1);
//        glTranslatef(0.0, 0.0, 1.5);
//    glPopMatrix();
//    gluDeleteQuadric(obj);
//}
//
//
//
//
//void draw_with_Texture2(float radius, int slices) {
//
//    GLUquadric* obj = gluNewQuadric();
//    gluQuadricTexture(obj, GL_TRUE);
//    gluQuadricNormals(obj, GLU_SMOOTH);
//    gluSphere(obj, radius, slices, slices);
//    gluDeleteQuadric(obj);
//
//}
//
//void draw_with_Texture3(float size) {
//    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//    /// 이 부분은 카메라의 바라보는 방향으로 그대로 입혀짐.
//    // 이걸 끄면 위에서 그대로 누르면서 텍스쳐가 입혀지는 느낌
//
//
//    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//    // GL_SPHERE_MAP은 구에 텍스쳐를 입히고, 반사해서 보여줌.
//
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//    glutSolidCube(size);
//}
//
//
//void quads_obj(void){
//    glBindTexture(GL_TEXTURE_2D, g_textureID);
//    glBegin(GL_QUADS);
//
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  //앞면
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
//
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //뒷면
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
//
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  //윗면
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
//
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //아랫면
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
//
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  //우측면
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
//
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //좌측면
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
//    glEnd();
//}
//
//void cube_obj(float size) {
//    glutSolidCube(size);
//}
//
//void teapot_obj(float size) {
//    glutSolidTeapot(size);
//}
//
//
//
//
//
//void render(void) {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, g_fDistance);
//    glRotatef(-g_fSpinY, 1.0f, 0.0f, 0.0f);
//    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);
//
//    glBindTexture(GL_TEXTURE_2D, g_textureID);
//
//    //Draw object
//    quads_obj();
//    //draw_with_Texture1(1);
//    //draw_with_Texture2(1, 50);
//    //draw_with_Texture3(1);
//    //cube_obj(1);
//    glutSwapBuffers();
//}
//
//
//
//void MyReshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//}
//
//void main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowPosition(150, 150);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Texture Mapping - Passivity");
//    init();
//    glutDisplayFunc(render);
//    glutReshapeFunc(MyReshape);
//    glutMouseFunc(MyMouse);
//    glutMotionFunc(MyMotion);
//
//    glutMainLoop();
//}