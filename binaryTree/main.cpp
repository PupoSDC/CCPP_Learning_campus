#include <iostream>
#include "tree.h"

using namespace std;

int main(){

	size_t numberOfLevels = 4;

	Tree *bintree = new Tree(numberOfLevels);

	cout << "swap 10 with 13: " << bintree->swap(10,13) << endl;
	bintree->printtree();

	return 0;
}