#include <ctime>
#include <math.h>
#include "MyShaders.h"
#include "Some_classes.h"
#include "Vars.h"
#define LOG(x) std::cout << x << std::endl;




//some variables for circle positioning and color:


std::ostringstream ossvs, ossfs;
std::ifstream ssvs("C:\\dev\\shaders\\BasicVertexShader.txt");
std::ifstream ssfs("C:\\dev\\shaders\\UniformBasicFragmentShader.txt");

template <typename T>
void def(std::vector<T> in, T number)
{
	for (int i = 0; i < in.size(); ++i)
		in+=number;
}
//this function will draw a circle:


bool checkPress(cRectangle obj, oglArray arrow)
{
	bool check = false;
	
	if (
		arrow.center[0]<obj.vPositions[0] &&
		arrow.center[1] <obj.vPositions[1] &&
		arrow.center[0] > obj.vPositions[4] &&
		arrow.center[1] > obj.vPositions[5]
		) check = true;
	return check;
}

void drawArrays0(
	float redVar, float greenVar, float blueVar,
	int arrayType, std::vector<float> vPosVar,
	unsigned int nVert
)
{
	float *pos = new float[vPosVar.size()];
	for (short i = 0; i < vPosVar.size(); ++i)
		pos[i] = vPosVar[i];
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*nVert*2, pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 2,
		0);
	glUniform4f(location, redVar, greenVar, blueVar, 1.0f);
	glDrawArrays(arrayType, 0, nVert);
	glDeleteBuffers(1,
		&buffer);
		delete pos;
}
void drawArrays(oglArray in)
{
	drawArrays0(
		in.R, in.G, in.B,
		in.glArrayType, in.vPositions,
		in.vert
	);
}
void mouse(GLFWwindow* w, cArrow& a)
{
	float xm0, ym0;
	
	xm0 = xm;
	ym0 = ym;
	glfwGetCursorPos(w,
		&valueDCX,
		&valueDCY
	);
	xm = static_cast<float>(valueDCX);
	ym = static_cast<float>(valueDCY);
	
	//std::cout << "xm0 = " << xm0 << ";\tym0 = " << ym0 << ";\txm = " << xm << ";\tym = " << ym<<std::endl;

	a.MoveCenterX((xm - xm0 )/800.0f);
	a.MoveCenterY(-(ym - ym0) / 400.0f);

	//std::cout << "CenterX = " << a.center[0] << ";\tCenterY = " << a.center[1] << std::endl;

	if (a.center[0] > 1.0f) a.MoveCenterX(1.0f - a.center[0]);
	if (a.center[1] > 1.0f) a.MoveCenterY(1.0f - a.center[1]);
	if (a.center[0] < -1.0f) a.MoveCenterX(-1.0f - a.center[0]);
	if (a.center[1] < -1.0f) a.MoveCenterY(-1.0f - a.center[1]);
}



