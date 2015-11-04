#include "Mesh.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

void CMesh::loadMesh(const char *fname) {
	FILE *fptr;
	fopen_s(&fptr, fname, "r");
	
	if (!fptr) { printf("file open error\n"); exit(0); }
	// vertex information
	fscanf_s(fptr, "%d", &nV);
	v = new cvertex[nV];
	for (int i = 0; i < nV; i++) {
		fscanf_s(fptr, "%f", &v[i].x);
		fscanf_s(fptr, "%f", &v[i].y);
		fscanf_s(fptr, "%f", &v[i].z);
	}
	// face information
	fscanf_s(fptr, "%d", &nF);
	f = new cface[nF];
	for (int i = 0; i < nF; i++) {
		fscanf_s(fptr, "%d", &f[i].v0);
		fscanf_s(fptr, "%d", &f[i].v1);
		fscanf_s(fptr, "%d", &f[i].v2);
	}

}

void CMesh::drawMesh() {
	glBegin(GL_POINTS);
	for(int i=0;i<nV;i++) glVertex3f(v[i].x, v[i].y, v[i].z);
	glEnd();
}