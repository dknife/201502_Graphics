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
#include "Camera.h"

bool bOrthoCam = false;
float aspRatio = 1.0;
float zoom = 1.0;

CCamera myCam;

GLfloat matSpec[] = {1.0, 1.0, 1.0, 1.0};
GLfloat matDiff[] = {1.0, 1.0, 0.0, 1.0};
GLfloat matAmbi[] = {0.1, 0.1, 0.1, 1.0};
GLfloat matShin[] = {127.0};

GLfloat light[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightPos[] = {1.0, 1.0, 1.0, 0.0};

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
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

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
	myCam.setGLCamera(); //gluLookAt(0.0, 2.5, 5.0, 0,0,0, 0,1,0);
	LightPosition();

	glDisable(GL_LIGHTING);
	glLineWidth(1);
	drawPlane();

	glLineWidth(5);
	drawAxes();
	
	glEnable(GL_LIGHTING);
	glutSolidTeapot(0.5);
	
	glutSwapBuffers();
}



void setCamera(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(!bOrthoCam)	gluPerspective(60/zoom, aspRatio, 0.1, 100);
	else glOrtho(-5*aspRatio/zoom,5*aspRatio/zoom,-5/zoom,5/zoom,-50,50);
	glutPostRedisplay();
}

void reshape(int w, int h) {
	aspRatio = float(w)/h;
	glViewport(0,0,w,h);

	setCamera();
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 27: exit(0);
	case 'c': bOrthoCam = bOrthoCam?false:true; break;
	case 'w': zoom *= 1.05; break;
	case 's': zoom *= 0.95; break;
	case 'o': myCam.moveForward( 0.05); break;
	case 'l': myCam.moveForward(-0.05); break;
	case 'k': myCam.moveRight(-0.05); break;
	case ';': myCam.moveRight( 0.05); break;
	case 'i': myCam.moveUp( 0.05); break;
	case 'p': myCam.moveUp(-0.05); break;
	case ',': myCam.rotate( 0.01f); break;
	case '.': myCam.rotate(-0.01f); break;
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
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Camera - Aspect");

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