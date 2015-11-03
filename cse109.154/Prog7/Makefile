OBJ = assembler.o Node.o Link.o Trie.o  
OPTS= -g -c -Wall -Werror

assembler: $(OBJ)
	g++ -o assembler $(OBJ) 

assembler.o: assembler.cpp Node.cpp Node.h Link.cpp Link.h Trie.cpp Trie.h
	g++ $(OPTS) assembler.cpp

Node.o: Node.cpp Node.h
	g++ $(OPTS) Node.cpp

Link.o: Link.cpp Link.h
	g++ $(OPTS) Link.cpp

Trie.o: Trie.cpp Trie.h
	g++ $(OPTS) Trie.cpp

clean:
	rm -f *.o assembler  *~
