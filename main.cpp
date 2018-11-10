#include <iostream>
#include "quadtree.h"
#include <GLFW/glfw3.h>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
using namespace std;
using namespace tbb;

QuadTree* aTree = new QuadTree();

void display() 
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);

	for (size_t i = 0; i < aTree->points.size(); i++)
	{
		glColor3f(0.8F, 0.196078F, 0.6F);
		glVertex2d(aTree->points[i]->x, aTree->points[i]->y);
	}

	glEnd();
	glFlush();
}

int main()
{
	//task_scheduler_init init(300);

	aTree->buildTreeParallel();
	GLFWwindow* window;

	if (!glfwInit()) {
		cout << "Error initializing GLFW" << std::endl;
		return -1;

	}
	window = glfwCreateWindow(800, 800, "Barne's Hut", NULL, NULL);
	if (!window)
	{
		cout << "Error creating window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	while (!glfwWindowShouldClose(window))
	{		
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	system("pause");
	return 0;
}