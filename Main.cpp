#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream> 
#include <vector>
#include <time.h>  
#include <ctype.h>

std::vector<std::vector<double>> Vecs2;
std::vector<std::vector<double>> Vecs;
std::vector<std::vector<double>> VecsR;

std::vector<std::vector<double>> Color;
std::vector<std::vector<double>> Color2;


void character_callback(GLFWwindow* window, unsigned int codepoint);
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

struct XYAxes
{
	GLfloat AxisX1[2];
	GLfloat AxisX2[2];

	GLfloat AxisY1[2];
	GLfloat AxisY2[2];
} Axis;

void render()
{ 
	//clear background screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(1);

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(Axis.AxisX1[0], Axis.AxisX1[1], Axis.AxisX1[2]);
	glVertex3f(Axis.AxisX2[0], Axis.AxisX2[1], Axis.AxisX2[2]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Axis.AxisY1[0], Axis.AxisY1[1], Axis.AxisY1[2]);
	glVertex3f(Axis.AxisY2[0], Axis.AxisY2[1], Axis.AxisY2[2]);
	glEnd();


	glLineWidth(3);
	for (int i = 0; i < Vecs.size(); i++)
	{
		    glColor3f(Color[i][0], Color[i][1], Color[i][2]);

			glBegin(GL_LINES);
			glVertex3f(0,0, 0);
			glVertex3f(Vecs[i][0], Vecs[i][1], 0);		
			glEnd();
	}
	for (int i = 0; i < Vecs2.size(); i++)
	{
			glColor3f(Color2[i][0], Color2[i][1], Color2[i][2]);
			glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(Vecs2[i][0], Vecs2[i][1], 0);
			glEnd();
	}

	for (int i = 0; i < VecsR.size(); i++)
	{
		//glColor3f(1.0,0.0,0.0);
		glColor3f(Color[i][0], Color[i][1], Color[i][2]);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		if (VecsR[i][0] != 0 | VecsR[i][1] != 0)
		{
			glVertex3f(VecsR[i][0], VecsR[i][1], 0);
		}
		glEnd();
	}
}

void OutputPrint(std::string Command)
{
	if (Command == "Help$")
	{
		printf("\n\n\n#Command#			#Formatting#\n");
		printf("Graph a Vector			x,y \n");
		printf("Sum of two Vectors		x1,y1,x2,y2 \n");
	}
}

void Move(GLfloat (&point)[2], double x, double y, double z)
{
	point[0] += x;
	point[1] += y;
	point[2] += z;
	printf("%lf\n", point[0]);
}

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(640, 640, "SimpleShapes", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetCharCallback(window, character_callback);
	glfwSwapInterval(1);

	glfwMakeContextCurrent(window);

	//###Initialise objects here###

	Axis.AxisX1[0] = 0.95;
	Axis.AxisX1[1] = 0;
	Axis.AxisX1[2] = 0;

	Axis.AxisX2[0] = -0.95;
	Axis.AxisX2[1] = 0;
	Axis.AxisX2[2] = 0;

	Axis.AxisY1[0] = 0;
	Axis.AxisY1[1] = -0.95;
	Axis.AxisY1[2] = 0;

	Axis.AxisY2[0] = 0;
	Axis.AxisY2[1] = 0.95;
	Axis.AxisY2[2] = 0;

	double updateDel = 0.01f;
	double updateTime = updateDel;

	printf("Space bar To enter input\n");
	printf("Type 'Help$' for a list of commands\n");

	while (!glfwWindowShouldClose(window))
	{
		double lastTime = glfwGetTime();
		float ratio;
		int width, height;
		
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);


		if (lastTime < updateTime)
		{
		}
		// every tick this runs
		else
		{
			//Move(Axis.Point1, 0, 0, 0);
			//Move(Axis.Point2, 0, 0, 0);
			updateTime = lastTime + updateDel;
		}				
		render();	
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


std::string::size_type sz;
std::string Input;

double x;
double y;

double x2;
double y2;

double xr;
double yr;

int arryCount = 0;
void character_callback(GLFWwindow* window, unsigned int codepoint)
{


	char c = codepoint;
	//printf("%c", c);
	printf("%c", c);

	if (c == 'x')
	{
		c = NULL;
		Input = "";
		Vecs.clear();
		Vecs2.clear();
		VecsR.clear();
		x = NULL;
		y = NULL;
		x2 = NULL;
		y2 = NULL;
		printf("###ALL VECTORS WIPED###\n");
		arryCount = 0;
	}
	else
	{
		//removes spaces from input buffer
		if (c != 32)//notspace
		{
			Input += c;
		}
		else
		{
			c = Input.back();
		}


		//printf("%d", codepoint);

		

		if (codepoint == GLFW_KEY_SPACE)
		{ 
			if (c == 36)
			{
				OutputPrint(Input);
			}
			else if (!isalpha(c))
			{
				Vecs2.push_back(std::vector<double>());
				VecsR.push_back(std::vector<double>());
				Vecs.push_back(std::vector<double>());
				Color.push_back(std::vector<double>());
				Color2 .push_back(std::vector<double>());

				printf("\n");

				std::string XPoint2  ="";
				std::string YPoint2 = "";

				size_t pos = 0;
				std::string delimiter = ",";
				std::vector<std::string> token;

				while ((pos = Input.find(delimiter)) != std::string::npos)
				{
					token.push_back(Input.substr(0, pos));
					Input.erase(0, pos + delimiter.length());
				}

				token.push_back(Input);

				std::string XPoint = token[0];
				std::string YPoint = token[1];

				if(token.size()>2)
				{					
					XPoint2 = token[2]; 
					YPoint2 = token[3];
				} 



				if (XPoint2 == "" | YPoint2 == "")
				{
					XPoint2 = "0";
					YPoint2 = "0";
				}

				x = std::stod(XPoint);
				printf("X point is %lf\n", x);
				y = std::stod(YPoint);
				printf("Y point is %lf\n", y);


				x2 = std::stod(XPoint2);
				printf("X2 point is %lf\n", x2);
				y2 = std::stod(YPoint2);
				printf("Y2 point is %lf\n", y2);

				xr = x + x2;
				yr = y + y2; 

				srand(time(NULL));

				double red = rand() % 100;
				red = red / 100;
				double green = rand() % 100;
				green = green / 100;
				double blue = rand() % 100;
				blue = blue / 100;


				Vecs[arryCount].push_back(x);
				Vecs[arryCount].push_back(y);

				Vecs2[arryCount].push_back(x2);
				Vecs2[arryCount].push_back(y2);

				VecsR[arryCount].push_back(xr);
				VecsR[arryCount].push_back(yr);

				Color[arryCount].push_back(red);
				Color[arryCount].push_back(green);
				Color[arryCount].push_back(blue);

				Color2[arryCount].push_back(red);
				Color2[arryCount].push_back(green);
				Color2[arryCount].push_back(blue);

				arryCount++;
			}
			c = NULL;
			Input = "";
		}
	}
}
