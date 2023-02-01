#pragma once

#include <vector>
#include "D3D9App.h"
#include "VertexPT.h"


using std::vector;

class PolygonFace
{
protected:
	vector<VertexPT> vertices;
	IDirect3DDevice9* vertexDevice;
	IDirect3DVertexBuffer9* vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	UINT num_vertices; 
	DWORD num_indices;
public:
	PolygonFace(IDirect3DDevice9* dev);

	~PolygonFace();

	void setVertex(float x, float y, float z, float tu, float tv);

	bool createVertexBuffer(bool useIndex = false);

	unsigned int getNumVertices() const { return this->num_vertices; }

	IDirect3DVertexBuffer9* getVertexBuffer() const { return this->vertexBuffer; }

};