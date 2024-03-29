#include "gl/glut.h"
#include <cstdio>

struct Vec2 {
    float x, y;
};

Vec2 linePt[4] = {
    {-0.3f, 0.2f},
    {0.6f, -0.7f},
    {-0.7f, -0.5f},
    {0.5f, 0.0f}
};

void greendot() {
    float x1 = linePt[0].x, y1 = linePt[0].y;
    float x2 = linePt[1].x, y2 = linePt[1].y;
    float x3 = linePt[2].x, y3 = linePt[2].y;
    float x4 = linePt[3].x, y4 = linePt[3].y;

    float denominator = ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));

    if (denominator == 0) {
        return;
    }

    float ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / denominator;
    float ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denominator;

    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
        float intersectionX = x1 + (ua * (x2 - x1));
        float intersectionY = y1 + (ua * (y2 - y1));
        
        glColor3f(0.0, 1.0, 0.0);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glVertex2f(intersectionX, intersectionY);
        glEnd();
    }
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw first line
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[0].x, linePt[0].y);
    glVertex2f(linePt[1].x, linePt[1].y);
    glEnd();

    // Draw second line
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[2].x, linePt[2].y);
    glVertex2f(linePt[3].x, linePt[3].y);
    glEnd();

    greendot();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) { 

    switch (key) {
    case 'w':
        linePt[0].y += 0.1f;
        linePt[1].y += 0.1f;
        break;
    case 's':
        linePt[0].y -= 0.1f;
        linePt[1].y -= 0.1f;
        break;
    case 'a':
        linePt[0].x -= 0.1f;
        linePt[1].x -= 0.1f;
        break;
    case 'd':
        linePt[0].x += 0.1f;
        linePt[1].x += 0.1f;
        break;
    case 27: // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
