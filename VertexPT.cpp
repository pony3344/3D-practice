#include "VertexPT.h"

VertexPT::VertexPT(float x, float y, float z, float U, float V)
	: coordinates(x, y, z),
	texCoord(U, V)
{

}

VertexPT::VertexPT(const Vector3D& v, const TexCoord& t)
{
	this->coordinates = v;
	this->texCoord = t;
}
