#ifdef WIN32
// window용 헤더
#include <windows.h>
#include <GL/GL.H>
#include <GL/glut.h>
#else
// Mac용 헤더
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


int width, height;

void init(void);
void display(void);
void reshape(int w, int h);
void DrawScene(float, float, float, float, float, float, float, float, float);
void DrawPlane(void);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE |
		GLUT_RGBA | GLUT_STENCIL);

	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Viewport & Scissors");

	init(); // 초기화


	// 콜백 함수 등록 
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop(); // 무한루프
	return 0;
}

void reshape(int w, int h)
{
	float asp = float(w) / float(h); // aspect ratio (종횡비)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	width = w;
	height = h;
	gluPerspective(45, asp, 0.1, 100);
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.5f, 0.6f, 0.8f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_STENCIL_TEST);
}


void DrawScene(float ex, float ey, float ez,
	float tx, float ty, float tz,
	float ux, float uy, float uz) {
	gluLookAt(ex, ey, ez, tx, ty, tz, ux, uy, uz);

	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	// 마름모 그리기 (스텐실 설정)
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	glStencilFunc(GL_EQUAL, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	// 주전자 그리기
	glColor3f(1, 1, 0);
	glutSolidTeapot(0.7);

}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawScene(0, 0, 3, 0, 0, 0, 0, 1, 0);


	glutSwapBuffers();
}
