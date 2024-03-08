 /*
 *   A c++ program for the line drawing algorithm using GLUT
 *      and using Bresenham's Line Drawing Algorithm.
 *
 *   This algorithm randomly generates a set of endpoints and
 *      calls drawLine() function for each two endpoint pairs
 *      and draws a line between the endpoints. The lines are
 *      colored according to their zone.
 */
 
#include <GL/glut.h>
 
#include <cstdlib>
#include <stdio.h>
#include<bits/stdc++.h>
#include <math.h>
 
#define LINE_COUNT 360
 
int lineCoords[LINE_COUNT][4];
 
#define Height 512
#define Width 512
#define RADIUS 200
 
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2-1, -Height/2, Height/2-1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
 
 
// Function to draw the pixels
void drawPixel(int x, int y)
{
    glVertex2i(x, y);
}
 
// Function to draw zone-0 line
void drawLine0(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dy - dx;
    int del_e = 2 * dy;
    int del_ne = 2 * (dy - dx);
    while (x < x1)
    {
        if (d < 0)
        {
            d += del_e;
            x++;
        }
        else
        {
            d += del_ne;
            x++;
            y++;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-1 line
void drawLine1(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = dy - 2 * dx;
    int del_n = -2 * dx;
    int del_ne = 2 * (dy - dx);
    while (y < y1)
    {
        if (d > 0)
        {
            d += del_n;
            y++;
        }
        else
        {
            d += del_ne;
            x++;
            y++;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-2 line
void drawLine2(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = -2 * dx - dy;
    int del_n = -2 * dx;
    int del_nw = -2 * (dx + dy);
    while (y < y1)
    {
        if (d < 0)
        {
            d += del_n;
            y++;
        }
        else
        {
            d += del_nw;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-3 line
void drawLine3(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = -2 * dx + dy;
    int del_w = -2 * dy;
    int del_nw = -2 * (dx + dy);
    while (x > x1)
    {
        if (d > 0)
        {
            d += del_w;
            x--;
        }
        else
        {
            d += del_nw;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-4 line
void drawLine4(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = dx - 2 * dy;
    int del_w = -2 * dy;
    int del_sw = -2 * (dy - dx);
    while (x > x1)
    {
        if (d < 0)
        {
            d += del_w;
            x--;
        }
        else
        {
            d += del_sw;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-5 line
void drawLine5(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx - dy;
    int del_s = 2 * dx;
    int del_sw = -2 * (dy - dx);
    while (y > y1)
    {
        if (d > 0)
        {
            d += del_s;
            y--;
        }
        else
        {
            d += del_sw;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-6 line
void drawLine6(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx + dy;
    int del_s = 2 * dx;
    int del_se = 2 * (dx + dy);
    while (y > y1)
    {
        if (d < 0)
        {
            d += del_s;
            y--;
        }
        else
        {
            d += del_se;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}
 
// Function to draw zone-7 line
void drawLine7(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx - dy;
    int del_e = 2 * dy;
    int del_se = 2 * (dx + dy);
    while (x < x1)
    {
        if (d > 0)
        {
            d += del_e;
            x++;
        }
        else
        {
            d += del_se;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}
 
// Function to find the zone value of the line
int findZone(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int zone;
    if (abs(dx) >= abs(dy)) {
        if (dx >= 0 && dy >= 0) zone = 0;
        if (dx >= 0 && dy < 0) zone = 7;
        if (dx < 0 && dy >= 0) zone = 3;
        if (dx < 0 && dy < 0) zone = 4;
    } else {
        if (dx >= 0 && dy >= 0) zone = 1;
        if (dx >= 0 && dy < 0) zone = 6;
        if (dx < 0 && dy >= 0) zone = 2;
        if (dx < 0 && dy < 0) zone = 5;
    }
 
    switch (zone)
    {
    case 0:
        glColor3ub(255, 0, 0);
        drawLine0(x0, y0, x1, y1);
        break;
    case 1:
        glColor3ub(0, 255, 0);
        drawLine1(x0, y0, x1, y1);
        break;
    case 2:
        glColor3ub(0, 0, 255);
        drawLine2(x0, y0, x1, y1);
        break;
    case 3:
        glColor3ub(255, 0, 255);
        drawLine3(x0, y0, x1, y1);
        break;
    case 4:
        glColor3ub(255, 255, 0);
        drawLine4(x0, y0, x1, y1);
        break;
    case 5:
        glColor3ub(0, 255, 255);
        drawLine5(x0, y0, x1, y1);
        break;
    case 6:
        glColor3ub(255, 255, 255);
        drawLine6(x0, y0, x1, y1);
        break;
    case 7:
        glColor3ub(128, 128, 0);
        drawLine7(x0, y0, x1, y1);
        break;
    }
    return zone;
}
 
 
void drawLine(int x0, int y0, int x1, int y1)
{
//    printf("(%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
//    printf("Zone: %d\n", zone);
    glColor3ub(128, 128, 128);
    glPointSize(200.0);
    glVertex2i(x0, y0);
    glColor3ub(69, 69, 69);
    glVertex2i(x1, y1);
    findZone(x0, y0, x1, y1);
}
 
int generateRandX() {
    return (rand() % Width) - Width/2;
}
 
int generateRandY() {
    return (rand() % Height) - Height/2;
}
 
void generateLines() {
    for (int i = 0; i < LINE_COUNT; i++) {
        lineCoords[i][0] = generateRandX();
        lineCoords[i][1] = generateRandY();
        lineCoords[i][2] = generateRandX();
        lineCoords[i][3] = generateRandY();
    }
}
 

int x_0, x_1, y_0, y_1;
 
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-Width/2, 0);
    glVertex2i(Width/2-1, 0);
    glVertex2i(0, -Height/2);
    glVertex2i(0, Height/2-1);
    glEnd();
    

    //display circle
    glPointSize(2);
    glBegin(GL_POINTS);
    
    for(int i=0;i<360;i++){
        glColor3b(0,0,1);
        glVertex2d(lineCoords[i][0], lineCoords[i][1]);
        glColor3b(0,1,0);
        glVertex2d(lineCoords[i][2], lineCoords[i][3]);
        glColor3b(1,1,1);
        drawLine(lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3]);
    }

    glEnd();
 
 
    glutSwapBuffers();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 

 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(Width,Height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
 
    glutCreateWindow("8 way symmetry and a circle");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    //use this function to generate 
    //generateLines();
    
    // equation used for drawing a circle
    for (int i = 0; i < 360; i++){
        lineCoords[i][0] = 0;
        lineCoords[i][1] = 0;
        lineCoords[i][2] = RADIUS * cos(i);
        lineCoords[i][3] = RADIUS * sin(i);
    }
    
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
///g++ Draw8way.cpp -o Draw8way -lglut -lGLU -lGL