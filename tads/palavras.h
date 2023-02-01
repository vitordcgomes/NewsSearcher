#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct palavras* Palavras;

// ---------------- MEMORIA ----------------
Palavras* Palavras_vetor_cria ();
Palavras Palavra_cria ();
void Propriedades_realoca (Palavras p);
void Palavras_Libera(Palavras pal);


// ---------------- INDEXADORES ----------------
int Palavra_le (Palavras* pal, FILE* f, int ind, int qtd);
double Calcula_IDF(int tot_doc, Palavras pal);
Palavras Calcula_TF_IDF(double idf, Palavras pal, int ind_prop);


// ---------------- BINARIO ----------------
void Palavras_Le_Binario(FILE* file, Palavras* pal, int qtd_pal);
void Palavras_Escreve_Binario(FILE* file, Palavras* pal, int qtd_pal);


// ---------------- AUXILIARES ----------------
int Palavras_Retorna_Prop_Usado(Palavras p);
void Palavras_imprime (Palavras* p, int qtd);
int Palavras_Retorna_Ind(Palavras p, int ind);
int Palavras_Retorna_Freq(Palavras p, int ind);
void Palavras_imprime_uma (Palavras* p, int ind);
Palavras* Palavras_Ordena(Palavras* pal, int qtd);
double Palavras_Retorna_tf_idf(Palavras p, int ind);
int String_Compara(const void *str1, const void *str2);
void Palavras_busca (Palavras* pal, int qtd, char* str);

