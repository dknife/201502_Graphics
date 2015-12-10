#include <windows.h>
#include <stdlib.h>

#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
void init(void);
void display(void);
void reshape(int w, int h);

float angle = 0.0;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ACCUM);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Depth of Field");

	init(); // 초기화

	// 콜백 함수 등록 
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glutReshapeFunc(reshape);
	// keyboard, mouse, idle 등의 콜백 함수도 등록 가능

	glutMainLoop(); // 무한루프
	return 0;
}

void reshape(int w, int h) {
	float asp = float(w) / float(h); // aspect ratio (종횡비)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, asp, 0.1, 100);
	glutPostRedisplay();
}

void init(void) {
	glClearColor(0, 0, 0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DrawTeapotAt(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidTeapot(0.5);
	glPopMatrix();
}

float rand(float min, float max) {
	float d = max - min;
	return min + d * float(rand() % 10001) / 10000.0;
}

void display(void) {

	glClear(GL_ACCUM_BUFFER_BIT);

	srand(1);
	float jMag = 0.1;
	int renderingIteration = 1000;
	for (int rIdx = 0; rIdx<renderingIteration; rIdx++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(1.0 + rand(-jMag, jMag), 1.0 + rand(-jMag, jMag), 6.0,
			0, 0, 2, 0, 1, 0);
		for (int i = -5; i <= 5; i++) {
			glColor3f(rand(0, 1), rand(0, 1), rand(0, 1));
			DrawTeapotAt(0, 0, i);
		}
		glAccum(GL_ACCUM, 1.0 / renderingIteration);
	}
	glAccum(GL_RETURN, 1.0);

	glutSwapBuffers();
}
