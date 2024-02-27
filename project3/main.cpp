#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <iostream>
#define PI 3.1415926535898

#define Cos(th) (float) cos(PI/180*(th))
#define Sin(th) (float ) sin(PI/180*(th))
GLuint  tetragwno, paralilogramo, trigwno, edafos, edafosmikro;

float R = 0;
float Ambient[] = { 0.03f  ,0.03f  ,0.03f  ,1.0 };
float Diffuse[] = { 0.03f ,0.03f ,0.03f,1.0 };
float Specular[] = { 1.00f ,1.00f ,1.00f,1.0 };
GLfloat v[4][3] = { {0.0f, 0.0f, 1.0f}, {0.0f, 0.942809f, -0.33333f},
                    {-0.816497f, -0.471405f, -0.333333f}, {0.816497f, -0.471405f, -0.333333f} };
bool toggleLight = true;
bool typeshader = true;
bool polygontype = true;
double Z = 0;
int h = 340;
int p = 0;

void menu1(int id) {
    switch (id) {
        case 0:
            exit(0);
    }
}
void polygons(int num) {
    switch (num)
    {
        case 1:
            polygontype = false;
            break;
        case 2:
            polygontype = true;
            break;
    }
    glutPostRedisplay();

}
void shader(int num) {
    switch (num)
    {
        case 1:
            typeshader = true;
            break;
        case 2:
            typeshader = false;
            break;
    }
    glutPostRedisplay();

}
void spotlight(int num) {
    switch (num)
    {
        case 1:
            toggleLight = false;
            break;
        case 2:
            toggleLight = true;
            break;
    }
    glutPostRedisplay();

}

void keyPress(int key, int x, int y)
{

    if (key == GLUT_KEY_RIGHT) p += 5;
    else if (key == GLUT_KEY_LEFT) p -= 5;

    glutPostRedisplay();

}
void kanonikopoihsh(GLfloat* v) {

    GLfloat distance = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= distance;
    v[1] /= distance;
    v[2] /= distance;

}
void upodiairesh(GLfloat* a, GLfloat* b, GLfloat* c, int vathos) {
    if (vathos > 0) {
        GLfloat ab[3], ac[3], bc[3];
        for (unsigned int i = 0; i < 3; i++)
        {
            ab[i] = a[i] + b[i];
        }
        kanonikopoihsh(ab);
        for (unsigned int i = 0; i < 3; i++)
        {
            ac[i] = a[i] + c[i];
        }
        kanonikopoihsh(ac);
        for (unsigned int i = 0; i < 3; i++)
        {
            bc[i] = c[i] + b[i];
        }
        kanonikopoihsh(bc);
        upodiairesh(a, ab, ac, vathos - 1);
        upodiairesh(b, bc, ab, vathos - 1);
        upodiairesh(c, ac, bc, vathos - 1);
        upodiairesh(ab, bc, ac, vathos - 1);
    }
    else
    {
        glBegin(GL_TRIANGLES);
        glColor3f(10.0f, 10.0f, 0.0f);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glEnd();
    }
}
void tetragwna()
{
    int k = 8;
    glPushMatrix();
    glNormal3f(0, 1, 0);
    glTranslatef(0, 5, 0);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            glColor3ub(0, 255, 0);
            glBegin(GL_POLYGON);
            glVertex3f(-5, -40.0 + i * k, 40.0 - (j * k));
            glVertex3f(-5, -40.0 + (i + 1) * k, 40.0 - j * k);
            glVertex3f(-5, -40.0 + (i + 1) * k, 40.0 - (j + 1) * k);
            glVertex3f(-5, -40.0 + i * k, 40.0 - (j + 1) * k);
            glEnd();
        }
    }
    glPopMatrix();
}

