CFLAGS= -ggdb -std=c++11 -Wall -Wextra

main.x: BinSearchTree.o Trie.o main.o
	g++ $(CFLAGS) -o main.x BinSearchTree.o Trie.o main.o
	
BinSearchTree.o: BinSearchTree.hpp BinSearchTree.cpp
	g++ $(CFLAGS) -c -o BinSearchTree.o BinSearchTree.cpp

Trie.o: Trie.hpp Trie.cpp
	g++ $(CFLAGS) -c -o Trie.o Trie.cpp
	
main.o: TreeNode.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp
	
clean:
	rm -f *.o *.x *~