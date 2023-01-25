#pragma once

typedef struct documentos* Documentos;

Documentos* Documentos_vetor_cria();
Documentos Documentos_cria (char* caminho, char* classe);
void Documentos_Libera(Documentos doc);
void Documentos_imprime(int qtd, Documentos* docs);
void Documentos_Propriedades_Realoca(Documentos doc);
Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal);
void Documentos_Atualiza(Documentos* doc, int ind);
