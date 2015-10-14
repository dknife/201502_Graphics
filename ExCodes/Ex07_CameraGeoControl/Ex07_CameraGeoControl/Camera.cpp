#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

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
	
}

void CCamera::moveUp(float d) {
	
}