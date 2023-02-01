#include <stdio.h>
#include <stdlib.h>
#include "tads/indices.h"

// ler as infos de um arquivo .txt e salva-las em um arquivo .bin;
// no final do documento, calcular o tf-idf;
//liberar memoria dos indices em caso de erro
//perguntar biblioteca - [esquecemos :)]

void Erros_Entrada_Indexador(int argc);

int main(int argc, char** argv) {

    Erros_Entrada_Indexador(argc);
    Indices ind = Indices_cria();
    ind = Le_Arquivo_Principal(ind, argv); //aqui esta o indexador de palavras e a estruturacao do indice de documentos
    Documentos_Indexador(ind); //aqui preenchemos o indice de documentos criado na funcao anterior
    //Imprime_Tudo(ind);
    Imprime_Binario(ind, argv);
    Indices_Libera(ind);

    return 0;
}

// ---------------- FUNCOES LOCAIS ----------------

void Erros_Entrada_Indexador (int argc){

    if (argc <= 1) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m O diretorio de arquivos de configuracao nao foi informado.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");
        exit(0);
    }

    else if (argc == 2) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m Informacoes insuficientes.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");
        exit(0);
    }
    
    else if (argc > 3) {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m O numero de entradas excedeu seu limite.\n");
        printf ("Favor fornecer entrada do tipo:\n\n\t./\033[3mnome_do_executavel caminho_do_diretorio arquivo_de_saida\033[0m\n\n");
        exit(0);
    }
}


