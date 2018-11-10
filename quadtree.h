#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "tbb/blocked_range.h"
using namespace std;
using namespace tbb;

/**
 *	\class Point
 *	\brief The Point class stores the coordinates of a particle.
*/
class Particle
{
public:
	Particle(double x, double y);/*!< Constructor. Takes the x and y coordinates as parameters and assigns them to the Point object.*/
	double x; /*!< The x coordinate of the particle.*/
	double y; /*!< The y coordinate of the particle.*/
};

/**	\class Square
*	\brief The Square class is used as a boundary when dividing in 4 squares
*/
class Square
{
public:
	Square(double x, double y, double width, double height); /*!< Constructor*/
	double x; /*!< The x coordinate of the center of the square.*/
	double y; /*!< The y coordinate of the center of the square.*/
	double width; /*!< Width of the square.*/
	double height; /*!< Height of the Square.*/
	bool contains(Particle* p); /*!< Determines if a square (sub quad tree) contains a point and returns true or false.*/
};

/** \class QuadTree
*	\brief This is the quad tree class that stores the whole tree and the sub trees
*/
class QuadTree
{
public:
	QuadTree(); /*!< Default constructor */
	QuadTree(Square* boundary, int capacity); /*!< Parameterized constructor.*/
	Square* boundary; /*!< Determines the boundaries of the Square that is continuously being divided.*/
	int capacity; /*!< The number of points that should be in a given square.*/
	vector<Particle*> points; /*!< Vector that stores the points.*/
	QuadTree* NE; /*!< The North East quadrant.*/
	QuadTree* NW; /*!< The North West quadrant.*/
	QuadTree* SW; /*!< The South West quadrant.*/
	QuadTree* SE; /*!< The South East quadrant.*/
	bool divided; /*!< Stores the information to determine whether or not a square (a sub tree) has already been divided or not.*/
	void subdivide(); /*!< Divides the square into 4 other squares.*/
	void buildTreeParallel(); /*!< Constructs the quad tree.*/
	//void operator()(const blocked_range<int>& r) const /*!< Method for parallel execution when inserting particles.*/
	//{
	//	std::default_random_engine generator((int)std::chrono::system_clock::now().time_since_epoch().count());
	//	std::uniform_real_distribution<double> distribution(-1.0, 1.0);
	//	double x;
	//	double y;

	//	for(size_t i = r.begin(); i != r.end(); i++)
	//	{
	//		x = distribution(generator);
	//		y = distribution(generator);
	//		Particle* aParticle = new Particle(x, y);
	//		insertToNode(aParticle);
	//	}
	//};

	bool insertToNode(Particle* p); /*!< Inserts points into the quad tree.*/
};
