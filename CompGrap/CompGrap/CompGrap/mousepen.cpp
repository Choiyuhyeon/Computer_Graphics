#include "gl/glut.h"
#include <cstdio>
#include <vector>

struct Vec2 {
    float x, y;
};

struct Pen {
    Vec2 position;
    float thickness;
};

std::vector<Pen> pens;
float currentThickness = 1.0f;

void drawPen(const Pen& pen) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(pen.thickness);
    glBegin(GL_POINTS);
    glVertex2f(pen.position.x, pen.position.y);
    glEnd();
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& pen : pens) {
        drawPen(pen);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Pen newPen;
        newPen.position.x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
        newPen.position.y = -(2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT) + 1.0f;
        newPen.thickness = currentThickness;
        pens.push_back(newPen);
        glutPostRedisplay();
    }
}

void mouseMotion(int x, int y) {
    Pen newPen;
    newPen.position.x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
    newPen.position.y = -(2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT) + 1.0f;
    newPen.thickness = currentThickness;
    pens.push_back(newPen);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        currentThickness = 1.0f;
        break;
    case '2':
        currentThickness = 2.0f;
        break;
    case '3':
        currentThickness = 3.0f;
        break;
    case '4':
        currentThickness = 4.0f;
        break;
    case '5':
        currentThickness = 5.0f;
        break;
    case 'R':
    case 'r':
        pens.clear();
        glutPostRedisplay();
        break;
    case 27: // ESC
        exit(0);
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    glutCreateWindow("OpenGL Pen Drawing");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
