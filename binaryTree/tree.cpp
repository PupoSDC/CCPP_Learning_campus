#include "tree.h"

Tree::Tree(size_t input_number_of_dimensions, size_t input_number_of_levels){

	number_of_levels     = input_number_of_levels;
	number_of_dimensions = input_number_of_dimensions;

	nodes.resize( (pow(pow(2,number_of_dimensions),number_of_levels) - 1) / ( pow(2,number_of_dimensions) -1) );

    // Initialize root node
	nodes[0] = new node();  // root
	nodes[0]->children.resize( pow(2,number_of_dimensions) );
	nodes[0]->scalar = 0.0;

	std::cout << "Creating tree with " << nodes.size() << " nodes" << std::endl;

	// For i... Go through each level except leaf level to create nodes
	//   For j...  Each level has 2^Ndimensions^levels nodes
	//     For k... Creates 2^Ndimensions children for each node
	for( int i = 0; i < number_of_levels-1; i++ ){
		for( int j = 0; j < pow( pow(2,number_of_dimensions),i); j++ ){
			for ( int k = 0; k < pow(2,number_of_dimensions); k++ ){

				int indexOfCurrentParent = (pow(pow(2,number_of_dimensions),i) - 1) / ( pow(2,number_of_dimensions) -1) + j;
				int indexOfCreatedChild  = indexOfCurrentParent * pow(2,number_of_dimensions) + 1 + k;
				
				// Debug output
				//std::cout << " level: " << i << " indexOfCurrentParent: " << indexOfCurrentParent 
				//          << " child: " << indexOfCreatedChild  << std::endl;

				nodes[indexOfCreatedChild] = new node();
				nodes[indexOfCreatedChild]->children.resize( pow(2,number_of_dimensions) );
				nodes[indexOfCreatedChild]->scalar = indexOfCreatedChild;
				
				nodes[indexOfCurrentParent]->children[k] = nodes[indexOfCreatedChild];
			}
		}
	}	
	
	//Initialize random seed
	srand(time(NULL));
}

bool Tree::swap(size_t node_index){

	// Evaluates if node is not leaf(level n) or first level tree (n-1)
	if( node_index >= nodes.size()/(2*pow(2,number_of_dimensions)) ){
		return false;
	}

	// Create array with four random numbers [0,2^N_dim]. 
	// First two randoms cannot be the same 
	int random_numbers[4] = { 0, 0, 0, 0 };
	
	while(random_numbers[0] == random_numbers[1]){
		random_numbers[0] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[1] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[2] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[3] = rand()%(int)pow(2,number_of_dimensions);
	}

	std::cout << random_numbers[0] << " "
	          << random_numbers[1] << " "
	          << random_numbers[2] << " "
	          << random_numbers[3] << " " << std::endl;

	node *grand_parent  = nodes[node_index];
	
	node *first_parent  = grand_parent->children[random_numbers[0]];
	node *first_child   = first_parent->children[random_numbers[2]];

	node *second_parent = grand_parent->children[random_numbers[1]];
	node *second_child  = second_parent->children[random_numbers[3]];

	std::cout << " first_parent : " << first_parent  << " " << std::endl; 
	std::cout << " first_child  : " << first_child   << " " << std::endl;

	std::cout << " second_parent: " << second_parent << " " << std::endl;
	std::cout << " second_child : " << second_child  << " " << std::endl;


	// Node exchange step, the two selected parents exchange their kids
	first_parent->children[random_numbers[2]]  = second_child;
	second_parent->children[random_numbers[3]] = first_child;

	return true;
}

void Tree::randomSwap(){
	
	int r = rand()%(int)( nodes.size()/ (2*pow(2,number_of_dimensions)) );

	std::cout << "Swap on node: "<< r << ", result: " << (this->swap(r) ? "sucess" : "failure") << std::endl;
}

void Tree::print(){

	std::cout << "Printing tree with " << nodes.size() << " nodes" << std::endl;

	std::cout << nodes[0]->scalar << std::endl;

	std::vector<node*> temp_nodes(nodes);

	for( int i = 0; i < number_of_levels-1; i++ ){
		for( int j = 0; j < pow( pow(2,number_of_dimensions),i); j++ ){
			for ( int k = 0; k < pow(2,number_of_dimensions); k++ ){

				int indexOfCurrentParent = (pow(pow(2,number_of_dimensions),i) - 1) / ( pow(2,number_of_dimensions) -1) + j;
				int indexOfCurrentChild  = indexOfCurrentParent * pow(2,number_of_dimensions) + 1 + k;

				temp_nodes[indexOfCurrentChild] = temp_nodes[indexOfCurrentParent]->children[k];

				std::cout << temp_nodes[indexOfCurrentParent]->children[k]->scalar << " ";
			}

			std::cout<< "  ";
		}

		std::cout<<std::endl;
	}	
}

