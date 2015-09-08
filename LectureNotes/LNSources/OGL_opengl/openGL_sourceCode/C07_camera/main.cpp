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


void init(int argc, char **argv) {
	// 윈도우 설정 및 프레임 버퍼 설정
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(512,512);
	glutCreateWindow("Dr. Kang's Graphics Lecture");
	
	// 추가적 초기화 ...
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	// 카메라의 종류를 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100.0);
}

void drawScene() {
	// 그리기 코드
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	// 산 1
	glVertex2f(-0.75, -0.25);
	glVertex2f(0.0, 0.25);
	glVertex2f(0.25, -0.25);
	// 산 2
	glColor3f(0.5, 0.5, 0.1);
	glVertex2f(-0.25, -0.25);
	glVertex2f(0.75, 0.25);
	glVertex2f(1.0, -0.25);
	
	glEnd();
	
	
	glBegin(GL_QUADS);
	// 지붕
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-1.0, 0.25);
	glVertex2f(-0.75, 0.5);
	glVertex2f(-0.25, 0.5);
	glVertex2f(0.0, 0.25);
	
	// 집
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.75, 0.25);
	glVertex2f(-0.75, -0.25);
	glVertex2f(-0.25, -0.25);
	glVertex2f(-0.25, 0.25);
	
	// 나무
	glColor3f(0.7, 0.5, 0.0);
	glVertex2f(0.5, 0.25);
	glVertex2f(0.75, 0.25);
	glVertex2f(0.75, -0.25);
	glVertex2f(0.5, -0.25);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	// 점들의 정보
	int n=20;
	float radius=0.1;
	glColor3f(1.0, 1.0, 0.0);
	float angle = 0.0; float step=(3.14159*2.0)/n;
	while (angle<3.14159*2.0) {
		glVertex2f(radius*cos(angle), radius*sin(angle)+0.75);
		angle += step;
	} 
	glEnd();
	
	glBegin(GL_POLYGON);
	// 점들의 정보
	n=20;
	radius=0.25;
	glColor3f(0.0, 1.0, 0.0);
	angle = 0.0; step=(3.14159*2.0)/n;
	while (angle<3.14159*2.0) {
		glVertex2f(radius*cos(angle)+0.625, radius*sin(angle)+0.25);
		angle += step;
	} 
	
	glEnd();	
}


void drawAxes() {
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
}

void display() {
	static float t=0.0;
	// 카메라 위치
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
			  2.0*sin(t), 1, 2.0*cos(t), 
			  0, 0, 0, 
			  0, 1, 0);
	t+=0.001;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	drawScene();
	
	glLineWidth(5);
	drawAxes();
	glLineWidth(1);
	
	// 화면 송출
	glFlush();
};

int main (int argc, char **argv) {
	// 시스템 수행 전에 해야할 초기화 작업 수행
	init(argc, argv);
	
	// callback 등록
	glutDisplayFunc(display);
	glutIdleFunc(display);
	
	// 이벤트를 기다리는 루프로 들어감.
	glutMainLoop();
}