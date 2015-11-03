OBJ= testhash.o hashTable.o link.o hash.o
OPTS= -g -c -Wall -Werror

testhash: $(OBJ)
	g++ -o testhash $(OBJ)

testhash.o: testhash.cc hash.h hashTable.h link.h
	g++ $(OPTS) testhash.cc

hashTable.o: hashTable.cc hashTable.h link.h hash.h
	g++ $(OPTS) hashTable.cc

hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc

clean:
	rm -f *.o testhash *~