int t = 0;
void idle() {
    R += 1;
    if (R > 180) {
        R = 0;
        t = 0;
    }
    if (R == 90) {
        t = 1;
    }
    if (t == 1) {
        if (Diffuse[0] - (1 - 0.03) / 90 < 0.03) {
            for (int i = 0; i < 3; i++) {
                //Ambient[i] -=(1-0.03)/90;
                Diffuse[i] = 0.03;
                Specular[i] = 0.03;

            }
        } else {
            for (int i = 0; i < 3; i++) {
                //Ambient[i] -=(1-0.03)/90;
                Diffuse[i] -= (1 - 0.03) / 90;
                Specular[i] -= (1 - 0.03) / 90;
            }
        }
    }
    else
    {
        if (Diffuse[0] + (1 - 0.03) / 90 > 1.0) {
            for (int i = 0; i < 3; i++) {
                Diffuse[i] = 1.0;
                Specular[i] = 1.0;

            }
        } else {
            for (int i = 0; i < 3; i++) {
                //Ambient[i] -=(1-0.03)/90;
                Diffuse[i] += (1 - 0.03) / 90;
                Specular[i] += (1 - 0.03) / 90;
            }
        }

    }
    glutPostRedisplay();
}
void myinit(void)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    tetragwno = glGenLists(1);
    glNewList(tetragwno, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(5, 5, 0.0f);
    glVertex3f(-5, 5, 0.0f);
    glVertex3f(-5, -5, 0.0f);
    glVertex3f(5, -5, 0.0f);
    glEnd();
    glEndList();
    paralilogramo = glGenLists(1);
    glNewList(paralilogramo, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(10, 5, 0.0f);
    glVertex3f(-10, 5, 0.0f);
    glVertex3f(-10, -5, 0.0f);
    glVertex3f(10, -5, 0.0f);
    glEnd();
    glEndList();
    trigwno = glGenLists(1);
    glNewList(trigwno, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(3.75, 0, 0.0f);
    glVertex3f(-5, 5, 0.0f);
    glVertex3f(-5, -5, 0.0f);
    glEnd();
    glEndList();
    edafos = glGenLists(1);
    glNewList(edafos, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor3ub(0, 255, 0);
    glVertex3f(-5, 40, -40.0f);
    glVertex3f(-5, -40, -40.0f);
    glVertex3f(-5, -40, 40.0f);
    glVertex3f(-5, 40, 40.0f);
    glEnd();
    glEndList();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void draw()
{

    if (typeshader == true)
    {
        glShadeModel(GL_SMOOTH);
    }
    else
    {
        glShadeModel(GL_FLAT);
    }
    double Ex = -20 * Sin(h) * Cos(p);
    double Ey = +20 * Sin(p);
    double Ez = +20 * Cos(h) * Cos(p);
    gluLookAt(Ex + 18, Ey, Ez, 0, 0, 0, 1, 0, 0);


    glPushMatrix();
    glRotatef(-R, 0, 0, 1);
    glTranslatef(0, 50, 0);
    GLfloat emission[] = { 1.0f, 1.0f, 0.0f, 1.0 };
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHT1);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
    float Position[] = { -1.0f,1.0f,0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, Position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glNormal3f(0, 0, 0);
    glPopMatrix();
    glPushMatrix();

    glRotatef(-R, 0, 0, 1);
    glTranslatef(0, 50, 0);
    glScalef(3, 3, 3);
    upodiairesh(v[0], v[2], v[1], 4);
    upodiairesh(v[0], v[3], v[2], 4);
    upodiairesh(v[0], v[1], v[3], 4);
    upodiairesh(v[1], v[2], v[3], 4);
    glPopMatrix();


    GLfloat materialspecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat nomaterial[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat materialdiffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat zeroshine[] = {0.0 };
    GLfloat fullshine[] = {100.0 };


    glMaterialfv(GL_FRONT, GL_AMBIENT, nomaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialdiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, nomaterial);
    glMaterialfv(GL_FRONT, GL_SHININESS, zeroshine);
    glMaterialfv(GL_FRONT, GL_EMISSION, nomaterial);

    if (polygontype == true) {
        tetragwna();
    }
    else {
        glPushMatrix();
        glNormal3f(0, 1, 0);
        glTranslatef(0, 5, 0);
        glCallList(edafos);
        glPopMatrix();
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, nomaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialdiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nomaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, zeroshine);

    //spiti toixoi
    glPushMatrix();
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glColor3ub(250, 0, 90);
    glVertex3f(5, 0, 10.0f);
    glVertex3f(-5, 0, 10.0f);
    glVertex3f(-5, 10, 10.0f);
    glVertex3f(5, 10, 10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);
    glColor3ub(250, 0, 90);
    glVertex3f(5, 0, -10.0f);
    glVertex3f(-5, 0, -10.0f);
    glVertex3f(-5, 10, -10.0f);
    glVertex3f(5, 10, -10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glColor3ub(250, 0, 90);
    glVertex3f(5, 0, 10.0f);
    glVertex3f(-5, 0, 10.0f);
    glVertex3f(-5, 0, -10.0f);
    glVertex3f(5, 0, -10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glColor3ub(250, 0, 90);
    glVertex3f(-5, 10, 10.0f);
    glVertex3f(5, 10, 10.0f);
    glVertex3f(5, 10, -10.0f);
    glVertex3f(-5, 10, -10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(250, 0, 90);
    glVertex3f(5, 0, 10.0f);
    glVertex3f(5, 10, 10.0f);
    glVertex3f(5, 10, -10.0f);
    glVertex3f(5, 0, -10.0f);
    glEnd();


   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, nomaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialdiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialspecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, fullshine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nomaterial);

    //spiti skeph
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glColor3ub(105, 105, 105);
    glVertex3f(13.75, 5, 10.0f);
    glVertex3f(5, 10, 10.0f);
    glVertex3f(5, 0, 10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);
    glColor3ub(105, 105, 105);
    glVertex3f(13.75, 5, -10.0f);
    glVertex3f(5, 10, -10.0f);
    glVertex3f(5, 0, -10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(1, -1, 0);
    glColor3ub(105, 105, 105);
    glVertex3f(13.75, 5, -10.0f);
    glVertex3f(13.75, 5, 10.0f);
    glVertex3f(5, 0, 10.0f);
    glVertex3f(5, 0, -10.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(1, 1, 0);
    glColor3ub(105, 105, 105);
    glVertex3f(13.75, 5, -10.0f);
    glVertex3f(13.75, 5, 10.0f);
    glVertex3f(5, 10, 10.0f);
    glVertex3f(5, 10, -10.0f);
    glEnd();
    glPopMatrix();

    if (toggleLight == 0) {



        GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_position[] = { 14, 5, 10.0f };
        GLfloat spot_direction[] = { -5,0.5,0.5 };
        GLfloat emission1[] = { 1.0f, 1.0f, 1.0f, 1.0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
        glMaterialfv(GL_LIGHT0, GL_EMISSION, emission1);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);


        glEnable(GL_LIGHT0);

    }
    else {
        glDisable(GL_LIGHT0);
    }
    glutSwapBuffers();
}

void erwthma1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    draw();
    glPopMatrix();
}

void display()
{
    erwthma1();

}


void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double dasd = 150.0;
    if (width >= height) {
        glOrtho(-dasd * aspect, dasd * aspect, -dasd, dasd, -dasd, dasd);
    }
    else {
        glOrtho(-dasd, dasd, -dasd / aspect, dasd / aspect, -dasd, dasd);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    int menu_id;
    glutInitWindowPosition(500, 500);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ergasia2");
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    myinit();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyPress);
    int polygonmenu = glutCreateMenu(polygons);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("many", 2);

    int shadermenu = glutCreateMenu(shader);
    glutAddMenuEntry("shading flat", 1);
    glutAddMenuEntry("shading smooth", 2);

    int spotlightmenu = glutCreateMenu(spotlight);
    glutAddMenuEntry("spot on", 1);
    glutAddMenuEntry("spot off", 2);

    int menu = glutCreateMenu(menu1);
    glutAddSubMenu("polygon", polygonmenu);
    glutAddSubMenu("spotlight", spotlightmenu);
    glutAddSubMenu("shade", shadermenu);
    glutAddMenuEntry("exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}