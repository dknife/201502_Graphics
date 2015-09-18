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
void drawArm() {
	glPushMatrix();
	glScalef(1.0, 4.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void drawHand() {
	glPushMatrix();
	glScalef(0.5, 2.0, 2.0);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void display() {
	
	// 카메라 위치
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
			  5, 5, 12, 
			  5, 5, 0, 
			  0, 1, 0);
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawAxes();
	
	glTranslated(0.0, 2.0, 0.0);
	drawLocalAxes();
	drawArm();

	glTranslated(0.0, 2.0, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslated(0.0, 2.0, 0.0);
	drawLocalAxes();
	drawArm();
	
	glPushMatrix(); 
	glTranslated(0.0, 2.0, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslated(0.0, 1.0, 0.0);
	drawLocalAxes();
	drawHand();
	glPopMatrix();
	
	glTranslated(0.0, 2.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glTranslated(0.0, 1.0, 0.0);
	drawLocalAxes();
	drawHand();
	
	
	
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
