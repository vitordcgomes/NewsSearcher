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

int Propriedades_busca (Propriedades p, int ind_doc, int qtd_prop){

    printf ("\n\nQTD PROP: %d\tIND: %d!", qtd_prop, ind_doc);

    //for (int i=0; i<qtd_prop; i++){
        //printf ("entrei!");
        printf ("\nindice: %d", p->indice);
        if (p->indice == ind_doc){
            //printf("I: %d\n", 1);
            return 1;
        }
    //}
    return 0;
}




Propriedades* Propriedade_Atualiza_Freq (Propriedades* p, int ind){
    
    p[ind]->frequencia++;
    return p;
}
