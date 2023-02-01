#pragma once

typedef struct indices* Indices;

// ---------------- MEMORIA ----------------
Indices Indices_cria ();
void Indices_Libera(Indices ind);
void Palavras_realoca (Indices indices);
void Documentos_realoca (Indices indices);

// ---------------- INDEXADORES ----------------
void Documentos_Indexador(Indices ind);
<<<<<<< HEAD
Indices Le_Arquivo_Principal(Indices ind, char** argv);
=======
Indices Le_Arquivo_Principal(Indices ind, int argc, char** argv);
>>>>>>> 0b64b0d95d2f50d6b205465321562490f5961c55
Indices Le_Subarquivo(Indices indices, char** argv, char* caminho, char* classe, int ind);

// ---------------- BINARIO ----------------
Indices Le_Binario(Indices ind, char* caminho);
void Imprime_Binario(Indices indices, char** argv);

// ---------------- FUNCIONALIDADES (menu) ----------------
void Texto_Busca(Indices ind);

// ---------------- AUXILIARES ----------------
void Imprime_Tudo(Indices indices);
