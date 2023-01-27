#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indices.h"
#include "propriedades.h"
#include "documentos.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct indices {

    Palavras* palavras_ind;
    Documentos* documentos_ind;

    long int palavras_usadas;
    long int palavras_alocadas;

    long int documentos_usados;
    long int documentos_alocados;
};

// ----------------------------------------------------------------------------------------------

Indices Indices_cria (){

    Indices indice = (Indices)calloc(1, sizeof(struct indices));

    indice->palavras_ind = Palavras_vetor_cria();
    indice->documentos_ind = Documentos_vetor_cria();

    indice->palavras_alocadas = QTD_INICIAL;
    indice->documentos_alocados = QTD_INICIAL;

    return indice;
}


Indices Le_Arquivo_Principal(Indices ind, int argc, char** argv) {
    
    if (argc <= 1) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m O diretorio de arquivos de configuracao nao foi informado.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");
        exit(0);
    }

    else if (argc == 2) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m O nome do arquivo de saida nao foi informado.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");

        exit(0);
    }
    
    else if (argc > 3) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m O numero de entradas excedeu seu limite.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");

        exit(0);
    }
    
    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m Nao foi possivel abrir o arquivo pelo caminho '%s'\n", argv[1]);
        exit(0);
    }

    while(!feof(file)) {

        char caminho[50];
        char classe[4];

        fscanf(file, "%[^ ] ", caminho);
        fscanf(file, "%[^\n]\n", classe);

        //Indexador de documentos:
            Documentos_realoca(ind);
            ind->documentos_ind[ind->documentos_usados] = Documentos_cria (caminho, classe);

            //Indexador de palavras:
            ind = Le_Subarquivo(ind, argv, caminho, classe, ind->documentos_usados);
            
            ind = Le_Subarquivo(ind, argv, caminho, classe, ind->documentos_usados);
            ind->documentos_usados++;
    }

    //Palavras_imprime (ind->palavras_ind, ind->palavras_usadas);
    //Documentos_imprime (ind->documentos_usados, ind->documentos_ind);

    fclose(file);

    return ind;
}


Indices Le_Subarquivo(Indices indices, char** argv, char* caminho, char* classe, int ind) {
    

    //modificando caminho
    char caminho_completo[1000];
    strcpy(caminho_completo, argv[1]);
    int tam_caminho = strlen(caminho_completo);

    for (int i = tam_caminho; i >= 0; i--) {
        if (caminho_completo[i] == '/') {
            sprintf(caminho_completo, "%s%s", caminho_completo, caminho);
            break;
        }
        caminho_completo[i] = '\0';
    }

    FILE* file = fopen(caminho_completo, "r");

    //printf("\n\n%s\n\n", caminho_completo);
    

    if (file == NULL) {
        printf("\033[91mNao foi possivel abrir o arquivo de conteudo pelo caminho '%s'\n\033[0m", caminho_completo);
        exit(0);
    }

    while(!feof(file)) {
        
        //Indexador de palavras:
        Palavras_realoca (indices);

        int palavra_nova = Palavra_le (indices->palavras_ind, file, ind, indices->palavras_usadas);
        if (palavra_nova)
            indices->palavras_usadas++;    
    }
    
    //Palavras_imprime (indices->palavras_ind, indices->palavras_usadas);
    fclose(file);

    return indices;
}


void Palavras_realoca (Indices indices){
    if (indices->palavras_usadas == indices->palavras_alocadas){
        indices->palavras_alocadas*=2;
        indices->palavras_ind = (Palavras*)realloc(indices->palavras_ind, indices->palavras_alocadas* sizeof(Palavras));
    }
}

void Documentos_realoca (Indices indices){
    if (indices->documentos_usados == indices->documentos_alocados){
        indices->documentos_alocados*=2;
        indices->documentos_ind = (Documentos*)realloc(indices->documentos_ind, indices->documentos_alocados* sizeof(Documentos));
    }
}

void Indices_Libera(Indices ind) {

    for (int i = 0; i < ind->documentos_usados; i++) {
        Documentos_Libera(ind->documentos_ind[i]);
    }

    for (int i = 0; i < ind->palavras_usadas; i++) {
        Palavras_Libera(ind->palavras_ind[i]);
    }

    free(ind->documentos_ind);
    free(ind->palavras_ind);
    free(ind);
}

void Documentos_Indexador(Indices ind) {

    //printf ("qtd: %d\n", ind->palavras_usadas);


    for (int i = 0; i < ind->palavras_usadas; i++) {

        // pega o indice do doc e a frequencia de cada palavra
        
        int prop_usado = Palavras_Retorna_Prop_Usado(ind->palavras_ind[i]); //qtd de docs q a palavra se encontra
        int ind_doc;
        int freq_pal;

        double idf = Calcula_IDF(ind->documentos_usados, ind->palavras_ind[i]);
        
        for (int j = 0; j < prop_usado; j++) {
            ind->palavras_ind[i] = Calcula_TF_IDF(idf, ind->palavras_ind[i], j);

            ind_doc = Palavras_Retorna_Ind(ind->palavras_ind[i], j);
            freq_pal = Palavras_Retorna_Freq(ind->palavras_ind[i], j);        
            ind->documentos_ind[ind_doc] = Documentos_Atribui(ind->documentos_ind[ind_doc], i, freq_pal);

        }
    }

    ind->palavras_ind = Palavras_Ordena(ind->palavras_ind, ind->palavras_usadas);
}

void Imprime_Tudo(Indices indices) {
    Palavras_imprime (indices->palavras_ind, indices->palavras_usadas);
    //Documentos_imprime(indices->documentos_usados, indices->documentos_ind);
    //Palavras_imprime_uma(indices->palavras_ind, 3);
}

void Imprime_Binario(Indices indices, char** argv) {
    FILE* file = fopen(argv[2], "wb");
    
    if (file == NULL) {
        printf("\033[91mNao foi possivel criar o arquivo de conteudo binario pelo caminho '%s'\n\033[0m", argv[2]);
        exit(0);
    }
    
    long int qtd_pal = indices->palavras_usadas;
    printf("\npalavras_usadas: %ld\n", qtd_pal);

    fwrite(&qtd_pal, sizeof(long int), 1, file);

    fclose(file);

    // grava o tamanho do indice de palavras
    // for : acessa cada posicao
    // grava todas as coisas que nao sao vetor
    // para o que for um vetor
    // grava o tamanho
    // grava cada elemento

    //se for gravar string, anota o tam da string e dps ela

    /*
    fwrite(string, sizeof(char), tamanho, file);
    
    for (int i = 0; i < indices->palavras_usadas; i++) {
        fwrite(indices->palavras_ind[i], sizeof(Palavras), indices->palavras_usadas, file); //imprime as palavras
    }
    fwrite(indices->palavras_ind, sizeof(Palavras), indices->palavras_usadas, file); //imprime as palavras

    fwrite(indices->documentos_ind, sizeof(Documentos), indices->documentos_usados, file); //imrprime os documentos
    */
}


//mostrar como fizemos
//é necessario ordenar com qsort?
//perguntar do binario
//perguntar biblioteca