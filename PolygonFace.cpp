#include "PolygonFace.h"

PolygonFace::PolygonFace(IDirect3DDevice9* dev)
{
	this->vertexDevice = dev;
	this->vertexBuffer = NULL;
	this->num_vertices = 0;
}

PolygonFace::~PolygonFace()
{

}

void PolygonFace::setVertex(float x, float y, float z, float tu, float tv)
{
	VertexPT p = VertexPT(x, y, z, tu, tv);
	this->vertices.push_back(p);
}

bool PolygonFace::createVertexBuffer(bool useIndex)
{
	this->num_vertices = (unsigned int)(vertices.size());
	HRESULT hr = vertexDevice->CreateVertexBuffer(
		num_vertices * sizeof(VertexPT),
		D3DUSAGE_DYNAMIC,
		D3DFVF_XYZ | D3DFVF_TEX0,
		D3DPOOL_DEFAULT,
		&vertexBuffer, NULL);

	if (FAILED(hr))
	{
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Could not create vertex buffer.", MB_OK | MB_ICONERROR);
		return false;
	}

	VOID* data = NULL;
	vertexBuffer->Lock(0, 0, (void**)&data, 0);
	memcpy(data, vertices.data(), sizeof(VertexPT));
	vertexBuffer->Unlock();

	return true;
}