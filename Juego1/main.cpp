#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>

/*
 *       UNIVERSIDAD DE EL SALVADOR
 *        ALGORITMOS GRAFICOS 2019
 *
 *    JUEGO DE CAÑON (TIRO PARABOLICO)
 *           - ROBERTO HERBERTH MALTEZ GUARDADO - MG16071
 *           - ROBERTO ANTONIO ORTIZ ACEVEDO    - OA14002
 *           - EDWIN OSMIN ORELLANA MARTINEZ    - OM140
 *
 * */


using namespace std;

//////////////////// initializations //////////////////////////
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

GLuint texture[0];
GLuint cannon[0];
GLuint rules[0];
GLuint  enemigo[0];
GLuint fuego[0];

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

// funcion para cargar audio
void my_audio_callback(void *userdata, Uint8 *stream, int len);

#define RUTA_AUDIO "Humans Are Such Easy Prey.wav" //nombre del archivo de audio

// variables para audio
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play



/////////////////////// functions /////////////////////////

void Draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    glMatrixMode(GL_MODELVIEW);

    SDL_PauseAudio(false); //reproducir el audiow

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

void castle(){
    texture[1] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "castle.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void theGun(){
    cannon[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "cannon.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cannon[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
    if (freeze == true && timer >= 0.5 && timer <= 2.8) {
        fire();
    }

    glPopMatrix();
}

void enemy(){
    glColor3f(1, 1, 1);

    enemigo[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "enemy.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, enemigo[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void fire(){

    glColor3f(1.0, 1.0, 1.0);

    fuego[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "fire.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fuego[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void explosion(){
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

void fence(){
    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "fence2.jpeg",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void theSurface(){

    glColor3f(0.0, 0.0, 0.0);

    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "softground.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

    if (collide == true) {
        explosion();
    }


    //srand((unsigned)time(0));
    //enemyX = (float)(rand() % 10 + 0);
    //printf("%f\n", enemyX);
    glPushMatrix();

    glTranslatef(enemyX, -0.55, -1.0);
    glScalef(1.2,1.2,0.0);
    enemy();
    glPopMatrix();

}

void theBullet(){
    glColor3f(0.2, 0.1, 0.1);
    glTranslatef(xVal, yVal+0.5, -0.2);
    glutSolidSphere(0.2, 15.0, 2.0);
}

void powerBar(){

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

    rules[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "rules.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, rules[0]);
    //parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void theCalculate(){
    a = tan(_angle*(THETA));
    b = gVal / (2 * vNot*vNot*cos(_angle*THETA)*cos(_angle*THETA));
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
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(70, 111);
    glutCreateWindow("JUEGO DEL CAÑON (TIRO PARABOLICO)");
    Initialize();

    // sonido
    // Inicializar SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        return 1;

    // Variables locales
    static Uint32 wav_length; // Longitud de nuestra muestra
    static Uint8 *wav_buffer; // Buffer que contiene nuestro archivo de audio
    static SDL_AudioSpec wav_spec; // Las especificaciones de nuestra pieza de música

    /* Cargar el WAV */
    // Las especificaciones, la longitud y el búfer de nuestro wav se llenan
    if( SDL_LoadWAV(RUTA_AUDIO, &wav_spec, &wav_buffer, &wav_length) == NULL )
    {
        return 1;
    }
    // Establecer la función de devolución de llamada
    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;

    // Establecer nuestras variables estáticas globales
    audio_pos = wav_buffer; // Copia el buffer de sonido
    audio_len = wav_length; // Copia la longitud del archivo

    /*Abrir el dispositivo de audio */
    if ( SDL_OpenAudio(&wav_spec, NULL) < 0 )
    {
        fprintf(stderr, "No se pudo abrir el audio: %s\n", SDL_GetError());
        exit(-1);
    }


    glutDisplayFunc(Draw);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();

    return 0;
}

void my_audio_callback(void *userdata, Uint8 *stream, int len)
{

    if (audio_len ==0)
        return;

    len = ( len > audio_len ? audio_len : len );

    SDL_memcpy (stream, audio_pos, len); // Simplemente copie desde un buffer en el otro
    //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 2); // Mezclar de un buffer a otro

    audio_pos += len;
    audio_len -= len;
}
