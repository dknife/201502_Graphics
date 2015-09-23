#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void drawCircle() {
	float c, s, angle;
	glColor3f(1,1,0);
	glBegin(GL_LINES);
		int nV = 100;
		for(int i=0; i<nV; i++) {
			angle = i*2.0*3.141592 / float(nV);
			c = cos(angle); 
			s = sin(angle);			
			glVertex3f(c, s, 0);
		}
	glEnd();
}
void drawRect() {
	glBegin(GL_QUADS);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(-0.5,-0.5, 0.0);
		glVertex3f( 0.5,-0.5, 0.0);
		glVertex3f( 0.5, 0.5, 0.0);		
	glEnd();
}
void drawTriangle() {
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f( 0.5, 0.0, 0.0);
		glVertex3f( 0.0, sqrt(0.75), 0.0);
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
	gluLookAt(2.0*sin(angle),0,2.0*cos(angle), 0,0,0, 0,1,0);

	drawCircle();
	glColor3f(0.0, 1.0, 0.0);
	drawTriangle();
	glColor3f(0.0, 0.0, 1.0);
	drawTriangle();
	
	drawCircle();
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