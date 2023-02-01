#pragma once

class TexCoord
{
protected:
	float texU;
	float texV;
public:
	TexCoord();

	TexCoord(float U, float V);

	void setTexCoord(float U, float V);

	void setU(float U);

	void setV(float V);

	float getU() const { return this->texU; }

	float getV() const { return this->texV; }
};