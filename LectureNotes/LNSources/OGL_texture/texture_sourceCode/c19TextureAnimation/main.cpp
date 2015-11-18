#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include "initWindow.h"
#include "texture.h"

GLuint tex1, tex2;

// 재질 색상 (material colors)
GLfloat mat_diffuse[] = {1.0, 1.0, 0.7, 1.0};
GLfloat mat_specular[]= {1.0, 1.0, 1.0, 1.0};
GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};

// 재질의 반질거림 (shininess)
GLfloat mat_shininess[] = { 120.0 };

// 광원 색상 (light colors)
GLfloat lit_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lit_specular[]= {1.0, 1.0, 1.0, 1.0};
GLfloat lit_ambient[] = {0.0, 0.0, 0.0, 1.0};

// 광원 위치 (light position)
GLfloat lit_position[] = {1.0, 1.0, 1.0, 0.0}; // 방향광

void LightSet(void) { // light와 material 특성 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lit_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lit_ambient);
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	// 광원을 이용한 조명 계산을 사용하도록 설정
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void LightPositioning(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
}
void init(int argc, char **argv) {
	initWindow(&argc, argv);
	LightSet();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9, 1.0, 1.0, 1.0);
	
	glActiveTexture(GL_TEXTURE0); // TEXTURE STAGE 0
	tex1 = setTexture("terrain.jpg");
	glActiveTexture(GL_TEXTURE1); // TEXTURE STAGE 1
	tex2 = setTexture32("science.jpg");
}

void reshape(int w, int h) {
	float aspRatio = float(w)/float(h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspRatio, 0.1, 1000);	
	
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float t=0.0;
	t+=0.01;
	gluLookAt(0, 0, 1.0, 0, 0, 0, 0, 1, 0);
	LightPositioning();
	
	
	glActiveTexture(GL_TEXTURE0);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	//glRotatef(t, 0, 0, 1);
	glScalef(1.0+sin(t)*0.1, 1.0+sin(t)*0.1, 1.0);
	
	glActiveTexture(GL_TEXTURE1);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(t,0,0);
	glScalef(5.0, 5.0, 1.0);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	
	glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
	glVertex3f(-0.5,-0.5, 0.0);
	glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
	glVertex3f( 0.5,-0.5, 0.0);
	glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
	glVertex3f( 0.5, 0.5, 0.0);
	glEnd();
	
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}