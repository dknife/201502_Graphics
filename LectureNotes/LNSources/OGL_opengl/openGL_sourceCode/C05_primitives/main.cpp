#include <stdio.h>
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
	glClearColor(1.0, 0.0, 0.0, 1.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// 그리기 코드
	glBegin(GL_TRIANGLES);
	// 점들의 정보
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	// 화면 송출
	glFlush();
};

int main (int argc, char **argv) {
	// 시스템 수행 전에 해야할 초기화 작업 수행
	init(argc, argv);
	
	// callback 등록
	glutDisplayFunc(display);
	// 이벤트를 기다리는 루프로 들어감.
	glutMainLoop();
}
