/**************************************************
* Program: Project03
* File: BinSearchTree.hpp
* Class: CS 415
* Author: James Rodriguez
* Date: 11-22-2019
**************************************************/
class TreeNode;

class BinSearchTree {
public:
   void insert( char v );
   bool find( char v );
   bool iterFind( char v );
   int size();
   void inorderDump();
   TreeNode *getRoot() {return root;}
   
   	void printiOP();
	TreeNode * inOrderPredecessor(TreeNode * root);

private:
   TreeNode *local_insert( TreeNode *, char );
   bool local_find(TreeNode *root, char v);
   int local_size(TreeNode *root);
   void local_inorderDump(TreeNode *root);
   
   TreeNode *root;
};