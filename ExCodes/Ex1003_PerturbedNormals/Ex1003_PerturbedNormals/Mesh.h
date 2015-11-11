#ifndef MESH_2015_HHH
#define MESH_2015_HHH

#include <stdio.h>
#include <math.h>

class cvertex {
public:
	float x;
	float y;
	float z;
public:
	float len() { return sqrt(x*x + y*y + z*z); }
	void normalize() { float l = len(); x /= l;  y /= l; z /= l; }
};

class cface{
public:
	int v0;
	int v1;
	int v2;
};

class CMesh {
	
	int nV;
	int nF;
	
	cvertex *v;
	cvertex *n;
	cface   *f;

	void computeNormals(void);
	void perturbNormals(int r, int c);

public:
	CMesh(): nV(0), nF(0), v(NULL), f(NULL) { }
	~CMesh() { if (v) delete[] v; if (f) delete[] f; }

	void loadMesh(const char *fname);
	void createTerrain(int row, int col, float x, float z, float w, float h);	
	void drawMesh();
};

#endif