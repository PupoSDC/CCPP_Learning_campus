#include <iostream>
#include <stdlib.h>     
#include <time.h>       
#include "tree.h"

int main(){

	_DEBUG( std::cout << "DEBUG mode is on!" << std::endl; );

	size_t numberOfLevels = 3;
	size_t dimensions     = 3; // 3D problem

	Tree *bintree = new Tree(dimensions,numberOfLevels);

	//bintree->print();
	

	for(int i = 0; i<1000; i++){
	//	bintree->randomSwap();
	}

	//bintree->print();

	std::cout << "Program Finished" << std::endl;
	
	return 0;
}