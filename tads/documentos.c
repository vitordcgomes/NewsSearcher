#include "documentos.h"
#include "propriedades.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct documentos {
    char nome[101];
    char classe[4];
    Propriedades p;
    double* tf_idf;
    int qtd_palavras;
};

Documentos* Documentos_vetor_cria(){

    Documentos* documento = (Documentos*)calloc(QTD_INICIAL, sizeof(Documentos));
    //tf_idf
    return documento;
}

 Documentos Documento_cria (){

    Documentos documento = (Documentos)calloc(1, sizeof(struct documentos));
    documento->p = Propriedades_cria();
    return documento;
 }