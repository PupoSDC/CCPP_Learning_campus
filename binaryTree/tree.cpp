#include "tree.h"

Tree::Tree(size_t input_number_of_dimensions, size_t input_number_of_levels){

	number_of_levels     = input_number_of_levels;
	number_of_dimensions = input_number_of_dimensions;
	children_per_node    = pow(2,number_of_dimensions);

	if( number_of_levels < 2 || number_of_dimensions < 0 ){
		std::cout << "Invalid number_of_dimensions and/or number_of_levels in" 
				  << " Tree::constructor()" << std::endl;
		return;
	}

	nodes.resize(  
		( pow(children_per_node,number_of_levels-1) - 1) / 
	    ( children_per_node -1)
	);  

	std::cout << "Creating "<< number_of_dimensions <<"D tree with " 
	          << number_of_levels << " levels and " << nodes.size() 
	          << " nodes. " << std::endl;
	
	_DEBUG( std::cout << "--Debug mode for this Tree is on!" << std::endl; );

    // Initialize root node.
	nodes[0] = new Tree_Cell();
	nodes[0]->children.resize( children_per_node );

	std::cout << "--Size of each node: " << sizeof( *nodes[0] ) << " bytes" << std::endl;

	// Auxiliary variable
	size_t nodes_in_parent_level = 0;

	// For i... Go through each level except leaf and leaf parent level to create tree_nodes
	//   For j...  Each level has number_of_children^level nodes
	//     For k... Creates "number_of_children" children for each node
	for( int i = 0; i < number_of_levels-2; i++ ){
		for( int j = 0; j < pow(children_per_node,i); j++ ){
			for ( int k = 0; k < children_per_node; k++ ){

				size_t index_of_current_parent = nodes_in_parent_level + j;
				size_t index_of_current_child  = index_of_current_parent * children_per_node + 1 + k;
				
				_DEBUG( 
					std::cout << "----creating level: " << i << " indexOfCurrentParent: " 
					              << index_of_current_parent << " child: " 
					              << index_of_current_child  
					              << std::endl; 
					  );

				nodes[index_of_current_child] = new Tree_Cell();
				nodes[index_of_current_child]->children.resize(children_per_node);
				nodes[index_of_current_parent]->children[k] = nodes[index_of_current_parent];
			}
		}
		nodes_in_parent_level += pow(children_per_node,i); // Sums number of nodes in this level
	}	

	// Initialize random seed (if debug mode, seed is constant)
	srand(time(NULL));
	_DEBUG(srand(3););
	
	std::cout << "--Tree creation sucessful" << std::endl;
}

///////////////////////////////////////////////////////////////////
/// Private functions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int Tree::selectOneTargetNode(){

	int r = rand()%(int)( nodes.size()/(children_per_node) );

	return r;
}

bool Tree::importLeafRow(std::vector<Cell*> input_leaves){
	
	int first_parent      = nodes.size() / pow(children_per_node,2);
    int first_leaf        = nodes.size() / children_per_node;

	if( input_leaves.size() != nodes.size()*children_per_node ){
		std::cout << "Provided leaf row size is wrong! Tree::updateLeafRow()" << std::endl;
		return false;
	}

	for( int i = 0; i < input_leaves.size(); i += children_per_node ){
		int index_of_parent = first_parent + i / children_per_node;
		for( int j = 0; j < children_per_node; j++){
			nodes[index_of_parent]->children[j] = input_leaves[i+j];
		}
	}

	return true;
}

bool Tree::exportLeafRow(Cell *first_child, Cell *second_child){
	
	int number_of_leaves_to_copy = 1;

	// While a leave is not reached, keep selecting the leftmost node for
	// both the first_child and second_child. Increment number of leaves to 
	// copy.
	while( dynamic_cast<Tree_Cell*>(first_child) != NULL )
	{
		first_child  =  dynamic_cast<Tree_Cell*>(first_child)->children[0] ;
		second_child =  dynamic_cast<Tree_Cell*>(second_child)->children[0];

		number_of_leaves_to_copy = number_of_leaves_to_copy * children_per_node;
	}

	// temp value
	Cell *temp_cell; 

	// For all leaves to copy copy by incrementing the leave pointer
	for( int i; i < number_of_leaves_to_copy; i++)
	{
		temp_cell = (second_child +i);

		*(first_child + i)  = *(second_child +i);
		*(second_child + i) = *temp_cell;
	}
}

///////////////////////////////////////////////////////////////////
/// Public functions //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void Tree::createEddyEvent(std::vector<Cell*> field){
	
	if( !importLeafRow(field) ){
		std::cout << "Failure importing leaves!" << std::endl;
		return;
	}

	int grandparent_index = selectOneTargetNode();

	// Create array with four random numbers [0,2^N_dim]. 
	// First two randoms cannot be the same 
	int random_numbers[4] = { 0, 0, 0, 0 };
	
	while( random_numbers[0] == random_numbers[1] ){
		random_numbers[0] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[1] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[2] = rand()%(int)pow(2,number_of_dimensions);
		random_numbers[3] = rand()%(int)pow(2,number_of_dimensions);
	}

	_DEBUG(
		std::cout << "    Target Node: " 
		          << grandparent_index
				  << ", Random numbers selected = [" 
			      << random_numbers[0] << ","
			      << random_numbers[1] << ","
			      << random_numbers[2] << ","
			      << random_numbers[3] << "] "
			      << std::endl;
	)

	Tree_Cell *grandparent   = (Tree_Cell*)(nodes[grandparent_index]);
	Tree_Cell *first_parent  = (Tree_Cell*)(grandparent->children[random_numbers[0]]);
	Tree_Cell *second_parent = (Tree_Cell*)(grandparent->children[random_numbers[1]]);

	Cell *first_child   = first_parent->children[random_numbers[2]];
	Cell *second_child  = second_parent->children[random_numbers[3]];

	// A call should be made to a test function to assess the 
	// viability of this exchange before proceeding
	// if ( !testexchange(grandparent,first_child,second_child)){
	// 		return false;
	// }
	//	else{
	//		break;
	//	}

	// Node exchange step, the two selected parents exchange their kids
	//first_parent->children[random_numbers[2]]  = second_child;
	//second_parent->children[random_numbers[3]] = first_child;

	exportLeafRow(first_child,second_child);

	std::cout << "Swap performed on node: " 
	          << grandparent_index 
	          << std::endl;

}