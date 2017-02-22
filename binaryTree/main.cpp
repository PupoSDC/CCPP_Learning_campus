#include <iostream>
#include <stdlib.h>     
#include <time.h>       
#include "tree.h"

int main(){

	size_t numberOfLevels = 3;
	size_t dimensions     = 2; // 3D problem

	Tree *bintree = new Tree(dimensions,numberOfLevels);

	//bintree->print();
	
	for(int i = 0; i<2; i++){
		bintree->randomSwap();
	}

	//bintree->print();

	std::cout << "Program Finished" << std::endl;
	
	return 0;
}