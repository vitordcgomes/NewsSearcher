#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indices.h"
#include "propriedades.h"
#include "documentos.h"
#include "palavras.h"

#define QTD_INICIAL 100
#define QTD_CLASSES 21

void Erros_Entrada(int argc, Indices ind);

struct indices
{

    Palavras *palavras_ind;
    Documentos *documentos_ind;

    long int palavras_usadas;
    long int palavras_alocadas;

    long int documentos_usados;
    long int documentos_alocados;
};

// ---------------- MEMORIA ----------------

Indices Indices_cria()
{

    Indices indice = (Indices)calloc(1, sizeof(struct indices));

    indice->palavras_ind = Palavras_vetor_cria();
    indice->documentos_ind = Documentos_vetor_cria();

    indice->palavras_alocadas = QTD_INICIAL;
    indice->documentos_alocados = QTD_INICIAL;

    return indice;
}

void Indices_Libera(Indices ind)
{

    for (int i = 0; i < ind->documentos_usados; i++)
    {
        Documentos_Libera(ind->documentos_ind[i]);
    }

    for (int i = 0; i < ind->palavras_usadas; i++)
    {
        Palavras_Libera(ind->palavras_ind[i]);
    }

    free(ind->documentos_ind);
    free(ind->palavras_ind);
    free(ind);
}

void Palavras_realoca(Indices indices)
{
    if (indices->palavras_usadas == indices->palavras_alocadas)
    {
        indices->palavras_alocadas *= 2;
        indices->palavras_ind = (Palavras *)realloc(indices->palavras_ind, indices->palavras_alocadas * sizeof(Palavras));
    }
}

void Documentos_realoca(Indices indices)
{
    if (indices->documentos_usados == indices->documentos_alocados)
    {
        indices->documentos_alocados *= 2;
        indices->documentos_ind = (Documentos *)realloc(indices->documentos_ind, indices->documentos_alocados * sizeof(Documentos));
    }
}

// ---------------- INDEXADORES ----------------

void Documentos_Indexador(Indices ind)
{

    for (int i = 0; i < ind->palavras_usadas; i++)
    {

        // pega o indice do doc e a frequencia de cada palavra

        int prop_usado = Palavras_Retorna_Prop_Usado(ind->palavras_ind[i]); // qtd de docs q a palavra se encontra
        int ind_doc;
        int freq_pal;
        double tf_idf_pal;

        double idf = Calcula_IDF(ind->documentos_usados, ind->palavras_ind[i]);

        for (int j = 0; j < prop_usado; j++)
        {
            ind->palavras_ind[i] = Calcula_TF_IDF(idf, ind->palavras_ind[i], j);

            ind_doc = Palavras_Retorna_Ind(ind->palavras_ind[i], j);
            freq_pal = Palavras_Retorna_Freq(ind->palavras_ind[i], j);
            tf_idf_pal = Palavras_Retorna_tf_idf(ind->palavras_ind[i], j);
            // printf("%.2lf\n", tf_idf_pal);

            ind->documentos_ind[ind_doc] = Documentos_Atribui(ind->documentos_ind[ind_doc], i, freq_pal, tf_idf_pal);
        }
    }

    ind->palavras_ind = Palavras_Ordena(ind->palavras_ind, ind->palavras_usadas);

    printf("\nINDEXADOR:\n");
    printf("\n\033[95mQuantidade de palavras distintas: \033[96m%ld\n", ind->palavras_usadas);
    printf("\033[95mQuantidade de documentos distintos: \033[96m%ld\n\n\033[0m", ind->documentos_usados);
}

Indices Le_Arquivo_Principal(Indices ind, char **argv)
{

    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("\033[91m\033[1m\nERRO:\033[0m\033[91m Nao foi possivel abrir o arquivo pelo caminho '%s'\n", argv[1]);
        Indices_Libera(ind);
        exit(0);
    }

    while (!feof(file))
    {

        char caminho[50];
        char classe[4];

        fscanf(file, "%[^ ] ", caminho);
        fscanf(file, "%[^\n]\n", classe);

        // Indexador de documentos:
        Documentos_realoca(ind);
        ind->documentos_ind[ind->documentos_usados] = Documentos_cria(caminho, classe);

        // Indexador de palavras:
        ind = Le_Subarquivo(ind, argv, caminho, classe, ind->documentos_usados);

        ind->documentos_usados++;
    }

    // Palavras_imprime (ind->palavras_ind, ind->palavras_usadas);
    // Documentos_imprime (ind->documentos_usados, ind->documentos_ind);

    fclose(file);

    return ind;
}

