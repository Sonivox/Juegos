/*
	Copyright 2016 Mohammad Imrul Jubair 
*/

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "imageloader.h"

using namespace std;

/*
COPYRIGHT : Mohammad Imrul Jubair.
Please provide reference to reuse this code.
*/

//////////////////// initializations //////////////////////////

void sky();
void theGun();
void theSurface();
void theBullet();
void theCalculate();
void update(int value);
void castle();
void powerBar();
void rulesBoard();
void fire();
void explosion();
void fence();
void enemy();


float random_float(const float, const float);

GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;
GLuint _textureId7;
GLuint _textureId8;

float THETA = 3.1416 / 180.0;
bool freeze = false;
bool collide = false;
bool hit = false;

float _angle = 0.0;
float gVal = 9.8;
float vNot = 8.0;
float xVal = 0.0, yVal = 0.0;
float collideX = 0.0, collideY = 0.0;

float enemyX = 5.0;


float a = 0.0;
float b = 0.0;

float timer = 0.0;

/////////////////////// functions /////////////////////////

void Draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();



    glPushMatrix();

    glTranslatef(-5.0, -1.0, -10.0);
    castle();


    glPushMatrix();

    glTranslatef(0.0, 0.5, 0.0);
    glRotatef(_angle, 0.0, 0.0, 1.0);
    theGun();

    glPopMatrix();


    glPushMatrix();

    glTranslatef(0, 0.1, 0.5);
    theSurface();
    powerBar();
    fence();
    glTranslatef(-1.0, 0.8, 0);
    rulesBoard();

    glPopMatrix();


    glPushMatrix();

    glTranslatef(0, 0, -0.5);
    //sky();

    glPopMatrix();


    glPushMatrix();

    theBullet();

    glPopMatrix();


    glPopMatrix();

    glFlush();

    glutSwapBuffers();
}

void sky()
{
    glBindTexture(GL_TEXTURE_2D, _textureId4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);glVertex3f(2.0, -0.55, 0.0);
    glTexCoord2f(1, 0);glVertex3f(14, -0.55, 0.0);
    glTexCoord2f(1, 1);glVertex3f(14, 5.0, 0.0);
    glTexCoord2f(0, 1);glVertex3f(2.0, 5.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);


}

