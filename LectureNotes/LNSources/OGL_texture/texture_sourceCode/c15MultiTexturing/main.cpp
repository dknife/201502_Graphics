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

// 재질에 설정될 값
GLfloat mat_specular[] = {0.0,1.0f,1.0f, 1.0f };
GLfloat mat_diffuse[] =  {1.0,1.0f,1.0f, 1.0f };
GLfloat mat_ambient[] =  {1.0,1.0f,1.0f, 1.0f };
GLfloat mat_shininess[] = { 120.0 };
// 광원에 설정될 값
GLfloat lit_specular[] = { 1.0,1.0f,1.0f,1.0f };
GLfloat lit_diffuse[] =  { 1.0,1.0f,1.0f,1.0f };
GLfloat lit_ambient[] =  { 0.0,0.0f,0.0f,1.0f };

// 광원의 위치 (방향광)
GLfloat light_position[] = {1.0,1.0f,1.0f,0.0f};

void LightSet(void) {
	glMaterialfv(GL_FRONT, GL_SPECULAR, 
				 mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, 
				 mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, 
				 mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, 
				 mat_shininess);
	glLightfv(GL_LIGHT0, GL_SPECULAR, 
			  lit_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, 
			  lit_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, 
			  lit_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void LightPositioning(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, 
			  light_position);
}



void init(int argc, char **argv) {
	initWindow(&argc, argv);
	
	// 초기화
	glClearColor(0.5, 0.9, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	tex1 = setTexture("surface.jpg");
	glActiveTexture(GL_TEXTURE1);
	tex2 = setTexture("spheremap.jpg");
	LightSet();
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
	float asp = float(w)/float(h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, asp, 0.1, 1000.0);
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	LightPositioning();
	
	static float angle = 0.0;
	glRotatef(angle, 0, 1, 1);
	angle += 0.5;
	
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	
	glutSolidTeapot(1.2);
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}