Indices Le_Subarquivo(Indices indices, char **argv, char *caminho, char *classe, int ind)
{

    char caminho_completo[1000];
    strcpy(caminho_completo, argv[1]);
    int tam_caminho = strlen(caminho_completo);

    // gerando caminho do subarquivo
    for (int i = tam_caminho; i >= 0; i--)
    {
        if (caminho_completo[i] == '/')
        {
            strcat(caminho_completo, caminho);
            break;
        }
        caminho_completo[i] = '\0';
    }

    FILE *file = fopen(caminho_completo, "r");

    if (file == NULL)
    {
        printf("\033[91mERRO: Nao foi possivel abrir o arquivo de conteudo pelo caminho '%s'\n\033[0m", caminho_completo);
        Indices_Libera(indices);
        exit(0);
    }

    while (!feof(file))
    {

        // Indexador de palavras:
        Palavras_realoca(indices);

        int palavra_nova = Palavra_le(indices->palavras_ind, file, ind, indices->palavras_usadas);
        if (palavra_nova)
            indices->palavras_usadas++;

        indices->documentos_ind[ind] = Documentos_Atualiza(indices->documentos_ind[ind]);
    }

    // Palavras_imprime (indices->palavras_ind, indices->palavras_usadas);
    fclose(file);

    return indices;
}

// ---------------- BINARIO ----------------

Indices Le_Binario(Indices ind, char *caminho)
{

    FILE *file = fopen(caminho, "rb");

    if (file == NULL)
    {
        printf("\033[91mERRO: Nao foi possivel abrir o arquivo de conteudo binario pelo caminho '%s'\n\033[0m", caminho);
        Indices_Libera(ind);
        exit(0);
    }

    // leitura de palavras
    fread(&ind->palavras_usadas, sizeof(long int), 1, file);
    // printf ("qtd_pal: %ld\n", ind->palavras_usadas);

    ind->palavras_ind = (Palavras *)realloc(ind->palavras_ind, ind->palavras_usadas * sizeof(Palavras));

    Palavras_Le_Binario(file, ind->palavras_ind, ind->palavras_usadas);

    // leitura documentos
    fread(&ind->documentos_usados, sizeof(long int), 1, file);
    // printf ("quantidade de documentos distintos: %ld\n", ind->documentos_usados);

    ind->documentos_ind = (Documentos *)realloc(ind->documentos_ind, ind->documentos_usados * sizeof(Documentos));

    Documentos_Le_Binario(file, ind->documentos_ind, ind->documentos_usados);

    printf("\nPRINCIPAL:\n");
    printf("\n\033[95mQuantidade de palavras distintas: \033[96m%ld\n", ind->palavras_usadas);
    printf("\033[95mQuantidade de documentos distintos: \033[96m%ld\n\n\033[0m", ind->documentos_usados);

    fclose(file);

    return ind;
}

void Imprime_Binario(Indices indices, char **argv)
{
    FILE *file = fopen(argv[2], "wb");

    if (file == NULL)
    {
        printf("\033[91mNao foi possivel criar o arquivo de conteudo binario pelo caminho '%s'\n\033[0m", argv[2]);
        exit(0);
    }

    long int qtd_pal = indices->palavras_usadas;
    // printf("\npalavras_usadas: %ld\n", qtd_pal);

    fwrite(&qtd_pal, sizeof(long int), 1, file);
    Palavras_Escreve_Binario(file, indices->palavras_ind, qtd_pal);

    long int qtd_doc = indices->documentos_usados;
    // printf("\nqtd_doc_antes: %ld", qtd_doc);

    fwrite(&qtd_doc, sizeof(long int), 1, file);
    Documentos_Escreve_Binario(file, indices->documentos_ind, qtd_doc);

    fclose(file);
}

// ---------------- FUNCIONALIDADES (menu) ----------------

void Texto_Busca(Indices ind)
{

    char str[1000];

    printf("Digite o que deseja buscar: \033[96m");
    scanf("%[^\n]%*c", str);
    printf("\n\033[0m");

    int cont_palavras = 0;
    int *vet_ind = (int *)calloc(1, sizeof(int));
    const char separador[] = " ";
    char *token;

    // retira o primeiro 'token'
    token = strtok(str, separador);
    int aux = 0;

    while (token != NULL)
    {
        void *endereco = Palavras_Retorna_Endereco(token, ind->palavras_ind, ind->palavras_usadas);

        if ((Palavras *)endereco != NULL)
        {
            cont_palavras += 1;
            vet_ind = (int *)realloc(vet_ind, (cont_palavras + 1) * sizeof(int));
            int indice = (Palavras *)endereco - ind->palavras_ind;

            vet_ind[aux] = indice;
            aux++;

            printf("Palavra '%s' encontrada no indice %d.\n", token, indice);
            // acessar o indice de cada palavras para calcular os atributos
        }

        else
        {
            printf("Palavra '%s' nao encontrada.\n", token);
        }

        // free(busca);
        token = strtok(NULL, separador);
    }

    qsort(vet_ind, cont_palavras, sizeof(int), Crescente_Inteiro); // ordena vet_ind em ordem crescente

    Indices ind_aux = (Indices)calloc(1, sizeof(struct indices));

    ind_aux->palavras_ind = Palavras_Indices_Buscados(ind->palavras_ind, vet_ind, cont_palavras, ind->documentos_usados);
    ind_aux->palavras_usadas = cont_palavras;

    
    printf("\ncont_pal = %d", cont_palavras);
    printf("\nind: ");
    for (int i = 0; i < cont_palavras; i++)
    {
        printf("%d ", vet_ind[i]);
    }
    printf("\n");

    for(int i = 0; i < cont_palavras; i++) {
        printf("Palavra de indice '%d' aparece nos seguinte documentos:\n", vet_ind[i]);
        Palavras_imprime_uma(ind_aux->palavras_ind, i);
    }
    
    //Palavras_imprime (ind_aux->palavras_ind, ind_aux->palavras_usadas);

    free(vet_ind);

    for (int i = 0; i < ind_aux->palavras_usadas; i++)
    {
        Palavras_Libera(ind_aux->palavras_ind[i]);
    }
    free(ind_aux->palavras_ind);
    free(ind_aux);
}

