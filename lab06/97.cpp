/*Kazi Shadman Sakib
Roll: 097*/
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLUT32.lib")
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include<cstdio>
#include<iostream>
#include <iostream>
#include <ctime>
#include<bits/stdc++.h>
using namespace std;
#define HEIGHT 720
#define WIDTH 1080
 
#define LINE_COUNT 10
 
struct Point3D {
    float x, y, z;
    Point3D(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    Point3D(){}
};


struct Point2D {
    int x, y;
    Point2D(int x, int y) {
            this->x = x;
            this->y = y;
        }
    Point2D(){}
};
  
vector<Point3D> POINT3D;
vector<Point2D> POINT2D;
 
 
//cube size, cop to pp, pp to object point
int A = 300, d = 600, L = 400;
 
void drawLine();
void findZone(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);
void drawPixel(int x, int y, int zone);
void generatePoint();
void generateProjection(float transformationMatrix[][4]);
void generateCube();
 
 
static void resize(int width, int height){
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH / 2, 0);
    glVertex2i(WIDTH / 2, 0);
    glVertex2i(0, -HEIGHT / 2);
    glVertex2i(0, HEIGHT / 2);
    glEnd();
 
    glPointSize(2);
    glBegin(GL_POINTS);
 
 
 
    float transformationMatrix[4][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0,float(-1.0/d), 0.0},
    };
 
    generateProjection(transformationMatrix);
    generateCube();
 
    glEnd();
 
    glutSwapBuffers();
}
 
static void idle(void){
    glutPostRedisplay();
}
 
void generatePoint() {
    POINT3D.push_back(Point3D(-A, -A, A));
    POINT3D.push_back(Point3D(A, -A, A));
    POINT3D.push_back(Point3D(A, A, A));
    POINT3D.push_back(Point3D(-A, A, A));
    POINT3D.push_back(Point3D(-A, -A, -A));
    POINT3D.push_back(Point3D(A, -A, -A));
    POINT3D.push_back(Point3D(A, A, -A));
    POINT3D.push_back(Point3D(-A, A, -A));
 
}
 
 
void generateProjection(float transformationMatrix[][4]){
    for(int i = 0; i<8; i++) {
        float x = transformationMatrix[0][0]*POINT3D[i].x + transformationMatrix[0][1]*POINT3D[i].y + transformationMatrix[0][2]*(POINT3D[i].z - d - L) + transformationMatrix[0][3];
        float y = transformationMatrix[1][0]*POINT3D[i].x + transformationMatrix[1][1]*POINT3D[i].y + transformationMatrix[1][2]*(POINT3D[i].z - d - L) + transformationMatrix[1][3];
        float z = transformationMatrix[2][0]*POINT3D[i].x + transformationMatrix[2][1]*POINT3D[i].y + transformationMatrix[2][2]*(POINT3D[i].z - d - L) + transformationMatrix[2][3];
        float w = transformationMatrix[3][0]*POINT3D[i].x + transformationMatrix[3][1]*POINT3D[i].y + transformationMatrix[3][2]*(POINT3D[i].z - d - L) + transformationMatrix[3][3];
 
        POINT2D.push_back(Point2D(x/w, y/w));
    }
}
void generateCube(){
    findZone(POINT2D[0].x, POINT2D[0].y, POINT2D[1].x, POINT2D[1].y);
    findZone(POINT2D[2].x, POINT2D[2].y, POINT2D[1].x, POINT2D[1].y);
    findZone(POINT2D[3].x, POINT2D[3].y, POINT2D[2].x, POINT2D[2].y);
    findZone(POINT2D[0].x, POINT2D[0].y, POINT2D[3].x, POINT2D[3].y);
 
    findZone(POINT2D[4].x, POINT2D[4].y, POINT2D[5].x, POINT2D[5].y);
    findZone(POINT2D[6].x, POINT2D[6].y, POINT2D[5].x, POINT2D[5].y);
    findZone(POINT2D[6].x, POINT2D[6].y, POINT2D[7].x, POINT2D[7].y);
    findZone(POINT2D[4].x, POINT2D[4].y, POINT2D[7].x, POINT2D[7].y);
 
    findZone(POINT2D[0].x, POINT2D[0].y, POINT2D[4].x, POINT2D[4].y);
    findZone(POINT2D[5].x, POINT2D[5].y, POINT2D[1].x, POINT2D[1].y);
    findZone(POINT2D[2].x, POINT2D[2].y, POINT2D[6].x, POINT2D[6].y);
    findZone(POINT2D[3].x, POINT2D[3].y, POINT2D[7].x, POINT2D[7].y);

    POINT2D.clear();
    POINT3D.clear();
}
 
 
void drawLine(void){    
    int x0 = 0, y0 = 0, x1, y1;
    for(int i=0; i<360; i=i+5) {
        findZone(x0, y0, (int)(200.0*cos(i)), (int)(200.0*sin(i)));
    } 
}
 
