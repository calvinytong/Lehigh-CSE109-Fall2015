OBJ = silc.o Lexer.o Token.o parser.o
OPTS= -g -c -Wall -Werror 
silc: $(OBJ)
	g++ -o silc $(OBJ)

silc.o: silc.cpp Lexer.cpp Lexer.h Token.cpp Token.h parser.cpp parser.h
	g++ $(OPTS) silc.cpp

Lexer.o: Lexer.cpp Lexer.h
	g++ $(OPTS) Lexer.cpp

Token.o: Token.cpp Token.h
	g++ $(OPTS) Token.cpp

parser.o: parser.cpp parser.h
	g++ $(OPTS) parser.cpp

clean:
	rm -f *.o silc *~
