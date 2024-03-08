#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

#define Width 500
#define Height 600

const int LEFT = -Width / 2;
const int RIGHT = Width / 2;
const int TOP = Height / 2;
const int DOWN = -Height / 2;

const int N = 1e5;

class Color {
 public:
  int r, g, b;
  Color();
  Color(int r, int g, int b);
  Color mixWith(Color b);
  friend std::ostream &operator<<(std::ostream &o, Color const &c);
};

Color::Color() {
  r = 255;
  g = 255;
  b = 255;
}

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}

Color Color::mixWith(Color c) {
  return Color((this->r + c.r) / 2, (this->g + c.g) / 2, (this->b + c.b) / 2);
}

std::ostream &operator<<(std::ostream &o, Color const &c) {
  return o << "(r,g,b) : "
           << "(" << c.r << ", " << c.g << ", " << c.b << ")\n";
}

Color color_red(255, 0, 0);
Color color_green(0, 255, 0);
Color color_blue(0, 0, 255);
Color color_black(0, 0, 0);
Color color_white(255, 255, 255);
Color color_yellow(255, 255, 0);
Color color_cyan(0, 255, 255);
Color color_magenta(255, 0, 255);
Color color_purple(128, 0, 128);
Color color_orange(255, 165, 0);
Color color_gray(180, 180, 180);

static void idle(void) { glutPostRedisplay(); }

const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

void myGLConfig() {
  glClearColor(0.1, 0.1, 0.1, 1);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

static void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-Width / 2, Width / 2 - 1, -Height / 2, Height / 2 - 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int circle_x[N];
int circle_y[N];
Color circle_colors[N];
int circlePointsCount;
int r;

void drawPixelCircle(int x, int y, Color c = color_red) {
  circle_x[circlePointsCount] = x;
  circle_y[circlePointsCount] = y;
  circle_colors[circlePointsCount] = c;
  circlePointsCount++;
}

void draw8Way(int x, int y) {
  drawPixelCircle(x, y);
  drawPixelCircle(y, x);
  drawPixelCircle(y, -x);
  drawPixelCircle(-x, y);
  drawPixelCircle(-x, -y);
  drawPixelCircle(-y, -x);
  drawPixelCircle(-y, x);
  drawPixelCircle(x, -y);
}

void drawCircle(int r) {
  int x = 0, y = r;
  int d = 5 - 4 * r;
  
  draw8Way(x, y);

  while (x < y) {
    if (d < 0) {
      d += 4 * (2 * x + 3);
      x++;
    } else {
      d += 4 * (2 * x - 2 * y + 5);
      x++;
      y--;
    }
    draw8Way(x, y);
  }
}


static void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(255, 255, 255);
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex2i(-Width / 2, 0);
  glVertex2i(Width / 2, 0);
  glVertex2i(0, -Height / 2);
  glVertex2i(0, Height / 2);
  glEnd();
  glPopMatrix();
  // Draw here
  glPointSize(5);
  glColor3ub(color_magenta.r, color_magenta.g, color_magenta.b);
  glPushMatrix();

  static float x = 0, y = 0, dx = .5, dy = .3;
  
  for (int i = 0; i < circlePointsCount; i++) {
    glBegin(GL_POINTS);
    glVertex2i(circle_x[i] + x, circle_y[i] + y);
    glEnd();
  }

  x += dx;
  y += dy;
  
  if (x - r < LEFT+100) {
    dx *= -1;
  }

  if (x + r > RIGHT-100) {
    dx *= -1;
  }

  if (y + r > TOP-100) {
    dy *= -1;
  }

  if (y - r < DOWN+100) {
    dy *= -1;
  }

  glPopMatrix();
  // last line
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(10, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutCreateWindow("Circle Drawing");

  glutReshapeFunc(reshape);
  
  drawCircle(100);

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();

  return EXIT_SUCCESS;
}