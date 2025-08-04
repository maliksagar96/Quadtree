#ifndef QUADTREEIO_H
#define QUADTREEIO_H

#include <Quadtree.h>
#include <fstream>
#include <vector>
#include <unordered_map>  

extern std::unordered_map<int, std::vector<int>> neighbours;  

void writeNeighboursToText(QuadtreeNode*);
void assignNeighboursMap(QuadtreeNode*);
void writeLeavesRecursive(QuadtreeNode*, std::ofstream&);
void writeLeavesToText(QuadtreeNode *, const std::string& );


#endif