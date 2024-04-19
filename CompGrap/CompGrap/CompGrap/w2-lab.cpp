#include "gl/glut.h"  // GLUT 라이브러리 헤더 파일을 포함
#include <cstdio>

// 2차원 벡터 구조체 정의
struct Vec2 {
    float x, y;
};

// 선의 두 점을 저장하는 배열
Vec2 linePt[4] = {
    {-0.3f, 0.2f},
    {0.6f, -0.7f},
    {-0.7f, -0.5f},
    {0.5f, 0.0f}
};

// OpenGL을 사용하여 그래픽을 그리는 display 함수
void display() {
    // 화면을 흰색으로 지우기
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 빨간색으로 첫 번째 선 그리기
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[0].x, linePt[0].y);  // 첫 번째 점
    glVertex2f(linePt[1].x, linePt[1].y);  // 두 번째 점
    glEnd();

    // 파란색으로 두 번째 선 그리기
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[2].x, linePt[2].y);  // 세 번째 점
    glVertex2f(linePt[3].x, linePt[3].y);  // 네 번째 점
    glEnd();

    // 녹색 점 찍기 (교점 계산을 위한 임시 위치)
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);  // (0, 0) 위치에 점 찍기
    glEnd();

    // 화면에 그린 그래픽을 화면에 표시
    glutSwapBuffers();
}

// 키보드 입력을 처리하는 함수
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':  // 'w' 키를 누르면 y 좌표 증가
        linePt[0].y += 0.1f;
        linePt[1].y += 0.1f;
        break;
    case 's':  // 's' 키를 누르면 y 좌표 감소
        linePt[0].y -= 0.1f;
        linePt[1].y -= 0.1f;
        break;
    case 'a':  // 'a' 키를 누르면 x 좌표 감소
        linePt[0].x -= 0.1f;
        linePt[1].x -= 0.1f;
        break;
    case 'd':  // 'd' 키를 누르면 x 좌표 증가
        linePt[0].x += 0.1f;
        linePt[1].x += 0.1f;
        break;
    case 27:  // ESC 키를 누르면 프로그램 종료
        exit(0);
        break;
    }
    // 화면을 다시 그리도록 요청
    glutPostRedisplay();
}

// 메인 함수
int main(int argc, char** argv) {
    // GLUT 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    // 윈도우 생성
    glutCreateWindow("OpenGL");

    // 콜백 함수 등록
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // GLUT 이벤트 루프 시작
    glutMainLoop();

    return 0;
}
