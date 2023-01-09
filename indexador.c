#include <stdio.h>
#include <stdlib.h>

// ler as infos de um arquivo .txt e salva-las em um arquivo .bin



void Le_Arquivo_Inicial(int argc, char** argv);
void Le_Conteudo(char* caminho, char* classe);

int main(int argc, char** argv) {

    Le_Arquivo_Inicial(argc, argv);

    return 0;
}

void Le_Arquivo_Inicial(int argc, char** argv) {
    
    if (argc <= 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado.\n");
        // imprimir 'help' posteriormente
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

    int i = 0;
    while(!feof(file)) {
        char caminho[50];
        char classe[4];

        fscanf(file, "%[^ ] ", caminho);
        printf("\n%s\n", caminho);
        fscanf(file, "%[^\n]\n", classe);
        printf("\n%s\n", classe);
        //Le_Conteudo(caminho, classe);
        
        i++;

    }

    fclose(file);
}

/*
void Le_Conteudo(char* caminho, char* classe) {
    FILE* file;

    file = fopen(caminho, "r");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de conteudo pelo caminho '%s'\n", caminho);
        exit(0);
    }

    while(!feof(file)) {

    }

}
*/