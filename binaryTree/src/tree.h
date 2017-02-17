#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

class Tree {

	struct node { 

	    size_t key;
	    node   *parent;
		double scalar;  // Example scalar

	};

	node               *root;
	std::vector<node*> nodes;

public:

	Tree(size_t number_of_levels);

	bool swap(size_t first_node, size_t second_node);

	void update(size_t node_id, double scalar);
};


