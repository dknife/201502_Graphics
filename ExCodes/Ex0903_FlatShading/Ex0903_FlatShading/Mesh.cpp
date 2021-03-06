#include "Mesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	n = new cvertex[nV];
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

	// compute normal vectors
	computeNormals();

}

void CMesh::computeNormals(void) { // private method

	for (int i = 0; i<nV; i++) {
		n[i].x = n[i].y = n[i].z = 0.0;
	}

	for (int i = 0; i<nF; i++) {
		// compute normal for each face
		cvertex p0, p1, p2;
		cvertex vec1, vec2; cvertex normal;
		int v0, v1, v2;
		v0 = f[i].v0; v1 = f[i].v1; v2 = f[i].v2;
		p0 = v[v0];
		p1 = v[v1];
		p2 = v[v2];
		vec1.x = p1.x - p0.x; vec1.y = p1.y - p0.y; vec1.z = p1.z - p0.z;
		vec2.x = p2.x - p0.x; vec2.y = p2.y - p0.y; vec2.z = p2.z - p0.z;

		normal.x = vec1.y*vec2.z - vec1.z*vec2.y;
		normal.y = vec1.z*vec2.x - vec1.x*vec2.z;
		normal.z = vec1.x*vec2.y - vec1.y*vec2.x;

		// add the computed normal to normals of vertices in the face
		n[v0].x += normal.x; n[v0].y += normal.y; n[v0].z += normal.z;
		n[v1].x += normal.x; n[v1].y += normal.y; n[v1].z += normal.z;
		n[v2].x += normal.x; n[v2].y += normal.y; n[v2].z += normal.z;
	}

	for (int i = 0; i<nV; i++) {
		// normalize n[i]
		float len = sqrt(n[i].x*n[i].x + n[i].y*n[i].y + n[i].z*n[i].z);
		n[i].x /= len; n[i].y /= len; n[i].z /= len;
	}

}

void CMesh::drawMesh() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nF; i++) {		
		int v0 = f[i].v0;
		int v1 = f[i].v1;
		int v2 = f[i].v2;
		glNormal3f(n[v0].x, n[v0].y, n[v0].z);
		glVertex3f(v[v0].x, v[v0].y, v[v0].z);
		glVertex3f(v[v1].x, v[v1].y, v[v1].z);
		glVertex3f(v[v2].x, v[v2].y, v[v2].z);
		
	}
	glEnd();
}