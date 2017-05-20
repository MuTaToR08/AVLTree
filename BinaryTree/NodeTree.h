#pragma once


template<class T>
struct NodeTree
{
	NodeTree *left, *right;
	T data;
	int heightNode;
	NodeTree(T key) {
		data = key;
		left = right = 0;
		heightNode = 1;
	}
};