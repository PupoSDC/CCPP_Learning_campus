#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     
#include <time.h>    
#include "cell.h"

class Tree {

	class Tree_Cell: public Cell {
		public:
			std::vector<Cell*> children; 
	};

	std::vector<Tree_Cell*> nodes;
	std::vector<     Cell*> leaves;

	bool debug_mode = false;
	int  number_of_levels;
	int  number_of_dimensions;

	void constructor(size_t number_of_dimensions, size_t number_of_levels, bool debug_mode);
	bool swap(size_t node_index);

public:

	Tree(size_t number_of_dimensions, size_t number_of_levels);
	Tree(size_t number_of_dimensions, size_t number_of_levels, bool debug_mode);

	void setDebugMode(bool debug_mode);
	void importLeafRow(std::vector<Cell*>  input_leaf_row);
	void exportLeafRow(std::vector<Cell*> target_leaf_row);

	void randomSwap();

	//void print();	
};


