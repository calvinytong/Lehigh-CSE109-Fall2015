OBJ = prog8.o Graph.o Node.o TrieNode.o Link.o Trie.o
OPTS = -g -c -Wall -Werror

wordlist: $(OBJ)
	g++ -o wordlist $(OBJ)

prog8.o: prog8.cpp Graph.o Node.o
	g++ $(OPTS) prog8.cpp

Graph.o: Graph.h Graph.cpp
	g++ $(OPTS) Graph.cpp

Node.o: Node.h Node.cpp
	g++ $(OPTS) Node.cpp

Trie.o: Trie.h Trie.cpp
	g++ $(OPTS) Trie.cpp

TrieNode.o: TrieNode.h TrieNode.cpp
	g++ $(OPTS) TrieNode.cpp

Link.o: Link.h Link.cpp
	g++ $(OPTS) Link.cpp

clean:
	rm -f *.o wordlist *~
