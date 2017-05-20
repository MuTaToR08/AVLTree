#include "BinaryTree.h"
#include <iostream>

void main()
{
	BinaryTree<int> binary;

	binary.add(5);
	binary.add(1);
	binary.add(3);
	binary.add(16);
	binary.add(6);
	binary.add(9);
	binary.add(24);
	binary.add(5);
	binary.add(4);
	binary.add(2);
	binary.add(10);

	binary.remove(100);
	binary.remove(5);
	binary.remove(9);
	binary.remove(300);

	binary.show();

	std::cin.get();

	return;

}