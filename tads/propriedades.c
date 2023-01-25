#include "propriedades.h"
#define QTD_INICIAL 100

struct propriedades {
    int frequencia;
    int indice;
};

Propriedades* Propriedades_vetor_cria(){
    Propriedades* p = (Propriedades*)calloc(QTD_INICIAL, sizeof(Propriedades));
    return p;
}

Propriedades Propriedades_cria (int ind){

    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));
    p->frequencia = 1;
    p->indice = ind;

 return p;
}


void Propriedades_Libera(Propriedades* p, int qtd) {
    for (int i=0; i<qtd; i++){
        free(p[i]);
    }
    
    free(p);
}

void Propriedades_Imprime (Propriedades* p, int qtd){
    
    //if (qtd > 1){

    
    for (int i=0; i<qtd; i++){
        printf ("Doc: %d; Freq: %d\n\t", p[i]->indice, p[i]->frequencia);
    }
    
    printf ("\n\n");
    //}

 }

int Propriedades_busca (Propriedades* p, int ind_doc, int qtd_prop){


    for (int i=0; i<qtd_prop; i++){

        if (p[i]->indice == ind_doc){
            p[i]->frequencia++;
            return i;
        }
    }

    return -1;
}

void Propriedade_Atualiza_Freq (Propriedades* p, int indice){
    p[indice]->frequencia++;
}

int Propriedades_Retorna_Ind(Propriedades* p, int ind) {
    return p[ind]->indice;
}

int Propriedades_Retorna_Freq(Propriedades* p, int ind) {
    return p[ind]->frequencia;
}

Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_vet, int ind_pal, int freq_pal) {
    //p[ind_vet] = Propriedades_cria(ind_vet);
    
    p->indice = ind_pal;
    p->frequencia = freq_pal;

    //printf("ind: %d; freq: %d\n", p->indice, p->frequencia);

    return p;
}

void Propriedades_Documentos_Imprime(Propriedades* p, int qtd) {

    for (int i = 0; i < qtd; i++) {
        printf("ind_pal: %d; freq: %d\n", p[i]->indice, p[i]->frequencia);

    }
    
    printf("\n\n");
}

Propriedades Documentos_Propriedade_Cria() {
    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));

    return p;
}
