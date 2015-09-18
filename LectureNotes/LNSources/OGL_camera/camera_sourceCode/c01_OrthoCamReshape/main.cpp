#include <stdio.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include "initWindow.h"

void init(int argc, char **argv) {
	initWindow(&argc, argv);
	
	// 초기화
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	
}

void reshape(int w, int h) {
	float asp = float(w)/float(h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0*asp, 2.0*asp, -2.0, 2.0, -2.0, 2.0);
	glutPostRedisplay();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glutWireTeapot(1.0);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}