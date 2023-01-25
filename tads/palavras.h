#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct palavras* Palavras;

Palavras* Palavras_vetor_cria ();
Palavras Palavra_cria ();
int Palavra_le (Palavras* pal, FILE* f, int ind, int qtd);
void Palavras_imprime (Palavras* p, int qtd);
void Palavras_imprime_uma (Palavras* p, int ind);
void Palavras_Libera(Palavras pal);
void Propriedades_realoca (Palavras p);
int Palavras_Retorna_Ind(Palavras p, int ind);
int Palavras_Retorna_Freq(Palavras p, int ind);
int Palavras_Retorna_Prop_Usado(Palavras p);
double Calcula_IDF(int tot_doc, Palavras pal);
Palavras Calcula_TF_IDF(double idf, Palavras pal, int ind_prop);


