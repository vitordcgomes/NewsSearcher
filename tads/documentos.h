#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct documentos *Documentos;

// ---------------- MEMORIA ----------------
Documentos *Documentos_vetor_cria();
void Documentos_Libera(Documentos doc);
void Documentos_Propriedades_Realoca(Documentos doc);
Documentos Documentos_cria(char *caminho, char *classe);
Documentos Documentos_Classif_Constroi(char *str, int qtd_palavras, int *ind_palavras, int *frequencias);

// ---------------- INDEXADORES ----------------
Documentos Documentos_Atualiza(Documentos d);
Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal);

// ---------------- FUNCIONALIDADES (menu) ----------------
void Relat_Documentos_Imprime(Documentos *d, int qtd);
void Ordena_KNN(Documentos *docs, int qtd_docs, char *str, int qtd_vizinhos);
void Modelo_Impressao_Docs(Documentos *docs, int qtd_impressao, int qtd_docs);
void Documentos_Classifica(char *str, Documentos *docs, int qtd_docs, int qtd_vizinhos, Documentos texto_digitado, int qtd_palavras, double *vet_tf_idf);

// ---------------- BINARIO ----------------
void Documentos_Le_Binario(FILE *file, Documentos *doc, int qtd_doc);
void Documentos_Escreve_Binario(FILE *file, Documentos *doc, int qtd_doc);

// ---------------- AUXILIARES ----------------
char *Retorna_Classe(Documentos d);
char *Documentos_Nome_Retorna(Documentos d);
int Crescente(const void *fst, const void *scnd);
void Documentos_imprime(int qtd, Documentos *docs);
int Compara_KNN(const void *fst, const void *scnd);
int Decrescente(const void *fst, const void *scnd);
