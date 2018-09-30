#pragma once
#include <vector>

struct Particle {
	double mass = 0.0;
	double centerOfMass = 0.0;
};

struct Node {
	const enum Quadrant {NE, NW, SW, SE};
	int numOfParticles = 0;
	Particle aParticle;
};

class QuadTree {
	private:

	public:
		void insertToNode(Node* newParticle);
		void buildTree();
		void resetTree();
};