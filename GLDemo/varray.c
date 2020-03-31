#include "gl_headers.h"

#define INIT_MODE_POINTER 1
#define INIT_MODE_INTERLEAVED 2

#define DEREF_MODE_ARRAY 1
#define DEREF_MODE_ARRAY_ELEMENT 2
#define DEREF_MODE_ELEMENTS 3

int initMode = INIT_MODE_POINTER;
int derefMode = DEREF_MODE_ARRAY_ELEMENT;

static GLint vertices[] = {25, 25,
    100,325,
    175, 25,
    175,325,
    250, 25,
    325, 325};


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (initMode == INIT_MODE_POINTER){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(2, GL_INT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);
    } else if (initMode == INIT_MODE_INTERLEAVED) {
        glInterleavedArrays(GL_C3F_V3F, 0, interwined);
    }
    if (derefMode == DEREF_MODE_ARRAY){
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }else if (derefMode == DEREF_MODE_ARRAY_ELEMENT) {
        glBegin(GL_TRIANGLES);
        glArrayElement(2);
        glArrayElement(3);
        glArrayElement(5);
        glEnd();
    } else if(derefMode == DEREF_MODE_ELEMENTS){
        GLuint indices[4] = {0,1,3,4};
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, indices);
    }
    if (glutDisplayMode == GLUT_SINGLE){
        glFlush();
    } else if (glutDisplayMode == GLUT_DOUBLE) {
        glutSwapBuffers();
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void mouse(int button, int state, int x, int y)
{
    switch(button){
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN){
                if(initMode == INIT_MODE_POINTER){
                    initMode = INIT_MODE_INTERLEAVED;
                } else {
                    initMode = INIT_MODE_POINTER;
                }
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
                if (derefMode == DEREF_MODE_ARRAY){
                    derefMode = DEREF_MODE_ARRAY_ELEMENT;
                } else if (derefMode == DEREF_MODE_ARRAY_ELEMENT){
                    derefMode = DEREF_MODE_ELEMENTS;
                } else {
                    derefMode = DEREF_MODE_ARRAY;
                }
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(glutDisplayMode|GLUT_RGB);
    glutInitWindowSize(350,350);
    glutInitWindowPosition(800, 600);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
