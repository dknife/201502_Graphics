#ifndef MESH_2015_HHH
#define MESH_2015_HHH

#include <stdio.h>

class cvertex {
public:
	float x;
	float y;
	float z;
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
	cface *f;

	void computeNormals(void);

public:
	CMesh(): nV(0), nF(0), v(NULL), f(NULL) { }
	~CMesh() { if (v) delete[] v; if (f) delete[] f; }

	void loadMesh(const char *fname);
	void drawMesh();
};

#endif