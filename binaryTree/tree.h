#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     
#include <time.h>    

class Tree {

	struct node { 
	    std::vector<node*> children; // Children.size() = 2^number_of_dimensions
		double scalar;               // Example scalar
	};

	int number_of_levels;
	int number_of_dimensions;

	std::vector<node*> nodes;
	std::vector<node*> temp_nodes; //used for support

	bool swap(size_t node_index);

public:

	Tree(size_t number_of_dimensions, size_t number_of_levels);

	void update(size_t node_id, double scalar);

	void randomSwap();
	
	void print();	

};


