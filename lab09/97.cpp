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
#define WIDTH 512
#define HEIGHT 512
 
#define LINE_COUNT 10
 
struct Point2D {
    int x, y;
    Point2D(int _x, int _y) {
            x = _x;
            y = _y;
        }
    Point2D(){}
};
 
struct Point3D {
    float x, y, z;
    Point3D(float _x, float _y, float _z) {
            x = _x;
            y = _y;
            z = _z;
        }
    Point3D(){}
};
 
vector<Point3D> POINT3D;
vector<Point3D> POINT3D2;
vector<Point2D> P2D;

 
 
int d = 6000, L = 6000, A = 200;
float thetaX = 0, thetaY = 0, thetaZ = 0;
 

void generatePoints();
void generateProjection(float matrix[][4]);
void makeCube();
void specialKey(int key, int x, int y);
void rotate();
void drawLine();
void findZone(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);
void drawPixel(int x, int y, int zone);
bool crossProduct(Point3D a, Point3D b, Point3D c);

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);
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
 
    glPointSize(2);
    glBegin(GL_POINTS);
 
 
    rotate();
   
    float matrix[4][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0,float(-1.0/d), 0.0},
    };
   
    generateProjection(matrix);
    makeCube();
 
    glEnd();
 
   
   
    glutSwapBuffers();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
void generatePoints() {
    POINT3D.push_back(Point3D(-A, -A, A));
    POINT3D.push_back(Point3D(A, -A, A));
    POINT3D.push_back(Point3D(A, A, A));
    POINT3D.push_back(Point3D(-A, A, A));
    POINT3D.push_back(Point3D(-A, -A, -A));
    POINT3D.push_back(Point3D(A, -A, -A));
    POINT3D.push_back(Point3D(A, A, -A));
    POINT3D.push_back(Point3D(-A, A, -A));
 
}
 
 
void generateProjection(float matrix[][4]){
    for(int i = 0; i<8; i++) {
        float x = matrix[0][0]*POINT3D2[i].x + matrix[0][1]*POINT3D2[i].y + matrix[0][2]*(POINT3D2[i].z - d - L) + matrix[0][3];
        float y = matrix[1][0]*POINT3D2[i].x + matrix[1][1]*POINT3D2[i].y + matrix[1][2]*(POINT3D2[i].z - d - L) + matrix[1][3];
        float z = matrix[2][0]*POINT3D2[i].x + matrix[2][1]*POINT3D2[i].y + matrix[2][2]*(POINT3D2[i].z - d - L) + matrix[2][3];
        float w = matrix[3][0]*POINT3D2[i].x + matrix[3][1]*POINT3D2[i].y + matrix[3][2]*(POINT3D2[i].z - d - L) + matrix[3][3];
 
        P2D.push_back(Point2D(x/w, y/w));
    }
}

bool crossProduct(Point3D a, Point3D b, Point3D c){

    float x0 = a.x-b.x, y0 = a.y-b.y, z0 = a.z-b.z;
    float x1 = c.x-b.x, y1 = c.y-b.y, z1 = c.z-b.z;
    float x = y0*z1 - z0*y1;
    float y = z0*x1 - x0*z1;
    float z = x0*y1 - y0*x1;

    return z > 0;
}

void makeCube(){
    //1
    if(crossProduct(POINT3D2[2], POINT3D2[1], POINT3D2[0])){
        findZone(P2D[0].x, P2D[0].y, P2D[1].x, P2D[1].y);
        findZone(P2D[2].x, P2D[2].y, P2D[1].x, P2D[1].y);
        findZone(P2D[3].x, P2D[3].y, P2D[2].x, P2D[2].y);
        findZone(P2D[0].x, P2D[0].y, P2D[3].x, P2D[3].y);
    }
    //2
    if(crossProduct(POINT3D2[4], POINT3D2[5], POINT3D2[6])){
        findZone(P2D[4].x, P2D[4].y, P2D[5].x, P2D[5].y);
        findZone(P2D[6].x, P2D[6].y, P2D[5].x, P2D[5].y);
        findZone(P2D[6].x, P2D[6].y, P2D[7].x, P2D[7].y);
        findZone(P2D[4].x, P2D[4].y, P2D[7].x, P2D[7].y);
    }
    //3
    if(crossProduct(POINT3D2[1], POINT3D2[5], POINT3D2[4])){
        findZone(P2D[4].x, P2D[4].y, P2D[5].x, P2D[5].y);
        findZone(P2D[0].x, P2D[0].y, P2D[1].x, P2D[1].y);
        findZone(P2D[0].x, P2D[0].y, P2D[4].x, P2D[4].y);
        findZone(P2D[5].x, P2D[5].y, P2D[1].x, P2D[1].y);
    }
 
    //4
    if(crossProduct(POINT3D2[6], POINT3D2[5], POINT3D2[1])){
        findZone(P2D[1].x, P2D[1].y, P2D[5].x, P2D[5].y);
        findZone(P2D[1].x, P2D[1].y, P2D[2].x, P2D[2].y);
        findZone(P2D[6].x, P2D[6].y, P2D[2].x, P2D[2].y);
        findZone(P2D[5].x, P2D[5].y, P2D[6].x, P2D[6].y);
    }
 
    //5
    if(crossProduct(POINT3D2[2], POINT3D2[3], POINT3D2[7])){
        findZone(P2D[2].x, P2D[2].y, P2D[6].x, P2D[6].y);
        findZone(P2D[2].x, P2D[2].y, P2D[3].x, P2D[3].y);
        findZone(P2D[7].x, P2D[7].y, P2D[6].x, P2D[6].y);
        findZone(P2D[7].x, P2D[7].y, P2D[3].x, P2D[3].y);
    }
 
    //6
    if(crossProduct(POINT3D2[4], POINT3D2[7], POINT3D2[3])){
        findZone(P2D[4].x, P2D[4].y, P2D[7].x, P2D[7].y);
        findZone(P2D[0].x, P2D[0].y, P2D[4].x, P2D[4].y);
        findZone(P2D[0].x, P2D[0].y, P2D[3].x, P2D[3].y);
        findZone(P2D[3].x, P2D[3].y, P2D[7].x, P2D[7].y);
    }
 
    POINT3D2.clear();
    P2D.clear();
}

