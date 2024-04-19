#include "gl/glut.h"  // GLUT 라이브러리 헤더 포함
#include <cstdio>     // printf 함수를 사용하기 위한 헤더

// 2차원 벡터 구조체 정의
struct Vec2 {
    float x, y;
};

Vec2 mousePt = { 0, 0 };  // 마우스 좌표를 저장할 구조체 변수 초기화

// 디스플레이 콜백 함수
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 배경색을 흰색으로 설정
    glClear(GL_COLOR_BUFFER_BIT);          // 색상 버퍼를 지우고 배경색으로 채움

    glColor3f(0.0f, 0.0f, 0.0f);  // 그리기 색상을 검은색으로 설정
    glPointSize(10.0);            // 포인트 크기를 10으로 설정

    glBegin(GL_POINTS);            // 점 그리기 모드 시작
    glVertex2f(mousePt.x, mousePt.y);  // 현재 마우스 좌표에 점 그리기
    glEnd();                        // 점 그리기 모드 종료

    glutSwapBuffers();  // 프론트와 백 버퍼를 교체하여 디스플레이 업데이트
}

// 키보드 입력 콜백 함수
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // ESC 키를 눌렀을 때
        exit(0);  // 프로그램 종료
        break;
    }
    glutPostRedisplay();  // 디스플레이 콜백 함수 호출
}

// 마우스 좌표 변환 함수
void mouseCoordinateTranslate(int winX, int winY) {
    // 윈도우 좌표를 정규화된 OpenGL 좌표로 변환 : viewport좌표계
    mousePt.x = winX / 250.0 - 1;
    mousePt.y = (winY / 250.0 - 1) * (-1.0);
}

// 마우스 클릭 이벤트 콜백 함수
void mouse(int button, int state, int x, int y) {
    printf("mouse: %d %d %d %d\n", button, state, x, y);  // 마우스 이벤트 정보 출력
    if (state == GLUT_DOWN) {  // 마우스 버튼이 눌렸을 때
        mouseCoordinateTranslate(x, y);  // 마우스 좌표 변환 함수 호출
    }
    glutPostRedisplay();  // 디스플레이 콜백 함수 호출
}

// 마우스 드래그 이벤트 콜백 함수
void mouseMotion(int x, int y) {
    printf("mouse motion: %d %d\n", x, y);  // 마우스 모션 정보 출력
    mouseCoordinateTranslate(x, y);  // 마우스 좌표 변환 함수 호출
    glutPostRedisplay();  // 디스플레이 콜백 함수 호출
}

// 마우스 패시브 모션 이벤트 콜백 함수 (주석 처리)
// void mousePassiveMotion(int x, int y) {
//     printf("mouse passive motion: %d %d\n", x, y);
//     mouseCoordinateTranslate(x, y);
//     glutPostRedisplay();
// }

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // 디스플레이 모드 설정
    glutInitWindowSize(500, 500);  // 윈도우 크기 설정
    glutInitWindowPosition(1480, 100);  // 윈도우 위치 설정

    glutCreateWindow("OpenGL");  // 윈도우 생성 및 타이틀 설정
    glutDisplayFunc(display);  // 디스플레이 콜백 함수 등록
    glutKeyboardFunc(keyboard);  // 키보드 입력 콜백 함수 등록
    glutMouseFunc(mouse);  // 마우스 이벤트 콜백 함수 등록
    glutMotionFunc(mouseMotion);  // 마우스 드래그 이벤트 콜백 함수 등록
    //glutPassiveMotionFunc(mousePassiveMotion);  // 마우스 패시브 모션 이벤트 콜백 함수 등록
    glutMainLoop();  // GLUT 이벤트 루프 진입

    return 0;
}
