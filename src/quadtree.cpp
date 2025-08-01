#include <iostream> 
#include "quadtree.h"

void QuadtreeNode::subDivide() {

  if(level >= maxLevel) {
    return;
  }

  double midX = (xmin + xmax) / 2.0;
  double midY = (ymin + ymax) / 2.0;

  children[0] = new QuadtreeNode(level + 1, maxLevel, xmin, midX, ymin, midY); // Bottom-left
  children[1] = new QuadtreeNode(level + 1, maxLevel, midX, xmax, ymin, midY); // Bottom-right
  children[2] = new QuadtreeNode(level + 1, maxLevel, xmin, midX, midY, ymax); // Top-left
  children[3] = new QuadtreeNode(level + 1, maxLevel, midX, xmax, midY, ymax); // Top-right

}