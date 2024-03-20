#include "gl/glut.h"

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 0.0f); // 0.0 ~ 1.0

    glBegin(GL_TRIANGLES); // GL_TRIANGLES
    glVertex2f(-0.5f, -0.5f); // 첫 번째 정점
    glVertex2f(0.5f, -0.5f); // 두 번째 정점
    glVertex2f(0.0f, 0.5f); // 세 번째 정점
    glEnd();

    glFinish();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
