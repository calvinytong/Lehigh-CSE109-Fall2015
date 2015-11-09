OBJ = assembler.o Node.o Link.o Trie.o Lexer.o Token.o
OPTS= -g -c -Wall -Werror

assembler: $(OBJ)
	g++ -o assembler $(OBJ) 

assembler.o: assembler.cpp Node.cpp Node.h Link.cpp Link.h Trie.cpp Trie.h Lexer.o Token.o
	g++ $(OPTS) assembler.cpp

Node.o: Node.cpp Node.h
	g++ $(OPTS) Node.cpp

Link.o: Link.cpp Link.h
	g++ $(OPTS) Link.cpp

Trie.o: Trie.cpp Trie.h
	g++ $(OPTS) Trie.cpp

Lexer.o: Lexer.cpp Lexer.h
	g++ $(OPTS) Lexer.cpp

Token.o: Token.cpp Token.h
	g++ $(OPTS) Token.cpp

clean:
	rm -f *.o assembler  *~