void Relatorio_Docs(Indices ind)
{
    Relat_Documentos_Imprime(ind->documentos_ind, ind->documentos_usados);
}

int Relatorio_Palavras(Indices ind)
{

    char *classe;
    int qtd_classes = 0;

    char **classes_usadas = (char **)calloc(QTD_CLASSES, sizeof(char *));
    int frequencias[QTD_CLASSES];

    char str[100];

    printf("Digite a palavra (tema) do relatorio: \033[96m");
    scanf("%[^\n]%*c", str);
    printf("\n\033[0m");

    int tam_string = strlen(str);

    for (int i = 0; i < tam_string; i++)
    {
        if (str[i] == ' ')
        {
            printf("\033[91m\033[1mERRO:\033[0m\033[91m Numero de palavras excedido. Favor digitar \033[1m1\033[0m\033[91m palavra.\n");
            free(classes_usadas);
            return 0;
        }
    }

    int ind_palavra = Relat_Palavras_Imprime(str, ind->palavras_ind, ind->palavras_usadas);

    if (ind_palavra < 0) {
        free(classes_usadas);
        return 0;
    }
        

    int qtd_docs = Palavras_Retorna_Prop_Usado(ind->palavras_ind[ind_palavra]);

    for (int i = 0; i < qtd_docs; i++)
    {

        int flag_igual = 0;
        int freq_classe = 0;
        char *classe_doc;

        int ind_doc = Palavras_Retorna_Ind(ind->palavras_ind[ind_palavra], i);
        classe = Retorna_Classe(ind->documentos_ind[ind_doc]);
        freq_classe += Palavras_Retorna_Freq(ind->palavras_ind[ind_palavra], i);

        // analisa se ja vimos essa classe anteriormente, se sim, pula o resto dessa iteracao
        for (int j = 0; j < qtd_classes; j++)
        {
            if (!strcmp(classe, classes_usadas[j]))
            {
                flag_igual = 1;
                break;
            }
        }

        if (flag_igual)
            continue;

        for (int k = i + 1; k < qtd_docs; k++)
        {
            int ind_doc2 = Palavras_Retorna_Ind(ind->palavras_ind[ind_palavra], k);
            classe_doc = Retorna_Classe(ind->documentos_ind[ind_doc2]);
            if (!strcmp(classe, classe_doc))
                freq_classe += Palavras_Retorna_Freq(ind->palavras_ind[ind_palavra], k);
        }

        classes_usadas[qtd_classes] = strdup(classe);
        frequencias[qtd_classes] = freq_classe;
        qtd_classes++;


        // freq_classe += Frequencia_por_classe (classe, ind->documentos_ind, ind->documentos_usados, ind_doc);
        // preciso passar pelos outros documentos, ver se tem a mesma classe e, se tiver, soma a frequencia, senao pula o arquivo e segue
    }

    Ordena_Classes(frequencias, classes_usadas, qtd_classes);

    for (int i = 0; i < qtd_classes; i++)
    {
        free(classes_usadas[i]);
    }

    free(classes_usadas);

    return 0;
}

// ---------------- AUXILIARES ----------------

void Imprime_Tudo(Indices indices)
{
    // Palavras_imprime (indices->palavras_ind, indices->palavras_usadas);
    Documentos_imprime(indices->documentos_usados, indices->documentos_ind);
    // Palavras_imprime_uma(indices->palavras_ind, 3);
}

int Decrescente_Inteiro(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    return (y - x);
}

void Ordena_Classes(int *frequencias, char **classes_usadas, int qtd_classes)
{

    int frequencias_2[qtd_classes];
    int aux;
    int ind;

    for (int i = 0; i < qtd_classes; i++)
        frequencias_2[i] = frequencias[i];

    qsort(frequencias_2, qtd_classes, sizeof(int), Decrescente_Inteiro);

    printf("\n\033[93m  ->\033[0m Frequencia por classe:\n\n");

    for (int i = 0; i < qtd_classes; i++)
    {
        aux = frequencias_2[i];

        for (int j = 0; j < qtd_classes; j++)
        {
            if (aux == frequencias[j])
            {
                ind = j;
                break;
            }
        }

        printf("\t\033[96m[\033[0m%s\033[96m]\033[0m - Aparece %d vez(es);\n\n", classes_usadas[ind], aux);
    }
}
