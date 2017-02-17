#include "tree.h"

Tree::Tree(size_t number_of_levels){

	nodes.reserve( pow(2,number_of_levels) - 1 );

	nodes[0] = new node();
	nodes[0]->parent = NULL;
	nodes[0]->key    = 0;

	// Init rest of tree with pointer to parents
	for( int i = 1; i<number_of_levels; i++ ){
		nodes[i]        = new node();
		nodes[i]->parent = nodes[(i-1)/2];
		nodes[i]->key    = i;
	}
	
}
