#include "propriedades.h"
#define QTD_INICIAL 100

struct propriedades
{
    int frequencia;
    int indice;
    double tf_idf;
};

// ---------------- MEMORIA ----------------

Propriedades *Propriedades_vetor_cria()
{
    Propriedades *p = (Propriedades *)calloc(QTD_INICIAL, sizeof(Propriedades));
    return p;
}

Propriedades *Propriedades_Vet_Cria(int qtd)
{
    Propriedades *p = (Propriedades *)calloc(qtd, sizeof(Propriedades));
    return p;
}

Propriedades Propriedades_cria(int ind)
{

    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));
    p->frequencia = 1;
    p->indice = ind;
    p->tf_idf = 0;

    return p;
}

Propriedades Documentos_Propriedade_Cria()
{
    Propriedades p = (Propriedades)calloc(1, sizeof(struct propriedades));

    return p;
}

void Propriedades_Libera(Propriedades *p, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        free(p[i]);
    }

    free(p);
}

// ---------------- INDEXADORES ----------------

Propriedades Atribui_TF_IDF(double idf, Propriedades prop)
{

    prop->tf_idf = prop->frequencia * idf;

    // printf("tf-idf: %.2lf\n", prop->tf_idf);

    return prop;
}

void Propriedade_Atualiza_Freq(Propriedades *p, int indice)
{
    p[indice]->frequencia++;
}

Propriedades Propriedades_Doc_Atribui(Propriedades p, int ind_vet, int ind_pal, int freq_pal, double tf_idf_pal)
{

    p->indice = ind_pal;
    p->frequencia = freq_pal;
    p->tf_idf = tf_idf_pal;

    return p;
}

Propriedades Atribui_Auxiliar(Propriedades destino, Propriedades origem)
{
    destino->indice = origem->indice;
    destino->frequencia = origem->frequencia;
    destino->tf_idf = origem->tf_idf;

    return destino;
}

// ---------------- BINARIO ----------------

void Propriedades_Escreve_Binario(FILE *file, Propriedades *prop, int qtd_prop)
{

    for (int i = 0; i < qtd_prop; i++)
    {
        fwrite(&prop[i]->frequencia, sizeof(int), 1, file);

        fwrite(&prop[i]->indice, sizeof(int), 1, file);

        fwrite(&prop[i]->tf_idf, sizeof(double), 1, file);
    }
}

void Propriedades_Le_Binario(FILE *file, Propriedades *prop, int qtd_prop)
{
    for (int i = 0; i < qtd_prop; i++)
    {

        prop[i] = Propriedades_cria(0);

        fread(&prop[i]->frequencia, sizeof(int), 1, file);
        // printf("\tfreq: %d; ", prop[i]->frequencia);

        fread(&prop[i]->indice, sizeof(int), 1, file);
        // printf("ind: %d; ", prop[i]->indice);

        fread(&prop[i]->tf_idf, sizeof(double), 1, file);
        // printf("tf-idf: %.2lf;\n", prop[i]->tf_idf);
    }

    // printf("\n\n");
}

// ---------------- FUNCIONALIDADES (menu) ----------------

/*int Busca_Indices_Docs(Propriedades* prop, int qtd, int* vet_docs, int tam_aloc, Propriedades* prop_aux){

    int qtd_docs = 0;

    for (int i = 0; i < qtd; i++) {

        for (int j = 0; j < qtd_docs; j++){
            if (prop[i]->indice == vet_docs[j]) {
                //soma tf_idf no prop_aux;
                break;
            }

            else {

                if (qtd_docs == tam_aloc){
                    tam_aloc *=2;
                    (int*)realloc(vet_docs, tam_aloc * sizeof(int));
                }
                vet_docs[qtd_docs] = prop[i]->indice;
                qtd_docs++;
            }
        }
    }


    return qtd_docs;
}
*/

