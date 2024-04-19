#include "gl/glut.h"  // GLUT ���̺귯�� ��� ����
#include <cstdio>     // printf �Լ��� ����ϱ� ���� ���

// 2���� ���� ����ü ����
struct Vec2 {
    float x, y;
};

Vec2 mousePt = { 0, 0 };  // ���콺 ��ǥ�� ������ ����ü ���� �ʱ�ȭ

// ���÷��� �ݹ� �Լ�
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // ������ ������� ����
    glClear(GL_COLOR_BUFFER_BIT);          // ���� ���۸� ����� �������� ä��

    glColor3f(0.0f, 0.0f, 0.0f);  // �׸��� ������ ���������� ����
    glPointSize(10.0);            // ����Ʈ ũ�⸦ 10���� ����

    glBegin(GL_POINTS);            // �� �׸��� ��� ����
    glVertex2f(mousePt.x, mousePt.y);  // ���� ���콺 ��ǥ�� �� �׸���
    glEnd();                        // �� �׸��� ��� ����

    glutSwapBuffers();  // ����Ʈ�� �� ���۸� ��ü�Ͽ� ���÷��� ������Ʈ
}

// Ű���� �Է� �ݹ� �Լ�
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // ESC Ű�� ������ ��
        exit(0);  // ���α׷� ����
        break;
    }
    glutPostRedisplay();  // ���÷��� �ݹ� �Լ� ȣ��
}

// ���콺 ��ǥ ��ȯ �Լ�
void mouseCoordinateTranslate(int winX, int winY) {
    // ������ ��ǥ�� ����ȭ�� OpenGL ��ǥ�� ��ȯ : viewport��ǥ��
    mousePt.x = winX / 250.0 - 1;
    mousePt.y = (winY / 250.0 - 1) * (-1.0);
}

// ���콺 Ŭ�� �̺�Ʈ �ݹ� �Լ�
void mouse(int button, int state, int x, int y) {
    printf("mouse: %d %d %d %d\n", button, state, x, y);  // ���콺 �̺�Ʈ ���� ���
    if (state == GLUT_DOWN) {  // ���콺 ��ư�� ������ ��
        mouseCoordinateTranslate(x, y);  // ���콺 ��ǥ ��ȯ �Լ� ȣ��
    }
    glutPostRedisplay();  // ���÷��� �ݹ� �Լ� ȣ��
}

// ���콺 �巡�� �̺�Ʈ �ݹ� �Լ�
void mouseMotion(int x, int y) {
    printf("mouse motion: %d %d\n", x, y);  // ���콺 ��� ���� ���
    mouseCoordinateTranslate(x, y);  // ���콺 ��ǥ ��ȯ �Լ� ȣ��
    glutPostRedisplay();  // ���÷��� �ݹ� �Լ� ȣ��
}

// ���콺 �нú� ��� �̺�Ʈ �ݹ� �Լ� (�ּ� ó��)
// void mousePassiveMotion(int x, int y) {
//     printf("mouse passive motion: %d %d\n", x, y);
//     mouseCoordinateTranslate(x, y);
//     glutPostRedisplay();
// }

// ���� �Լ�
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // GLUT �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // ���÷��� ��� ����
    glutInitWindowSize(500, 500);  // ������ ũ�� ����
    glutInitWindowPosition(1480, 100);  // ������ ��ġ ����

    glutCreateWindow("OpenGL");  // ������ ���� �� Ÿ��Ʋ ����
    glutDisplayFunc(display);  // ���÷��� �ݹ� �Լ� ���
    glutKeyboardFunc(keyboard);  // Ű���� �Է� �ݹ� �Լ� ���
    glutMouseFunc(mouse);  // ���콺 �̺�Ʈ �ݹ� �Լ� ���
    glutMotionFunc(mouseMotion);  // ���콺 �巡�� �̺�Ʈ �ݹ� �Լ� ���
    //glutPassiveMotionFunc(mousePassiveMotion);  // ���콺 �нú� ��� �̺�Ʈ �ݹ� �Լ� ���
    glutMainLoop();  // GLUT �̺�Ʈ ���� ����

    return 0;
}
