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


void Propriedades_Libera(Propriedades p) {
    free(p);
}

void Propriedades_Imprime (Propriedades* p, int qtd){
    
    if (qtd > 1){

    
    for (int i=0; i<qtd; i++){
        printf ("Doc: %d; Freq: %d\n", p[i]->indice, p[i]->frequencia);
    }
    
    printf ("\n\n");
    }

 }

int Propriedades_busca (Propriedades* p, int ind_doc, int qtd_prop){

    //printf ("\n\nQTD PROP: %d\tIND: %d!", qtd_prop, ind_doc);

    for (int i=0; i<qtd_prop; i++){
        //printf ("entrei!");

        if (p[i]->indice == ind_doc){
            //printf ("\nindice doc: %d, indice vetor: %d\n", p[i]->indice, i);
            p[i]->frequencia++;
            //printf ("freq: %d\n", p[i]->frequencia);
            return i;
        }
    }

    return -1;
}

void Propriedade_Atualiza_Freq (Propriedades* p, int indice){
    p[indice]->frequencia++;
}
