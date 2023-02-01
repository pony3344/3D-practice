#include "Vector3D.h"

Vector3D::Vector3D()
	: x(0.0),
	y(0.0),
	z(0.0)
{

}

Vector3D::Vector3D(float x, float y, float z)
	: x(x),
	y(y),
	z(z)
{

}

void Vector3D::setX(float x)
{
	this->x = x;
}

void Vector3D::setY(float y)
{
	this->y = y;
}

void Vector3D::setZ(float z)
{
	this->z = z;
}

void Vector3D::setVector3D(float x, float y, float z)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}
