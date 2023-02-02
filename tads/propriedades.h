#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct propriedades* Propriedades;

// ---------------- MEMORIA ----------------
Propriedades* Propriedades_vetor_cria();
Propriedades* Propriedades_Vet_Cria(int qtd);
Propriedades Propriedades_cria (int ind);
Propriedades Documentos_Propriedade_Cria();
void Propriedades_Libera(Propriedades* p, int qtd);


// ---------------- INDEXADORES ----------------
Propriedades Atribui_TF_IDF(double idf, Propriedades prop);
void Propriedade_Atualiza_Freq (Propriedades* p, int indice);
Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_vet, int ind_pal, int freq_pal, double tf_idf_pal);
Propriedades Atribui_Auxiliar(Propriedades destino, Propriedades origem);


// ---------------- BINARIO ----------------
void Propriedades_Le_Binario(FILE* file, Propriedades* prop, int qtd_prop);
void Propriedades_Escreve_Binario(FILE* file, Propriedades* prop, int qtd_prop);

// ---------------- AUXILIARES ----------------
void Propriedades_Imprime (Propriedades* p, int qtd);
int Propriedades_Retorna_Ind(Propriedades* p, int ind);
int Propriedades_Retorna_Freq(Propriedades* p, int ind);
double Propriedades_Retorna_tf_idf(Propriedades* p, int ind);
void Propriedades_Documentos_Imprime(Propriedades* p, int qtd);
int Propriedades_busca (Propriedades* p, int ind, int qtd_prop);
void Propriedades_Ordena (Propriedades* prop, int qtd);
int Compara_prop (const void *str1, const void *str2);
void Verifica_classe (Propriedades* prop, int qtd);
