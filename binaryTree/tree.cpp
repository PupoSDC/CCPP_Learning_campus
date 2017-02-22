#include "tree.h"

void Tree::constructor(size_t input_number_of_dimensions, size_t input_number_of_levels, bool input_debug_mode){

	debug_mode           = input_debug_mode;
	number_of_levels     = input_number_of_levels;
	number_of_dimensions = input_number_of_dimensions;

	if( number_of_levels < 2 || number_of_dimensions < 0 ){
		std::cout << "Invalid number_of_dimensions and/or number_of_levels in" 
				  << " Tree::constructor()" << std::endl;
		return;
	}

	// pre calculates of useful indexes
	int children_per_node  = pow(2,number_of_dimensions);
	int number_of_nodes    = ( pow(children_per_node,number_of_levels-1) - 1) / (children_per_node -1);
	int number_of_leaves   = pow(children_per_node,number_of_levels);

	// Alocation of vectors
	nodes.resize(  number_of_nodes  );
	leaves.resize( number_of_leaves );

	std::cout << "Creating "<< number_of_dimensions <<"D tree with " 
	          << number_of_levels << " levels, " << number_of_nodes  
	          << " nodes and "<< number_of_leaves << " leaves. " 
	          << ( debug_mode ? "  Debug mode for this Tree is on!" : "" ) 
	          << std::endl;	

    // Initialize root node.
	nodes[0] = new Tree_Cell();
	nodes[0]->children.resize( children_per_node );

	std::cout << "Size of each node: " << sizeof( *nodes[0] ) << " bytes" << std::endl;

	// Auxiliary variable
	int nodes_in_parent_level = 0;

	// For i... Go through each level except leaf and leaf parent level to create tree_nodes
	//   For j...  Each level has number_of_children^level nodes
	//     For k... Creates "number_of_children" children for each node
	for( int i = 0; i < number_of_levels-2; i++ ){
		for( int j = 0; j < pow(children_per_node,i); j++ ){
			for ( int k = 0; k < children_per_node; k++ ){

				int indexOfCurrentParent = nodes_in_parent_level + j;
				int indexOfCreatedChild  = indexOfCurrentParent * children_per_node + 1 + k;
				
				if(debug_mode){
					std::cout << "  creating level: " << i << " indexOfCurrentParent: " 
					       << indexOfCurrentParent << " child: " << indexOfCreatedChild  
					       << std::endl;			
				}
				nodes[indexOfCreatedChild] = new Tree_Cell();
				nodes[indexOfCreatedChild]->children.resize(children_per_node);
				nodes[indexOfCurrentParent]->children[k] = nodes[indexOfCreatedChild];
			}
		}
		nodes_in_parent_level += pow(children_per_node,i); // Sums number of nodes in this level
	}	

	// For the leaf parent level ( number_of_levels-1), creates leaf nodes with generic class Cell
	for( int j = 0; j < pow(children_per_node,number_of_levels-1); j++ ){
		for ( int k = 0; k < children_per_node; k++ ){
			int indexOfCurrentParent = nodes_in_parent_level + j;
			int indexOfCreatedChild  = indexOfCurrentParent * children_per_node + 1 + k;	
			leaves[indexOfCreatedChild] = new Cell();
		}
	}
	
	//Initialize random seed (if debug mode, seed is constant)
	if(debug_mode){ srand(3);          }
	else          { srand(time(NULL)); }
	
	std::cout << "Tree creation sucessful" << std::endl;
}

Tree::Tree(size_t input_number_of_dimensions, size_t input_number_of_levels){
	constructor(input_number_of_dimensions,input_number_of_levels,false);
}

Tree::Tree(size_t input_number_of_dimensions, size_t input_number_of_levels, bool input_debug_mode){
	constructor(input_number_of_dimensions,input_number_of_levels,input_debug_mode);
}

void Tree::setDebugMode(bool input_debug_mode){
	debug_mode = input_debug_mode;
	
	std::cout << "debug mode for this tree changed to " 
	          << ( debug_mode ? "true" : "false") << std::endl;
}

void Tree::importLeafRow(std::vector<Cell*> input_leaves){
	if( leaves.size() != input_leaves.size() ){
		std::cout << "Provided leaf row size is wrong! Tree::updateLeafRow()" << std::endl;
		return;
	}

	for( int i = 0; i < leaves.size(); i++ ){
		leaves[i] = input_leaves[i];
	}
}

void Tree::exportLeafRow(std::vector<Cell*> target_leaf_row){
	
	std::vector<Tree_Cell*> temp_nodes(nodes);

	// Auxiliary variables
	int children_per_node     = pow(2,number_of_dimensions);
	int nodes_in_parent_level = 0;

	// Goes over the entire Tree re-organizing nodes
	for( int i = 0; i < number_of_levels-2; i++ ){
		for( int j = 0; j < pow( children_per_node ,i); j++ ){
			for ( int k = 0; k < children_per_node; k++ ){

				int indexOfCurrentParent = nodes_in_parent_level + j;
				int indexOfCurrentChild  = indexOfCurrentParent * children_per_node + 1 + k;

				temp_nodes[indexOfCurrentChild] = (Tree_Cell*)(temp_nodes[indexOfCurrentParent])->children[k];
			}
		}
		nodes_in_parent_level += pow(children_per_node,i); // Sums number of nodes in this level
	}

	// For the leaf parent level ( number_of_levels-1), writes new pointers to output
	for( int j = 0; j < pow(children_per_node,number_of_levels-1); j++ ){
		for ( int k = 0; k < children_per_node; k++ ){
			int indexOfCurrentParent     = nodes_in_parent_level + j;
			int indexOfLeaf              =  j* children_per_node + k;	
			target_leaf_row[indexOfLeaf] = temp_nodes[indexOfCurrentParent]->children[k];
		}
	}
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

	if(debug_mode){
		std::cout << "    Random numbers selected = [" 
			      << random_numbers[0] << ","
			      << random_numbers[1] << ","
			      << random_numbers[2] << ","
			      << random_numbers[3] << "] "
			      << std::endl;
	}

	Tree_Cell *grand_parent  = (Tree_Cell*)(nodes[node_index]);
	Tree_Cell *first_parent  = (Tree_Cell*)(grand_parent->children[random_numbers[0]]);
	Tree_Cell *second_parent = (Tree_Cell*)(grand_parent->children[random_numbers[1]]);

	Cell *first_child   = first_parent->children[random_numbers[2]];
	Cell *second_child  = second_parent->children[random_numbers[3]];

	// Node exchange step, the two selected parents exchange their kids
	first_parent->children[random_numbers[2]]  = second_child;
	second_parent->children[random_numbers[3]] = first_child;

	return true;
}

void Tree::randomSwap(){
	
	int r = rand()%(int)( nodes.size()/ (2*pow(2,number_of_dimensions)) );

	std::cout << "Swap on node: "<< r << ", result: " << (this->swap(r) ? "sucess" : "failure") << std::endl;
}


/*
void Tree::print(){

	std::cout << "Printing tree with " << nodes.size() << " nodes" << std::endl;

	std::cout << nodes[0]->scalar << std::endl;

	std::vector<Cell*> temp_nodes(nodes);

	for( int i = 0; i < number_of_levels-1; i++ ){
		for( int j = 0; j < pow( pow(2,number_of_dimensions),i); j++ ){
			for ( int k = 0; k < pow(2,number_of_dimensions); k++ ){


				std::cout << temp_nodes[indexOfCurrentParent]->children[k]->scalar << " ";
			}

			std::cout<< "  ";
		}

		std::cout<<std::endl;
	}	
}
*/
