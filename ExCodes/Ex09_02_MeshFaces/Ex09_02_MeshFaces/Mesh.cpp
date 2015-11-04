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

	for (int i = 0; i < nF; i++) {
		glBegin(GL_LINE_LOOP);
		int v0 = f[i].v0;
		int v1 = f[i].v1;
		int v2 = f[i].v2;
		glVertex3f(v[v0].x, v[v0].y, v[v0].z);
		glVertex3f(v[v1].x, v[v1].y, v[v1].z);
		glVertex3f(v[v2].x, v[v2].y, v[v2].z);
		glEnd();
	}
}