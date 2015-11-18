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


CCamera::CCamera() {
	up[0] = 0.0; 
	up[1] = 1.0; 
	up[2] = 0.0;

	forward[0] = 0.0; 
	forward[1] = 0.0; 
	forward[2] = -1.0;

	right[0] = 1.0; 
	right[1] = 0.0; 
	right[2] = 0.0;

	loc[0] = 0.0;
	loc[1] = 0.0;
	loc[2] = 3.0; 
}

void CCamera::setGLCamera() {
	gluLookAt(loc[0], loc[1], loc[2],  // eye
				loc[0]+forward[0], loc[1]+forward[1], loc[2]+forward[2], // target
				up[0], up[1], up[2]);

}

void CCamera::moveForward(float d) {
	for(int i=0;i<3;i++) loc[i] += forward[i]*d;
}

void CCamera::moveRight(float d) {
	for(int i=0;i<3;i++) loc[i] += right[i]*d;	
}

void CCamera::moveUp(float d) {
	for(int i=0;i<3;i++) loc[i] += up[i]*d;	
}

void CCamera::rotate(float angle) {
	// change forward and right vectors
	float c = cos(angle);
	float s = sin(angle);	
	forward[0] =  c*forward[0] + s*forward[2];
	forward[2] = -s*forward[0] + c*forward[2];
	right[0]   =  c*right[0]   + s*right[2];
	right[2]   = -s*right[0]   + c*right[2];
}