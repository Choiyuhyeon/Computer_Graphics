#include "gl/glut.h"
#include <cstdio>
#include <cmath>
#include <vector>

struct Vec2 {
    float x, y;
};

class BezierCurve2D {
public:
    BezierCurve2D(const std::vector<Vec2>& controlPoints) : controlPoints(controlPoints) {}

    Vec2 Evaluate(float t) {
        float oneMinusT = 1.0f - t;
        float t2 = t * t;
        float oneMinusT2 = oneMinusT * oneMinusT;

        Vec2 point;
        point.x = oneMinusT2 * oneMinusT * controlPoints[0].x +
            3 * oneMinusT2 * t * controlPoints[1].x +
            3 * oneMinusT * t2 * controlPoints[2].x +
            t2 * t * controlPoints[3].x;
        point.y = oneMinusT2 * oneMinusT * controlPoints[0].y +
            3 * oneMinusT2 * t * controlPoints[1].y +
            3 * oneMinusT * t2 * controlPoints[2].y +
            t2 * t * controlPoints[3].y;
        return point;
    }

    std::vector<Vec2> GetControlPoints() const {
        return controlPoints;
    }

private:
    std::vector<Vec2> controlPoints;
};

Vec2 mousePt = { 1, 0 };
float rotateAngle = 0.0;
std::vector<Vec2> ctrlPts;

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    // Draw Bezier Curves and AABBs
    for (int i = 0; i < ctrlPts.size() - 3; i += 3) {
        BezierCurve2D curve({ ctrlPts[i], ctrlPts[i + 1], ctrlPts[i + 2], ctrlPts[i + 3] });
        glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= 100; j++) {
            auto pt = curve.Evaluate(j / 100.0);
            glVertex2f(pt.x, pt.y);
        }
        glEnd();

        auto controlPoints = curve.GetControlPoints();

        // Calculate AABB for the curve
        float minX = controlPoints[0].x, maxX = controlPoints[0].x;
        float minY = controlPoints[0].y, maxY = controlPoints[0].y;
        for (const auto& pt : controlPoints) {
            if (pt.x < minX) minX = pt.x;
            if (pt.x > maxX) maxX = pt.x;
            if (pt.y < minY) minY = pt.y;
            if (pt.y > maxY) maxY = pt.y;
        }

        // Draw AABB
        glColor3f(0, 0, 1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(minX, minY);
        glVertex2f(maxX, minY);
        glVertex2f(maxX, maxY);
        glVertex2f(minX, maxY);
        glEnd();
    }

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

void mouseCoordinateTranslate(int winX, int winY) {
    mousePt.x = winX / 50.0 - 5;
    mousePt.y = (winY / 50.0 - 5) * (-1.0);
}

void changeCtrlPts() {
    for (auto& pt : ctrlPts) {
        if (sqrt(pow(pt.x - mousePt.x, 2) + pow(pt.y - mousePt.y, 2)) < 0.5) {
            pt = mousePt;
            break;
        }
    }
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        mouseCoordinateTranslate(x, y);
        changeCtrlPts();
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    mouseCoordinateTranslate(x, y);
    changeCtrlPts();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1480, 100);

    ctrlPts.push_back({ -2, -1 });
    ctrlPts.push_back({ 0, 2 });
    ctrlPts.push_back({ 2, -1 });
    ctrlPts.push_back({ -1, 1 }); // Additional control point
    ctrlPts.push_back({ 2, 2 }); // Additional control point
    ctrlPts.push_back({ -2, 2 }); // Additional control point

    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();

    return 0;
}
