#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct propriedades* Propriedades;

Propriedades* Propriedades_vetor_cria();
Propriedades Propriedades_cria (int ind);
void Propriedades_Libera(Propriedades p);
Propriedades* Propriedade_Atualiza_Freq (Propriedades* p, int ind);
int Propriedades_busca (Propriedades p, int ind, int qtd_prop);
