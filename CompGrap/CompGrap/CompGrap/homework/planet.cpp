#include "gl/glut.h"
#include <cstdio>
#include <ctime>
#include <cmath>

#define PI 3.14159265358979323846

bool isAnimation = false;
int arrowNum[2] = { 0,0 };
int width = 500, height = 500;
int timeIdx = 0;

void DrawCircle(double radius, bool isFill = true)
{
    glPointSize(15.0);
    if (isFill)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++)
        glVertex2d(radius * cos(i * PI / 180.0),
            radius * sin(i * PI / 180.0));
    glEnd();
}

void DrawAxis()
{
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(10.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(1, 0);
    glColor3f(0.0, 10.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(0, 1);
    glColor3f(0.0, 0.0, 10.0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);
    glEnd();
}

void AddPlanet(double distance, double radius, double rotation_period, double r, double g, double b, double incline = 0)
{
    glPushMatrix();
    glRotated(incline, 0, 0, 1);  // Inclination
    glRotated(timeIdx / rotation_period * 360.0, 0, 0, 1);
    glTranslated(distance, 0.0, 0.0);
    glColor3f(r, g, b);
    DrawCircle(radius);
    glPopMatrix();
}

void AddSatellite(double distance, double radius, double rotation_period, double r, double g, double b)
{
    glPushMatrix();
    glRotated(timeIdx / rotation_period * 360.0, 0, 0, 1);
    glTranslated(0.0, distance, 0.0);
    glColor3f(r, g, b);
    DrawCircle(radius);
    glPopMatrix();
}

void display() {
    printf("time: %d\n", timeIdx);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20 + arrowNum[1], 0, 0, 0, 0, 1, 0);
    DrawAxis();

    // Sun
    glColor3f(1, 0, 0);
    DrawCircle(3.0);

    // Earth
    AddPlanet(7.0, 1.0, 365.0, 0, 0, 1);

    // Moon
    AddSatellite(1.5, 0.3, 27.0, 1, 0, 1);

    // Mars
    AddPlanet(10.0, 0.5, 687.0, 1.0, 0.5, 0.0);

    // Jupiter
    AddPlanet(15.0, 2.0, 4333.0, 0.0, 1.0, 0.0);

    // Saturn
    AddPlanet(20.0, 1.0, 29 * 365.0, 1.0, 1.0, 0.0);

    // Titan
    AddSatellite(2.0, 0.3, 16.0, 0.5, 0.0, 1.0);

    glFinish();
    glutSwapBuffers();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        timeIdx++;
        break;
    case GLUT_KEY_DOWN:
        timeIdx--;
        break;
    case GLUT_KEY_RIGHT:
        arrowNum[1]++;
        break;
    case GLUT_KEY_LEFT:
        arrowNum[1]--;
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
}

void timer(int value)
{
    if (isAnimation) {
        glutTimerFunc(10, timer, 0);
        timeIdx += 1;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'p': case 'P':
        isAnimation = !isAnimation;
        glutTimerFunc(10, timer, 0);
        break;
    case 27: // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(1480, 100);

    glutCreateWindow("OpenGL");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
