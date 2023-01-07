all: indices.c tads/palavras.c tads/palavras.h tads/documento.c tads/documento.h tads/propriedades.c tads/propriedades.h
	gcc -c indices.c
	gcc -c tads/palavras.c
	gcc -c tads/documento.c
	gcc -c tads/propriedades.c
	gcc -o indices indices.o palavras.o documento.o propriedades.o

run: 
	make
	./indices datasets/tiny/test/1016102006poc.txt tolete.bin 

clean:
	rm -f indices *.o

valgrind:
	valgrind ./indices datasets/tiny/test/1016102006poc.txt tolete.bin