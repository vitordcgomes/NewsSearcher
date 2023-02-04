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
int Palavra_le (Palavras* p, FILE* f, int ind, int qtd);
double Calcula_IDF(int tot_doc, Palavras p);
Palavras Calcula_TF_IDF(double idf, Palavras p, int ind_prop);


// ---------------- BINARIO ----------------
void Palavras_Le_Binario(FILE* file, Palavras* p, int qtd_palavras);
void Palavras_Escreve_Binario(FILE* file, Palavras* p, int qtd_palavras);

// ---------------- FUNCIONALIDADES (menu) ----------------
void Palavras_busca(Palavras *palavras, int qtd_palavras, char** nomes_docs);
int* Cria_Ind_Docs(Palavras *palavras, int qtd_palavras);
Palavras* Palavras_Retorna_Endereco(char* token, Palavras* palavras, int qtd_palavras);
int Relat_Palavras_Imprime (char* str, Palavras* p, int qtd_palavras);
Palavras* Palavras_Indices_Buscados(Palavras* pal, int* vet_ind, int tam_vet, int qtd_docs);

// ---------------- AUXILIARES ----------------
int Palavras_Retorna_Prop_Usado(Palavras p);
void Palavras_imprime (Palavras* p, int qtd);
Palavras* Palavras_Ordena(Palavras* p, int qtd);
void Palavras_imprime_uma (Palavras* p, int ind);
int Palavras_Retorna_Ind(Palavras p, int ind_doc);
int Palavras_Retorna_Freq(Palavras p, int ind_doc);
double Palavras_Retorna_tf_idf(Palavras p, int ind);
int Crescente_Inteiro(const void *a, const void *b);
int String_Compara(const void *str1, const void *str2);


