#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

class Tree {

	struct node { 
	    node   *left  = NULL;
	    node   *right = NULL;
		double scalar;  // Example scalar
	};

	int                number_of_levels;
	node               *root;
	std::vector<node*> nodes;
	std::vector<node*> temp_nodes; //used for suport

public:

	Tree(size_t number_of_levels);

	bool swap(size_t node_index);

	void update(size_t node_id, double scalar);

	void randomSwap();
	
	void printtree();

};


