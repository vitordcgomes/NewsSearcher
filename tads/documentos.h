#pragma once

typedef struct documentos* Documentos;

Documentos* Documentos_vetor_cria();
Documentos Documento_cria ();
void Documentos_Libera(Documentos doc);