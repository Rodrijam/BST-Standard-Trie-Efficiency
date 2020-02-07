/**************************************************
* Program: Project03
* File: TrieNode.hpp
* Class: CS 415
* Author: Jason Hubbs and James Rodriguez
* Date: 11-22-2019
**************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string.h>
#include <stdio.h>

#include "TreeNode.hpp"
#include "BinSearchTree.hpp"
#include "Trie.hpp"

using namespace std;
using namespace std::chrono; 

BinSearchTree *insertNode(BinSearchTree *tree, int idx, int lvl, string word);
vector<string> findOthers (TreeNode *currNode, vector<string> qList, string cQuery);
void setEndFlag(BinSearchTree *tree, char inChar);

int nodeCount;
vector<string> finalList;

int main (int argc, char *argv[]){
	
	if (argc != 3 || ((strcmp(argv[2], "1") != 0) && (strcmp(argv[2], "2") != 0)))
	{
		cerr << "Not enough arguments in command or arguments invalid, format: {executable file 1/2}" << endl;
		exit(0);
	}
	
    ifstream inFile;
    inFile.open(argv[1]);
	
    if (!inFile) {
        cout << "Unable to open file" << endl;
        exit(1);
    }
	
	BinSearchTree *tree = new BinSearchTree();
	string word;
	
	vector<string> docList;
	
	// reading in strings adds words to docList
	while (inFile >> word)								
	{
		string newWord = "";
		for(unsigned int i = 0; i < word.size(); i++)	// go through strings and set characters to lowercase
			newWord += tolower(word[i]);
		string inWord;
		remove_copy_if(newWord.begin(), newWord.end(), back_inserter(inWord),ptr_fun<int, int>(&ispunct)); // From algorithm library to remove puncuation form strings
		docList.push_back(inWord);						// insertion into the collection of strings
	}

	// Goes through docList and add to BST
	auto BSTbuildstart = high_resolution_clock::now(); 	//start insert clock
	for (unsigned int i = 0; i < docList.size(); i++)
	{
		string docWord = docList[i];
		for (unsigned int j = 0; j < docWord.size(); j++)
			tree = insertNode(tree, j, 0, docWord);
	}
	auto BSTbuildstop = high_resolution_clock::now(); 	//ends insert clock
	auto BSTbuildduration = duration_cast<microseconds>(BSTbuildstop - BSTbuildstart);

	Trie *trie = new Trie();
	auto STDbuildstart = high_resolution_clock::now(); 	//start insert clock
	for (unsigned int i = 0; i < docList.size(); i++)	
	{
		string docWord = docList[i];
		trie->Insert(docWord);
	}	
	auto STDbuildstop = high_resolution_clock::now(); 	//ends insert clock
	auto STDbuildduration = duration_cast<microseconds>(STDbuildstop - STDbuildstart);	

	cout << "Time taken to build the standard Trie is " << STDbuildduration.count() << " microseconds and space occupied by it is " << trie->nodeCount * 26 << " nodes" <<endl; // number of nodes * 26
	cout << "Time taken to build the BST based Trie is " << BSTbuildduration.count() << " microseconds and space occupied by it is " << nodeCount << " nodes" << endl << endl;
	
	string query;

	if (strcmp(argv[2], "2") == 0)
	{
		auto BSTsearchAllstart = high_resolution_clock::now();
		for (unsigned int i = 0; i < docList.size(); i++)
		{
			query = docList[i];
			BinSearchTree *currTree = tree;
			for (unsigned int j = 0; j < query.size(); j++)
			{	
				TreeNode *currNode = currTree->getRoot();
				while (query[j] != currNode->nodeTrie()->value())
				{
					if (query[j] < currNode->nodeTrie()->value())
						currNode = currNode->leftSubtree();
					else
						currNode = currNode->rightSubtree();
				}
				currTree = currNode->nodeTrie()->childTree();			
			}			
		}
		auto BSTsearchAllstop = high_resolution_clock::now(); 
		auto BSTsearchAllduration = duration_cast<microseconds>(BSTsearchAllstop - BSTsearchAllstart);
		
		auto STDsearchAllstart = high_resolution_clock::now();
		for (unsigned int i = 0; i < docList.size(); i++)
		{
			query = docList[i];
			trie->ReturnSubTrie(query);
		}
		auto STDsearchAllstop = high_resolution_clock::now(); 
		auto STDsearchAllduration = duration_cast<microseconds>(STDsearchAllstop - STDsearchAllstart);
		
		

		
		cout << "Time taken to search all the strings in the standard Trie is " << STDsearchAllduration.count() << " microseconds" << endl;
		
		cout << "Time taken to search all the strings in the BST based Trie is " << BSTsearchAllduration.count() << " microseconds" << endl;
	}
	else
	{
		while (query != "$")
		{

			vector<string> qList;

			cout << "Enter search string: ";
			cin >> query;

			if(trie->Search(query)){ //Check if query exists in tree, continue if true
				auto STDsearchstart = high_resolution_clock::now();
				auto pronounTrie = trie->ReturnSubTrie(query);
				auto STDsearchstop = high_resolution_clock::now();
				auto STDsearchduration = duration_cast<microseconds>(STDsearchstop - STDsearchstart);

				cout << "Time taken to search in the standard Trie is " << STDsearchduration.count() << " microseconds" << endl;
				cout << "Auto-complete results using standard Trie are: ";

				auto STDautostart = high_resolution_clock::now();

				//Populate and print list
				pronounTrie->FillList(pronounTrie);

				int size = pronounTrie->list.size();
				for(int i = 0; i < size; i++){
					if(size == (i + 1))
						cout << pronounTrie->list[i];
					else
						cout << pronounTrie->list[i] << ", ";
				}

				cout << endl;
				auto STDautostop = high_resolution_clock::now();
				auto STDautoduration = duration_cast<microseconds>(STDautostop - STDautostart);
				cout << "Time taken to find auto-complete results in the standard Trie is " << STDautoduration.count() << " microseconds" << endl << endl;
			}
			
			BinSearchTree *currTree = tree;
			
			auto BSTsearchstart = high_resolution_clock::now(); 
			for (unsigned int i = 0; i < query.size(); i++)		// search for query string
			{	
				if (currTree == NULL || !currTree->find(query[i]))
				{
					cout << "Query " << query << " does not exist in tree." << endl;
					return 0;
				}
				else
				{
					TreeNode *currNode = currTree->getRoot();
					while (query[i] != currNode->nodeTrie()->value())
					{
						if (query[i] < currNode->nodeTrie()->value())
							currNode = currNode->leftSubtree();
						else
							currNode = currNode->rightSubtree();
					}
					if (i == query.size()-1)
					{
						if (currNode->nodeTrie()->isEnd())
							qList.push_back(query);
					}
					currTree = currNode->nodeTrie()->childTree();
				}
			
			}
			auto BSTsearchstop = high_resolution_clock::now(); 
			auto BSTsearchduration = duration_cast<microseconds>(BSTsearchstop - BSTsearchstart);

			auto BSTautostart = high_resolution_clock::now(); 	
			if (currTree != NULL)
				qList = findOthers(currTree->getRoot(), qList, query);	// search for other autocomplete strings using query
			auto BSTautostop = high_resolution_clock::now(); 
			auto BSTautoduration = duration_cast<microseconds>(BSTautostop - BSTautostart);

			
			cout << "Time taken to search in the BST based Trie is " << BSTsearchduration.count() << " microseconds" << endl;
			
			if (qList.empty())
				cout << "No results could be found from query '" << query << "'" << endl;
			else
				cout << "Auto-complete results using BST based Trie are: ";
			
			for (unsigned int i = 0; i < qList.size(); i++)
				{
					cout << qList[i];
					if (i != qList.size()-1)
						cout << ", "; 
				}
			cout << endl;

			cout << "Time taken to find auto-complete results in the BST based Trie is " << BSTautoduration.count() << " microseconds" << endl << endl;
		}
	}
	return 0;
}

BinSearchTree *insertNode(BinSearchTree *tree, int idx, int lvl, string word)
{
	//char inChar = tolower(word[idx]);		 // Sets character for index in word
	char inChar = word[idx];
	if (idx == 0) 					// Takes the first character of the word to add to the root node
	{		
		if (!tree->find(inChar)) 	// Checks if character is in root already
		{
			tree->insert(inChar);	//inserts node into tree
			nodeCount++;
		}
		if ((unsigned int)idx == word.size()-1)		// Checks if the isEnd flag should be set
			setEndFlag(tree, inChar);
	}
	
	TrieNode *tn = tree->getRoot()->nodeTrie();

	if (idx == lvl)					// if the character is at the level it should be at
	{	
		if (!tree->find(inChar))	//checks if character is already in the current tree
		{
			tree->insert(inChar);
			nodeCount++;
		}

		if ((unsigned int)idx == word.size()-1)
			setEndFlag(tree, inChar);
		
		return tree;
	}
	
	if (tn->childTree() == NULL && word[lvl] == tn->value())	// checks if the current node has a child tree to work with
	{
		BinSearchTree *tree2 = new BinSearchTree();
		tree2->insert(inChar);
		nodeCount++;
					
		if ((unsigned int)idx == word.size()-1)
			setEndFlag(tree2, inChar);
		
		tn->childTree(tree2);
		return tree;
	}
	
	if (word[lvl] == tn->value())	// if the characters in the word allign so far, move to the next tree
		tn->childTree(insertNode(tn->childTree(), idx, lvl+1, word));
	else 							// compare values of previous levels with the current to see where to navigate in the tree
	{
		if (word[lvl] > tn->value())	// navigate to the right subtree
		{
			TreeNode *rTree = tree->getRoot()->rightSubtree();
			while (rTree->nodeTrie()->value() != word[lvl])	// grabs the right node from the tree
			{
				if (word[lvl] < rTree->nodeTrie()->value())
					rTree = rTree->leftSubtree();
				else
					rTree = rTree->rightSubtree();
			}
			if (rTree->nodeTrie()->childTree() == NULL)
			{
				BinSearchTree *newTree = new BinSearchTree();
				newTree->insert(inChar);
				nodeCount++;
				
				if ((unsigned int)idx == word.size()-1)
					setEndFlag(newTree, inChar);
				
				rTree->nodeTrie()->childTree(newTree);
			}
			else
				rTree->nodeTrie()->childTree(insertNode(rTree->nodeTrie()->childTree(), idx, lvl+1, word));
		}
		else			// navigate to the leftt subtree
		{
			TreeNode *lTree = tree->getRoot()->leftSubtree();
			while (lTree->nodeTrie()->value() != word[lvl])	// grabs the right node from the tree
			{
				if (word[lvl] < lTree->nodeTrie()->value())
					lTree = lTree->leftSubtree();
				else
					lTree = lTree->rightSubtree();
			}
			if (lTree->nodeTrie()->childTree() == NULL)
			{
				BinSearchTree *newTree = new BinSearchTree();
				newTree->insert(inChar);
				nodeCount++;
							
				if ((unsigned int)idx == word.size()-1)
					setEndFlag(newTree, inChar);
				
				lTree->nodeTrie()->childTree(newTree);		
			}
			else
				lTree->nodeTrie()->childTree(insertNode(lTree->nodeTrie()->childTree(), idx, lvl+1, word));
		}

	}
	return tree;		
}


vector<string> findOthers (TreeNode *currNode, vector<string> qList, string cQuery)
{
	if (currNode == NULL)
		return qList;
	string newQ = cQuery + currNode->nodeTrie()->value();

	if (currNode->nodeTrie()->isEnd())	// if the node has an isEnd flag, it marks a completed string
		qList.push_back(newQ);

	if (currNode->nodeTrie()->childTree() != NULL)
		qList = findOthers(currNode->nodeTrie()->childTree()->getRoot(), qList, newQ);	// adds strings from current node
	if (currNode->leftSubtree() != NULL)
		qList = findOthers(currNode->leftSubtree(), qList, cQuery);	// adds strings from left subtree of current node
	if (currNode->rightSubtree() != NULL)
		qList = findOthers(currNode->rightSubtree(), qList, cQuery); // adds strings from right subtree of current node
		
	return qList;
}

void setEndFlag(BinSearchTree *tree, char inChar) // function to iterate through a BST, until a specific character node is found, then sets that node's isEnd flag to true
{
	TreeNode *getN = tree->getRoot();
	while (inChar != getN->nodeTrie()->value())
		{
		if( inChar < getN->nodeTrie()->value())
			getN = getN->leftSubtree();
		else
			getN = getN->rightSubtree();
		}
	getN->nodeTrie()->setIsEnd(true);
}
