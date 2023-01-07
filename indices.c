#include <stdio.h>
#include <stdlib.h>

// ler as infos de um arquivo .txt e salva-las em um arquivo .bin



void Le_Arquivo_Inicial(int argc, char** argv);

int main(int argc, char** argv) {

    Le_Arquivo_Inicial(argc, argv);

    return 0;
}

void Le_Arquivo_Inicial(int argc, char** argv) {
    
    if (argc <= 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado.\n");
        exit(0);
    }

    
    else if (argc == 2) {
        printf("ERRO: O nome do arquivo de saida nao foi informado.\n");
        exit(0);
    }
    

    else if (argc > 3) {
        printf("ERRO: O numero de entradas excedeu o limite de 2 arquivos.\n");
        exit(0);
    }
    
    FILE *file;

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo pelo caminho '%s'\n", argv[1]);
        exit(0);
    }

    printf("\nsucesso!\n\n");


    //while(!feof(file)) {
        //fscanf(file, "%[^ ] ", var);
    //}

    fclose(file);
}