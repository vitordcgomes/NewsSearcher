#include "palavras.h"
#include "propriedades.h"

#define QTD_INICIAL 100

struct palavras {
    char nome[101];
    Propriedades p;
    double tf_idf;
};


Palavras* Palavras_vetor_cria (){

    Palavras* palavra = (Palavras*)calloc(QTD_INICIAL, sizeof(Palavras));
    return palavra;
}


 Palavras Palavra_cria (){

    Palavras palavra = (Palavras)calloc(1, sizeof(struct palavras));
    palavra->p = Propriedades_cria();
    return palavra;
 }

 Palavras Palavra_le (Palavras p, FILE* f){

    fscanf(f, "%[^ ] ", p->nome);
    return p;
 }

 void Palavras_imprime (Palavras* p, int qtd){

    for (int i=0; i<qtd; i++){
        printf ("%s ", p[i]->nome);
    }
    
    printf ("\n\n");

 }