/**************************************************
* Program: Project03
* File: TrieNode.hpp
* Class: CS 415
* Author: James Rodriguez
* Date: 11-22-2019
**************************************************/

class BinSearchTree;

class TrieNode {
public:
	TrieNode(): child(nullptr) {}
	TrieNode( char n ): data(n), child(nullptr) {}

    bool &isEnd() { return isEndof; }
	void setIsEnd( bool isEndof) { this->isEndof = isEndof; }
	
    BinSearchTree *childTree() {return child;}
	
    void childTree( BinSearchTree *child ) { this->child = child; }
	
    char &value() { return data; } 

private:
    char data;
	BinSearchTree *child;
	bool isEndof;
};  
