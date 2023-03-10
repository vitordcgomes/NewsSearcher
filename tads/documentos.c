#include "documentos.h"
#include "propriedades.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct documentos
{
    char nome[101];
    char classe[4];

    Propriedades *prop;

    int prop_alocado;
    int prop_usado;

    int qtd_palavras;
    double knn;
};

// ---------------- MEMORIA ----------------

Documentos *Documentos_vetor_cria()
{

    Documentos *documento = (Documentos *)calloc(QTD_INICIAL, sizeof(Documentos));
    return documento;
}

void Documentos_Libera(Documentos doc)
{
    Propriedades_Libera(doc->prop, doc->prop_usado);
    free(doc);
}

void Documentos_Propriedades_Realoca(Documentos doc)
{
    doc->prop_alocado *= 2;
    doc->prop = (Propriedades *)realloc(doc->prop, doc->prop_alocado * sizeof(Propriedades));
}

Documentos Documentos_cria(char *caminho, char *classe)
{

    Documentos doc = (Documentos)calloc(1, sizeof(struct documentos));

    strcpy(doc->classe, classe);
    strcpy(doc->nome, caminho);

    doc->prop = Propriedades_vetor_cria();

    doc->prop_alocado = QTD_INICIAL;
    doc->prop_usado = 0;
    doc->qtd_palavras = 0;

    return doc;
}

Documentos Documentos_Classif_Constroi(char *str, int qtd_palavras, int *ind_palavras, int *frequencias)
{

    Documentos doc_aux = Documentos_cria(str, "classe");

    for (int j = 0; j < qtd_palavras; j++)
    {
        doc_aux->prop[j] = Documentos_Propriedade_Cria();
        Propriedades_Doc_Atribui(doc_aux->prop[j], ind_palavras[j], frequencias[j], 0.00);
    }

    doc_aux->prop_usado = qtd_palavras;

    qsort(doc_aux->prop, doc_aux->prop_usado, sizeof(Propriedades), Ind_Crescente);

    return doc_aux;
}

// ---------------- INDEXADORES ----------------

Documentos Documentos_Atualiza(Documentos d)
{
    d->qtd_palavras++;
    return d;
}

Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal)
{

    if (doc->prop_usado == doc->prop_alocado)
        Documentos_Propriedades_Realoca(doc);

    doc->prop[doc->prop_usado] = Documentos_Propriedade_Cria();
    doc->prop[doc->prop_usado] = Propriedades_Doc_Atribui(doc->prop[doc->prop_usado], ind_pal, freq_pal, tf_idf_pal);
    doc->prop_usado++;

    return doc;
}

// ---------------- FUNCIONALIDADES (menu) ----------------

void Relat_Documentos_Imprime(Documentos *d, int qtd)
{

    int qtd_impressao = 10;
    Documentos *docs = (Documentos *)calloc(qtd, sizeof(Documentos));

    for (int i = 0; i < qtd; i++)
    {
        docs[i] = (Documentos)calloc(1, sizeof(struct documentos));
        docs[i]->qtd_palavras = d[i]->qtd_palavras;
        strcpy(docs[i]->classe, d[i]->classe);
        strcpy(docs[i]->nome, d[i]->nome);
    }

    printf("\n\n\n\033[1m========= RELATORIO DE DOCUMENTO =========\033[0m\n");
    printf("\n\033[93mMaiores documentos (ordem decrescente):\033[0m\n\n");

    qsort(docs, qtd, sizeof(Documentos), Decrescente);
    Modelo_Impressao_Docs(docs, qtd_impressao, qtd);

    printf("\n\n");
    printf("\n\033[93mMenores documentos (ordem crescente):\033[0m\n\n");

    qsort(docs, qtd, sizeof(Documentos), Crescente);
    Modelo_Impressao_Docs(docs, qtd_impressao, qtd);

    for (int i = 0; i < qtd; i++)
    {
        free(docs[i]);
    }
    free(docs);
}

