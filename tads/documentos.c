#include "documentos.h"
#include "propriedades.h"
#include "palavras.h"

#define QTD_INICIAL 100

struct documentos {
    char nome[101];
    char classe[4];
    
    Propriedades* prop;

    int prop_alocado;
    int prop_usado;

    int qtd_palavras;
    double knn;
};

// ---------------- MEMORIA ----------------

Documentos* Documentos_vetor_cria(){

    Documentos* documento = (Documentos*)calloc(QTD_INICIAL, sizeof(Documentos));
    return documento;
}

void Documentos_Libera(Documentos doc) {
    Propriedades_Libera(doc->prop, doc->prop_usado);
    free(doc);
}

void Documentos_Propriedades_Realoca(Documentos doc) {
    doc->prop_alocado*= 2;
    doc->prop = (Propriedades*)realloc(doc->prop, doc->prop_alocado* sizeof(Propriedades));
}

 Documentos Documentos_cria (char* caminho, char* classe){

    Documentos doc = (Documentos)calloc(1, sizeof(struct documentos));

    strcpy(doc->classe, classe);
    strcpy(doc->nome, caminho);
    //printf("doc_nome: %s\n", doc->nome);

    doc->prop = Propriedades_vetor_cria();

    doc->prop_alocado = QTD_INICIAL;
    doc->prop_usado = 0;
    doc->qtd_palavras = 0;

    return doc;
 }


// ---------------- INDEXADORES ----------------

Documentos Documentos_Atribui(Documentos doc, int ind_pal, int freq_pal, double tf_idf_pal) {

    if(doc->prop_usado == doc->prop_alocado) 
        Documentos_Propriedades_Realoca(doc);
    
    doc->prop[doc->prop_usado] = Documentos_Propriedade_Cria();
    doc->prop[doc->prop_usado] = Propriedades_Doc_Atribui(doc->prop[doc->prop_usado], ind_pal, freq_pal, tf_idf_pal);
    doc->prop_usado++;

    //Propriedades_Documentos_Imprime (doc->prop, doc->prop_usado);
 
    return doc;
}

Documentos Documentos_Atualiza (Documentos d){
    d->qtd_palavras++;
    return d;
}


// ---------------- FUNCIONALIDADES (menu) ----------------

void Relat_Documentos_Imprime (Documentos* d, int qtd){

    int qtd_impressao = 10;
    Documentos* docs = (Documentos*)calloc(qtd, sizeof(Documentos));

    for (int i = 0; i<qtd; i++){
        docs[i] = (Documentos)calloc(1, sizeof(struct documentos));
        docs[i]->qtd_palavras = d[i]->qtd_palavras;
        strcpy(docs[i]->classe, d[i]->classe);
        strcpy(docs[i]->nome, d[i]->nome);
    }

    printf ("\n\n\n\033[1m========= RELATORIO DE DOCUMENTO =========\033[0m\n");
    printf ("\n\033[93mMaiores documentos (ordem decrescente):\033[0m\n\n");

    qsort(docs, qtd, sizeof(Documentos), Decrescente);
    Modelo_Impressao_Docs (docs, qtd_impressao, qtd);

    printf ("\n\n");
    printf ("\n\033[93mMenores documentos (ordem crescente):\033[0m\n\n");

    qsort(docs, qtd, sizeof(Documentos), Crescente);
    Modelo_Impressao_Docs (docs, qtd_impressao, qtd);

    for (int i = 0; i<qtd; i++){
        free (docs[i]);
    }
    free (docs);

}


// ---------------- BINARIO ----------------

