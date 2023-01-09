all: indexador.c tads/palavras.c tads/palavras.h tads/documento.c tads/documento.h tads/propriedades.c tads/propriedades.h
	gcc -c indexador.c
	gcc -c tads/palavras.c
	gcc -c tads/documento.c
	gcc -c tads/propriedades.c
	gcc -o indexador indexador.o palavras.o documento.o propriedades.o

run: 
	make
	./indexador datasets/tiny/test.txt tolete.bin 

clean:
	rm -f indexador *.o

valgrind:
	valgrind ./indexador datasets/tiny/test.txt tolete.bin