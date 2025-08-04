#include "Quadtree.h"
#include "QuadtreeIO.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>

std::unordered_map<int, std::vector<int>> neighbours; 


void assignNeighboursMap(QuadtreeNode* node) {
  if (!node) return;

  if (node->isleaf()) {
    std::vector<int> n;
    n.push_back(node->left ? node->left->leaf_id : -1);
    n.push_back(node->right ? node->right->leaf_id : -1);
    n.push_back(node->top ? node->top->leaf_id : -1);
    n.push_back(node->bottom ? node->bottom->leaf_id : -1);
    neighbours[node->leaf_id] = n;
  } else {
    for (int i = 0; i < 4; ++i) {
      assignNeighboursMap(node->children[i]);
    }
  }
}

void writeNeighboursToText(QuadtreeNode* node) {
  assignNeighboursMap(node);

  std::ofstream out("neighbours.txt");
  if (!out) return;

  for (const auto& pair : neighbours) {
    out << pair.first << " ";
    for (int id : pair.second) {
      out << id << " ";
    }
    out << "\n";
  }

  out.close();
}


// Internal recursive function to write leaf info
void writeLeavesRecursive(QuadtreeNode *node, std::ofstream& out) {
  if (!node) return;

  if (node->isleaf()) {
    out << node->xmin << " " << node->xmax << " "
        << node->ymin << " " << node->ymax << " "
        << node->leaf_id << "\n";
  } else {
    for (int i = 0; i < 4; ++i)
      writeLeavesRecursive(node->children[i], out);
  }
}

// Wrapper function
void writeLeavesToText(QuadtreeNode *node,const std::string& filename) {
  std::ofstream out(filename);
  if (!out) return;
  writeLeavesRecursive(node, out);
  out.close();
}

