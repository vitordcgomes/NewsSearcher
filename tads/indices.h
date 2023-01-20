#pragma once

typedef struct indices* Indices;

Indices Indices_cria ();
Indices Le_Arquivo_Inicial(Indices ind, int argc, char** argv);
Indices Le_Conteudo(Indices indices, char** argv, char* caminho, char* classe, int ind);
void Palavras_realoca (Indices indices);
void Documentos_realoca (Indices indices);
void Indices_Libera(Indices ind);