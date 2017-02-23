#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     
#include <time.h>   
#include "cell.h"

//#define DEBUG
#include "debug.h"

class Tree {

	class Tree_Cell: public Cell {
		public:
			std::vector<Cell*> children; 
	};

	std::vector<Tree_Cell*> nodes;

	size_t number_of_levels;
	size_t number_of_dimensions;
	size_t children_per_node;

	int  selectOneTargetNode();
	bool importLeafRow(std::vector<Cell*>  input_leaf_row);
	bool exportLeafRow(Cell *first_child, Cell *second_child);

public:

	Tree(size_t number_of_dimensions, size_t number_of_levels);

	void createEddyEvent(std::vector<Cell*> field);

};


