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

Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal) {

    if(doc->prop_usado == doc->prop_alocado) 
        Documentos_Propriedades_Realoca(doc);
    
    doc->prop[doc->prop_usado] = Documentos_Propriedade_Cria();
    doc->prop[doc->prop_usado] = Propriedades_Doc_Atribui(doc->prop[doc->prop_usado], doc->prop_usado, ind_pal, freq_pal, tf_idf_pal);
    doc->prop_usado++;
    
    //Propriedades_Documentos_Imprime (doc->prop, doc->prop_usado);
 
    return doc;
}

void Documentos_Escreve_Binario(FILE* file, Documentos* doc, int qtd_doc) {
    for (int i = 0; i < qtd_doc; i++) {
        int tam_nome = strlen(doc[i]->nome) + 1; // +1 para incluir o '\0' da string

        fwrite(&tam_nome, sizeof(int), 1, file);
        fwrite(doc[i]->nome, tam_nome, 1, file);
        fwrite(doc[i]->classe, 4, 1, file);

        fwrite(&doc[i]->prop_usado, sizeof(int), 1, file);

        Propriedades_Documentos_Escreve_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}


/******************ARQ2***********************/

void Documentos_Le_Binario(FILE* file, Documentos* doc, int qtd_doc) {
    for (int i = 0; i < qtd_doc; i++) {

        int tam_string_doc = 0;
        fread(&tam_string_doc, sizeof(int), 1, file);

        //vet_nomes_doc[i] = (char*)malloc(tam_string_doc);
        
        char nome[tam_string_doc];
        fread(nome, tam_string_doc, 1, file);
        

        //vet_classe_doc[i] = (char*)malloc(4); //tamanho da string classe eh fixo e == 4

        char classe[4];
        fread(classe, 4, 1, file);

        doc[i] = Documentos_cria(nome, classe);

        //printf("nome_doc: %s; ", doc[i]->nome);
        //printf("classe: %s;\n", doc[i]->classe);

        fread(&doc[i]->prop_usado, sizeof(int), 1, file);

        doc[i]->prop = (Propriedades*)realloc(doc[i]->prop, doc[i]->prop_usado* sizeof(Propriedades));

        Propriedades_Documentos_Le_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}
