#include <iostream>
#include "quadtree.h"

int main() {
  // Create root node over domain [0, 1] x [0, 1], with max depth 1
  QuadtreeNode* rootNode = new QuadtreeNode(0, 1, 0, 0, 1, 1);

  // Subdivide the domain
  rootNode->subDivide();

  // Output the leaf nodes to a text file
  rootNode->writeLeavesToText("rootNode.txt");
  rootNode->traverseLeaves(rootNode);
  rootNode->writeNeighboursToText();
  // Clean up
  delete rootNode;

  return 0;
}
