#pragma once

typedef struct indices *Indices;

// ---------------- MEMORIA ----------------
Indices Indices_cria();
void Indices_Libera(Indices ind);
void Palavras_realoca(Indices indices);
void Documentos_realoca(Indices indices);

// ---------------- INDEXADORES ----------------

void Documentos_Indexador(Indices ind);
Indices Le_Arquivo_Principal(Indices ind, char **argv);
Indices Le_Subarquivo(Indices indices, char **argv, char *caminho, char *classe, int ind);

// ---------------- BINARIO ----------------
Indices Le_Binario(Indices ind, char *caminho);
void Imprime_Binario(Indices indices, char **argv);

// ---------------- FUNCIONALIDADES (menu) ----------------
void Texto_Busca(Indices ind);
void Relatorio_Docs(Indices ind);
int Relatorio_Palavras(Indices ind);
void Texto_Classifica(Indices ind, int knn);

// ---------------- AUXILIARES ----------------
void Imprime_Tudo(Indices indices);
int Decrescente_Inteiro(const void *a, const void *b);
