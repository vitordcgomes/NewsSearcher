#pragma once

typedef struct indices* Indices;

Indices Indices_cria ();
Indices Le_Arquivo_Principal(Indices ind, int argc, char** argv);
Indices Le_Subarquivo(Indices indices, char** argv, char* caminho, char* classe, int ind);
void Palavras_realoca (Indices indices);
void Documentos_realoca (Indices indices);
void Indices_Libera(Indices ind);
void Documentos_Indexador(Indices ind);
void Imprime_Tudo(Indices indices);
void Imprime_Binario(Indices indices, char** argv);


Indices Le_Binario(Indices ind, char* caminho);
void Texto_Busca(Indices ind);