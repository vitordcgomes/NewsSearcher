#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct documentos* Documentos;


// ---------------- MEMORIA ----------------
Documentos* Documentos_vetor_cria();
void Documentos_Libera(Documentos doc);
void Documentos_Propriedades_Realoca(Documentos doc);
Documentos Documentos_cria (char* caminho, char* classe);

// ---------------- INDEXADORES ----------------
Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal);
Documentos Documentos_Atualiza (Documentos d);

// ---------------- FUNCIONALIDADES (menu) ----------------
void Relat_Documentos_Imprime (Documentos* d, int qtd);

// ---------------- BINARIO ----------------
void Documentos_Le_Binario(FILE* file, Documentos* doc, int qtd_doc);
void Documentos_Escreve_Binario(FILE* file, Documentos* doc, int qtd_doc);

// ---------------- AUXILIARES ----------------
void Documentos_imprime(int qtd, Documentos* docs);
int Crescente (const void *fst, const void *scnd);
int Decrescente (const void *fst, const void *scnd);
void Modelo_Impressao_Docs (Documentos* docs, int qtd_impressao, int qtd_docs);
char* Retorna_Classe (Documentos d);
char* Documentos_Nome_Retorna (Documentos d);
int Documentos_Verifica_Existencia (char* str, Documentos* docs, int qtd_docs);
void Documentos_Classifica (char* str, Documentos* docs, int qtd_docs, int qtd_vizinhos, Documentos texto_digitado, int qtd_palavras, double* tf_idf);
void Ordena_KNN (Documentos* docs, int qtd_docs, char* str, int qtd_vizinhos);
int Compara_KNN (const void *fst, const void *scnd);
Documentos Documentos_Classif_Constroi (char* str, int qtd_palavras, int* ind_palavras, int* frequencias);
