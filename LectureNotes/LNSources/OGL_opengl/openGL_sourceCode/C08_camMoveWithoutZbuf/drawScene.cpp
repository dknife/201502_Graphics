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

#include "drawScene.h"


void draw() {
	
	drawScene();
	
	drawAxes();
}

void drawScene() {
	
	// 그리기 코드
	
	glBegin(GL_QUADS);
	// 뚜껑
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f( 0.5, 0.5, -0.5);
	glVertex3f( 0.5, 0.5,  0.5);
	glVertex3f(-0.5, 0.5,  0.5);
	
	// 바닥 
	glColor3f(0.0,1.0,1.0);
	glVertex3f(-0.5,-0.5, -0.5);
	glVertex3f( 0.5,-0.5, -0.5);
	glVertex3f( 0.5,-0.5,  0.5);
	glVertex3f(-0.5,-0.5,  0.5);
	
	// 좌측 벽
	glColor3f(0.0,1.0,0.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5,  0.5);
	glVertex3f(-0.5,-0.5,  0.5);
	glVertex3f(-0.5,-0.5, -0.5);
	
	// 우측 벽
	glColor3f(1.0,1.0,1.0);
	glVertex3f( 0.5, 0.5, -0.5);
	glVertex3f( 0.5, 0.5,  0.5);
	glVertex3f( 0.5,-0.5,  0.5);
	glVertex3f( 0.5,-0.5, -0.5);
	glEnd();
	
}


void drawAxes() {
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glLineWidth(1);
}
