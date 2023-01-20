all: indexador.c tads/palavras.c tads/palavras.h tads/documentos.c tads/documentos.h tads/propriedades.c tads/propriedades.h tads/indices.c tads/indices.h
	gcc -c indexador.c
	gcc -c tads/palavras.c
	gcc -c tads/documentos.c
	gcc -c tads/propriedades.c
	gcc -c tads/indices.c
	gcc -o indexador indexador.o palavras.o documentos.o propriedades.o indices.o

run: 
	make
	./indexador datasets/tiny/test.txt tolete.bin 

clean:
	rm -f indexador *.o

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all ./indexador datasets/tiny/test.txt tolete.bin