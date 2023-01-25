#include <stdio.h>
#include <stdlib.h>
#include "tads/indices.h"

// ler as infos de um arquivo .txt e salva-las em um arquivo .bin;
// no final do documento, calcular o tf-idf;

int main(int argc, char** argv) {

    Indices ind = Indices_cria();
    ind = Le_Arquivo_Principal(ind, argc, argv); //aqui esta o indexador de palavras e a estruturacao do indice de documentos
    Documentos_Indexador(ind); //aqui preenchemos o indice de documentos criado na funcao anterior
    //Imprime_Binario();
    Imprime_Tudo(ind);
    Indices_Libera(ind);

    return 0;
}


