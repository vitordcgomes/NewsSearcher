FLAGS = -c -Wall

all: 
	make indexador
	make principal
#make experimental

run: 
	make
	./indexador datasets/medium-small/test.txt binario.bin
	./principal binario.bin 42

clean:
	rm -f indexador principal *.o
	rm binario.bin
	clear

valgrind:
	make
#	valgrind --leak-check=full --show-leak-kinds=all ./indexador datasets/medium-small/test.txt binario.bin
	valgrind --leak-check=full --show-leak-kinds=all ./principal binario.bin 10

gdb:
	make
	gdb ./indexador datasets/medium-small/test.txt binario.bin 

indexador: indexador.c tads/palavras.c tads/palavras.h tads/documentos.c tads/documentos.h tads/propriedades.c tads/propriedades.h tads/indices.c tads/indices.h 
	gcc $(FLAGS) indexador.c
	gcc $(FLAGS) tads/palavras.c 
	gcc $(FLAGS) tads/documentos.c
	gcc $(FLAGS) tads/propriedades.c
	gcc $(FLAGS) tads/indices.c
	gcc -o indexador indexador.o palavras.o documentos.o propriedades.o indices.o -lm

#./indexador datasets/tiny/test.txt binario.bin

principal: principal.c
	gcc $(FLAGS) tads/palavras.c 
	gcc $(FLAGS) tads/documentos.c
	gcc $(FLAGS) tads/propriedades.c
	gcc $(FLAGS) tads/indices.c
	gcc $(FLAGS) principal.c
	gcc -o principal principal.o palavras.o documentos.o propriedades.o indices.o -lm

#./principal caminho_binario K

experimental:
	gcc -c algo.c
	gcc -o experimentos algo.o
	./experimentos