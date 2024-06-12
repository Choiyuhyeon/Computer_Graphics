#include "gl/glut.h"
#include <cstdio>
#include "GCBezierCurve.h"


Vec2 mousePt = { 1, 0 };
float rotateAngle = 0.0;
std::vector<Vec2> ctrlPts;

void displayGlutPrimitives() {

    glutWireSphere(1.0, 20, 20);
    //glutSolidSphere(1.0, 20, 20);

    //glutWireCube(0.5);
    //glutSolidCube(0.5);

    //glutWireCone(1.0, 1.5, 12, 12);
    //glutSolidCone(1.0, 1.5, 12, 12);

    //glutWireTorus(0.3, 0.7, 20, 20);
    //glutSolidTorus(0.3, 0.7, 20, 20);

    //glutWireTeapot(1.0);
    //glutSolidTeapot(1.0);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION); // **
    glLoadIdentity(); // 행렬 초기화
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // 2d 직교 매트릭스 만들기

//----------------- 0. Display Glut Primitives -------------------
    displayGlutPrimitives(); 
// ----------------------------------------------------------------


//--------------- 1. Simple transform ------------------------
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLoadIdentity();
    glTranslatef(1.0, 0.0, 0.0);
    displayGlutPrimitives();

    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0.0, 1.0, 0.0); // scale로 수정해야함 강의자료 12p
    displayGlutPrimitives();

    glColor3f(0.0, 0.0, 1.0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 1.0); // scale로 수정해야함
    displayGlutPrimitives();
// ----------------------------------------------------------------


// --------------- 2. Multiple transform -------------------------- // 주전자 하나는 원점기준 회전, 하나는 자기자신 기준 회전
   
    glMatrixMode(GL_MODELVIEW);
    // Rotate-Translate
    // 원점을 중심으로 z축을 기준으로 회전하고, 그 후 x축 방향으로 1.0만큼 이동
    glLoadIdentity();
    glColor3f(1, 0, 0);
    glRotatef(rotateAngle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    displayGlutPrimitives();

    //Translate-Rotate
    // x축 방향으로 1.0만큼 이동한 후, 자신의 좌표를 기준으로 z축을 회전
    glColor3f(0, 0, 1);
    glLoadIdentity();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(rotateAngle, 0.0, 0.0, 1.0);
    displayGlutPrimitives();
// ----------------------------------------------------------------


// --------------- 3. Bezier Curve --------------------------
// BezierCurve2D 클래스의 객체를 생성하고, 제어점(ctrlPts)을 전달합니다.
BezierCurve2D curve(ctrlPts);
glPointSize(5.0); // 점의 크기
glLineWidth(1.0);// 선의 두께를 설정합니다.
glColor3f(1, 0, 0);

// 제어점들을 그립니다.
glBegin(GL_POINTS);
for (auto& pt : ctrlPts)
    glVertex2f(pt.x, pt.y);
glEnd();

// 제어점들을 연결한 선을 그립니다.
glBegin(GL_LINE_STRIP);
for (auto &pt : ctrlPts)
    glVertex2f(pt.x, pt.y);
glEnd();

// 검은색으로 그래픽 컬러를 설정합니다.
glColor3f(0, 0, 0);

// 선의 두께를 더 크게 설정합니다.
glLineWidth(2.0);

// 베지어 곡선을 그립니다.
glBegin(GL_LINE_STRIP);
for (int i = 0; i <= 100; i++) {
    // 베지어 곡선을 평가하여 점을 가져옵니다.
    auto pt = curve.Evaluate(i / 100.0);
    glVertex2f(pt.x, pt.y);
}
glEnd();



// // --------------- 3. Bezier Curve 추가본!!!! 공부해야할 부분 --------------------------
// // BezierCurve2D 클래스의 객체를 생성하고, 제어점(ctrlPts)을 전달합니다.
// BezierCurve2D curve(ctrlPts);
// glPointSize(5.0); // 점의 크기
// glLineWidth(1.0);// 선의 두께를 설정합니다.
// glColor3f(1, 0, 0);

// // 제어점들을 그립니다.
// glBegin(GL_POINTS);
// for (auto& pt : ctrlPts)
//     glVertex2f(pt.x, pt.y);
// glEnd();

// // 제어점들을 연결한 선을 그립니다.
// glBegin(GL_LINE_STRIP);
// for (auto &pt : ctrlPts)
//     glVertex2f(pt.x, pt.y);
// glEnd();

// // 검은색으로 그래픽 컬러를 설정합니다.
// glColor3f(0, 0, 0);

// // 선의 두께를 더 크게 설정합니다.
// glLineWidth(2.0);

// // 베지어 곡선을 그립니다.
// glBegin(GL_LINE_STRIP);
// for (int i = 0; i <= 100; i++) {
//     // 베지어 곡선을 평가하여 점을 가져옵니다.
//     auto pt = curve.Evaluate(i / 100.0);
//     glVertex2f(pt.x, pt.y);
// }
// glEnd();


// ----------------------------------------------------------------

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 27: // ESC
	exit(0);
	break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
	rotateAngle += 10;
	break;
    case GLUT_KEY_DOWN:
	rotateAngle -= 10;
	break;
    }
    glutPostRedisplay();
}

void mouseCoordinateTranslate(int winX, int winY)
{
    mousePt.x = winX / 50.0 - 5;
    mousePt.y = (winY / 50.0 - 5) * (-1.0);
}

void changeCtrlPts()
{
    for (auto &pt : ctrlPts) {
	if (sqrt(pow(pt.x - mousePt.x, 2) + pow(pt.y - mousePt.y, 2)) < 0.5) {
	    pt = mousePt;
	    break;
	}
    }
}

void mouse(int button, int state, int x, int y)
{
    printf("mouse: %d %d %d %d\n", button, state, x, y);
    if (state == GLUT_DOWN) {
	mouseCoordinateTranslate(x, y);
	changeCtrlPts();
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    printf("mouse motion: %d %d\n", x, y);
    mouseCoordinateTranslate(x, y);
    changeCtrlPts();

    glutPostRedisplay();
}

void mousePassiveMotion(int x, int y)
{
    printf("mouse passive motion: %d %d\n", x, y);
    mouseCoordinateTranslate(x, y);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    ctrlPts.push_back({ -2, -1 });
    ctrlPts.push_back({ 0, 2 });
    ctrlPts.push_back({ 2, -1 });

    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(mousePassiveMotion);
    glutMainLoop();

    return 0;
}