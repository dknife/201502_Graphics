#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0); // x
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0); // y
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1); // z
	glEnd();
}

void drawPlane(void) {
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	for(int i=0;i<40;i++) {
		glVertex3f(-20, 0, i-20);
		glVertex3f( 20, 0, i-20);
	}
	for(int i=0;i<40;i++) {
		glVertex3f(i-20, 0, -20);
		glVertex3f(i-20, 0,  20);
	}
	glEnd();

	glColor3f(0,0,0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-20, 0,  0);
	glVertex3f( 20, 0,  0);
	glVertex3f(  0, 0,-20);
	glVertex3f(  0, 0, 20);
	glEnd();
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 2.5, 5.0, 0,0,0, 0,1,0);

	glLineWidth(1);
	drawPlane();

	glLineWidth(3);
	drawAxes();
	
	glLineWidth(1);

	glutWireTeapot(0.5);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	float asp = float(w)/h;
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, asp, 0.1, 100);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Camera - Aspect");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	// display callback and idle callback
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	//reshape callback
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}