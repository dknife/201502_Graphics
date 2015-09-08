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
#include "initWindow.h"

float cameraDepth = 0;
float horizontalOffset = 0.0;


void init(int argc, char **argv) {
	
	initWindow(&argc, argv);
	
	// 추가적 초기화 ...
	glClearColor(0.3, 0.3, 0.3, 1.0);
	
	// 카메라의 종류를 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100.0);
}



void display() {
	
	// 카메라 위치
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0+horizontalOffset, 0.75, 3-cameraDepth, 
			  0, 0, 0, //0+horizontalOffset, 0.5, 0-cameraDepth, 
			  0, 1, 0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	draw();
	
	// 화면 송출
	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
		case 'w': cameraDepth+= 0.05; break;
		case 's': cameraDepth-= 0.05; break;
		case 'a': horizontalOffset-= 0.05; break;
		case 'd': horizontalOffset+= 0.05; break;
		default: break;
	}
	glutPostRedisplay();
}

int main (int argc, char **argv) {
	// 시스템 수행 전에 해야할 초기화 작업 수행
	init(argc, argv);
	
	// callback 등록
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	
	// 이벤트를 기다리는 루프로 들어감.
	glutMainLoop();
}