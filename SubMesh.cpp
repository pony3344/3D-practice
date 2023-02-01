#include "SubMesh.h"

SubMesh::SubMesh(IDirect3DDevice9* dev)
{
	this->subDevice = dev;
}

SubMesh::~SubMesh()
{

}

PolygonFace* SubMesh::createPolygons(
	const VertexPT& v1,
	const VertexPT& v2,
	const VertexPT& v3,
	const VertexPT& v4)
{
	PolygonFace* face = new PolygonFace(subDevice);
	
	// First vertex.
	face->setVertex(v1.getCoordinates().getX(),
		v1.getCoordinates().getY(),
		v1.getCoordinates().getZ(),
		v1.getTexCoordinates().getU(),
		v1.getTexCoordinates().getV());

	// Second vertex.
	face->setVertex(v2.getCoordinates().getX(),
		v2.getCoordinates().getY(),
		v2.getCoordinates().getZ(),
		v2.getTexCoordinates().getU(),
		v2.getTexCoordinates().getV());

	// Third vertex.
	face->setVertex(v3.getCoordinates().getX(),
		v3.getCoordinates().getY(),
		v3.getCoordinates().getZ(),
		v3.getTexCoordinates().getU(),
		v3.getTexCoordinates().getV());
	
	// Fourth vertex.
	face->setVertex(v4.getCoordinates().getX(),
		v4.getCoordinates().getY(),
		v4.getCoordinates().getZ(),
		v4.getTexCoordinates().getU(),
		v4.getTexCoordinates().getV());

	face->createVertexBuffer();

	this->polygons.push_back(face);
	return face;
}

void SubMesh::drawSubMesh(unsigned int id)
{
	this->submeshID = id;
	if (submeshID >= 0)
	{
		vector<PolygonFace*>::const_iterator i;
		for (i = polygons.begin(); i != polygons.end(); i++)
		{
			PolygonFace* p = (*i);
			this->subDevice->SetStreamSource(0, p->getVertexBuffer(), 0, sizeof(VertexPT));
			this->subDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, p->getNumVertices() / 3);

		}
	}
}
