#include "quadtree.h"


Particle::Particle(double x, double y)
{
	this->x = x;
	this->y = y;
	this->force = 0;
	this->massOfParticle = 0;
	aQuadrant = NONE;
}

Node::Node()
{
	this->mass = 0;
	this->centerOfMass = 0;
	this->posCenterOfMassX = 0;
	this->posCenterOfMassY = 0;
	this->massCM = 0;
	this->numOfParticles = 0;
	this->subNode = false;
}

QuadTree::QuadTree()
{
	this->root = new Node();
}

void QuadTree::buildTree()
{
	for (int i = 1; i <= QuadTree::numOfParticlesToAdd; i++)
	{
		this->insertToNode(new Particle(), this->root);
	}
}

void QuadTree::insertToNode(Particle* p, Node* n)
{
	if (n->subNode)
	{
		if (n->numOfParticles > 1)
		{
			insertToNode(p, n);
		}
		else if (n->numOfParticles == 1)
		{

		}
	}
	else
	{

	}
	n->particlesInNode.push_back(p);
	n->numOfParticles++;
}
