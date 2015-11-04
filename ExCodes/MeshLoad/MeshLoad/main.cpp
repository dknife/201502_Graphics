#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <stdio.h>
#include <math.h>

float aspRatio = 1.0;

GLfloat matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat matDiff[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat matAmbi[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat matShin[] = { 127.0 };

GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos[] = { -1.0, 1.0, 1.0, 1.0 };
GLfloat dir[] = { 0, 0, 0 };

void LightSet(void) {
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbi);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShin);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void LightPosition(void) {
	// change light position
	
	static float angle = 0.0;
	lightPos[0] = cos(angle);
	lightPos[1] = 2.0;
	lightPos[2] = sin(angle);
	lightPos[3] = 0;
	angle += 0.05;
	
}

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0); // x
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0); // y
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1); // z
	glEnd();
}


void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10, 10, 0, 0, 0, 0, 1, 0);

	LightPosition();

	glDisable(GL_LIGHTING);
	glLineWidth(5);
	drawAxes();

	glEnable(GL_LIGHTING);


	glutSwapBuffers();
}



void setCamera(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspRatio, 0.1, 100.0);

	glutPostRedisplay();
}

void reshape(int w, int h) {
	aspRatio = float(w) / h;
	glViewport(0, 0, w, h);

	setCamera();
}

void keyboard(unsigned char k, int x, int y) {
	switch (k) {
	case 27: exit(0);
	}
	setCamera();

}

void GLInit(void) {

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	LightSet();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("lights");

	GLInit();

	// display callback and idle callback
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	//reshape callback
	glutReshapeFunc(reshape);

	// keyboard callback
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}