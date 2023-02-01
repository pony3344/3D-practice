#pragma once

class Vector3D
{
protected:
	float x;
	float y;
	float z;
public:
	Vector3D();

	Vector3D(float x, float y, float z);

	void setX(float x);

	void setY(float y);

	void setZ(float z);

	void setVector3D(float x, float y, float z);

	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

};