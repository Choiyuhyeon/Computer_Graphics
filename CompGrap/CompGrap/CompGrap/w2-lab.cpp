#include "gl/glut.h"  // GLUT ���̺귯�� ��� ������ ����
#include <cstdio>

// 2���� ���� ����ü ����
struct Vec2 {
    float x, y;
};

// ���� �� ���� �����ϴ� �迭
Vec2 linePt[4] = {
    {-0.3f, 0.2f},
    {0.6f, -0.7f},
    {-0.7f, -0.5f},
    {0.5f, 0.0f}
};

// OpenGL�� ����Ͽ� �׷����� �׸��� display �Լ�
void display() {
    // ȭ���� ������� �����
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // ���������� ù ��° �� �׸���
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[0].x, linePt[0].y);  // ù ��° ��
    glVertex2f(linePt[1].x, linePt[1].y);  // �� ��° ��
    glEnd();

    // �Ķ������� �� ��° �� �׸���
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[2].x, linePt[2].y);  // �� ��° ��
    glVertex2f(linePt[3].x, linePt[3].y);  // �� ��° ��
    glEnd();

    // ��� �� ��� (���� ����� ���� �ӽ� ��ġ)
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);  // (0, 0) ��ġ�� �� ���
    glEnd();

    // ȭ�鿡 �׸� �׷����� ȭ�鿡 ǥ��
    glutSwapBuffers();
}

// Ű���� �Է��� ó���ϴ� �Լ�
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':  // 'w' Ű�� ������ y ��ǥ ����
        linePt[0].y += 0.1f;
        linePt[1].y += 0.1f;
        break;
    case 's':  // 's' Ű�� ������ y ��ǥ ����
        linePt[0].y -= 0.1f;
        linePt[1].y -= 0.1f;
        break;
    case 'a':  // 'a' Ű�� ������ x ��ǥ ����
        linePt[0].x -= 0.1f;
        linePt[1].x -= 0.1f;
        break;
    case 'd':  // 'd' Ű�� ������ x ��ǥ ����
        linePt[0].x += 0.1f;
        linePt[1].x += 0.1f;
        break;
    case 27:  // ESC Ű�� ������ ���α׷� ����
        exit(0);
        break;
    }
    // ȭ���� �ٽ� �׸����� ��û
    glutPostRedisplay();
}

// ���� �Լ�
int main(int argc, char** argv) {
    // GLUT �ʱ�ȭ
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    // ������ ����
    glutCreateWindow("OpenGL");

    // �ݹ� �Լ� ���
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // GLUT �̺�Ʈ ���� ����
    glutMainLoop();

    return 0;
}
