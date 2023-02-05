#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct propriedades* Propriedades;

// ---------------- MEMORIA ----------------
Propriedades* Propriedades_vetor_cria();
Propriedades Propriedades_cria (int ind);
Propriedades Documentos_Propriedade_Cria();
Propriedades* Propriedades_Vet_Cria(int qtd);

void Propriedades_Libera(Propriedades* p, int qtd);


// ---------------- INDEXADORES ----------------
Propriedades Atribui_TF_IDF(double idf, Propriedades prop);
void Propriedade_Atualiza_Freq (Propriedades* p, int indice);
Propriedades Atribui_Auxiliar(Propriedades destino, Propriedades origem);
Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_pal, int freq_pal, double tf_idf_pal);


// ---------------- BINARIO ----------------
void Propriedades_Le_Binario(FILE* file, Propriedades* prop, int qtd_prop);
void Propriedades_Escreve_Binario(FILE* file, Propriedades* prop, int qtd_prop);

// ---------------- FUNCIONALIDADES (menu) ----------------

Propriedades TF_IDF_Classif (Propriedades p, double tf_idf);
void Ordena_Classes (int* frequencias, char** classes_usadas, int qtd_classes);
void Ordena_tf_idf(int *ind_docs, double *tf_idf, int tam, char nomes_docs[][100]);
double Calcula_Cosseno (Propriedades* prop_ref, Propriedades* prop, int qtd_ref, int qtd_prop);

// ---------------- AUXILIARES ----------------
int Ind_compara (const void *a, const void *b);
int Ind_Crescente(const void *a, const void *b);
int Crescente_freq(const void *a, const void *b);
int Decrescente_freq(const void *a, const void *b);
int Prop_Ind_compara (const void *a, const void *b);
int Decrescente_double(const void *a, const void *b);
void Propriedades_Imprime (Propriedades* p, int qtd);
int Compara_prop (const void *str1, const void *str2);
int Propriedades_Retorna_Ind(Propriedades* p, int ind);
void Propriedades_Ordena (Propriedades* prop, int qtd);
int Propriedades_Retorna_Freq(Propriedades* p, int ind);
double Propriedades_Retorna_tf_idf(Propriedades* p, int ind);
void Propriedades_Documentos_Imprime(Propriedades* p, int qtd);
int Propriedades_busca (Propriedades* p, int ind, int qtd_prop);
Propriedades Propriedades_Copia (Propriedades origem, Propriedades destino);
