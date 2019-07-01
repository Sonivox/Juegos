#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL_mixer.h"

#include <stdlib.h>
#include <time.h>

#define RUTA_AUDIO "resources/audio/sweden.wav"

void suelo();
void torre();
void puente();
void perimetro();
void porton();
void steveHead();
void steveTorso();
void steveBrazo();
void stevePierna();

void objeto1();
void objeto2();
void objeto3();

int animating = 0;
int frameNumber; // Numero de frames

//Definimos variables
double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;

GLfloat X = 0.0f;
GLfloat Y = -5.5f;
GLfloat Z = -2.5f;
GLfloat scale = 0.1f;

//Parametros del personaje
GLfloat step = 2.5;
GLfloat RotPersoAngle = 180.0f, RotPersoX = 0.0f, RotPersoY = 1.0f, RotPersoZ = 0.0f;
GLfloat PosPersoX = 0.0f, PosPersoY = 13.5f, PosPersoZ = -14.5f;

GLfloat PosObj1X = 0.0f, PosObj1Y = 80.0f, PosObj1Z = 15.0f;
GLfloat PosObj2X = 40.0f, PosObj2Y = 80.0f, PosObj2Z = 15.0f;
GLfloat PosObj3X = -40.0f, PosObj3Y = 80.0f, PosObj3Z = 15.0f;

GLuint ListTower, ListPuente, ListPerimetro, ListPorton, ListSuelo;
GLuint ListHead, ListTorso, ListBrazo, ListPierna;
GLuint ListObjeto1, ListObjeto2, ListObjeto3;

//Arreglo de imagenes
GLuint texture[0];

//parametros de la fuente de luz
GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};

void init(void) {
    //Carga la textura
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.046f, 0.714f, 0.945f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    //activa la luz
    glEnable(GL_LIGHT0);

    /* Generador de numeros aleatorios */
    srand(time(NULL));
    int posRand = 1 + rand() % (90 - 1);
    std::cout << posRand << std::endl;
    if(posRand > 45){
        PosPersoX = (posRand - 45) * - 1;
    }else{
        PosPersoX = posRand;
    }
    std::cout << PosPersoX << std::endl;

    ListTower = glGenLists(1);
    glNewList(ListTower, GL_COMPILE);
    torre();
    glEndList();

    ListPuente = glGenLists(1);
    glNewList(ListPuente, GL_COMPILE);
    puente();
    glEndList();

    ListPerimetro = glGenLists(1);
    glNewList(ListPerimetro, GL_COMPILE);
    perimetro();
    glEndList();

    ListPorton = glGenLists(1);
    glNewList(ListPorton, GL_COMPILE);
    porton();
    glEndList();

    ListSuelo = glGenLists(1);
    glNewList(ListSuelo, GL_COMPILE);
    suelo();
    glEndList();

    ListHead = glGenLists(1);
    glNewList(ListHead, GL_COMPILE);
    steveHead();
    glEndList();

    ListTorso = glGenLists(1);
    glNewList(ListTorso, GL_COMPILE);
    steveTorso();
    glEndList();

    ListBrazo = glGenLists(1);
    glNewList(ListBrazo, GL_COMPILE);
    steveBrazo();
    glEndList();

    ListPierna = glGenLists(1);
    glNewList(ListPierna, GL_COMPILE);
    stevePierna();
    glEndList();

    ListObjeto1 = glGenLists(1);
    glNewList(ListObjeto1, GL_COMPILE);
    objeto1();
    glEndList();

    ListObjeto2 = glGenLists(1);
    glNewList(ListObjeto2, GL_COMPILE);
    objeto2();
    glEndList();

    ListObjeto3 = glGenLists(1);
    glNewList(ListObjeto3, GL_COMPILE);
    objeto3();
    glEndList();

}

