#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct documentos* Documentos;

Documentos* Documentos_vetor_cria();
Documentos Documentos_cria (char* caminho, char* classe);
void Documentos_Libera(Documentos doc);
void Documentos_imprime(int qtd, Documentos* docs);
void Documentos_Propriedades_Realoca(Documentos doc);
Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal);
void Documentos_Atualiza(Documentos* doc, int ind);
void Documentos_Escreve_Binario(FILE* file, Documentos* doc, int qtd_doc);

void Documentos_Le_Binario(FILE* file, Documentos* doc, int qtd_doc);
