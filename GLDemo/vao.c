#include "gl_headers.h"

#define NumberOf(array) (sizeof(array)/sizeof(array[0]))

typedef struct {
    GLfloat x, y, z;
}vec3;

typedef struct {
    vec3 xlate;
    GLfloat angle;
    vec3 axis;
}XForm;

enum{Cube, Cone, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimeType[NumVAOs];
GLsizei NumElements[NumVAOs];
XForm Xform[NumVAOs] = {
    {{-2.0, 0.0, 0.0}, 0.0, {0.0, 1.0, 0.0}},
    {{0.0, 0.0, 2.0}, 0.0, {1.0, 0.0, 0.0}},
};

GLfloat Angle = 0.0;

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

static GLfloat cubeColors[][3] ={
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0},
};

static GLubyte cubeIndices[] = {
    0, 1, 3, 2,
    4, 6, 7, 5,
    2, 3, 7, 6,
    0, 4, 5, 1,
    0, 2, 6, 4,
    1, 5, 7, 3
};

void init(void)
{
    enum {Vertices, Colors, Elements, NumVBOs};
    GLuint buffers[NumVBOs];

    glGenVertexArrays(NumVAOs, VAO);

    {
        glBindVertexArray(VAO[Cube]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
        PrimeType[Cube] = GL_QUADS;
        NumElements[Cube] = NumberOf(cubeIndices);
    }
    {
        int i, idx;
        float dTheta;
#define NumConePoints 36
#define M_PI 3.14159265354
        GLfloat coneVerts[NumConePoints+1][3]={
            {0.0, 0.0, 1.0}
        };
        GLfloat coneColors[NumConePoints+1][3]={
            {1.0, 1.0, 1.0}
        };
        GLubyte coneIndices[NumConePoints+1];

        dTheta = 2 * M_PI/(NumConePoints-1);
        idx = 1;
        for (i=0; i < NumConePoints; ++i, ++idx) {
            float theta = i*dTheta;
            coneVerts[idx][0] = cos(theta);
            coneVerts[idx][1] = sin(theta);
            coneVerts[idx][2] = 0.0;

            coneColors[idx][0] = cos(theta);
            coneColors[idx][1] = sin(theta);
            coneColors[idx][2] = 0.0;

            coneIndices[idx] = idx;
        }
        glBindVertexArray(VAO[Cone]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);
        PrimeType[Cone] = GL_TRIANGLE_FAN;
        NumElements[Cone] = NumberOf(coneIndices);
    }
    glEnable(GL_DEPTH_TEST);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_SMOOTH);
}

void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(Angle, 0.0, 1.0, 0.0);
    for(i=0;i<NumVAOs;++i){
        glPushMatrix();
        glTranslatef(Xform[i].xlate.x, Xform[i].xlate.y,
                     Xform[i].xlate.z);
        glRotatef(Xform[i].angle, Xform[i].axis.x,
                  Xform[i].axis.y, Xform[i].axis.z);
        glBindVertexArray(VAO[i]);
        glDrawElements(PrimeType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        glPopMatrix();
    }
    glPopMatrix();

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
