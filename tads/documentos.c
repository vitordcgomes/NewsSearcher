#include "documentos.h"
#include "propriedades.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct documentos {
    char nome[101];
    char classe[4];
    
    Propriedades* prop;

    double* tf_idf;

    int qtd_palavras;
    int prop_alocado;
    int prop_usado;
};

Documentos* Documentos_vetor_cria(){

    Documentos* documento = (Documentos*)calloc(QTD_INICIAL, sizeof(Documentos));
    //tf_idf
    return documento;
}

 Documentos Documentos_cria (char* caminho, char* classe){

    Documentos doc = (Documentos)calloc(1, sizeof(struct documentos));

    strcpy(doc->classe, classe);
    strcpy(doc->nome, caminho); //precisa tirar o "test/"??

    doc->prop = Propriedades_vetor_cria();

    doc->prop_alocado = QTD_INICIAL;
    doc->prop_usado = 0;
    doc->qtd_palavras = 0;

    return doc;
 }

void Documentos_Libera(Documentos doc) {
    Propriedades_Libera(doc->prop, doc->prop_usado);
    free(doc);
}

void Documentos_imprime(int qtd, Documentos* docs){

    for (int i=0; i<qtd; i++){
        printf ("DOC: %d, NOME: %s, CLASSE: %s\n", i, docs[i]->nome, docs[i]->classe);
        Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
    }

    /*
    for (int i = 0; i < qtd; i++) {
        //Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
        //printf("prop_usado: %d", docs[i]->prop_usado);
    }
    */

    
}

void Documentos_Propriedades_Realoca(Documentos doc) {
    doc->prop_alocado*= 2;
    doc->prop = (Propriedades*)realloc(doc->prop, doc->prop_alocado* sizeof(Propriedades));
}

void Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal) {

    if(doc->prop_usado == doc->prop_alocado) {
        Documentos_Propriedades_Realoca(doc);
    }

    //printf("\nprop_usado: %d\nprop_alocado: %d\nqtd_palavras: %d\n\n", doc->prop_usado, doc->prop_alocado, doc->qtd_palavras);
    doc->prop[doc->prop_usado] = Documentos_Propriedade_Cria();

    //int i = 1;
    //printf("\n\nTESTE\n\n");
    doc->prop[doc->prop_usado] = Propriedades_Doc_Atribui(doc->prop[doc->prop_usado], doc->prop_usado, ind_pal, freq_pal);

    doc->prop_usado++;

    //return doc;
}

void Documentos_Atualiza(Documentos* doc, int ind) {
    doc[ind]->qtd_palavras++;

    //return doc;
}