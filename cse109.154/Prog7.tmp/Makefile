OBJ= testhash.o hashTable.o link.o hash.o
OPTS= -g -c -Wall -Werror

testhash: $(OBJ)
	g++ -o testhash $(OBJ)

testhash.o: testhash.cpp hash.h hashTable.h link.h
	g++ $(OPTS) testhash.cpp

hashTable.o: hashTable.cpp hashTable.h link.h hash.h
	g++ $(OPTS) hashTable.cpp

hash.o: hash.h hash.cpp
	g++ $(OPTS) hash.cpp

link.o: link.cpp link.h
	g++ $(OPTS) link.cpp

clean:
	rm -f *.o testhash *~
