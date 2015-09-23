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

void drawTeapot() {
	glutWireTeapot(0.5);
}


void myDisplay() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawAxes();
	drawTeapot();
	glTranslatef(1,0,0);
	glColor3f(1,1,0);
	drawTeapot();
	glTranslatef(0,1,0);
	glRotatef(180, 0,0,1);
	drawTeapot();
	glTranslatef(1,0,0);
	drawTeapot();
    
	glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Transform");

	glEnable(GL_DEPTH_TEST);

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
    glutMainLoop();

    return 0;
}