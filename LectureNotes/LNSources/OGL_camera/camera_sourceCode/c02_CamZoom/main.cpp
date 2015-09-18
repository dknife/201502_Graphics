#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include "initWindow.h"

bool  bOrthoCam = true;
float aspRatio = 1.0;
float zoomFactor = 1.0;

void setCamera(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (bOrthoCam) {
		glOrtho(-2.0*aspRatio/zoomFactor, 2.0*aspRatio/zoomFactor, 
				-2.0/zoomFactor, 2.0/zoomFactor, 
				-200.0, 200.0);
	}
	else { // perspective camera
		gluPerspective(60/zoomFactor, aspRatio, 0.1, 100);
	}
	
}
void init(int argc, char **argv) {
	initWindow(&argc, argv);
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// 초기화
	setCamera();
	
}
void keyboard(unsigned char k, int x, int y) {
	switch (k) {
		case 'm': // camera mode change
			bOrthoCam = bOrthoCam?false:true;
			break;
		case '<': // zoom out
			zoomFactor *= 0.95;
			break;
		case '>': // zoom in
			zoomFactor *= 1.05;
			break;
		default:
			break;
	}
	setCamera();
	glutPostRedisplay();
}
void reshape(int w, int h) {
	aspRatio = float(w)/float(h);
	glViewport(0, 0, w, h);
	setCamera();
	
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glutWireTeapot(1.0);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}