#include <iostream>
#include "quadTree.h"
using namespace std;


void QuadTree::resetTree() {

}

void QuadTree::buildTree() {
	resetTree();
	
}

void QuadTree::insertToNode(Node* aNode) {
	if (aNode->numOfParticles > 1) {

	}
	else if (aNode->numOfParticles == 1) {

	}
	else if (aNode == NULL) {
		aNode = new Node();
	}
}

int main() {



	return 0;
}