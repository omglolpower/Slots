#pragma once
#include <vector>
#define PI() 3.14159265f
class oglArray
{
public:
	oglArray();
	~oglArray();
	int type;
	float center[2];
	
	float R, G, B;
	int glArrayType;
	unsigned int vert;
	std::vector<float> vPositions;
	void centerFuncX();
	void centerFuncY();
	void centerFunc();
	void MoveCenterX(float move);
	void MoveCenterY(float move);
	void MoveCenter(float moveX, float moveY);
};


class cTriangle : public oglArray
{
public:
	cTriangle();
	cTriangle(
		float r, float g, float b,
		float scale,
		float centerX, float centerY
	);
};
class cRectangle : public oglArray
{
public:
	cRectangle();
	cRectangle(
		float r, float g, float b,
		float aCnstr, float bCnstr,
		float centerX, float centerY
	);
};

class cCircle : public oglArray
{
public:
	cCircle();
	cCircle(
		float r, float g, float b,
		float scale,
		float centerX, float centerY
	);
};
class cStar : public oglArray
{
public:
	cStar();
	cStar(
		float r, float g, float b,
		float scale,
		float centerX, float centerY
	);
};
class cArrow : public oglArray
{
public:
	cArrow();
	cArrow(
		float r, float g, float b,
		float scale,
		float centerX, float centerY
	);
};