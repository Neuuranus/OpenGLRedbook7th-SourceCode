#include "gl_headers.h"

static int year = 0, day = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawSatelite()
{
    glTranslated(0.5, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 0.0, 1.0);
    glutWireSphere(0.1, 10, 8);
}

void drawPlanets(GLfloat distance)
{
    glPushMatrix();
    glTranslated(distance, 0.0, 0.0);
    glRotatef((GLfloat)day, 1.0, 1.0, -1.0);
    glutWireSphere(0.3, 50, 8);
    drawSatelite();
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glutWireSphere(1.0, 100, 16);
    glRotatef((GLfloat)year, 0.0, 1.0, 0.2);
    drawPlanets(5);
    glColor3f(1.0, 0.0, 0.0);
    drawPlanets(10);
    glColor3f(0.0, 0.0, 1.0);
    drawPlanets(15);
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);

    if (glutDisplayMode == GLUT_SINGLE){
        glFlush();
    } else if (glutDisplayMode == GLUT_DOUBLE) {
        glutSwapBuffers();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, (GLfloat)w/(GLfloat)h, 1.0, 140.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 70.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd':
            day = (day+10)%360;
            glutPostRedisplay();
            break;
        case 'D':
            day = (day-10)%360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year+10)%360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year-10)%360;
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(glutDisplayMode|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(800, 600);
    glutCreateWindow("Planet");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
