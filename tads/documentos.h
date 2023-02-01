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

// ---------------- BINARIO ----------------
void Documentos_Le_Binario(FILE* file, Documentos* doc, int qtd_doc);
void Documentos_Escreve_Binario(FILE* file, Documentos* doc, int qtd_doc);

// ---------------- AUXILIARES ----------------
void Documentos_imprime(int qtd, Documentos* docs);