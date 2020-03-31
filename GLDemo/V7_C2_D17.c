#include "gl_headers.h"


#define VERTICES 0
#define INDICES 1
#define NUM_BUFFERS 2

GLuint buffers[NUM_BUFFERS];

static GLint vertices[][3] = {
    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},
};

static GLubyte indices[][4] = {
    {0, 1, 2, 3},
    {4, 7, 6, 5},
    {0, 4, 5, 1},
    {3, 2, 6, 7},
    {0, 3, 7, 4},
    {1, 5, 6, 2}
};

static GLfloat cubeVerts[][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0},
    {-1.0, 1.0, 1.0},
    {1.0, -1.0, -1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0},
};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glGenBuffers(NUM_BUFFERS, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
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
            break;
        case GLUT_RIGHT_BUTTON:
        case GLUT_MIDDLE_BUTTON:
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
