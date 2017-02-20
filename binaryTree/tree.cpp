#include "tree.h"

Tree::Tree(size_t input_number_of_levels){

	number_of_levels = input_number_of_levels;

	nodes.resize( pow(2,number_of_levels) - 1 );
    temp_nodes.resize( pow(2,number_of_levels) - 1 );

	nodes[0] = new node();  // root
	nodes[0]->scalar = 0.0;

	// For each node, creates 2 new nodes in the vector and allocates
	// them to it's left and right.
	for( int i = 0; i < number_of_levels-1; i++ ){
		for( int j = 0; j < pow(2,i); j++ ){
			nodes[(pow(2,i)-1+j)*2 + 1]	   = new node();
			nodes[(pow(2,i)-1+j)*2 + 2]	   = new node();

			nodes[pow(2,i)-1+j]->left      = nodes[(pow(2,i)-1+j)*2 + 1];
			nodes[pow(2,i)-1+j]->right     = nodes[(pow(2,i)-1+j)*2 + 2];

			nodes[pow(2,i)-1+j]->left->scalar  = (pow(2,i)-1+j)*2 + 1; // temp value to keep track
			nodes[pow(2,i)-1+j]->right->scalar = (pow(2,i)-1+j)*2 + 2; // of nodes
		}
	}	

	//Initialize random seed
	srand (time(NULL));
}

bool Tree::swap(size_t node_index){

	// Evaluates if node is not leaf( level n) or first level tree (n-1)
	if( node_index >= nodes.size()/4 ){
		return false;
	}

	// Get 2 random numbers
	int randomA = rand()%2;
	int randomB = rand()%2;

	// Auxiliary node pointer for exchange
	node *temp_node;

	// 4 Scenarios of exchange are possible:
	if ( randomA == 0 && randomB == 0 ){
		temp_node                      = nodes[node_index]->left->left;	
		nodes[node_index]->left->left  = nodes[node_index]->right->left;	
		nodes[node_index]->right->left = temp_node;	
		return true;
	}

	if ( randomA == 0 && randomB == 1 ){
		temp_node                       = nodes[node_index]->left->left;	
		nodes[node_index]->left->left   = nodes[node_index]->right->right;	
		nodes[node_index]->right->right = temp_node;
		return true;	
	}
	
	if ( randomA == 1 && randomB == 0 ){
		temp_node                      = nodes[node_index]->left->right;	
		nodes[node_index]->left->right = nodes[node_index]->right->left;	
		nodes[node_index]->right->left = temp_node;	
		return true;
	}

	if ( randomA == 1 && randomB == 1 ){
		temp_node                       = nodes[node_index]->left->right;	
		nodes[node_index]->left->right  = nodes[node_index]->right->right;	
		nodes[node_index]->right->right = temp_node;
		return true;
	}

	return false;
}

void Tree::randomSwap(){
	
	int r = rand()%(nodes.size()/4);

	cout << "Swap on node: "<< r << ", result: " << (this->swap(r) ? "sucess" : "failure") << endl;
}

void Tree::printtree(){

	cout << "Printing tree with " << nodes.size() << " nodes" << endl;

	cout << nodes[0]->scalar << endl;

	temp_nodes[0] = nodes[0];

	for( int i = 0; i < number_of_levels-1; i++ ){
		
		for( int j = 0; j < pow(2,i); j++ ){

			temp_nodes[pow(2,i+1)+j*2-1]   = temp_nodes[pow(2,i)-1+j]->left;
			temp_nodes[pow(2,i+1)+j*2]     = temp_nodes[pow(2,i)-1+j]->right; 

			cout << temp_nodes[pow(2,i+1)+j*2-1]->scalar  << " ";		
			cout << temp_nodes[pow(2,i+1)+j*2]->scalar    << " ";
		}

		cout << endl;
	}


	cout << endl << "finished printing tree" << endl;
}