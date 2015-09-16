OBJ = prog3.o Node.o Link.o Trie.o  
OPTS= -g -c -Wall -Werror

testtrie: $(OBJ)
	g++ -o testtrie $(OBJ) 

prog3.o: prog3.cpp Node.cpp Node.h Link.cpp Link.h Trie.cpp Trie.h
	g++ $(OPTS) prog3.cpp

Node.o: Node.cpp Node.h
	g++ $(OPTS) Node.cpp

Link.o: Link.cpp Link.h
	g++ $(OPTS) Link.cpp

Trie.o: Trie.cpp Trie.h
	g++ $(OPTS) Trie.cpp

clean:
	rm -f *.o testtrie  *~
