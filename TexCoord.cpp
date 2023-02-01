#include "TexCoord.h"

TexCoord::TexCoord()
	: texU(0.0),
	texV(0.0)
{

}

TexCoord::TexCoord(float U, float V)
	: texU(U),
	texV(V)
{

}

void TexCoord::setTexCoord(float U, float V)
{
	this->setU(U);
	this->setV(V);
}

void TexCoord::setU(float U)
{
	this->texU = U;
}

void TexCoord::setV(float V)
{
	this->texV = V;
}