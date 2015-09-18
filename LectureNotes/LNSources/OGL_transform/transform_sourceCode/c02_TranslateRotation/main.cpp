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
	
	// 추가적 초기화 ...
	glClearColor(0.3, 0.3, 0.3, 1.0);
	
	// 카메라의 종류를 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(10.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0,10.0,0.0);
	glColor3f(0.0,0.0,1.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0,0.0,10.0);
	glEnd();
}

void drawLocalAxes() {
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.5,0.0,0.0);
	glColor3f(0.0,1.0,0.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0,0.5,0.0);
	glColor3f(0.0,0.0,1.0); 
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0,0.0,0.5);
	glEnd();
	glLineWidth(1);
}
void draw() {
	glutWireTeapot(0.30);
}

void display() {
	
	// 카메라 위치
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
			  2, 2, 3, 
			  0, 0, 0, 
			  0, 1, 0);
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawAxes();
	
	drawLocalAxes();
	glColor4f(1, 1, 0, 0.25);
	draw();

	glTranslatef(1.0, 0.0, 0.0);
	drawLocalAxes();
	glColor4f(0, 1, 1, 0.25);	
	draw();
	
	glRotatef(180, 0.0, 0.0, 1.0);
	glTranslatef(0.0,-1.0, 0.0);
	drawLocalAxes();
	glColor4f(1, 0, 0, 0.25);
	draw();
	
	
	glTranslatef(1.0, 0.0, 0.0);
	drawLocalAxes();
	glColor4f(1, 1, 1, 0.25);
	draw();
	
	// 화면 송출
	glutSwapBuffers();
}

int main (int argc, char **argv) {
	// 시스템 수행 전에 해야할 초기화 작업 수행
	init(argc, argv);
	
	// callback 등록
	glutDisplayFunc(display);
	glutIdleFunc(display);
	
	// 이벤트를 기다리는 루프로 들어감.
	glutMainLoop();
}
