#include "quadtree.h"
#include <random>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
using namespace std;
using namespace tbb;

Particle::Particle(double x, double y)
{
	this->x = x;
	this->y = y;
}

Square::Square(double x, double y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool Square::contains(Particle* p)
{
	return (p->x >= this->x - this->width &&
		p->x < this->x + this->width &&
		p->y >= this->y - this->height &&
		p->y < this->y + this->height);
}

QuadTree::QuadTree()
{
	this->boundary = new Square(1, 1, 1, 1);
	this->capacity = 5000;
	this->divided = false;
	Square* ne = new Square(this->boundary->x + (this->boundary->width / 2), this->boundary->y - (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* nw = new Square(this->boundary->x - (this->boundary->width / 2), this->boundary->y - (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* sw = new Square(this->boundary->x - (this->boundary->width / 2), this->boundary->y + (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* se = new Square(this->boundary->x + (this->boundary->width / 2), this->boundary->y + (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	this->NE = new QuadTree(ne, this->capacity);
	this->NW = new QuadTree(nw, this->capacity);
	this->SW = new QuadTree(sw, this->capacity);
	this->SE = new QuadTree(se, this->capacity);
	this->divided = true;
}

QuadTree::QuadTree(Square* boundary, int capacity)
{
	this->boundary = boundary;
	this->capacity = 5000;
	this->divided = false;
}

void QuadTree::subdivide()
{
	Square* ne = new Square(this->boundary->x + (this->boundary->width / 2), this->boundary->y - (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* nw = new Square(this->boundary->x - (this->boundary->width / 2), this->boundary->y - (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* sw = new Square(this->boundary->x - (this->boundary->width / 2), this->boundary->y + (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	Square* se = new Square(this->boundary->x + (this->boundary->width / 2), this->boundary->y + (this->boundary->height / 2), this->boundary->width / 2, this->boundary->height / 2);
	this->NE = new QuadTree(ne, this->capacity);
	this->NW = new QuadTree(nw, this->capacity);
	this->SW = new QuadTree(sw, this->capacity);
	this->SE = new QuadTree(se, this->capacity);
	this->divided = true;
}

void QuadTree::buildTreeParallel()
{
	parallel_for(blocked_range<size_t>(0, 5000), [=](const blocked_range<size_t>& r)
	{

		std::default_random_engine generator((int)std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> distribution(-1.0, 1.0);
		double x;
		double y;

		for (size_t i = r.begin(); i != r.end(); i++)
		{
			x = distribution(generator);
			y = distribution(generator);
			Particle* aParticle = new Particle(x, y);
			insertToNode(aParticle);
		}
	});
}

bool QuadTree::insertToNode(Particle* p)
{
	if (!this->boundary->contains(p))
	{
		return false;
	}

	if (this->points.size() < (size_t) this->capacity)
	{
		this->points.push_back(p);
		return true;
	}

	else
	{
		if (!this->divided)
		{
			this->subdivide();
		}

		if (this->NE->insertToNode(p))
		{
			return true;
		}
		else if (this->NW->insertToNode(p))
		{
			return true;
		}
		else if (this->SW->insertToNode(p))
		{
			return true;
		}
		else if (this->SE->insertToNode(p))
		{
			return true;
		}
	}
}
