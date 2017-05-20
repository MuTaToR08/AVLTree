#pragma once
#include "NodeTree.h"
#include <iostream>
#include <vector>
#include <string>

template <class T>
class BinaryTree
{
	NodeTree<T> *root;
	std::vector<std::string> str;
	NodeTree<T>* insert(NodeTree<T>* node, T elem);
	NodeTree<T>* remove(NodeTree<T>* node, T elem);
	void showNode(NodeTree<T>* node);


	NodeTree<T>* findmin(NodeTree<T>* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	NodeTree<T>* removemin(NodeTree<T>* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}
	unsigned char height(NodeTree<T>* p)
	{
		return p!= nullptr ? p->heightNode : 0;
	}

	int bfactor(NodeTree<T>*& p)
	{
		return height(p->right) - height(p->left);
	}

	void fixHeight(NodeTree<T>*& p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->heightNode = (hl > hr ? hl : hr) + 1;
	}

	NodeTree<T>* rotateRight(NodeTree<T>*& p)
	{
		NodeTree<T>* q = p->left;
		p->left = q->right;
		q->right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}
	NodeTree<T>* rotateLeft(NodeTree<T>*& q)
	{
		NodeTree<T>* p = q->right;
		q->right = p->left;
		p->left = q;
		fixHeight(q);
		fixHeight(p);
		return p;
	}
	NodeTree<T>* balance(NodeTree<T>* p)
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if(bfactor(p) == -1)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}
	void printWithLvls(NodeTree<T> *w, int level = 0, int shift = 0, bool node_shit=false)
	{
		std::string s = "                                                                               ";
		if (this->str.size() <= level)
			str.push_back(s);

		if (w != NULL)
		{
			int center = s.size() / 2;
			std::string tmpData = std::to_string(w->data);
			str[level].insert(center + shift+(level*level*(node_shit?-1:1)), std::to_string(w->data));

			printWithLvls(w->left, level + 1, shift - root->heightNode*3, false);
			printWithLvls(w->right, level + 1, shift + root->heightNode * 3, true);

		}
	}
public:
	BinaryTree();
	~BinaryTree();

	void add(T elem);
	void remove(T elem);
	void show();

	unsigned char height()
	{
		return height(root);
	}

private:

};

template<class T>
NodeTree<T> * BinaryTree<T>::insert(NodeTree<T>* node, T elem)
{
	if (elem == 3746)
		elem = elem;
	if (node == nullptr)
	    return new NodeTree<T>(elem);
	 
	if (elem <= node->data)
        node->left = insert(node->left, elem);
	else
	    node->right = insert(node->right, elem);
	return balance(node);

}

template<class T>
inline NodeTree<T>* BinaryTree<T>::remove(NodeTree<T>* node, T elem)
{
	if (node == nullptr)
		return nullptr;
	if (elem < node->data)
		node->left = remove( node->left, elem);
	else if(elem > node->data)
		node->right = remove( node->right, elem);
	else
	{
		NodeTree<T>* q = node->left;
		NodeTree<T>* r = node->right;
		delete node;
		if (!r) return q;
		NodeTree<T>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}

	return balance(node);
}

 template<class T>
void BinaryTree<T>::showNode(NodeTree<T>* node)
 {
	
	 if (node != nullptr)
	 {
		 showNode(node->left);
		 std::cout << node->data << " < ";
		 showNode(node->right);
	 }
 }

/*
template<class T>
void BinaryTree<T>::printWithLvls(NodeTree<T> *w,  int level=0,bool use_t = false)
{
	std::string s = "                                               ";
	if (this->str.size() <= level)
		str.push_back(s);

	if (w != NULL)
	{
		int center = s.size() / 2;
		std::string tmpData = std::to_string(w->data);


		printWithLvls(w->left, level + 1,false);
		for (int i = 0; i < level; i++)
			std::cout << "     ";
		std::cout << w->data<< '\n';
		printWithLvls(w->right, level + 1,true);

	}
}*/

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
}

template<class T>
void BinaryTree<T>::add(T elem)
{
	root = insert( root, elem);
}
template<class T>
void BinaryTree<T>::remove(T elem)
{
	root = remove(root, elem );
}

template<class T>
void BinaryTree<T>::show()
{
	printWithLvls(root);
	for (int i = 0; i < str.size(); i++)
		std::cout << str[i].substr(0, 80)<<std::endl;
}
