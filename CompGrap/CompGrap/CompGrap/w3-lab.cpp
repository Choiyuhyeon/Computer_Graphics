#include "gl/glut.h"  // GLUT 라이브러리 포함
#include <cstdio>     // printf 함수를 사용하기 위한 헤더

// 2차원 벡터 구조체 정의
struct Vec2 {
    float x, y;
};

Vec2 mousePt = { 0, 0 };  // 마우스 좌표를 저장할 벡터 초기화

// 그래픽 출력 함수
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 배경색을 흰색으로 설정
    glClear(GL_COLOR_BUFFER_BIT);          // 화면을 지우고 새로 그림

    glColor3f(0.0f, 0.0f, 0.0f);  // 그리기 색상을 검은색으로 설정
    glPointSize(10.0);            // 점의 크기를 10으로 설정

    glBegin(GL_POINTS);            // 점 그리기 시작
    glVertex2f(mousePt.x, mousePt.y);  // 마우스 좌표에 점 그리기
    glEnd();                        // 점 그리기 종료

    glutSwapBuffers();  // 더블 버퍼링을 사용하여 그래픽 버퍼 교체
}

// 키보드 입력 처리 함수
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // ESC 키를 누르면
        exit(0);  // 프로그램 종료
        break;
    }
    glutPostRedisplay();  // 화면 다시 그리기 요청
}

// 마우스 좌표 변환 함수
void mouseCoordinateTranslate(int winX, int winY) {
    // 윈도우 좌표를 OpenGL 좌표로 변환: viewport 좌표
    mousePt.x = winX / 250.0 - 1;
    mousePt.y = (winY / 250.0 - 1) * (-1.0);
}

// 마우스 클릭 이벤트 처리 함수
void mouse(int button, int state, int x, int y) {
    printf("mouse: %d %d %d %d\n", button, state, x, y);  // 마우스 이벤트 정보 출력
    if (state == GLUT_DOWN) {  // 마우스 버튼이 눌렸을 때
        mouseCoordinateTranslate(x, y);  // 마우스 좌표 변환 함수 호출
    }
    glutPostRedisplay();  // 화면 다시 그리기 요청
}

// 마우스 이동 이벤트 처리 함수
void mouseMotion(int x, int y) {
    printf("mouse motion: %d %d\n", x, y);  // 마우스 이동 정보 출력
    mouseCoordinateTranslate(x, y);  // 마우스 좌표 변환 함수 호출
    glutPostRedisplay();  // 화면 다시 그리기 요청
}

// 주 프로그램
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // 그래픽 모드 설정
    glutInitWindowSize(500, 500);  // 윈도우 크기 설정
    glutInitWindowPosition(1480, 100);  // 윈도우 위치 설정

    glutCreateWindow("OpenGL");  // 윈도우 생성
    glutDisplayFunc(display);  // 그래픽 출력 함수 등록
    glutKeyboardFunc(keyboard);  // 키보드 입력 처리 함수 등록
    glutMouseFunc(mouse);  // 마우스 클릭 이벤트 처리 함수 등록
    glutMotionFunc(mouseMotion);  // 마우스 이동 이벤트 처리 함수 등록
    glutMainLoop();  // GLUT 이벤트 루프 시작

    return 0;
}
