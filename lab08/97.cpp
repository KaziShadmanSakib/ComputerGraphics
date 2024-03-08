/*Kazi Shadman Sakib
Roll: 097*/
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;
 
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;
 
typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int imagesize;
    int xresolution;
    int yresolution;
    unsigned int ncolors;
    unsigned int importantcolors;
} BMPInfoHeader;
 
void loadBMP(const char* filename, int at_window) {
    FILE* file = fopen(filename, "rb");
 
    if (!file) {
        printf("Error: Unable to open BMP file.\n");
        return;
    }
 
    BMPHeader header;
    fread(&header.type, sizeof(unsigned short), 1, file);
 
    if (header.type != 0x4D42) {
        printf("Error: Invalid BMP file.\n");
        fclose(file);
        return;
    }
 
    fread(&header.size, sizeof(unsigned int), 1, file);
    fread(&header.reserved1, sizeof(unsigned short), 1, file);
    fread(&header.reserved2, sizeof(unsigned short), 1, file);
    fread(&header.offset, sizeof(unsigned int), 1, file);
 
    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);
 
    unsigned char* data = new unsigned char[infoHeader.imagesize];
    fseek(file, header.offset, SEEK_SET);
    fread(data, sizeof(unsigned char), infoHeader.imagesize, file);
 
    fclose(file);

    for(int i = 0; i < infoHeader.imagesize; i += 3) {
        if(at_window == 2) {
            data[i] = 255 - data[i];
            data[i + 1] = 255 - data[i];
            data[i + 2] = 255 - data[i];
        }

        else if(at_window >= 3) {

            double B = data[i];
            double G = data[i + 1];
            double R = data[i + 2];

            // double _R = R, _G = G, _B = B;

            double _R = R / 255;
            double _G = G / 255;
            double _B = B / 255;

            double Cmax = max({_R, _G, _B});
            double Cmin = min({_R, _G, _B});
            double del = Cmax - Cmin;

            double H, S, V;

            if(at_window == 3) {
                if(Cmax == _R) {
                    H = ((_G - _B) / del) * 60;
                    H += 120;
                }
                else {
                    H = (_R - _G) / del;
                    H *= 60;
                    H += 240;
                }

                if(H < 0) H += 360;
                H /= 360;
                H *= 240;

                data[i] = data[i + 1] = data[i + 2] = H;
            }

            if(at_window == 4) {
                if(Cmax == 0) {
                    S = 0;
                } else {
                    S = del / Cmax;
                }

                S *= 240;
                data[i] = data[i + 1] = data[i + 2] = S;
            }

            if(at_window == 5) {
                V = Cmax * 240;
                data[i] = data[i + 1] = data[i + 2] = V;
            }
        }
    }
 
    glEnable(GL_TEXTURE_2D);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, infoHeader.width, infoHeader.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
 
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);
    glEnd();
 
    glFlush();
}
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Window 1, Original BMP
    glutInitWindowSize(800, 600);
    glutCreateWindow("BMP Image");
    glutDisplayFunc(display);
    loadBMP("image.bmp", 1);

    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Window 2, Negative Image
    glutInitWindowSize(800, 600);
    glutCreateWindow("Negative Image");
    glutDisplayFunc(display);

    loadBMP("image.bmp", 2);

    // Window 3, S
    glutInitWindowSize(800, 600);
    glutCreateWindow("H");
    glutDisplayFunc(display);

    loadBMP("image.bmp", 3);
   
    // Window 4, S
    glutInitWindowSize(800, 600);
    glutCreateWindow("S");
    glutDisplayFunc(display);

    loadBMP("image.bmp", 4);

    // Window 5, V
    glutInitWindowSize(800, 600);
    glutCreateWindow("V");
    glutDisplayFunc(display);

    loadBMP("image.bmp", 5);


    glutMainLoop();
 
    return 0;
}

//g++ 97.cpp -o bmp -lglut -lGLU -lGL