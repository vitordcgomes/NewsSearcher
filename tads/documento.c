#include "documento.h"
#include "propriedades.h"
#include "palavras.h"

struct documento {
    char nome[101];
    char classe[4];
    Propriedades p;
};
