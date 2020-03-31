#ifndef __GL_DEMO_H__
#define __GL_DEMO_H__
#include <stdlib.h>
#include <stdio.h>
#ifdef OS_LINUX
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#else
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#endif

#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + (bytes))

int glutDisplayMode = GLUT_DOUBLE;

static GLfloat colors[] = { 1.0, 0.2, 0.2,
    0.2, 0.2, 1.0,
    0.8, 1.0, 0.2,
    0.75, 0.75, 0.75,
    0.35, 0.35, 0.35,
    0.5, 0.5, 0.5};

static GLfloat interwined[] ={1.0, 0.2, 1.0, 100.0, 100.0, 0.0,
    1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
    1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
    0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
    0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
    0.2, 0.2, 1.0, 200.0, 100.0, 0.0};


#endif
