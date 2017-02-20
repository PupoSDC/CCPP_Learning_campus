#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

class Tree {

	struct node { 
	    node   *left;
	    node   *right;
		double scalar;  // Example scalar
	};

	node               *root;
	std::vector<node*> nodes;
	
	//node* searchfunction for printing

public:

	Tree(size_t number_of_levels);

	bool swap(size_t first_node, size_t second_node);

	void update(size_t node_id, double scalar);

	void printtree();


};


