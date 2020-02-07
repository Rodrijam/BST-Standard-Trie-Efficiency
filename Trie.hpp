/**************************************************
* Program: Project03
* File: Trie.hpp
* Class: CS 415
* Author: Jason Hubbs
* Date: 11-22-2019
**************************************************/

#ifndef P3_TRIE_HPP
#define P3_TRIE_HPP
#define CHAR_SIZE 26

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Trie {
public:
    string value;
    bool isLeaf;
    Trie* children[CHAR_SIZE];

    Trie(){
        isLeaf = false;
        value ="";
        for(int i = 0; i < CHAR_SIZE; i++){
            children[i] = nullptr;
        }
    }

	int nodeCount;
    vector<string> list;
	
    void Insert(string key);
    bool Search(string key);
    void FillList(Trie *sub);
    void SetValue(string v);
    bool IsLast(Trie *sub);
    Trie* ReturnSubTrie(string key);

};


#endif //P3_TRIE_HPP