void Ordena_KNN(Documentos *docs, int qtd_docs, char *str, int qtd_vizinhos)
{

    Documentos *cpy_docs = (Documentos *)calloc(qtd_docs, sizeof(Documentos));
    char** classes_vizinhos = (char**)calloc(qtd_vizinhos, sizeof(char*));
    int* frequencias = (int*)calloc(qtd_vizinhos, sizeof(int));
    int classes_diff = 0;

    for (int i = 0; i < qtd_docs; i++)
    {
        cpy_docs[i] = (Documentos)calloc(1, sizeof(struct documentos));
        strcpy(cpy_docs[i]->nome, docs[i]->nome);
        strcpy(cpy_docs[i]->classe, docs[i]->classe);
        cpy_docs[i]->knn = docs[i]->knn;
    }

    qsort(cpy_docs, qtd_docs, sizeof(Documentos), Compara_KNN);

    for (int i=0; i<qtd_vizinhos; i++){

        char*classe = strdup(cpy_docs[i]->classe);
        int* endereco = (int*)bsearch (&classe, classes_vizinhos, classes_diff, sizeof(char*), String_Compara);

        if (endereco == NULL){
        classes_vizinhos[classes_diff] = strdup(cpy_docs[i]->classe);
        frequencias[classes_diff] = 1 ;
        classes_diff++;

        qsort(classes_vizinhos, classes_diff, sizeof(char*), String_Compara);
        }

        else {
            int indice = endereco - (int*)classes_vizinhos;
            frequencias[indice]++;
        }
       free (classe); 
    }

    int idx = 0;
    for (int i=0; i<classes_diff; i++){
        if (frequencias[idx] < frequencias[i])
            idx = i;
        printf ("classe : %s; freq: %d;\n", classes_vizinhos[i], frequencias[i]);
    }

    char resp;
    printf("Estima-se que a classe do texto digitado seja: \033[96m%s\033[0m! \nAcertamos? sim(s) ou nao(n):\033[95m ", classes_vizinhos[idx]);
    scanf("%c%*c", &resp);

    if (resp == 's')
        printf("\033[92m\nQue bom! Fico feliz em ajudar :)\033[0m\n\n");
    else if (resp == 'n')
        printf("\033[91m\nPoxa :( Espero conseguir te ajudar numa proxima oportunidade!\033[0m\n\n");

    for (int i = 0; i < qtd_docs; i++)
        free(cpy_docs[i]);

    for (int i = 0; i < classes_diff; i++)
        free (classes_vizinhos[i]);

    free (classes_vizinhos);
    free(frequencias);
    free(cpy_docs);
}

void Modelo_Impressao_Docs(Documentos *docs, int qtd_impressao, int qtd_docs)
{

    if (qtd_impressao > qtd_docs)
    {
        qtd_impressao = qtd_docs;
    }

    for (int i = 0; i < qtd_impressao; i++)
    {
        printf("  \033[96m[\033[0m%d\033[96m]\033[0m - %s, %d palavra(s), classe %s;\n\n", i + 1, docs[i]->nome, docs[i]->qtd_palavras, docs[i]->classe);
    }
}

void Documentos_Classifica(char *str, Documentos *docs, int qtd_docs, int qtd_vizinhos, Documentos texto_digitado, int qtd_palavras, double *vet_tf_idf)
{

    // Calculamos tf-idf pelo vetor de palavras, entao nao eh possivel calcular da mesma maneira agora;

    for (int i = 0; i < qtd_palavras; i++)
    {
        texto_digitado->prop[i] = TF_IDF_Classif(texto_digitado->prop[i], vet_tf_idf[i]);
    }

    for (int j = 0; j < qtd_docs; j++)
    {

        // retorna distancia entre o texto de referencia (ind_doc) e o texto atual (j)
        docs[j]->knn = Calcula_Cosseno(texto_digitado->prop, docs[j]->prop, qtd_palavras, docs[j]->prop_usado);
    }

    Ordena_KNN(docs, qtd_docs, str, qtd_vizinhos);
}

// ---------------- BINARIO ----------------

void Documentos_Le_Binario(FILE *file, Documentos *doc, int qtd_doc)
{
    for (int i = 0; i < qtd_doc; i++)
    {

        int tam_string_doc = 0;
        fread(&tam_string_doc, sizeof(int), 1, file);

        char nome[tam_string_doc];
        fread(nome, tam_string_doc, 1, file);

        char classe[4];
        fread(classe, 4, 1, file);

        doc[i] = Documentos_cria(nome, classe);

        fread(&doc[i]->qtd_palavras, sizeof(int), 1, file);
        fread(&doc[i]->prop_usado, sizeof(int), 1, file);

        doc[i]->prop = (Propriedades *)realloc(doc[i]->prop, doc[i]->prop_usado * sizeof(Propriedades));

        Propriedades_Le_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}

void Documentos_Escreve_Binario(FILE *file, Documentos *doc, int qtd_doc)
{
    for (int i = 0; i < qtd_doc; i++)
    {
        int tam_nome = strlen(doc[i]->nome) + 1; // +1 para incluir o '\0' da string

        fwrite(&tam_nome, sizeof(int), 1, file);
        fwrite(doc[i]->nome, tam_nome, 1, file);
        fwrite(doc[i]->classe, 4, 1, file);

        fwrite(&doc[i]->qtd_palavras, sizeof(int), 1, file);
        fwrite(&doc[i]->prop_usado, sizeof(int), 1, file);

        Propriedades_Escreve_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}

// ---------------- AUXILIARES ----------------

char *Retorna_Classe(Documentos d)
{
    return d->classe;
}

char *Documentos_Nome_Retorna(Documentos d)
{
    return d->nome;
}

int Crescente(const void *fst, const void *scnd)
{

    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    return (d1->qtd_palavras - d2->qtd_palavras);
}

void Documentos_imprime(int qtd, Documentos *docs)
{

    for (int i = 0; i < qtd; i++)
    {
        printf("DOC: %d, NOME: %s, CLASSE: %s\n", i, docs[i]->nome, docs[i]->classe);
        Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
    }
}

int Compara_KNN(const void *fst, const void *scnd)
{
    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    double diferenca = d2->knn - d1->knn;

    if (diferenca > 0)
        return 1;
    if (diferenca < 0)
        return -1;
    return 0;
}

int Decrescente(const void *fst, const void *scnd)
{
    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    return (d2->qtd_palavras - d1->qtd_palavras);
}
