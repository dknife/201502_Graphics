#ifdef WIN32
#include <Windows.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <stdio.h>
#include <math.h>

GLfloat matShin[] = { 127.0 };


GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightAmb[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat lightPos[] = { 0.0, 1.0, 1.0, 0.0 };

void LightSet(void) {

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShin);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void LightPosition(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
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
	gluLookAt(0.0, 0.5, 1.5, 0, 0, 0, 0, 1, 0);
	LightPosition();

	glDisable(GL_LIGHTING);
	glLineWidth(5);
	drawAxes();

	glEnable(GL_LIGHTING);


	static float angle = 0.0;
	glRotatef(angle, 0.0, 1.0, 0.0);
	angle += 0.5;

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glColor4f(1, 0, 0, 1);
	glutSolidTeapot(0.5);
	glPopMatrix();

	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glutSolidTeapot(0.5);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthFunc(GL_EQUAL);
	glColor4f(0, 0, 1, 0.5);
	glutSolidTeapot(0.5);
	glDepthFunc(GL_LESS);


	glutSwapBuffers();
}




void reshape(int w, int h) {
	float aspRatio = float(w) / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspRatio, 0.1, 100);
	glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y) {
	switch (k) {
	case 27: exit(0);
	}

}

void GLInit(void) {

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.6, 0.3, 0.3, 1.0);

	LightSet();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Camera - Aspect");

	//glewInit();
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