/* Kazi Shadman Sakib */
/* Roll: 97 */

#include <GL/glut.h>
 
#include <cstdlib>
#include <stdio.h>
#include<bits/stdc++.h>
#include <math.h>

#include <bits/stdc++.h>
using namespace std;

#define LINE_COUNT 360
 
int lineCoords[LINE_COUNT][4];
 
#define Height 512
#define Width 512
#define RADIUS 200

/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2-1, -Height/2, Height/2-1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

// find zone of the lines
int findZone(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int zone;
    
    if (abs(dx) >= abs(dy)) {
        if (dx >= 0 && dy >= 0){
            zone = 0;
        }
        if (dx >= 0 && dy < 0){
             zone = 7;
        }
        if (dx < 0 && dy >= 0){
             zone = 3;
        }
        if (dx < 0 && dy < 0){
            zone = 4;
        }
    } 
    
    else {
        if (dx >= 0 && dy >= 0){
            zone = 1;
        }
        if (dx >= 0 && dy < 0){
            zone = 6;
        }
        if (dx < 0 && dy >= 0){
            zone = 2;
        }
        if (dx < 0 && dy < 0){
             zone = 5;
        }
    }
    return zone;
}

void drawPixel (int x, int y, int zone){
    switch (zone){
    case 0:
        glColor3d(0, 102, 0);
        glVertex2i(x, y);
        break;
    case 1:
        glColor3d(0, 102, 102);
        glVertex2i(y, x);
        break;
    case 2:
        glColor3d(51, 0, 102);
        glVertex2i(-y, x);
        break;
    case 3:
        glColor3d(255, 255, 0);
        glVertex2i(-x, y);
        break;
    case 4:
        glColor3d(204, 0, 0);
        glVertex2i(-x, -y);
        break;
    case 5:
        glColor3d(255, 153, 255);
        glVertex2i(-y, -x);
        break;
    case 6:
        glColor3d(102, 102, 0);
        glVertex2i(y, -x);
        break;
    case 7:
        glColor3d(102, 0, 51);
        glVertex2i(x, -y);
        break;
    }
}

void drawLine0 (int x0, int y0, int x1, int y1, int zone){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dy - dx;
    int de = 2 * dy;
    int dne = 2 * (dy - dx);
    while (x <= x1){
        drawPixel (x, y, zone);
        
        if (d < 0){
            ++x;
            d += de;
        }

        else
        {
            ++x;
            ++y;
            d += dne;
        }
    }
}

// from any zone to zone 0
void drawLine (int x0, int y0, int x1, int y1){
    int zone = findZone(x0, y0, x1, y1);

    cout<< zone << endl;

    switch (zone){
    case 0:
        drawLine0(x0, y0, x1, y1, zone);
        break;
    case 1:
        drawLine0(y0, x0, y1, x1, zone);
        break;
    case 2:
        drawLine0(y0, -x0, y1, -x1, zone);
        break;
    case 3:
        drawLine0(-x0, y0, -x1, y1, zone);
        break;
    case 4:
        drawLine0(-x0, -y0, -x1, -y1, zone);
        break;
    case 5:
        drawLine0(-y0, -x0, -y1, -x1, zone);
        break;
    case 6:
        drawLine0(-y0, x0, -y1, x1, zone);
        break;
    case 7:
        drawLine0(x0, -y0, x1, -y1, zone);
        break;
    }
}


int x_0, x_1, y_0, y_1;

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



static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-Width/2, 0);
    glVertex2i(Width/2-1, 0);
    glVertex2i(0, -Height/2);
    glVertex2i(0, Height/2-1);
    glEnd();


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

static void idle(void){
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(Width,Height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("8 way symmetry efficiently"); 

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

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
///g++ Draw8wayEfficient.cpp -o Draw8wayEfficient -lglut -lGLU -lGL
