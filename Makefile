# Graham Arnold
# HW5
# 5/12/17 

# Makefile file to compile all dependencies into autocomplete executable 


all: autocomplete

autocomplete: main.o trie.o
	gcc  main.o trie.o -o autocomplete -Wall -std=c11 -g

trie.o: trie.c trie.h
	gcc  -c trie.c -o trie.o -Wall -std=c11 -g

main.o: trie.h main.c
	gcc  -c main.c -o main.o -Wall -std=c11 -g

clean:
	rm -f *.o autocomplete