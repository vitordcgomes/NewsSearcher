FLAGS = -c -Wall

COMPILED = compiled

LIBRARY = -I tarefas -L . -ltads -lm

all: libtads.a indexador principal
	
#make experimental

%.o: 
	mkdir $(COMPILED)
	gcc $(FLAGS) tads/palavras.c -o $(COMPILED)/palavras.o
	gcc $(FLAGS) tads/documentos.c -o $(COMPILED)/documentos.o
	gcc $(FLAGS) tads/propriedades.c -o $(COMPILED)/propriedades.o
	gcc $(FLAGS) tads/indices.c -o $(COMPILED)/indices.o

libtads.a: $(COMPILED)/palavras.o $(COMPILED)/documentos.o $(COMPILED)/propriedades.o $(COMPILED)/indices.o
	ar -crs libtads.a $(COMPILED)/palavras.o $(COMPILED)/documentos.o $(COMPILED)/propriedades.o $(COMPILED)/indices.o

indexador: indexador.c 
	gcc -o indexador indexador.c $(LIBRARY)

principal: principal.c 
	gcc -o principal principal.c $(LIBRARY)

experimental: experimental.c
	gcc -o experimental experimental.c $(LIBRARY)
	./experimentos
	
run: 
	make
	./indexador datasets/medium-small/test.txt binario.bin
	./principal binario.bin 42

clean:
	rm -f indexador principal
	rm libtads.a
	rm -rf $(COMPILED)
	rm binario.bin
	clear

valgrind:
	make
#	valgrind --leak-check=full --show-leak-kinds=all ./indexador datasets/medium-small/test.txt binario.bin
	valgrind --leak-check=full --show-leak-kinds=all ./principal binario.bin 10

gdb:
	make
	gdb ./indexador datasets/medium-small/test.txt binario.bin 
