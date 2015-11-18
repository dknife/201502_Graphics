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

#define TEXSIZE 16
GLubyte myTex[TEXSIZE][TEXSIZE][3];

#include <stdlib.h>
void CreateTexture(void) {
	for(int i=0;i<TEXSIZE;i++) {
		for(int j=0;j<TEXSIZE;j++) {
			for(int k=0;k<3;k++) {			
				myTex[i][j][k] = 
				(GLubyte) (255*float(rand()%1000)/999.0);
			} // end k
		} // end j
	} // end i
}

void SetupTexture(void) 
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
				 TEXSIZE, TEXSIZE, 0, GL_RGB, 
				 GL_UNSIGNED_BYTE, &myTex[0][0][0]);
	
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, 
					GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}

void init(int argc, char **argv) {
	initWindow(&argc, argv);
	
	// 초기화
	glClearColor(0.5, 0.9, 1.0, 1.0);
	CreateTexture();
	SetupTexture();
}

void reshape(int w, int h) {
	float asp = float(w)/float(h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, asp, 0.1, 1000.0);
}


void drawAPlane(void) {
	float m=-1;
	float p= 1;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(m,p,0); 
	glTexCoord2f(0, 0);
	glVertex3f(m,m,0); 
	glTexCoord2f(1, 0);
	glVertex3f(p,m,0); 
	glTexCoord2f(1, 1);
	glVertex3f(p,p,0);
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	
	drawAPlane();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}