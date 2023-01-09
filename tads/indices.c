#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indices.h"
#include "documentos.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct indices {

    Palavras* palavras_ind;
    Documentos* documentos_ind;

    int palavras_usadas;
    int palavras_alocadas;
    int documentos_usados;
    int documentos_alocados;
};

// ----------------------------------------------------------------------------------------------

Indices Indices_cria (){

    Indices indice = (Indices)calloc(1, sizeof(struct indices));

    indice->palavras_ind = Palavras_vetor_cria ();
    indice->documentos_ind = Documentos_vetor_cria();

    indice->palavras_alocadas = QTD_INICIAL;
    indice->documentos_alocados = QTD_INICIAL;

    return indice;
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
        
        Le_Conteudo(caminho, classe);
        
        i++;

    }

    printf ("\n\n\nQTD: %d\n\n\n", i);
    fclose(file);
}


void Le_Conteudo(char* caminho, char* classe) {

    Indices indices = Indices_cria ();
    
    char caminho_completo[QTD_INICIAL];
    sprintf (caminho_completo, "datasets/tiny/%s", caminho);
    FILE* file = fopen(caminho_completo, "r");
    

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de conteudo pelo caminho '%s'\n", caminho_completo);
        exit(0);
    }

    while(!feof(file)) {

        Palavras_realoca (indices);
        indices->palavras_ind[indices->palavras_usadas] = Palavra_cria ();
        indices->palavras_ind[indices->palavras_usadas] = Palavra_le (indices->palavras_ind[indices->palavras_usadas], file);
        indices->palavras_usadas++;
    }

    //Palavras_imprime (indices->palavras_ind, indices->palavras_usadas);

}


void Palavras_realoca (Indices indices){
    if (indices->palavras_usadas == indices->palavras_alocadas){
        indices->palavras_alocadas*=2;
        indices->palavras_ind = (Palavras*)realloc(indices->palavras_ind, indices->palavras_alocadas* sizeof(Palavras));
    }
}

void Documentos_realoca (Indices indices){
    if (indices->documentos_usados == indices->documentos_usados){
        indices->documentos_alocados*=2;
        indices->documentos_ind = (Documentos*)realloc(indices->documentos_ind, indices->documentos_alocados* sizeof(Documentos));
    }
}