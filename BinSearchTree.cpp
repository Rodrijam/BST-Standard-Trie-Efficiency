/**************************************************
* Program: Project03
* File: BinSearchTree.cpp
* Class: CS 415
* Author: James Rodriguez
* Date: 11-22-2019
**************************************************/

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"

#include <iostream>
#include <queue>


TreeNode *BinSearchTree::local_insert( TreeNode *root, char v ) 
{
   if( root == nullptr )
       return new TreeNode( v );
   if( root->nodeTrie()->value() < v )
       root->rightSubtree( local_insert( root->rightSubtree(), v ) );
   else
       root->leftSubtree( local_insert( root->leftSubtree(), v ) );
   return root;
}

void BinSearchTree::insert(char v) 
{
    if( ! find(v) )
        root = local_insert( root, v );
}

bool BinSearchTree::local_find(TreeNode *root, char v)
{
	if (root == nullptr)
		return false;
	if (v == root->nodeTrie()->value())
		return true;
	if (v > root->nodeTrie()->value())
		return local_find(root->rightSubtree(),v);
	return local_find(root->leftSubtree(),v);	
}

bool BinSearchTree::find(char v)
{
	return local_find(root, v);
}

bool BinSearchTree::iterFind(char v)
{
	TreeNode *troot = root;
	while(troot != nullptr)
	{
		if (v == troot->nodeTrie()->value())
			return true;
		if (v > troot->nodeTrie()->value())
			troot = troot->rightSubtree();
		else
			troot = troot->leftSubtree();
	}
	return false;
}

int BinSearchTree::local_size(TreeNode *root)
{
	if(root == nullptr)
		return 0;
	return 1 + local_size(root->leftSubtree()) + local_size(root->rightSubtree());
}

int BinSearchTree::size()
{
	return local_size(root);
}

void BinSearchTree::local_inorderDump(TreeNode *root)
{
	if (root == nullptr)
		return;
	local_inorderDump(root->leftSubtree());
	std::cout << root->nodeTrie()->value() << std::endl;
	local_inorderDump(root->rightSubtree());
}

void BinSearchTree::inorderDump()
{
	local_inorderDump(root);
}

void BinSearchTree::printiOP()
{
	std::cout << inOrderPredecessor(root)->nodeTrie()->value() << std::endl;
}

TreeNode * BinSearchTree::inOrderPredecessor(TreeNode * root)
{
	if (root == nullptr)
		return nullptr;
	if (root->leftSubtree() == nullptr)
		return nullptr;
	root = root -> leftSubtree();
	if (root -> rightSubtree() != nullptr)
		return root -> rightSubtree();
	return root;
}
