#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void drawCircle(float x, float y, float r) {
	float c, s, angle;
	glColor3f(1,1,0);
	glBegin(GL_LINES);
		int nV = 100;
		for(int i=0; i<nV; i++) {
			angle = i*2.0*3.141592 / float(nV);
			c = cos(angle); 
			s = sin(angle);
			
			glVertex3f(r*c+x, r*s+y, 0);
		}
	glEnd();
}
void drawRect(float x, float y, float w, float h) {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(x,y,0);
		glVertex3f(x,y-h,0);
		glVertex3f(x+w,y-h,0);
		glVertex3f(x+w,y,0);
	glEnd();
}
void drawTriangle(float x1, float y1, float z1,
				float x2, float y2, float z2,
				float x3, float y3, float z3) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x3,y3,z3);
	glEnd();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	static float angle = 0.0;
	angle+=0.001;
	gluLookAt(2.0*sin(angle),0,2.0*cos(angle), 0,0,0, 0,1,0);

	drawCircle(-0.5,0.5, 0.3);
	drawTriangle(-1,-0.5,0.5, 0,-0.5,0.5, -0.5,0.5,0.5);
	drawTriangle(-0.5,-0.5,-0.5, 0.5,-0.5,-0.5, 0,0.5,-0.5);
	
	drawCircle(0.5,0.5, 0.4);
	drawRect(0.4,0.5, 0.2,1);
    
	glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("A New GL Window");

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
    glutMainLoop();

    return 0;
}