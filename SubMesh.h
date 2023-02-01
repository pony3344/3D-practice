#pragma once

#include "PolygonFace.h"

class SubMesh
{
protected:
	unsigned int submeshID;
	vector<PolygonFace*> polygons;
	IDirect3DDevice9* subDevice;
	
public:
	SubMesh(IDirect3DDevice9* dev);

	~SubMesh();

	PolygonFace* createPolygons(
		const VertexPT& v1,
		const VertexPT& v2,
		const VertexPT& v3,
		const VertexPT& v4);

	void drawSubMesh(unsigned int id);

};