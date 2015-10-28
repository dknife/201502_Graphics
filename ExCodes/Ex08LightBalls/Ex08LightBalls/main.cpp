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
bool bLightRotate = true;
bool bPointLight = true;
bool bSpotLight = false;


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
	if (bLightRotate) {
		float r = 7;
		static float angle = 0.0;
		lightPos[0] = r * cos(angle);
		lightPos[1] = 0.0;
		lightPos[2] = r * sin(angle);
		lightPos[3] = bPointLight?1.0:0.0;
		angle += 0.05;
	}
	if (bSpotLight) {
		dir[0] = -lightPos[0];
		dir[1] = -lightPos[1];
		dir[2] = -lightPos[2];
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	}
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



void drawSpheres(void) {
	for (int x = -5; x <= 5; x++) {
		for (int y = -5; y <= 5; y++) {
			glPushMatrix();
			glTranslatef(x, y, 0);
			glutSolidSphere(0.5, 100, 100);
			glPopMatrix();
		}
	}
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	LightPosition();

	glDisable(GL_LIGHTING);
	glLineWidth(5);
	drawAxes();

	// light source
	glPushMatrix();
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	drawSpheres();


	glutSwapBuffers();
}



void setCamera(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8*aspRatio, 8*aspRatio, -8, 8, -10, 10);
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
	case 'r': bLightRotate = bLightRotate ? false : true; break;
	case 'p': bPointLight = bPointLight ? false : true; break;
	case 's': bSpotLight = bSpotLight ? false : true; break;
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