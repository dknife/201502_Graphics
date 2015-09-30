#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void drawSphere(float r) {
	glPushMatrix();
	glRotatef(90, 1,0,0);
	glutWireSphere(r, 10, 10);
	glPopMatrix();
}

void myDisplay() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100); 
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 2.5, 5.0, 0,0,0, 0,1,0);

	static float angle = 0.0;
	angle += 1;

	// Sun
	glColor3f(1,1,0.5);
	glPushMatrix();
	glRotatef(angle*1.3, 0,1,0);
	drawSphere(0.5);	
	glPopMatrix();

	

	glPushMatrix();
	// Earth
	glColor3f(0.4, 0.7, 1.0);
	glRotatef(angle, 0,1,0); // 공전
	glTranslatef(1.5, 0, 0);
	glPushMatrix();
	glRotatef(angle*5, 0,1,0); // 자전 
	drawSphere(0.2);
	glPopMatrix();

	// Moon
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(angle, 0,1,0);
	glTranslatef(0.5, 0, 0);
	glRotatef(angle*3, 0,1,0);
	drawSphere(0.05);

	glPopMatrix();

	// Mars
	glColor3f(1, 0.3, 0.3);
	glRotatef(angle*0.5, 0,1,0); // 공전
	glTranslatef(3, 0, 0);
	glPushMatrix();
	glRotatef(angle*2.5, 0,1,0); // 자전 
	drawSphere(0.2);
	glPopMatrix();

	
    
	glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Solar System");

	glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
    glutMainLoop();

    return 0;
}