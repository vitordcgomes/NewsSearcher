#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct propriedades* Propriedades;

Propriedades* Propriedades_vetor_cria();
Propriedades Propriedades_cria (int ind);
void Propriedades_Libera(Propriedades* p, int qtd);
void Propriedade_Atualiza_Freq (Propriedades* p, int indice);
int Propriedades_busca (Propriedades* p, int ind, int qtd_prop);
void Propriedades_Imprime (Propriedades* p, int qtd);
int Propriedades_Retorna_Ind(Propriedades* p, int ind);
int Propriedades_Retorna_Freq(Propriedades* p, int ind);
Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_vet, int ind_pal, int freq_pal);
void Propriedades_Documentos_Imprime(Propriedades* p, int qtd);
Propriedades Documentos_Propriedade_Cria();
Propriedades Atribui_TF_IDF(double idf, Propriedades prop);
void Propriedades_Palavras_Escreve_Binario(FILE* file, Propriedades* prop, int qtd_prop);
void Propriedades_Documentos_Escreve_Binario(FILE* file, Propriedades* prop, int qtd_prop);
