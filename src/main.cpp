#include <iostream>
#include "Quadtree.h"
#include "QuadtreeIO.h" 

int main() {
  // Create root node over domain [0, 1] x [0, 1], with max depth 1
  QuadtreeNode* rootNode = new QuadtreeNode(0, 2, 0, 0, 1, 1);

  // Subdivide the domain
  rootNode->subDivide();
  rootNode->assignNeighbours(rootNode);
  writeLeavesToText(rootNode, "rootNode.txt");
  writeNeighboursToText(rootNode);

  // Clean up
  delete rootNode;

  return 0;
}