//main function. creating window, context, etc.:
int main(void)
{
	

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(screenWidth, screenHeight, "$lots", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	ossvs << ssvs.rdbuf();
	ossfs << ssfs.rdbuf();

	vertexShader = ossvs.str();
	fragmentShader = ossfs.str();
	unsigned int  shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
	location = glGetUniformLocation(shader, "u_Color");
	glfwGetPrimaryMonitor();

	glfwSetInputMode(window,
		GLFW_CURSOR,
		GLFW_CURSOR_DISABLED
	);
	
	cRectangle background;
	
	cRectangle bgSlots{
		0.0f, 0.0f, 0.0f,
		bgSlotsA, bgSlotsB,
		bgSlotsX, bgSlotsY
	};
	
	cRectangle stop{
		0.0f, 0.0f, 0.0f,
		buttonA, buttonB,
		buttonX, -buttonY
	};

	cRectangle start{
		0.0f, 0.0f, 0.0f,
		buttonA, buttonB,
		buttonX, buttonY
	};

	cCircle circle{
		0.2f,0.5f,0.6f,
		0.5f,
		0.0f,0.0f
	};

	for (int i = 0; i < 5; ++i)
	{
		barrelsX[i] = bgSlotsX + (i - 2) * barrelA * 2.0f;
	}
	cRectangle* barrels = new cRectangle[5];
	for (int i = 0; i < 5; ++i)
	{
		barrels[i] = cRectangle(
			1.0f, 1.0f, 1.0f,
			barrelA * 0.979f, barrelB * 0.99f,
			barrelsX[i], bgSlotsY
		);

	}
	
	for (int i = 0; i < 5; ++i)
	{
		slotY[i] = bgSlotsY - 2.0f * bgSlotsB / 3.0f * static_cast<float>(i - 2);
	}
	oglArray** slots = new oglArray * [5];
	for (int i = 0; i < 5; ++i)
	{
		slots[i] = new oglArray[5];
	}
	std::srand(std::time(nullptr));
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			int iRand = rand() % 4;
			switch (iRand)
			{
			case 0:
				slots[i][j] = cRectangle(
					0.0f, 0.0f, 0.0f,
					squareA * ratio, squareA,
					barrelsX[i], slotY[j]
				); break;
			case 1:
				slots[i][j] = cTriangle(
					0.0f, 0.0f, 0.0f,
					squareA,
					barrelsX[i], slotY[j]
				); break;
			case 2:
				slots[i][j] = cCircle(
					0.0f, 0.0f, 0.0f,
					squareA,
					barrelsX[i], slotY[j]
				); break;
			case 3:
				slots[i][j] = cStar(
					0.0f, 0.0f, 0.0f,
					squareA * 1.1f,
					barrelsX[i], slotY[j]
				); break;
			}
		}

	
	cArrow* arrow = new cArrow{
		0.0f, 0.0f, 0.0f,
		squareA * 0.45f,
		0.0f, 0.0f
	};
	cArrow* arrow1 = new cArrow{
		0.8f, 0.8f, 0.0f,
		squareA * 0.3f,
		0.0f, 0.0f
	};
	cArrow* arrow2 = new cArrow{
		0.8f, 0.8f, 0.0f,
		squareA * 0.3f*0.9f,
		0.0f, 0.0f
	};
	glfwGetCursorPos(window,
		&valueDCX,
		&valueDCY
	);

	xm = static_cast<float>(valueDCX);
	ym = static_cast<float>(valueDCY);
	

	cRectangle plateLower{
		1.0f, 1.0f, 1.0f,
		bgSlotsA, bgSlotsB,
		bgSlotsX, bgSlotsY-2.0f* bgSlotsB
	};
	cRectangle plateUpper{
		1.0f, 1.0f, 1.0f,
		bgSlotsA, bgSlotsB,
		bgSlotsX, bgSlotsY + 2.0f * bgSlotsB
	};

	oglArray* spin0 = new cCircle[4];
	spin0[0] = cTriangle(
		0.0f, 0.0f, 0.0f,
		squareA,
		0.0f, 0.0f
	);
	spin0[1] = cRectangle(
		0.0f, 0.0f, 0.0f,
		squareA * ratio, squareA,
		0.0f, 0.0f
	);
	spin0[2] = cStar(
		0.0f, 0.0f, 0.0f,
		squareA * 1.1f,
		0.0f, 0.0f
	);
	spin0[3] = cCircle(
		0.0f, 0.0f, 0.0f,
		squareA,
		0.0f, 0.0f
	);
	
	oglArray* stopSign = new cRectangle(
		1.0f, 1.0f, 1.0f,
		buttonB * ratio*0.5f, buttonB*0.5f,
		buttonX, -buttonY
	);
	oglArray* startSign = new cTriangle(
		1.0f, 1.0f, 1.0f,
		buttonB*0.5f,
		0.0f, 0.0f
	);
	
	for (int i = 0; i < startSign->vPositions.size()-1; ++i,++i)
	{
		float x = startSign->vPositions[i];
		float y = startSign->vPositions[i + 1];
		startSign->vPositions[i] = y;
		startSign->vPositions[i + 1] = -x;
		startSign->vPositions[i] *= 0.5f;
		startSign->vPositions[i + 1] *= 2.0f;
		startSign->vPositions[i] += buttonX;
		startSign->vPositions[i + 1] += buttonY;
	}
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		drawArrays(background);
		drawArrays(bgSlots);
		drawArrays(start);
		drawArrays(stop);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			++waitLMB; else waitLMB = 0;
		if (waitLMB == 1)
		{
			if (mayPressStart)
			{
				if (checkPress(start, *arrow))
				{
					LOG("PRESSED START")
					for (int i = 0; i < 5; ++i) speedUpSet[i] = true;
					motion = true;
					slow = false;
					mayPressStart = false;
					timerStop = 0;
					speedZero = false;
				}
			}
			if (mayPressStop)
			{
				if (checkPress(stop, *arrow))
				{
					LOG("PRESSED STOP")
					for (int i = 0; i < 5; ++i) speedUpSet[i] = true;
					motion = false;
					slow = true;
					mayPressStop = false;
				}
			}
		}
		
		if (motion)
		{
			++timerStop;
			for (int i = 0; i < 5; ++i)
			{
				if (speedUpSet[i])
				{
					speedUp[i] = true;
					randLag[i] = rand() % 25;
					speedUpSet[i] = false;
				}
				if (speedUp[i]) {  if (randLag[i] < 1)speed[i] += 0.00013f; else --randLag[i]; }
				if (speed[i] > 0.017f) {
					speedUp[i] = false; mayPressStop = true;
				}
			}
		}
		
		if (timerStop == 400)
		{
			LOG("AUTO STOP")
			timerStop = 0;
			for (int i = 0; i < 5; ++i) speedUpSet[i] = true;
			motion = false;
			slow = true;
			mayPressStop = false;
			
		}

		if (slow)
		{
			for (int i = 0; i < 5; ++i)
			{
				if ( speedUpSet[i])
				{
					speedUp[i] = true;
					randLag[i] = rand() % 15;
					speedUpSet[i] = false;
				}
				if (speedUp[i]) { if (randLag[i] < 1)speed[i] -= 0.0002f; else --randLag[i]; }
				if (speed[i] < 0.005f) 
				{
					speed[i] = 0.0025f;
					speedUp[i] = false;  
					for (int j = 0; j < 5; ++j)
					{
						if (slots[i][j].center[1] < 0.0025f && slots[i][j].center[1] > -0.025f)
						{
							speed[i] = 0.0f;
						}
					}
					if (speed[0] == 0.0f &&
						speed[1] == 0.0f &&
						speed[2] == 0.0f &&
						speed[3] == 0.0f &&
						speed[4] == 0.0f)
					{
						speedZero = true;
					}
				}
			}
		}
		
		
			if (
				speedZero)
			{
				
				checkMatch=true;
				speedZero = false;
				slow = false;
				m = 0;
			}
			if (checkMatch)
			{		
					for (int i = 0; i < 5; ++i)
					{
						for (int j = 0; j < 5; ++j)
						{
							if (slots[i][j].type == m)
							{
								origCenter[0] = slots[i][j].center[0];
								origCenter[1] = slots[i][j].center[1];
								for (int k = 0; k < slots[i][j].vPositions.size(); ++k, ++k)
									slots[i][j].vPositions[k] = spin0[m].vPositions[k] * cosf(angle) + origCenter[0];
								
							}
						}
					}
					angle += 0.05f;
					if (angle > PI())
					{
						angle = 0.0f;
						++m;
					}
					if (m > 3)
					{
						checkMatch = false;
						mayPressStart = true;
					}
			}
			
			
		for (int i = 0; i < 5; ++i)
			drawArrays(barrels[i]);

		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
				drawArrays(slots[i][j]);
		if (motion || slow)
			for (int i = 0; i < 5; ++i)
				for (int j = 0; j < 5; ++j)
				{
					slots[i][j].MoveCenterY(-speed[i]*speedConst );
					if (slots[i][j].center[1] < slotY[4])
					{
						counter[i]++;
						int iRand = rand() % 4;
						float difference = slotY[4]-slots[i][j].center[1];
						switch (iRand)
						{
						case 0:
							slots[i][j] = cRectangle(
								0.0f, 0.0f, 0.0f,
								squareA * ratio, squareA,
								barrelsX[i], (slotY[1]) * 3.0f - difference
							); break;
						case 1:
							slots[i][j] = cTriangle(
								0.0f, 0.0f, 0.0f,
								squareA,
								barrelsX[i], (slotY[1]) * 3.0f - difference
							); break;
						case 2:
							slots[i][j] = cCircle(
								0.0f, 0.0f, 0.0f,
								squareA,
								barrelsX[i], (slotY[1]) * 3.0f - difference
							); break;
						case 3:
							slots[i][j] = cStar(
								0.0f, 0.0f, 0.0f,
								squareA * 1.1f,
								barrelsX[i], (slotY[1]) * 3.0f - difference
							); break;
						}
					}
				}
		mouse(window, *arrow);

		drawArrays(*stopSign);
		drawArrays(*startSign);
		drawArrays(plateLower);
		drawArrays(plateUpper);
		drawArrays(*arrow);
		*arrow1 = *arrow;
		arrow1->vPositions[0] += 0.2f * (0.16f * 0.3f);
		arrow1->vPositions[1] += 0.2f * (0.16f * 0.3f);
		arrow1->vPositions[2] -= 0.0f;
		arrow1->vPositions[3] -= 0.2f * (0.16f * 0.3f);
		arrow1->vPositions[4] -= 0.2f * (0.16f * 0.3f);
		arrow1->vPositions[5] += 0.2f * (0.16f * 0.3f);
		arrow1->R = 1.0f;
		arrow1->G = 1.0f;
		arrow1->B = 1.0f;
		*arrow2 = *arrow1;
		drawArrays(*arrow1);
		arrow2->vPositions[0] += 0.2f * (0.16f * 0.3f);
		arrow2->vPositions[1] += 0.2f * (0.16f * 0.3f);
		arrow2->vPositions[2] -= 0.0f;
		arrow2->vPositions[3] -= 0.2f * (0.16f * 0.3f);
		arrow2->vPositions[4] -= 0.2f * (0.16f * 0.3f);
		arrow2->vPositions[5] += 0.2f * (0.16f * 0.3f);
		arrow2->R = 0.0f;
		arrow2->G = 0.0f;
		arrow2->B = 0.0f;
		
		drawArrays(*arrow2);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}
