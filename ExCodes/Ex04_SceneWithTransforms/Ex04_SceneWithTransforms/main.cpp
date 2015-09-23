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

void drawCircle() {
	float c, s, angle;
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		int nV = 100;
		for(int i=0; i<nV; i++) {
			angle = i*2.0*3.141592 / float(nV);
			c = 0.5*cos(angle); 
			s = 0.5*sin(angle);			
			glVertex3f(c, s, 0);
		}
	glEnd();
}
void drawRect() {
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(-0.5,-0.5, 0.0);
		glVertex3f( 0.5,-0.5, 0.0);
		glVertex3f( 0.5, 0.5, 0.0);		
	glEnd();
}
void drawTriangle() {
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -sqrt(0.75)/2, 0.0);
		glVertex3f( 0.5, -sqrt(0.75)/2, 0.0);
		glVertex3f( 0.0, sqrt(0.75)/2, 0.0);
	glEnd();
}

void myDisplay() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	static float angle = 0.0;
	angle+=0.01;
	gluLookAt(0.0, 0.5 ,5.0, 0,0,0, 0,1,0);

	drawAxes();

	// 현재 상태를 저장하자!
	glPushMatrix();
	glTranslatef(-1,2,0);   // T
	glScalef(0.25, 0.25, 1); // S
	drawCircle();
	glPopMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix(); // !!!!!!
	glTranslatef(-1.0, 0.4,-0.1);
	glScalef(3,3,3);
	drawTriangle();
	glPopMatrix(); // !!!!!! 상태를 불러와라.

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix(); // !#@$!@#$
	glTranslatef( 1.0, 0.4, -0.3);
	glScalef(3,3,3);
	drawTriangle();
	glPopMatrix(); // !@#$!@#$ 상태를 불러와라.
	
	glTranslatef(1.0, 2.0, 1.0);
	drawCircle();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.25, 3.0, 1.0);
	glTranslatef(0.0, -0.5, 0.0);
	drawRect();
    
	//glFlush();
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