void suelo() {
    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "suelo.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-400.0f, 00.0f, -400.0f);
    glTexCoord2f(62.0f, 0.0f); glVertex3f(400.0f, 00.0f, -400.0f);
    glTexCoord2f(62.0f, 62.0f); glVertex3f(400.0f, 00.0f, 400.0f);
    glTexCoord2f(0.0f, 62.0f); glVertex3f(-400.0f, 00.0f, 400.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void torre() {
    //Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "stonebrick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, 10.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(10.0f, 0.0f, 10.0f);
    glTexCoord2f(4.0f, 16.0f); glVertex3f(10.0f, 100.0f, 10.0f);
    glTexCoord2f(0.0f, 16.0f); glVertex3f(-10.0f, 100.0f, 10.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
    glTexCoord2f(4.0f, 16.0f); glVertex3f(-10.0f, 100.0f, -10.0f);
    glTexCoord2f(0.0f, 16.0f); glVertex3f(10.0f, 100.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-10.0f, 100.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 100.0f, 10.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(10.0f, 100.0f, 10.0f);
    glTexCoord2f(4.0f, 4.0f); glVertex3f(10.0f, 100.0f, -10.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
    glTexCoord2f(4.0f, 16.0f); glVertex3f(10.0f, 100.0f, -10.0f);
    glTexCoord2f(0.0f, 16.0f); glVertex3f(10.0f, 100.0f, 10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-10.0f, 0.0f, 10.0f);
    glTexCoord2f(4.0f, 16.0f); glVertex3f(-10.0f, 100.0f, 10.0f);
    glTexCoord2f(0.0f, 16.0f); glVertex3f(-10.0f, 100.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void puente() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "stonebrick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 75.0f, 8.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(50.0f, 75.0f, 8.0f);
    glTexCoord2f(17.0f, 2.5f); glVertex3f(50.0f, 90.8f, 8.0f);
    glTexCoord2f(0.0f, 2.5f); glVertex3f(-50.0f, 90.8f, 8.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(-50.0f, 75.0f, -8.0f);
    glTexCoord2f(17.0f, 2.5f); glVertex3f(-50.0f, 90.8f, -8.0f);
    glTexCoord2f(0.0f, 2.5f); glVertex3f(50.0f, 90.8f, -8.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, 75.0f, -8.0f);
    glEnd();

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 70.0f, 10.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(50.0f, 70.0f, 10.0f);
    glTexCoord2f(17.0f, 1.0f); glVertex3f(50.0f, 75.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 75.0f, 10.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(-50.0f, 70.0f, -10.0f);
    glTexCoord2f(17.0f, 1.0f); glVertex3f(-50.0f, 75.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 75.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, 70.0f, -10.0f);
    glEnd();

    // Arriba
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-50.0f, 75.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 75.0f, 10.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(50.0f, 75.0f, 10.0f);
    glTexCoord2f(17.0f, 4.0f); glVertex3f(50.0f, 75.0f, -10.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(17.0f, 4.0f); glVertex3f(-50.0f, 70.0f, -10.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(50.0f, 70.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, 70.0f, 10.0f);
    glTexCoord2f(17.0f, 0.0f); glVertex3f(-50.0f, 70.0f, 10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void perimetro() {
    //Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "stonebrick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    //Pared perimetral izquierda
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-200.0f, 0.0f, 0.0f);
    glTexCoord2f(28.0f, 0.0f); glVertex3f(-10.0f, 0.0f, 0.0f);
    glTexCoord2f(28.0f, 12.0f); glVertex3f(-10.0f, 65.0f, 0.0f);
    glTexCoord2f(0.0f, 12.0f); glVertex3f(-200.0f, 65.0f, 0.0f);
    glEnd();


    glDisable(GL_TEXTURE_2D);
}

void porton() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "oak.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
    glTexCoord2f(16.0f, 0.0f); glVertex3f(110.0f, 0.0f, 0.0f);
    glTexCoord2f(16.0f, 6.0f); glVertex3f(110.0f, 50.0f, 0.0f);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(10.0f, 50.0f, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void steveHead() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void objeto1() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto1/crafting_table_front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto1/crafting_table_button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto1/crafting_table_side.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto1/crafting_table_top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void objeto2() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto2/bookshelf.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto2/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );


    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void objeto3() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto3/melon_side.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "objeto3/melon_top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );


    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void steveTorso() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void steveBrazo() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void stevePierna() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Transladar el cubo a las siguientes coordenadas
    glTranslatef(0.0f, 0.0f, -5.5f);

    // Rotar la camara en el eje X,Y y Z
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glTranslatef(X, Y, Z);    // Transladar la camara en los 3 ejes
    // Otras transformaciones
    glScalef(scale, scale, scale); //Configurar la escala de la escena

    glTranslatef(0.0, -22.5, 0.0);
    glCallList(ListSuelo);
    //glTranslatef(0.0, 22.5, 0.0);

    glTranslatef(-60.0, 0.0f, 0.0);
    glCallList(ListTower);
    glCallList(ListPerimetro);
    glTranslatef(330.0, 0.0f, 0.0);
    glCallList(ListPerimetro);
    glTranslatef(-330.0, 0.0f, 0.0);

    glCallList(ListPorton);

    glTranslatef(120.0, 0.0f, 0.0);
    glCallList(ListTower);
    glTranslatef(-60.0, 0.0f, 0.0);
    glCallList(ListPuente);

    /* Carga de los diferentes Objetos */


    glTranslatef(PosObj1X, PosObj1Y, PosObj1Z);
    glScalef(0.5f,0.5f,0.5f);
    glCallList(ListObjeto1);
    glScalef(2.0f,2.0f,2.0f);
    glTranslatef(PosObj1X*-1, PosObj1Y*-1, PosObj1Z*-1);

    glTranslatef(PosObj2X, PosObj2Y, PosObj2Z);
    glScalef(0.5f,0.5f,0.5f);
    glCallList(ListObjeto2);
    glScalef(2.0f,2.0f,2.0f);
    glTranslatef(PosObj2X*-1, PosObj2Y*-1, PosObj2Z*-1);

    glTranslatef(PosObj3X, PosObj3Y, PosObj3Z);
    glScalef(0.5f,0.5f,0.5f);
    glCallList(ListObjeto3);
    glScalef(2.0f,2.0f,2.0f);
    glTranslatef(PosObj3X*-1, PosObj3Y*-1, PosObj3Z*-1);


    //PERSONAJE
    glRotatef(RotPersoAngle, RotPersoX, RotPersoY, RotPersoZ);
    glTranslatef(PosPersoX, PosPersoY, PosPersoZ); //Para coordinar la posición del personaje

    glScalef(0.6f,0.6f,0.6f);
    glCallList(ListTorso);
    glTranslatef(0.0, 12.5, 0.0);
    glCallList(ListHead);

    glTranslatef(7.5, -6.5, 4.5);
    glRotatef(260,1,0,0);
    glCallList(ListBrazo);
    glTranslatef(-15.0, 0.0, 1.5);
    glRotatef(-15,1,0,0);
    glCallList(ListBrazo);

    glRotatef(-245,1,0,0);
    glTranslatef(5.0, -22.5, -4.30);
    glCallList(ListPierna);
    glTranslatef(5, 0.0, 0.0f);
    glCallList(ListPierna);

    //glFlush();
    glutSwapBuffers();

}

// Función para controlar teclas especiales
void specialKeys(int key, int x, int y) {

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_UP)
        rotate_x += 7;
        //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
        //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
        //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float) w / (float) h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

void pauseAnimation() {
    // Llamamo a la función para detener la animación
    animating = 0;
}

void updateFrame() {
    // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma

    glColor3f(0.0,1.0,0.0);
    //Hacemos que la tetera gire
    for (int i=0; i<=5; i++){
        PosObj1Y = PosObj1Y -= 0.5;
        PosObj2Y = PosObj2Y -= 0.5;
        PosObj3Y = PosObj3Y -= 0.5;
        //std::cout << PosObj1Y << std::endl;
    }
    //Verificamos el numero de frames para detener animación
    if(frameNumber==25)
    {
        pauseAnimation();
        frameNumber=0;
    }
    //Almacenamos el numero de frames
    frameNumber++;
    printf ("Numero de Frame: %d \n", frameNumber);
}

void timerFunction(int timerID) {
    // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones
    if (animating) {
        updateFrame();
        glutTimerFunc(30, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
    // llamamos la función para iniciar la animación
    if (!animating) {
        animating= 1;
        glutTimerFunc(30, timerFunction, 1);
    }
}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y) {
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    GLfloat temp;
    switch (key) {
        case 'w':
            if (RotPersoAngle != 180) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 180;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;

        case 'a':
            PosObj1X -= 1;
            PosObj2X -= 1;
            PosObj3X -= 1;

            /*if (RotPersoAngle != 270) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 270;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;*/
            break;

        case 's' :

            if (RotPersoAngle != 0) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = -1*PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 0;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;

        case '1':
            PosObj1Y = 280.0f;
            PosObj2Y = 280.0f;
            PosObj3Y = 80.0f;
            break;
        case '2':
            PosObj1Y = 80.0f;
            PosObj2Y = 280.0f;
            PosObj3Y = 280.0f;
            break;
        case '3':
            PosObj1Y = 280.0f;
            PosObj2Y = 80.0f;
            PosObj3Y = 280.0f;
            break;
        case 'd' :
            PosObj1X += 1;
            PosObj2X += 1;
            PosObj3X += 1;
            /*if (RotPersoAngle != 90) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 90;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;*/
            break;
        case '8' :
            Y -= 0.1f;
            break;
        case '5' :
            Y += 0.1f;
            break;
        case '4':
            X -= 0.1f;
            break;
        case '6':
            X += 0.1f;
            break;
        case '7':
            rotate_y += 5;
            break;
        case '9':
            rotate_y -= 5;
            break;
        case '-':
            Z -= 0.1f;
            break;
        case '+':
            Z += 0.1f;
            break;
        case '?':
            std::cout << "X: " << X << std::endl;
            std::cout << "Y: " << Y << std::endl;
            std::cout << "Z: " << Z << std::endl;
            std::cout << "Perso X: " << PosPersoX << std::endl;
            std::cout << "Perso Y: " << PosPersoY << std::endl;
            std::cout << "Perso Z: " << PosPersoZ << std::endl;
            std::cout << "Perso Angle: " << RotPersoAngle << std::endl;
            std::cout << "Perso RotX: " << RotPersoX << std::endl;
            std::cout << "Perso RotY: " << RotPersoY << std::endl;
            std::cout << "Perso RotZ: " << RotPersoZ << std::endl;
            break;
        case ' ':
            if (animating){
                pauseAnimation();
            }else{
                startAnimation();
            }
            break;
        case 'q':
            exit(0);            // exit
    }
    glutPostRedisplay();
}

void update(int value) {
    rotate_y += 5;
    rotate_x += 6;
    rotate_z += 7;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[]) {

    if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
    // Setup audio mode
    Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
    Mix_Music *mus;  // Background Music

    mus = Mix_LoadMUS(RUTA_AUDIO);
    Mix_PlayMusic(mus,1); //Music loop=1

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc, argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    // Crear ventana
    glutCreateWindow("Defiende la puerta");
    init();
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    //glutTimerFunc(30, update, 0);
    // Pasar el control de eventos a GLUT
    glutMainLoop();

    // Regresar al sistema operativo
    return 0;

}