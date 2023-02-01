#include "propriedades.h"
#define QTD_INICIAL 100

struct propriedades {
    int frequencia;
    int indice;
    double tf_idf;
};

// ---------------- MEMORIA ----------------

Propriedades* Propriedades_vetor_cria(){
    Propriedades* p = (Propriedades*)calloc(QTD_INICIAL, sizeof(Propriedades));
    return p;
}

Propriedades Propriedades_cria (int ind){

    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));
    p->frequencia = 1;
    p->indice = ind;
    p->tf_idf = 0;

 return p;
}

Propriedades Documentos_Propriedade_Cria() {
    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));

    return p;
}

void Propriedades_Libera(Propriedades* p, int qtd) {
    for (int i=0; i<qtd; i++){
        free(p[i]);
    }
    
    free(p);
}

// ---------------- INDEXADORES ----------------

Propriedades Atribui_TF_IDF(double idf, Propriedades prop) {

    prop->tf_idf = prop->frequencia * idf;

    //printf("tf-idf: %.2lf\n", prop->tf_idf);

    return prop;
}

void Propriedade_Atualiza_Freq (Propriedades* p, int indice){
    p[indice]->frequencia++;
}

Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_vet, int ind_pal, int freq_pal, double tf_idf_pal) {

    p->indice = ind_pal;
    p->frequencia = freq_pal;
    p->tf_idf = tf_idf_pal;

    return p;
}


// ---------------- BINARIO ----------------

void Propriedades_Escreve_Binario(FILE* file, Propriedades* prop, int qtd_prop) {

    for (int i = 0; i < qtd_prop; i++) {
        fwrite(&prop[i]->frequencia, sizeof(int), 1, file);

        fwrite(&prop[i]->indice, sizeof(int), 1, file);

        fwrite(&prop[i]->tf_idf, sizeof(double), 1, file);
    }
}

void Propriedades_Le_Binario(FILE* file, Propriedades* prop, int qtd_prop) {
    for (int i = 0; i < qtd_prop; i++) {

        prop[i] = Propriedades_cria(0);

        fread(&prop[i]->frequencia, sizeof(int), 1, file);
        //printf("\tfreq: %d; ", prop[i]->frequencia);

        fread(&prop[i]->indice, sizeof(int), 1, file);
        //printf("ind: %d; ", prop[i]->indice);

        fread(&prop[i]->tf_idf, sizeof(double), 1, file);
        //printf("tf-idf: %.2lf;\n", prop[i]->tf_idf);
    }

    //printf("\n\n");
}


// ---------------- AUXILIARES ----------------

void Propriedades_Imprime (Propriedades* p, int qtd){
    
    for (int i=0; i<qtd; i++){
        printf ("Doc: %d; Freq: %d; tf-idf: %.2lf;\n\t", p[i]->indice, p[i]->frequencia, p[i]->tf_idf);
    }
    
    printf ("\n\n");

 }

int Propriedades_Retorna_Ind(Propriedades* p, int ind) {
    return p[ind]->indice;
}

int Propriedades_Retorna_Freq(Propriedades* p, int ind) {
    return p[ind]->frequencia;
}

double Propriedades_Retorna_tf_idf(Propriedades* p, int ind) {
    return p[ind]->tf_idf;
}

 void Propriedades_Documentos_Imprime(Propriedades* p, int qtd) {

    for (int i = 0; i < qtd; i++) {
        printf("i: %d; ind_pal: %d; freq: %d\n",i, p[i]->indice, p[i]->frequencia);
    }
    
    printf("\n\n");
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