void rotate() {
    float matrix[4][4] = {
        {cos(thetaY)*cos(thetaZ), sin(thetaX)*sin(thetaY)*cos(thetaZ)-cos(thetaX)*sin(thetaZ), cos(thetaX)*sin(thetaY)*cos(thetaZ)+sin(thetaX)*sin(thetaZ) },
        { cos(thetaY)*sin(thetaZ), sin(thetaX)*sin(thetaY)*sin(thetaZ)+cos(thetaX)*cos(thetaZ), cos(thetaX)*sin(thetaY)*sin(thetaZ)-sin(thetaX)*cos(thetaZ) },
        { -sin(thetaY), sin(thetaX)*cos(thetaY), cos(thetaX)*cos(thetaY) },
    };
 
    for(int i = 0; i<8; i++) {
        float x = matrix[0][0]*POINT3D[i].x + matrix[0][1]*POINT3D[i].y + matrix[0][2]*(POINT3D[i].z);
        float y = matrix[1][0]*POINT3D[i].x + matrix[1][1]*POINT3D[i].y + matrix[1][2]*(POINT3D[i].z);
        float z = matrix[2][0]*POINT3D[i].x + matrix[2][1]*POINT3D[i].y + matrix[2][2]*(POINT3D[i].z);
        float w = matrix[3][0]*POINT3D[i].x + matrix[3][1]*POINT3D[i].y + matrix[3][2]*(POINT3D[i].z);
 
        POINT3D2.push_back(Point3D(x, y, z));
    }
}
 
void drawLine(void)
{    
    int x0 = 0, y0 = 0, x1, y1;
    for(int i=0; i<360; i=i+5) {
        findZone(x0, y0, (int)(200.0*cos(i)), (int)(200.0*sin(i)));
    }
}
 
void findZone(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    glColor3ub(255, 255, 255); // white
 
    if (abs(dx) >= abs(dy))
    { // 0, 3, 4, 7
        if (dx >= 0 && dy >= 0){ // zone 0
            glColor3ub(255, 255, 255); // white
            drawLine0(x0, y0, x1, y1, 0);
        }
        else if (dx < 0 && dy >= 0){ // zone 3
            glColor3ub(255, 0, 0); // red
            drawLine0(-x0, y0, -x1, y1, 3);
        }
        else if (dx < 0 && dy < 0){ // zone 4
            glColor3ub(0, 255, 0); // green
            drawLine0(-x0, -y0, -x1, -y1, 4);
        }
        else{ // zone 7
            glColor3ub(0, 0, 255); // blue
            drawLine0(x0, -y0, x1, -y1, 7);
        }
    }
    else
    { // 1, 2, 5, 6
        if (dx >= 0 && dy >= 0){ // zone 1
            glColor3ub(255, 255, 0); // yellow
            drawLine0(y0, x0, y1, x1, 1);
        }
        else if (dx < 0 && dy >= 0){
            glColor3ub(0, 100, 100); // cyan
            drawLine0(y0, -x0, y1, -x1, 2);
        }
        else if (dx < 0 && dy < 0){
            glColor3ub(255, 191, 0); // orange
            drawLine0(-y0, -x0, -y1, -x1, 5);
        }
        else{
             glColor3ub(128, 128, 128); // gray
            drawLine0(-y0, x0, -y1, x1, 6);
        }
    }
}
 
void drawLine0(int x0, int y0, int x1, int y1, int zone)
{
 
    int dx = x1 - x0, dy = y1 - y0;
    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;
 
    drawPixel(x0, y0, zone);
 
    while (x < x1)
    {
        if (d < 0)
        { // delE
            d += delE;
            x++;
        }
        else
        { // delNE
            d += delNE;
            x++;
            y++;
        }
 
        drawPixel(x, y, zone);
    }
}
 
 
void drawPixel(int x, int y, int zone)
{
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
 
void specialKey(int key, int x, int y) {
    switch (key){
        case GLUT_KEY_UP:
            thetaX += 0.1;
            break;
        case GLUT_KEY_DOWN:
            thetaX -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            thetaY += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            thetaY -= 0.1;
            break;
        case GLUT_KEY_F1:
            thetaZ += 0.01;
            break;
        case GLUT_KEY_F2:
            thetaZ -= 0.01;
            break;
        case GLUT_KEY_F3:
            d += 10;
            break;
        case GLUT_KEY_F4:
            d -= 10;
            break;
        case GLUT_KEY_F5:
            L += 10;
            break;
        case GLUT_KEY_F6:
            L -= 10;
            break;
    }
   
}
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Experiment 08");
 
    generatePoints();
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKey);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
//g++ 97.cpp -o rotation -lglut -lGLU -lGL