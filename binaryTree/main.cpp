#include <iostream>
#include <stdlib.h>     
#include <time.h>       
#include "tree.h"

using namespace std;

int main(){

	size_t numberOfLevels = 20;

	Tree *bintree = new Tree(numberOfLevels);

	bintree->printtree();
	for(int i = 0; i< 100; i++){
		bintree->randomSwap();
	}
	bintree->printtree();

	return 0;
}