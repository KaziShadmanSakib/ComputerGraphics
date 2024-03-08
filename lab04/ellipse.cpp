#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
#include <GL/glut.h> 
#include <cstdlib>
#include <stdio.h>
#include<bits/stdc++.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<cstdio>
#include<iostream>
#include<bits/stdc++.h>


#define WIDTH 1000
#define HEIGHT 1000

void drawEllipse(int cx, int cy, int a, int b);
void draw4way(int cx, int cy, int x, int y);
void bounceEllipse();


static void idle(void)
{
    static bool spacebarPressed = false;
    if (spacebarPressed) {
        bounceEllipse();
        spacebarPressed = false;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
    if (key == 'z') {
        glutPostRedisplay();
        glutIdleFunc(idle);
        static bool spacebarPressed = false;
        spacebarPressed = true;
    }
}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2 - 1, -HEIGHT / 2, HEIGHT / 2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH / 2, 0);
    glVertex2i(WIDTH / 2, 0);
    glVertex2i(0, -HEIGHT / 2);
    glVertex2i(0, HEIGHT / 2);
    glEnd();

    glPointSize(1);
    glBegin(GL_POINTS);

    bounceEllipse();
    
    glEnd();

    glutSwapBuffers();
}


int cx, cy;
void drawEllipse(int cx, int cy, int a, int b)
{
    int x = 0, y = b;
    int d = 4 * (b*b - a*a*b) + a*a;
    int delE = 4*b*b * (2*x + 3);
    int delSE = 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);

    draw4way(cx,cy, x, y);

    while(2*b*b*(x + 1) < a*a*(2*y - 1)){
        if(d < 0){
            d += 4*b*b*(2*x + 3);
            x++;
        }
        else{
            d += 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);
            x++;
            y--;
        }
        draw4way(cx,cy, x, y);
    }

    while(y > 0){
        if(d < 0){
            d += 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);
            x++;
            y--;
        }
        else{
            d += 4*a*a * (2 - 2*y);
            y--;
        }
        draw4way(cx,cy, x, y);
    }
}


void draw4way(int cx, int cy, int x, int y)
{
    glColor3d(0, 102, 0);
    glVertex2i(cx+x, cy+y);
    glColor3d(255, 255, 0);
    glVertex2i(cx+-x, cy+y);
    glColor3d(204, 0, 0);
    glVertex2i(cx+-x, cy+-y);
    glColor3d(102, 0, 51);
    glVertex2i(cx+x, cy+-y);
}

int min_return(int a, int b){
    if(a>b){
        return b;
    }
    else{
        return a;
    }
}

int ACCELERATION = 9.8;
int BOUNCE_FACTOR = 50;
void bounceEllipse(){
    int cx = 120;
    int cy = 0;
    int a = 60;
    int b = 60;
    int r = a;
    int yMin = -HEIGHT / 2;
    int yMax = HEIGHT / 2 - 1;
    while(getchar()){
        //going up
        while (cy > yMin+BOUNCE_FACTOR){
            getchar();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBegin(GL_POINTS);
            int tmp_b = min_return(b, cy-yMin);
            drawEllipse(cx, cy, sqrt(2*r*r-tmp_b*tmp_b), tmp_b);
            //decreasing acceleration
            cy = cy - (1 - cy/ACCELERATION);
            glEnd();
            glutSwapBuffers();
        }
        //going down
        while(cy < 0){
            getchar();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBegin(GL_POINTS);
            int tmp_b = min_return(b, cy-yMin);
            drawEllipse(cx, cy, sqrt(2*r*r-tmp_b*tmp_b), tmp_b);
            //increasing acceleration
            cy = cy + (1 - cy/ACCELERATION);
            glEnd();
            glutSwapBuffers();

        }
    }

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ellipse Drawing");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
//g++ ellipse.cpp -o ellipse -lglut -lGLU -lGL