void findZone(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    
    // 0, 3, 4, 7
    if (abs(dx) >= abs(dy)){ 
        // zone 0
        if (dx >= 0 && dy >= 0){
            glColor3ub(255, 255, 0); // yellow 
            drawLine0(x0, y0, x1, y1, 0);
        }
        // zone 3
        else if (dx < 0 && dy >= 0){ 
            glColor3ub(0, 100, 100); // cyan
            drawLine0(-x0, y0, -x1, y1, 3);
        }
        // zone 4
        else if (dx < 0 && dy < 0){ 
            glColor3ub(255, 191, 0); // orange
            drawLine0(-x0, -y0, -x1, -y1, 4);
        }
        else{ 
            // zone 7
            glColor3ub(128, 128, 128); // gray
            drawLine0(x0, -y0, x1, -y1, 7);
        }
    }

    // 1, 2, 5, 6
    else{ 
        // zone 1
        if (dx >= 0 && dy >= 0){ 
            glColor3ub(255, 255, 255); // white
            drawLine0(y0, x0, y1, x1, 1);
        }
        //zone 2
        else if (dx < 0 && dy >= 0){
            glColor3ub(255, 0, 0); // red
            drawLine0(y0, -x0, y1, -x1, 2);
        }
        //zone 5
        else if (dx < 0 && dy < 0){
            glColor3ub(0, 255, 0); // green
            drawLine0(-y0, -x0, -y1, -x1, 5);
        }
        //zone 6
        else{
            glColor3ub(0, 0, 255); // blue
            drawLine0(-y0, x0, -y1, x1, 6);
        }
    }
}
 
void drawLine0(int x0, int y0, int x1, int y1, int zone){
 
    int dx = x1 - x0, dy = y1 - y0;
    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;
 
    drawPixel(x0, y0, zone);
 
    while (x < x1){
        // delE
        if (d < 0){ 
            d += delE;
            x++;
        }
        // delNE
        else{ 
            d += delNE;
            x++;
            y++;
        }
 
        drawPixel(x, y, zone);
    }
}
 
 
void drawPixel(int x, int y, int zone){
    switch (zone){
        case 0:
            glVertex2i(x, y);
            break;
        case 1:
            glVertex2i(y, x);
            break;
        case 2:
            glVertex2i(-y, x);
            break;
        case 3:
            glVertex2i(-x, y);
            break;
        case 4:
            glVertex2i(-x, -y);
            break;
        case 5:
            glVertex2i(-y, -x);
            break;
        case 6:
            glVertex2i(y, -x);
            break;
        case 7:
            glVertex2i(x, -y);
            break;
 
    }
 
}

void specialKey(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            d+=10;
            break;
        case GLUT_KEY_DOWN:
            d-=10;
        case GLUT_KEY_LEFT:
            L+= 10;
            break;
        case GLUT_KEY_RIGHT:
            L -= 10;
            break;
    }
}
 
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Experiment 05");
 
    generatePoint();
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKey);
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
//g++ 97.cpp -o projection -lglut -lGLU -lGL