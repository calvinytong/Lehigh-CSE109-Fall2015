OBJ = prog4.o Lexer.o Token.o
OPTS= -g -c -Wall -Werror -std=c++0x

lextest: $(OBJ)
	g++ -o lextest $(OBJ)

prog4.o: prog4.cpp Lexer.cpp Lexer.h Token.cpp Token.h
	g++ $(OPTS) prog4.cpp

Lexer.o: Lexer.cpp Lexer.h
	g++ $(OPTS) Lexer.cpp

Token.o: Token.cpp Token.h
	g++ $(OPTS) Token.cpp

clean:
	rm -f *.o lextest *~
