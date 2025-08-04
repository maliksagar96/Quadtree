#include <iostream>
#include <fstream>
#include <vector>
#include "Quadtree.h"

// Define static member
int QuadtreeNode::next_leaf_id = 0;

// Subdivide the quadtree
void QuadtreeNode::subDivide() {
  if (level >= maxLevel) {
    leaf_id = next_leaf_id++;
    return;
  }

  double midX = (xmin + xmax) / 2.0;
  double midY = (ymin + ymax) / 2.0;

  // Create 4 children: BL, BR, TL, TR
  children[0] = new QuadtreeNode(level + 1, maxLevel, xmin, ymin, midX, midY);
  children[1] = new QuadtreeNode(level + 1, maxLevel, midX, ymin, xmax, midY);
  children[2] = new QuadtreeNode(level + 1, maxLevel, xmin, midY, midX, ymax);
  children[3] = new QuadtreeNode(level + 1, maxLevel, midX, midY, xmax, ymax);

  for (int i = 0; i < 4; ++i)
    children[i]->parent = this;

  for (int i = 0; i < 4; ++i)
    children[i]->subDivide();
}

// Assign neighbors recursively
void QuadtreeNode::assignNeighbours(QuadtreeNode* node) {
  if (!node) return;

  if (!node->isleaf()) {
    // Set internal sibling neighbors
    node->children[0]->right = node->children[1];  // BL → BR
    node->children[1]->left  = node->children[0];

    node->children[2]->right = node->children[3];  // TL → TR
    node->children[3]->left  = node->children[2];

    node->children[0]->top   = node->children[2];  // BL ↑ TL
    node->children[2]->bottom = node->children[0];

    node->children[1]->top   = node->children[3];  // BR ↑ TR
    node->children[3]->bottom = node->children[1];

    // External neighbors from parent's neighbors
    if (node->left && node->left->children[1]) {
      node->children[0]->left = node->left->children[1];  // BL ← BR of left neighbor
      node->children[2]->left = node->left->children[3];  // TL ← TR of left neighbor
    }

    if (node->right && node->right->children[0]) {
      node->children[1]->right = node->right->children[0];  // BR → BL of right neighbor
      node->children[3]->right = node->right->children[2];  // TR → TL of right neighbor
    }

    if (node->bottom && node->bottom->children[2]) {
      node->children[0]->bottom = node->bottom->children[2];  // BL ↓ TL of bottom neighbor
      node->children[1]->bottom = node->bottom->children[3];  // BR ↓ TR of bottom neighbor
    }

    if (node->top && node->top->children[0]) {
      node->children[2]->top = node->top->children[0];  // TL ↑ BL of top neighbor
      node->children[3]->top = node->top->children[1];  // TR ↑ BR of top neighbor
    }

    for (int i = 0; i < 4; ++i)
      assignNeighbours(node->children[i]);
  }
}

// Leaf check
bool QuadtreeNode::isleaf() const {
  return children[0] == nullptr;
}

