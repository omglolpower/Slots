#include"Some_classes.h"


oglArray::oglArray()
	{
		R = G = B = 1.0f;
		glArrayType = 0;
		vert = 0;
		center[0] = center[1] = 0.0f;
	};
oglArray::~oglArray() {};
	
	void oglArray::centerFuncX()
	{
		for (int i = 0; i < vPositions.size(); ++i, ++i)
			vPositions[i] += center[0];
	}
	void oglArray::centerFuncY()
	{
		for (int i = 1; i < vPositions.size(); ++i, ++i)
			vPositions[i] += center[1];
	}
	void oglArray::centerFunc()
	{
		centerFuncX();	centerFuncY();
	}
	void oglArray::MoveCenterX(float move)
	{
		center[0] += move;
		for (int i = 0; i < vPositions.size(); ++i, ++i)
			vPositions[i] += move;
	}
	void oglArray::MoveCenterY(float move)
	{
		center[1] += move;
		for (int i = 1; i < vPositions.size(); ++i, ++i)
			vPositions[i] += move;
	}
	void oglArray::MoveCenter(float moveX, float moveY)
	{
		MoveCenterX(moveX);
		MoveCenterY(moveY);
	}

	
	
		cTriangle::cTriangle()
		{
			R = G = B = 0.5f;
			glArrayType = 4; //GL_TRIANGLES
			vert = 3;
			vPositions.resize(6, 0);
			vPositions[0] = -2.0f / 1.732f * 0.5f;
			vPositions[1] = -1.0f;
			vPositions[2] = 0.0f * 0.5f;
			vPositions[3] = 1.0f;
			vPositions[4] = 2.0f / 1.732f * 0.5f;
			vPositions[5] = -1.0f;
			centerFunc();
			type = 0;
		}
		cTriangle::cTriangle(
			float r, float g, float b,
			float scale,
			float centerX, float centerY
		)
		{
			type = 0;
			R = r;
			G = g;
			B = b;
			glArrayType = 4; //GL_TRIANGLES
			vert = 3;
			vPositions.resize(6, 0);
			vPositions[0] = -2.0f / 1.732f * 0.5f*scale;
			vPositions[1] = -1.0f * scale;
			vPositions[2] = 0.0f * 0.5f;
			vPositions[3] = 1.0f * scale;
			vPositions[4] = 2.0f / 1.732f * 0.5f*scale;
			vPositions[5] = -1.0f * scale;
			center[0] = centerX;
			center[1] = centerY;
			centerFunc();
		}
	
		cRectangle::cRectangle()
		{
			R = G = B = 1.0f;
			glArrayType = 7; //gl_quads
			vert = 4;
			vPositions.resize(8, 0);
			vPositions[0] = 1.0f;
			vPositions[1] = 1.0f;
			vPositions[2] = -1.0f;
			vPositions[3] = 1.0f;
			vPositions[4] = -1.0f;
			vPositions[5] = -1.0f;
			vPositions[6] = 1.0f;
			vPositions[7] = -1.0f;
			centerFunc();
			type = 1;
		}
		cRectangle::cRectangle(
			float r, float g, float b,
			float aCnstr, float bCnstr,
			float centerX, float centerY
		)
		{
			R = r;
			G = g;
			B = b;
			glArrayType = 7; //gl_quads
			vert = 4;
			vPositions.resize(8, 0);
			vPositions[0] = aCnstr;
			vPositions[1] = bCnstr;
			vPositions[2] = -aCnstr;
			vPositions[3] = bCnstr;
			vPositions[4] = -aCnstr;
			vPositions[5] = -bCnstr;
			vPositions[6] = aCnstr;
			vPositions[7] = -bCnstr;
			center[0] = centerX;
			center[1] = centerY;
			centerFunc();
			type = 1;
		}

		cCircle::cCircle()
		{
			R = G = B = 1.0f;
			glArrayType = 9; //GL_POLYGON
			vert = 50;
			vPositions.resize(102, 0);
			for (int i = 0; i < 51; ++i)
			{
				vPositions[(i + 0) * 2] = cosf(PI() / 10.0f * static_cast<float>(i)) * 0.5f;
				vPositions[2 * (i + 0) + 1] = sinf(PI() / 10.0f * static_cast<float>(i))  ;
			}
			type = 3;
			centerFunc();

		}
		cCircle::cCircle(
			float r, float g, float b,
			float scale,
			float centerX, float centerY
			)
		{
			R = r;
			G = g;
			B = b;
			glArrayType = 9; //GL_POLYGON
			vert = 50;
			vPositions.resize(vert*2+2, 0);
			for (int i = 0; i < vert+1; ++i)
			{
				vPositions[(i + 0) * 2] = cosf(PI() / static_cast<float>(vert/2) * static_cast<float>(i)) * scale * 0.5f;
				vPositions[2 * (i + 0) + 1] = sinf(PI() / static_cast<float>(vert/2) * static_cast<float>(i)) * scale;
			}
			type = 3;
			center[0] = centerX;
			center[1] = centerY;
			centerFunc();
		}
		cStar::cStar()
		{
			R = G = B = 1.0f;
			glArrayType = 6; //GL_TRIANGLE_FAN
			vert = 11;
			vPositions.resize(24, 0);
			for (int i = 0; i < 51; i++)
			{
				vPositions[(i + 1) * 2] = cosf(PI() / 180 * i);
				vPositions[2 * (i + 1) + 1] = sinf(PI() / 180 * i);
			}
			centerFunc();
			type = 2;
		}
		cStar::cStar(
			float r, float g, float b,
			float scale,
			float centerX, float centerY
		)
		{
			R = r;
			G = g;
			B = b;
			glArrayType = 6; //GL_TRIANGLE_FAN
			vert = 12; 
			vPositions.resize(vert * 2+2, 0);
			vPositions[0] = 0.0f;
			vPositions[1] = 0.0f;
			for (int i = 0; i < vert; ++i)
			{
				vPositions[(i + 1) * 2] = cosf(PI() / static_cast<float>((vert-2) / 2) * static_cast<float>(i)+PI()/2.0f+ PI()) * scale * 0.5f;
				vPositions[2 * (i + 1) + 1] = sinf(PI() / static_cast<float>((vert-2) / 2) * static_cast<float>(i) + PI() / 2.0f+ PI()) * scale;
			}
			for (int i = 0; i < vert; ++i,++i)
			{
				vPositions[(i + 1) * 2]*=0.5f;
				vPositions[2 * (i + 1) + 1]*=0.5f;
			}

			
			center[0] = centerX;
			center[1] = centerY;
			centerFunc();
			type = 2;
		}

		cArrow::cArrow()
		{
			R = G = B = 0.5f;
			glArrayType = 4; //GL_TRIANGLES
			vert = 3;
			vPositions.resize(8, 0);
			vPositions[0] = -2.0f / 1.732f * 0.5f;
			vPositions[1] = -1.0f;
			vPositions[2] = 0.0f * 0.5f;
			vPositions[3] = 1.0f;
			vPositions[4] = 2.0f / 1.732f * 0.5f;
			vPositions[5] = -1.0f;
			centerFunc();
			type = 0;
		}
		cArrow::cArrow(
			float r, float g, float b,
			float scale,
			float centerX, float centerY
		)
		{
			type = 0;
			R = r;
			G = g;
			B = b;
			glArrayType = 7; //GL_TRIANGLES
			vert = 4;
			vPositions.resize(8, 0);
			vPositions[0] = -1.5f / 1.732f * 0.5f * scale;
			vPositions[1] = -1.0f * scale;
			vPositions[2] = 0.0f * 0.5f;
			vPositions[3] = 1.0f * scale;
			vPositions[4] = 1.5f / 1.732f * 0.5f * scale;
			vPositions[5] = -1.0f * scale;
			center[0] = centerX;
			center[1] = centerY;
			centerFunc();
			for (int i = 1; i <vPositions.size(); ++i, ++i)
			{
				vPositions[i] -= (scale -centerY);
			}
		}