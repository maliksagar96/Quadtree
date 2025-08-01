#ifndef QUADTREE_H
#define QUADTREE_H

class QuadtreeNode {
public:
  QuadtreeNode* children[4];
  int level;
  int maxLevel;

  QuadtreeNode(int lvl, int maxLvl, double xmin, double xmax, double ymin, double ymax);
  ~QuadtreeNode() {
    for (int i = 0; i < 4; ++i) {
      delete children[i];
    }
  }

  bool isleaf() const;

private:
  void subDivide();
  double xmin, xmax, ymin, ymax;
  double max_level;
  
};

#endif // QUADTREE_H