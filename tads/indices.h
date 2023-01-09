#pragma once

typedef struct indices* Indices;

Indices Indices_cria ();
void Le_Arquivo_Inicial(int argc, char** argv);
void Le_Conteudo(char* caminho, char* classe);
void Palavras_realoca (Indices indices);
void Documentos_realoca (Indices indices);