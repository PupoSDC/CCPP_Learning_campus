#include "tree.h"

Tree::Tree(size_t number_of_levels){

	nodes.resize( pow(2,number_of_levels) - 1 );

	nodes[0] = new node();
	nodes[0]->parent = NULL;
	nodes[0]->scalar = 0.0;

	// Init rest of tree with pointer to parents
	for( int i = 1; i< nodes.size(); i++ ){
		nodes[i]         = new node();
		nodes[i]->parent = nodes[(i-1)/2];
		nodes[i]->left   = NULL;
		nodes[i]->right  = NULL;

		if( nodes[i]->parent->left == NULL ){
			nodes[i]->parent->left = nodes[i];
		}
		else {
			nodes[i]->parent->right = nodes[i];
		}
		
		nodes[i]->scalar = i;
	}	
}

bool Tree::swap(size_t first_node, size_t second_node){

	// Evaluates if nodes are root or the same
	if( first_node == 0 || second_node == 0 || first_node == second_node){
		return false;
	}

	// Evaluates if the two nodes are NOT on the same level
	for( int i = 1; pow(2,i) < ( nodes.size() ); i++){
		if( (first_node + 1)/ pow(2,1) == 1 && ( second_node + 1)/ pow(2,1) != 1 ){
			return false;
		}
	}

	node *temp_node             = nodes[first_node];
	nodes[first_node]           = nodes[first_node]->parent; 
	nodes[second_node]->parent  = temp_node->parent;

	return true;
}

void Tree::printtree(){

	cout << "Printing tree with " << nodes.size() << " nodes" << endl;


	cout << endl << "finished printing tree" << endl;
}