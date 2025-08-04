#ifndef QUADTREE_H
#define QUADTREE_H

#include <string>
#include <vector>

class QuadtreeNode {
  public:
    QuadtreeNode *children[4];
    QuadtreeNode *parent;
    QuadtreeNode *left, *right, *top, *bottom; // Neighbors
    int level;
    int maxLevel;
    int leaf_id;  // Assigned only if node is a leaf
    double xmin, xmax, ymin, ymax;
    
    QuadtreeNode(int level_, int maxLevel_, double xmin_, double ymin_, double xmax_, double ymax_)
      : level(level_), maxLevel(maxLevel_),
        xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_),
        leaf_id(-1), parent(nullptr) 
    {
      for (int i = 0; i < 4; ++i)
        children[i] = nullptr;
    }

    ~QuadtreeNode() {
      for (int i = 0; i < 4; ++i) {
        delete children[i];
      }
    }

    
    void subDivide();
    bool isleaf() const;
    void assignNeighbours(QuadtreeNode*);
    

  private:
    double centroid[2];
    static int next_leaf_id;  // Counter for assigning leaf IDs
  
};

#endif // QUADTREE_H
