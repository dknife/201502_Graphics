#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
	float c, s, angle;
	glBegin(GL_POLYGON);
		int nV = 100;
		for(int i=0; i<nV; i++) {
			angle = i*2.0*3.141592 / float(nV);
			c = cos(angle); 
			s = sin(angle);
			glColor3f(c,s,c*s);
			glVertex3f(c, s, 0.0);
		}
	glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("A New GL Window");

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}