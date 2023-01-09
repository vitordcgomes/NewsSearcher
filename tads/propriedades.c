#include "propriedades.h"

struct propriedades {
    int frequencia;
    int indice;
};

Propriedades Propriedades_cria(){
    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));
    return p;
}
