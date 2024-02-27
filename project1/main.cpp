
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
static int value=0;
static int epanalipseis=8000;
static int suntelestis=3.0;
static int lastvalue=3;
double left1=0.0;
double right1=500.0;
double bottom=0.0;
double top=500.0;
void myinit(void)
{
/* attributes */
    glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
    glColor3f(0.0, 0.0, 0.0); /* draw in red */
/* set up viewing */
/* 500 x 500 window with origin lower left */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left1,right1,bottom,top);
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_MODELVIEW);
}

void menu(int num)
{
    if (num==0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3b(1.0,1.0,1.0);
        exit(0);
    }
    else
    {
        lastvalue=num;
        if(num==2) {
            epanalipseis=8000;
        }
        if(num==3){
            epanalipseis=10000;
        }
        if(num==4){
            suntelestis=8/3;
        }
        if(num==5)
        {
            suntelestis=3.0;
        }
    }
    glutPostRedisplay();
}
void createMenu(void)
{

    int menuid= glutCreateMenu(menu);
    glutAddMenuEntry("end",0);
    glutAddMenuEntry("8000 points",2);
    glutAddMenuEntry("10000 points",3);
    glutAddMenuEntry( "3/8",4);
    glutAddMenuEntry("1/3",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
float objX = 250;
float objY = 250;
float objSize = 50;
bool dragging = false;
float oldX=0;
float oldY=0;
void mouse( int button, int state, int x, int y )
{
    if( GLUT_DOWN == state && button==GLUT_LEFT_BUTTON)
    {
            dragging = true;
            objX = x;
            objY = y;
    }
    else
    {
        dragging = false;
    }
}
double a=500;
double b=0;
void motion( int x, int y )
{
    int dx,dy;
    if( dragging )
    {
        oldX=objX;
        oldY=objY;
        objX = x;
        objY = y;
        dx=objX-oldX;
        dy=objY-oldY;
    }

    //(objX-oldX),1*(oldY-objY),0);
    glMatrixMode(GL_PROJECTION); //start editing the projection matrix
    glLoadIdentity(); //remove current projection
    left1=left1-dx;
    right1=right1-dx;
    bottom=bottom+dy;
    top=top+dy;
    gluOrtho2D(left1,right1, bottom,top);
    glMatrixMode(GL_MODELVIEW); //back to editing the modelview matrix
    glutPostRedisplay();
}
int r=8000;
int t=0;
void Func(int q)
{
    typedef GLfloat point2[2];
    if(r!=q || t!=0)
    {
    glColor3ub( rand()%255, rand()%255, rand()%255 );
    }
    point2 vertices[5] = { {500,400},{405,469},{441,581},{559,581},{595,469} }; /* A triangle */
    int i, j,k;
    //long rand();       /* standard random number generator */
    point2 p = {500.0, 500.0};  /* An srbitrary initial point */
    glClear(GL_COLOR_BUFFER_BIT);
    for (k = 0; k < q; k++)
    {
        j = rand() % 5; /* pick a vertex at random */
        /* Compute point halfway between vertex and old point */
        p[0] = (p[0] + vertices[j][0]) / 3.0;
        p[1] = (p[1] + vertices[j][1]) / 3.0;
        /* plot new point */
        glBegin(GL_POINTS);
        glVertex2fv(p);
        glEnd();
    }
    glutSwapBuffers(); /* clear buffers */
    r=q;
    t=0;
}
void Func1(int q)
{
    typedef GLfloat point2[2];
    if(r!=q || t!=1)
    {
        glColor3ub( rand()%255, rand()%255, rand()%255 );
    }
    point2 vertices[5] = { {500,400},{405,469},{441,581},{559,581},{595,469}};/* A pentagon */
    int i,j,k;
    //long rand();       /* standard random number generator */
    point2 p = {500.0, 500.0};  /* An srbitrary initial point */
    glClear(GL_COLOR_BUFFER_BIT);
    for (k = 0; k < q; k++)
    {
        j = rand() % 5; /* pick a vertex at random */
        /* Compute point halfway between vertex and old point */
        p[0] = 3.0*p[0]/8.0 + 3.0*vertices[j][0]/8.0;
        p[1] = 3.0*p[1]/8.0 + 3.0*vertices[j][1]/8.0;
        /* plot new point */
        glBegin(GL_POINTS);
        glVertex2fv(p);
        glEnd();
    }
    glutSwapBuffers(); /* clear buffers */
    r=q;
    t=1;
}
void display( void ) {
    glClear(GL_COLOR_BUFFER_BIT);
/* define a point data type */
    if(suntelestis==3.0) {
        Func(epanalipseis);
    }
    else
    {
        Func1(epanalipseis);
    }
/* computes and plots 5000 new points */

}
int main(int argc, char** argv)
{

/* Standard GLUT initialization */

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Pentagons"); /* window title */
    glutDisplayFunc(display); /* display callback invoked when window opened */
    createMenu();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    myinit(); /* set attributes */
    glutMainLoop(); /* enter event loop */
}

