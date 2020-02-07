/**************************************************
* Program: Project03
* File: Trie.cpp
* Class: CS 415
* Author: Jason Hubbs
* Date: 11-22-2019
**************************************************/

#include "Trie.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**************************************************
* Function: void Trie::Insert(string key)
* Description: Insert key into Trie
**************************************************/
void Trie::Insert(string key) {
    Trie *curr = this;
    string value;

    for(unsigned int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        value+= key[i];

        if(curr->children[index] == nullptr){ //Create child node and add it to array[index], if there is not one already
            auto newTrie = new Trie();
			nodeCount++;
            newTrie->SetValue(value);
            curr->children[index] = newTrie;
        }
        curr = curr->children[index]; //Iterates to next node
    }
    curr->isLeaf = true; //Sets leaf value to true at the end of word insert
}

/**************************************************
* Function: bool Trie::Search(string key)
* Description: Search Trie for key
**************************************************/
bool Trie::Search(string key) {
    Trie *curr = this;

    for(unsigned int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if(!curr->children[index]) //Return false if next node doesn't contain next element in key
            return false;
        curr = curr->children[index]; //Iterates to next node
    }
    return true;
}

/**************************************************
* Function: Trie* Trie::ReturnSubTrie(string key)
* Description: Iterates through Trie and returns
* "pronoun" trie of key
**************************************************/
Trie* Trie::ReturnSubTrie(string key){
    Trie *curr = this;

    for(unsigned int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if(!curr->children[index])
            return children[index];
        curr = curr->children[index];
    }
    return curr;
}

bool Trie::IsLast(Trie *sub) {
    Trie *curr = sub;

    for(int i = CHAR_SIZE; i > 0; i--){
        if(curr->children[i] == nullptr){
            IsLast(curr->children[i]);
        }
    }
    return false;
}

/**************************************************
* Function: void Trie::Print(Trie *sub)
* Description: Recursively iterates through trie
* and prints all words that exist in *curr
**************************************************/
void Trie::FillList(Trie *pronoun) {

    Trie *curr = pronoun;


    if(curr->isLeaf) {
        list.push_back(curr->value);
    }

    for(unsigned int i = 0; i < CHAR_SIZE; i++){
        if(curr->children[i] != nullptr){
            FillList(curr->children[i]);
        }
    }
}

/**************************************************
* Function: void Trie::SetValue(string v)
* Description: Sets the value of a node to v
**************************************************/
void Trie::SetValue(string v) {
    value = v;
}