#pragma once

#include "Vector3D.h"
#include "TexCoord.h"

class VertexPT
{
protected:
	Vector3D coordinates;
	TexCoord texCoord;
public:
	VertexPT(float x, float y, float z, float U, float V);

	VertexPT(const Vector3D& v, const TexCoord& t);

	Vector3D getCoordinates() const { return this->coordinates; }

	TexCoord getTexCoordinates() const { return this->texCoord; }

};