void Documentos_Le_Binario(FILE* file, Documentos* doc, int qtd_doc) {
    for (int i = 0; i < qtd_doc; i++) {

        int tam_string_doc = 0;
        fread(&tam_string_doc, sizeof(int), 1, file);

        //vet_nomes_doc[i] = (char*)malloc(tam_string_doc);
        
        char nome[tam_string_doc];
        fread(nome, tam_string_doc, 1, file);
        

        //vet_classe_doc[i] = (char*)malloc(4); //tamanho da string classe eh fixo e == 4

        char classe[4];
        fread(classe, 4, 1, file);

        doc[i] = Documentos_cria(nome, classe);

        //printf("nome_doc: %s; ", doc[i]->nome);
        //printf("classe: %s;\n", doc[i]->classe);

        fread(&doc[i]->qtd_palavras, sizeof(int), 1, file);
        fread(&doc[i]->prop_usado, sizeof(int), 1, file);

        doc[i]->prop = (Propriedades*)realloc(doc[i]->prop, doc[i]->prop_usado* sizeof(Propriedades));

        Propriedades_Le_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}

void Documentos_Escreve_Binario(FILE* file, Documentos* doc, int qtd_doc) {
    for (int i = 0; i < qtd_doc; i++) {
        int tam_nome = strlen(doc[i]->nome) + 1; // +1 para incluir o '\0' da string

        fwrite(&tam_nome, sizeof(int), 1, file);
        fwrite(doc[i]->nome, tam_nome, 1, file);
        fwrite(doc[i]->classe, 4, 1, file);

        fwrite (&doc[i]->qtd_palavras, sizeof(int), 1, file);
        fwrite(&doc[i]->prop_usado, sizeof(int), 1, file);

        Propriedades_Escreve_Binario(file, doc[i]->prop, doc[i]->prop_usado);
    }
}


// ---------------- AUXILIARES ----------------

void Documentos_imprime(int qtd, Documentos* docs){

    for (int i=0; i<qtd; i++){
        printf ("DOC: %d, NOME: %s, CLASSE: %s\n", i, docs[i]->nome, docs[i]->classe);
        Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
    }

    /*
    for (int i = 0; i < qtd; i++) {
        Propriedades_Documentos_Imprime(docs[i]->prop, docs[i]->prop_usado);
    }
    */
}

int Crescente (const void *fst, const void *scnd){

    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    return (d1->qtd_palavras - d2->qtd_palavras);
}

int Decrescente (const void *fst, const void *scnd){
    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    return (d2->qtd_palavras - d1->qtd_palavras);
}

void Modelo_Impressao_Docs (Documentos* docs, int qtd_impressao, int qtd_docs){

    if (qtd_impressao > qtd_docs){
        qtd_impressao = qtd_docs;
    }

        for (int i=0; i<qtd_impressao; i++){
            printf ("  \033[96m[\033[0m%d\033[96m]\033[0m - %s, %d palavra(s), classe %s;\n\n", i+1, docs[i]->nome, docs[i]->qtd_palavras, docs[i]->classe);
        }

}

char* Retorna_Classe (Documentos d){
    return d->classe;
}

char* Documentos_Nome_Retorna (Documentos d){
    return d->nome;
}

int Documentos_Verifica_Existencia (char* str, Documentos* docs, int qtd_docs){

    //como o vetor se encontra DESORDENADO, pela ordem alfabetica, nao usaremos bsearch (especificacao diz busca em arquivos ORDENADOS devem ser por bsearch)

    for (int i=0; i<qtd_docs; i++){
        if (!strcmp (docs[i]->nome, str))
        return i;
    }

    return -1;
}


void Documentos_Classifica (char* str, Documentos* docs, int qtd_docs, int qtd_vizinhos, Documentos texto_digitado, int qtd_palavras, double* tf_idf){

    //calculamos tf-idf pelo vetor de palavras, entao nao eh possivel calcular da mesma maneira agora;

    //Propriedades_Imprime (texto_digitado->prop, qtd_palavras);
    for (int i=0; i<qtd_palavras; i++){
        texto_digitado->prop[i] = TF_IDF_Classif (texto_digitado->prop[i], tf_idf[i]);
    }
    
    for (int j=0; j<qtd_docs; j++){

        //retorna distancia entre o texto de referencia (ind_doc) e o texto aual (j)
        docs[j]->knn = Calcula_Cosseno (texto_digitado->prop, docs[j]->prop, qtd_palavras, docs[j]->prop_usado);
    }

    Ordena_KNN (docs, qtd_docs, str, qtd_vizinhos);

    //LIBERAR PROP E DOCS
}


void Ordena_KNN (Documentos* docs, int qtd_docs, char* str, int qtd_vizinhos){

    Documentos* cpy_docs = (Documentos*)calloc(qtd_docs, sizeof(Documentos));
    int cont = qtd_vizinhos;

    for (int i=0; i<qtd_docs; i++){
        cpy_docs[i] = (Documentos)calloc(1, sizeof(struct documentos));
        strcpy(cpy_docs[i]->nome, docs[i]->nome);
        strcpy(cpy_docs[i]->classe, docs[i]->classe);
        cpy_docs[i]->knn = docs[i]->knn;
    }

    qsort (cpy_docs, qtd_docs, sizeof(Documentos), Compara_KNN);

    if (qtd_docs < qtd_vizinhos){
        cont = qtd_docs;
    }

    printf("\n\033[93m  ->\033[0m Top 10 documentos mais proximos de '%s':\n\n", str);

    for (int i=0; i<cont; i++){
        printf("\t\033[96m[\033[0m%d\033[96m]\033[0m - '%s', com %.2lf de proximidade;\n\n", i + 1, cpy_docs[i]->nome, cpy_docs[i]->knn);
    }

    for (int i=0; i<qtd_docs; i++)
        free (cpy_docs[i]);
    
    free (cpy_docs);

}

int Compara_KNN (const void *fst, const void *scnd){
    Documentos d1 = *(Documentos *)fst;
    Documentos d2 = *(Documentos *)scnd;

    double diferenca = d2->knn - d1->knn;

    if (diferenca > 0) return 1;
    if (diferenca < 0) return -1;
    return 0;
}

Documentos Documentos_Classif_Constroi (char* str, int qtd_palavras, int* ind_palavras, int* frequencias){
    
    Documentos doc_aux = Documentos_cria (str, "classe");
    
    for (int j=0; j<qtd_palavras; j++){
            doc_aux->prop[j] = Documentos_Propriedade_Cria();
            Propriedades_Doc_Atribui(doc_aux->prop[j], ind_palavras[j], frequencias[j], 0.00);
            //printf ("indice palavra: %d, frequencia: %d;\n", ind_palavras[j], frequencias[j]);
        }
        
    doc_aux->prop_usado = qtd_palavras;
     
    return doc_aux;
}