void Ordena_tf_idf(int *ind_docs, double *tf_idf, int tam, char** nomes_docs)
{
    // RETORNAR DOCUMENTO

    Propriedades *prop = (Propriedades *)calloc(tam, sizeof(Propriedades));
    int qtd = 10;
    int indice = 0;

    for (int i = 0; i < tam; i++)
    {
        prop[i] = (Propriedades)calloc(1, sizeof(struct propriedades));
        prop[i]->tf_idf = tf_idf[i];
        prop[i]->indice = ind_docs[i];
    }

    qsort(prop, tam, sizeof(Propriedades), Decrescente_double);

    printf("\n\033[93m  ->\033[0m Top 10 documentos em que a(s) palavra(s) mais aparece(m):\n\n");

    if (tam < 10) qtd = tam;

    for (int i = 0; i < qtd; i++)
    {   
        //int* endereco = bsearch (&prop[i]->indice, ind_docs, tam, sizeof(int), Ind_compara);
        //int indice = endereco - ind_docs;

        for (int j=0; j < tam; j++){
            if (prop[i]->indice == ind_docs[j]) {
                indice = j;
                break;
            }

        }
        printf("\t\033[96m[\033[0m%d\033[96m]\033[0m - '%s'; ind: '%d'\n\n", i + 1, nomes_docs[indice], prop[i]->indice);
    }

    for (int i = 0; i < tam; i++)
    {
        free(prop[i]);
    }
    free(prop);
}

int Decrescente_double(const void *a, const void *b)
{
    Propriedades prop1 = *(Propriedades *)a;
    Propriedades prop2 = *(Propriedades *)b;
    return (int)(prop2->tf_idf - prop1->tf_idf);
}

// ---------------- AUXILIARES ----------------

void Propriedades_Imprime(Propriedades *p, int qtd)
{

    printf("\n");
    for (int i = 0; i < qtd; i++)
    {
        printf("\tDoc: %d; Freq: %d; tf-idf: %.2lf;\n", p[i]->indice, p[i]->frequencia, p[i]->tf_idf);
    }

    printf("\n\n");
}

int Compara_prop(const void *a, const void *b)
{

    Propriedades p1 = *(Propriedades *)a;
    Propriedades p2 = *(Propriedades *)b;

    return (p2->frequencia - p1->frequencia);
}

int Propriedades_Retorna_Ind(Propriedades *p, int ind)
{
    return p[ind]->indice;
}

void Propriedades_Ordena(Propriedades *prop, int qtd)
{

    int qtd_impressao = 10;

    qsort(prop, qtd, sizeof(Propriedades), Compara_prop);

    if (qtd_impressao > qtd)
    {
        qtd_impressao = qtd;
    }

    for (int i = 0; i < qtd_impressao; i++)
    {
        printf("\t\033[96m[\033[0m%d\033[96m]\033[0m - %d vez(es);\n\n", prop[i]->indice, prop[i]->frequencia);
    }
}

int Propriedades_Retorna_Freq(Propriedades *p, int ind)
{
    return p[ind]->frequencia;
}

double Propriedades_Retorna_tf_idf(Propriedades *p, int ind)
{
    return p[ind]->tf_idf;
}

void Propriedades_Documentos_Imprime(Propriedades *p, int qtd)
{

    for (int i = 0; i < qtd; i++)
    {
        printf("i: %d; ind_pal: %d; freq: %d\n", i, p[i]->indice, p[i]->frequencia);
    }

    printf("\n\n");
}

int Propriedades_busca(Propriedades *p, int ind_doc, int qtd_prop)
{

    for (int i = 0; i < qtd_prop; i++)
    {

        if (p[i]->indice == ind_doc)
        {
            p[i]->frequencia++;
            return i;
        }
    }

    return -1;
}

void Ordena_Classes(int *frequencias, char **classes_usadas, int qtd_classes)
{
    Propriedades *prop = (Propriedades *)calloc(qtd_classes, sizeof(Propriedades));

 for (int i = 0; i < qtd_classes; i++)
    {
        prop[i] = (Propriedades)calloc(1, sizeof(struct propriedades));
        prop[i]->frequencia = frequencias[i];
        prop[i]->indice = i;
    }

    qsort(prop, qtd_classes, sizeof(Propriedades), Decrescente_int);

    printf("\n\033[93m  ->\033[0m Frequencia por classe:\n\n");

    for (int i = 0; i < qtd_classes; i++)
    {
        printf("\t\033[96m[\033[0m%s\033[96m]\033[0m - Aparece %d vez(es);\n\n", classes_usadas[prop[i]->indice], prop[i]->frequencia);
    }

        for (int i = 0; i < qtd_classes; i++)
    {
        free(prop[i]);
    }
    free(prop);

}

int Decrescente_int(const void *a, const void *b)
{
    Propriedades x = *(Propriedades *)a;
    Propriedades y = *(Propriedades *)b;

    return (y->frequencia - x->frequencia);
}

int Ind_compara (const void *a, const void *b){
  int x = *(const int *)a;
  int y = *(const int *)b;

  if (x < y) return -1;
  if (x > y) return 1;
  return 0;
}