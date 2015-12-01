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
float angle = 0.0;
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
	glutCreateWindow("Mirror");

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glColor3f를 이용해서 재질 색을 결정할 수 있다.
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_STENCIL_TEST);
}


void DrawScene(float ex, float ey, float ez,
	float tx, float ty, float tz,
	float ux, float uy, float uz) {
	gluLookAt(ex, ey, ez, tx, ty, tz, ux, uy, uz);

	angle += 1.0;

	glClear(GL_STENCIL_BUFFER_BIT);

	// 주전자 그리기
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glColor3f(0.0, 0.5, 1.0);
	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0);
	glRotated(angle, 0.0, 0.0, 1.0);
	glutSolidTeapot(0.7);
	glPopMatrix();


	// 거울을 위한 스텐실 영역 설정
	glColorMask(0, 0, 0, 0);
	glDepthMask(0);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glColorMask(1, 1, 1, 1);
	glDepthMask(1);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);


	// 주전자의 거울상 그리기
	glColor3f(0.0, 0.5, 1.0);
	glPushMatrix();
	glScalef(1.0, -1.0, 1.0);
	glTranslated(0.0, 1.0, 0.0);
	glRotated(angle, 0.0, 0.0, 1.0);
	glutSolidTeapot(0.7);
	glPopMatrix();


	glColor4f(1.0, 1.0, 0.0, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();


}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawScene(3, 4, 3, 0, 0, 0, 0, 1, 0);


	glutSwapBuffers();
}
