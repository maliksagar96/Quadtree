/*

1) First level, second level and third level trees can be found in the readme section. 
2) Neighbours are taken as left, right, top , bottom.
*/


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "quadtree.h"

int QuadtreeNode::next_leaf_id = 0;  // Define static member

void QuadtreeNode::subDivide() {
  if (level >= maxLevel) {
    leaf_id = next_leaf_id++;
    return;
  }

  double midX = (xmin + xmax) / 2.0;
  double midY = (ymin + ymax) / 2.0;

  // Create 4 children
  children[0] = new QuadtreeNode(level + 1, maxLevel, xmin, ymin, midX, midY); // BL
  children[1] = new QuadtreeNode(level + 1, maxLevel, midX, ymin, xmax, midY); // BR
  children[2] = new QuadtreeNode(level + 1, maxLevel, xmin, midY, midX, ymax); // TL
  children[3] = new QuadtreeNode(level + 1, maxLevel, midX, midY, xmax, ymax); // TR

  // Set current node as parent
  for (int i = 0; i < 4; ++i)
    children[i]->parent = this;


  /*
    First level, second level and third level trees can be found in the readme section. 
    From there we can derive that the neighbours can be found in the following way.
  */  

  // Set internal sibling neighbors
  children[0]->right = children[1];  // BL → BR
  children[1]->left  = children[0];

  children[2]->right = children[3];  // TL → TR
  children[3]->left  = children[2];

  children[0]->top   = children[2];  // BL ↑ TL
  children[2]->bottom = children[0];

  children[1]->top   = children[3];  // BR ↑ TR
  children[3]->bottom = children[1];

  // Set external neighbors from parent's neighbors
  // if (left && left->children[1]) {
  //   children[0]->left = left->children[1];  // BL ← BR of left neighbor
  //   children[2]->left = left->children[3];  // TL ← TR of left neighbor
  // }

  // if (right && right->children[0]) {
  //   children[1]->right = right->children[0];  // BR → BL of right neighbor
  //   children[3]->right = right->children[2];  // TR → TL of right neighbor
  // }

  // if (bottom && bottom->children[2]) {
  //   children[0]->bottom = bottom->children[2];  // BL ↓ TL of bottom neighbor
  //   children[1]->bottom = bottom->children[3];  // BR ↓ TR of bottom neighbor
  // }

  // if (top && top->children[0]) {
  //   children[2]->top = top->children[0];  // TL ↑ BL of top neighbor
  //   children[3]->top = top->children[1];  // TR ↑ BR of top neighbor
  // }

  // Recursively subdivide
  for (int i = 0; i < 4; ++i)
    children[i]->subDivide();
}


bool QuadtreeNode::isleaf() const {
  return children[0] == nullptr;
}

void QuadtreeNode::traverseLeaves(const QuadtreeNode* node) {
  if (!node) return;

  if (node->isleaf()) {
    std::cout << "Leaf ID: " << node->leaf_id
              << " Bounds: (" << node->xmin << ", " << node->xmax
              << ") x (" << node->ymin << ", " << node->ymax << ")\n";

    neighbours[node->leaf_id] = {
      node->left ? node->left->leaf_id : -1,
      node->right ? node->right->leaf_id : -1,
      node->top ? node->top->leaf_id : -1,
      node->bottom ? node->bottom->leaf_id : -1
    };
  } else {
    for (int i = 0; i < 4; ++i)
      traverseLeaves(node->children[i]);
  }
}

void QuadtreeNode::writeNeighboursToText() {
  std::ofstream out("neighbours.txt");
  if (!out) return;

  for (const auto& pair : neighbours) {
    int leafID = pair.first;
    const std::vector<int>& nbrs = pair.second;
    out<<leafID<<" ";        
    for (int id : nbrs) {
      out << id << " ";
    }
    out << "\n";
  }

  out.close();
}

void writeLeavesToText(const QuadtreeNode* node, std::ofstream& out) {
  if (node == nullptr) return;

  if (node->isleaf()) {
  out << node->xmin << " " << node->xmax << " "
      << node->ymin << " " << node->ymax << " "
      << node->leaf_id << "\n";
  }
  else {
    for (int i = 0; i < 4; ++i) {
      writeLeavesToText(node->children[i], out);
    }
  }
}

void QuadtreeNode::writeLeavesToText(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out) return;
  ::writeLeavesToText(this, out);
  out.close();
}
