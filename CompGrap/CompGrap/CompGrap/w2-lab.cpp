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


void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[0].x, linePt[0].y);  
    glVertex2f(linePt[1].x, linePt[1].y);  
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[2].x, linePt[2].y); 
    glVertex2f(linePt[3].x, linePt[3].y);
    glEnd();

    // 두 선분의 접점 함수 추가 필요
    // 두 선분의 접점을 계산하기 위해 각 선분의 시작점과 끝점의 좌표를 변수에 저장합니다.
    float x1 = linePt[0].x, y1 = linePt[0].y; // 첫 번째 선분의 시작점 좌표
    float x2 = linePt[1].x, y2 = linePt[1].y; // 첫 번째 선분의 끝점 좌표
    float x3 = linePt[2].x, y3 = linePt[2].y; // 두 번째 선분의 시작점 좌표
    float x4 = linePt[3].x, y4 = linePt[3].y; // 두 번째 선분의 끝점 좌표

    // 선분이 교차하는지 확인하기 위한 분모 값 계산
    float denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    // 분모 값이 0이 아닌 경우 선분들이 교차할 수 있으므로 계산을 계속합니다.
    if (denom != 0) {
        // ua와 ub는 각 선분이 교차하는 점의 위치를 나타냅니다.
        float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
        float ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;

        // ua와 ub가 0과 1 사이에 있으면 두 선분이 교차하는 것입니다.
        if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
            // 교차점의 좌표를 계산합니다.
            float intersectionX = x1 + ua * (x2 - x1);
            float intersectionY = y1 + ua * (y2 - y1);
    
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0, 0); 
    glEnd();

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
