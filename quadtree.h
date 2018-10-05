#pragma once
#include <vector>
using namespace std;

const enum Quadrant { NE = 1, NW, SW, SE, NONE };

class Particle 
{
	public:
		Particle(double x=0, double y=0);
		double x;
		double y;
		double force;
		double massOfParticle;
		Quadrant aQuadrant;
};

class Node
{
	public:
		Node();
		vector<Particle*> particlesInNode;
		double mass;
		double centerOfMass;
		double posCenterOfMassX;
		double posCenterOfMassY;
		double massCM;
		bool subNode;
		int numOfParticles;
};

class QuadTree 
{
	public:
		QuadTree();
		Node* root;
		const int numOfParticlesToAdd = 30;
		void insertToNode(Particle* p, Node* n);
		void buildTree();
};
