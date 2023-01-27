#include "documentos.h"
#include "propriedades.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct documentos {
    char nome[101];
    char classe[4];
    
    Propriedades* prop;

    int prop_alocado;
    int prop_usado;
};

Documentos* Documentos_vetor_cria(){

    Documentos* documento = (Documentos*)calloc(QTD_INICIAL, sizeof(Documentos));
    return documento;
}

 Documentos Documentos_cria (char* caminho, char* classe){

    Documentos doc = (Documentos)calloc(1, sizeof(struct documentos));

    strcpy(doc->classe, classe);
    strcpy(doc->nome, caminho); //precisa tirar o "test/"??

    doc->prop = Propriedades_vetor_cria();

    doc->prop_alocado = QTD_INICIAL;
    doc->prop_usado = 0;

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
        Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
    }
    */

    
}

void Documentos_Propriedades_Realoca(Documentos doc) {
    doc->prop_alocado*= 2;
    doc->prop = (Propriedades*)realloc(doc->prop, doc->prop_alocado* sizeof(Propriedades));
}

Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal) {

    if(doc->prop_usado == doc->prop_alocado) 
        Documentos_Propriedades_Realoca(doc);
    
    doc->prop[doc->prop_usado] = Documentos_Propriedade_Cria();
    doc->prop[doc->prop_usado] = Propriedades_Doc_Atribui(doc->prop[doc->prop_usado], doc->prop_usado, ind_pal, freq_pal);
    doc->prop_usado++;
    
    //Propriedades_Documentos_Imprime (doc->prop, doc->prop_usado);
 
    return doc;
}

int Documentos_Escreve_Binario(FILE* file, Documentos doc) {
    int tam_nome = strlen(doc->nome) + 1; // +1 para incluir o '\0' da string

    fwrite(&tam_nome, sizeof(int), 1, file);
    
    fwrite(&doc->nome, sizeof(char), tam_nome, file);
    fwrite(&doc->classe, sizeof(char), 4, file);

    fwrite(&doc->prop_usado, sizeof(int), 1, file);

    return doc->prop_usado;
}

void Documentos_Propriedades_Escreve_Binario(FILE* file, Documentos doc, int ind_prop) {
    Propriedades_Documentos_Escreve_Binario(file, doc->prop[ind_prop]);
}