void castle()
{

    glBindTexture(GL_TEXTURE_2D, _textureId2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3f(1,1,1);

    glTexCoord2f(0,0);glVertex3f(-2.8, -0.45, 0.0);
    glTexCoord2f(1, 0);glVertex3f( 0.6, -0.45, 0.0);
    glTexCoord2f(1, 1);glVertex3f( 0.6, 4.0, 0.0);
    glTexCoord2f(0, 1);glVertex3f(-2.8, 4.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void theGun()
{
    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);glVertex3f(-0.2, -0.5, 0.0);
    glTexCoord2f(1, 0);glVertex3f(1.4, -0.5, 0.0);
    glTexCoord2f(1, 1);glVertex3f(1.4, 0.3, 0.0);
    glTexCoord2f(0, 1);glVertex3f(-0.2, 0.3, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(0.0,0.0,-0.25);
    if (freeze == true && timer >= 0.5 && timer <= 2.8)
        fire();

    glPopMatrix();
}

void enemy()
{
    glColor3f(1, 1, 1);

    glBindTexture(GL_TEXTURE_2D, _textureId8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0);glVertex3f(0.9, 0, 0);
    glTexCoord2f(1, 1);glVertex3f(0.9, 1, 0);
    glTexCoord2f(0, 1);glVertex3f(0, 1, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void fire()
{
    glColor3f(1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, _textureId6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);glVertex3f(1.35, -0.4, 0.0);
    glTexCoord2f(1, 0);glVertex3f(2.2, -0.4, 0.0);
    glTexCoord2f(1, 1);glVertex3f(2.2, 0.2, 0.0);
    glTexCoord2f(0, 1);glVertex3f(1.35, 0.2, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void explosion()
{

    glColor3f(0.2, 0.0, 0.0);
    glLineWidth(1);
    glPushMatrix();
    glTranslatef(collideX, -0.5, -1.0);

    for (float i = 0; i <= 9; i=i+1) {

        glBegin(GL_LINES);
        glVertex3f( -0.5, 0, 0.0);
        glVertex3f( -0.3, 0, 0.0);
        glEnd();
        glRotatef(-20, 0, 0, 1);
    }

    //glColor3f(0.65, 0.16, 0.16);
    glutSolidSphere(0.2, 15.0, 2.0);

    glPopMatrix();
}

void fence()
{
    glBindTexture(GL_TEXTURE_2D, _textureId7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);glVertex3f(5.0, -1.0, 0.0);
    glTexCoord2f(9, 0);glVertex3f(12.5, -1.0, 0.0);
    glTexCoord2f(9, 1);glVertex3f(12.5, 0.2, 0.0);
    glTexCoord2f(0, 1);glVertex3f(5.0, 0.2, 0.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void theSurface()
{

    glColor3f(0.0, 0.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, _textureId1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0, 1.0, 1.0);

    glTexCoord2f(0, 1);glVertex3f(-5.0, -0.4, 0.0);
    glTexCoord2f(4, 1);glVertex3f(15.0, -0.4, 0.0);
    glTexCoord2f(4, 0);glVertex3f(15.0, -5.0, 0.0);

    glTexCoord2f(0, 0);glVertex3f(-5.0, -5.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    if (collide == true)
        explosion();


    //srand((unsigned)time(0));
    //enemyX = (float)(rand() % 10 + 0);
    //printf("%f\n", enemyX);
    glPushMatrix();

    glTranslatef(enemyX, -0.55, -1.0);
    glScalef(1.2,1.2,0.0);
    enemy();
    glPopMatrix();

}

void theBullet()
{
    glColor3f(0.2, 0.1, 0.1);
    glTranslatef(xVal, yVal+0.5, -0.2);
    glutSolidSphere(0.2, 15.0, 2.0);


}

void powerBar()
{

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);

    glColor3f(0.2, 0.2, 0.2);

    glVertex3f(-1.6, -0.56, 0.5);
    glVertex3f(0.6, -0.56, 0.5);
    glVertex3f(0.6, -0.82, 0.5);
    glVertex3f(-1.6, -0.82, 0.5);

    glEnd();

    glLineWidth(6);
    glBegin(GL_LINES);

    glColor3f(0.2, 0.2, 0.2);

    glVertex3f(-1.5, -0.7, 0.5);
    glVertex3f(-1.5 + (vNot*0.3-1.6), -0.7 , 0.5);

    glEnd();

}

void rulesBoard()
{
    glColor3f(1, 1, 1);

    glBindTexture(GL_TEXTURE_2D, _textureId5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);glVertex3f(1.0, 2.0, 0.0);
    glTexCoord2f(1, 0);glVertex3f(3.5, 2.0, 0.0);
    glTexCoord2f(1, 1);glVertex3f(3.5, 4.2, 0.0);
    glTexCoord2f(0, 1);glVertex3f(1.0, 4.2, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (freeze == false) {
        switch (key) {
            case 'w':
                if (_angle <= 50) {
                    _angle += 1.0;
                    glutPostRedisplay();
                }
                break;
            case 's':
                if (_angle >= -20) {
                    _angle -= 1.0;
                    glutPostRedisplay();
                }
                break;
            case 'e':
                if (vNot <= 12){
                    vNot += 0.1;
                    glutPostRedisplay();
                }
                break;
            case 'd':
                if (vNot >= 6.0) {
                    vNot -= 0.1;
                    glutPostRedisplay();
                }
                break;
            case 'a':
                update(0);

                break;
        }

        theCalculate();
    }
}

void update(int value)
{
    xVal += 0.08;
    yVal = a*xVal - b*xVal*xVal;

    if (yVal > -0.9 && xVal < 16.0) {
        collide = false;
        freeze = true;
        timer = timer + 0.1;

        glutTimerFunc(15.0, update, 0);

    }
    else
    {
        collideX = xVal;
        //collideY = yVal;
        xVal = 0.0;
        yVal = 0.0;
        timer = 0.0;
        freeze = false;
        collide = true;
        srand((unsigned)time(0));
        enemyX = (float)(rand() %8 + 0);
    }



    glutPostRedisplay();
}

void theCalculate()
{
    a = tan(_angle*(THETA));
    b = gVal / (2 * vNot*vNot*cos(_angle*THETA)*cos(_angle*THETA));
}

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void textureSetting(){

    Image* image1 = loadBMP("./images/softground.bmp");
    Image* image2 = loadBMP("./images/castle.bmp");
    Image* image3 = loadBMP("./images/cannon.bmp");
    Image* image4 = loadBMP("./images/jungle3.bmp");
    Image* image5 = loadBMP("./images/rules.bmp");
    Image* image6 = loadBMP("./images/fire.bmp");
    Image* image7 = loadBMP("./images/fence3.bmp");
    Image* image8 = loadBMP("./images/spy_white.bmp");



    _textureId1 = loadTexture(image1);
    _textureId2 = loadTexture(image2);
    _textureId3 = loadTexture(image3);
    _textureId4 = loadTexture(image4);
    _textureId5 = loadTexture(image5);
    _textureId6 = loadTexture(image6);
    _textureId7 = loadTexture(image7);
    _textureId8 = loadTexture(image8);


    delete image1;
    delete image2;
    delete image3;
    delete image4;
    delete image5;
    delete image6;
    delete image7;
    delete image8;



}

void Initialize() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 2.00, 1.0, 200.0);

}

float random_float(const float min, const float max)
{
    srand((unsigned)time(0));
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}

int main(int iArgc, char** cppArgv) {

    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 300);
    glutInitWindowPosition(70, 111);
    glutCreateWindow("physics");
    Initialize();
    textureSetting();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();

    return 0;
}
