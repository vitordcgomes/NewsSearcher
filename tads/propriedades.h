#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct propriedades* Propriedades;

Propriedades Propriedades_cria();
void Propriedades_Libera(Propriedades p);