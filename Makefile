all: 
	make indexador
	make principal
#make experimental

run: 
	make
	./indexador datasets/tiny/test.txt binario.bin
#	./principal caminho_binario K

clean:
	rm -f indexador principal *.o
	rm binario.bin
	clear

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all ./indexador datasets/tiny/test.txt binario.bin

gdb:
	make
	gdb ./indexador datasets/tiny/test.txt binario.bin 

indexador: indexador.c tads/palavras.c tads/palavras.h tads/documentos.c tads/documentos.h tads/propriedades.c tads/propriedades.h tads/indices.c tads/indices.h 
	gcc -c indexador.c
	gcc -c tads/palavras.c 
	gcc -c tads/documentos.c
	gcc -c tads/propriedades.c
	gcc -c tads/indices.c
	gcc -o indexador indexador.o palavras.o documentos.o propriedades.o indices.o -lm

#./indexador datasets/tiny/test.txt binario.bin

principal: principal.c
	gcc -c principal.c
	gcc -o principal principal.o

#./principal caminho_binario K

experimental:
	gcc -c algo.c
	gcc -o experimentos algo.o
	./experimentos