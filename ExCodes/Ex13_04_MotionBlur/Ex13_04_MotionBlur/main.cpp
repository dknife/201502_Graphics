#ifdef WIN32
// window�� ���
#include <windows.h>
#include <GL/GL.H>
#include <GL/glut.h>
#else
// Mac�� ���
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
void DrawScene(void);
void DrawPlane(void);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM);


	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Accumulation Buffer");

	init(); // �ʱ�ȭ


	// �ݹ� �Լ� ��� 
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop(); // ���ѷ���
	return 0;
}

void reshape(int w, int h)
{
	float asp = float(w) / float(h); // aspect ratio (��Ⱦ��)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	width = w;
	height = h;
	gluPerspective(45, asp, 0.1, 100);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glAccum(GL_ACCUM, 1.0);
	glAccum(GL_RETURN, 1.0);
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// glColor3f�� �̿��ؼ� ���� ���� ������ �� �ִ�.
	glEnable(GL_COLOR_MATERIAL);

}


void DrawScene(void) {


	// ������ �׸���
	angle += 2;
	glColor3f(0.0, 0.5, 1.0);
	glPushMatrix();
	glRotated(angle, 0.0, 0.0, 1.0);
	glTranslated(0.0, 1.0, 0.0);

	glutSolidTeapot(0.7);
	glPopMatrix();

	glColor3f(1.0, 0.5, 0.0);
	glPushMatrix();
	glTranslated(0.0, 2.0*sin(angle*0.01), 0.0);

	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();


}


void display(void)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawScene();
	glAccum(GL_MULT, 0.75);
	glAccum(GL_ACCUM, 0.25);
	glAccum(GL_RETURN, 1.0);

	glutSwapBuffers();
}
