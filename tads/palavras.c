#include "palavras.h"
#include "propriedades.h"

#define QTD_INICIAL 100

struct palavras
{

  char nome[101];
  Propriedades *prop;

  int prop_alocado;
  int prop_usado;
};

// ---------------- MEMORIA ----------------

Palavras Palavra_cria()
{

  Palavras palavra = (Palavras)calloc(1, sizeof(struct palavras));
  palavra->prop = Propriedades_vetor_cria();
  palavra->prop_alocado = QTD_INICIAL;
  palavra->prop_usado = 0;

  return palavra;
}

Palavras *Palavras_vetor_cria()
{

  Palavras *palavra = (Palavras *)calloc(QTD_INICIAL, sizeof(Palavras));
  return palavra;
}

void Palavras_Libera(Palavras p)
{
  Propriedades_Libera(p->prop, p->prop_usado);
  free(p);
}

void Propriedades_realoca(Palavras p)
{

  p->prop_alocado *= 2;
  p->prop = (Propriedades *)realloc(p->prop, p->prop_alocado * sizeof(Propriedades));
}

// ---------------- INDEXADORES ----------------

double Calcula_IDF(int tot_doc, Palavras p)
{

  double idf;
  double num = 0.0, denom = 0.0;

  num = 1 + tot_doc;
  denom = 1 + p->prop_usado;
  idf = log(num / denom) + 1;

  return idf;
}

double Calcula_IDF_Classif(int tot_doc, Palavras p)
{

  double idf = 0;
  double num = 0.0, denom = 0.0;

  num = 1 + 1;
  denom = 1 + 1;
  idf = log(num / denom) + 1;

  return idf;
}

int Palavra_le(Palavras *p, FILE *f, int ind_doc, int ind_palavra)
{

  char nome[100];
  fscanf(f, "%[^ ] ", nome);

  int indice_vetor = 0;

  for (int i = ind_palavra - 1; i >= 0; i--)
  {
    if (!strcmp(nome, p[i]->nome))
    {

      // busca o indice no vetor de propriedades do documento de indice = ind
      indice_vetor = Propriedades_busca(p[i]->prop, ind_doc, p[i]->prop_usado);

      // se o indice do documento não existir no vetor de propriedades, ou seja, a função retornar <0, criamos outra "casinha" para o novo indice
      if (indice_vetor < 0)
      {
        if (p[i]->prop_alocado == p[i]->prop_usado)
        {
          Propriedades_realoca(p[i]);
        }

        p[i]->prop[p[i]->prop_usado] = Propriedades_cria(ind_doc);
        p[i]->prop_usado++;
      }

      return 0; // retornar 0 indica que a palavra lida já existia no vetor.
    }
  }

  // se a palavra for nova, criamos outra posição para ela ocupar
  p[ind_palavra] = Palavra_cria();
  strcpy(p[ind_palavra]->nome, nome);
  p[ind_palavra]->prop[p[ind_palavra]->prop_usado] = Propriedades_cria(ind_doc);
  p[ind_palavra]->prop_usado++;

  return 1; // retornar 1 significa que foi criada uma palavra nova.
}

Palavras Calcula_TF_IDF(double idf, Palavras p, int ind_prop)
{

  p->prop[ind_prop] = Atribui_TF_IDF(idf, p->prop[ind_prop]);
  return p;
}

// ---------------- BINARIO ----------------

void Palavras_Le_Binario(FILE *file, Palavras *p, int qtd_palavras)
{

  for (int i = 0; i < qtd_palavras; i++)
  {

    p[i] = Palavra_cria();

    int tam_string = 0;
    fread(&tam_string, sizeof(int), 1, file);
    fread(p[i]->nome, tam_string, 1, file);
    fread(&p[i]->prop_usado, sizeof(int), 1, file);

    p[i]->prop = (Propriedades *)realloc(p[i]->prop, p[i]->prop_usado * sizeof(Propriedades));

    Propriedades_Le_Binario(file, p[i]->prop, p[i]->prop_usado);
  }
}

void Palavras_Escreve_Binario(FILE *file, Palavras *p, int qtd_palavras)
{

  for (int i = 0; i < qtd_palavras; i++)
  {
    int tam_nome = strlen(p[i]->nome) + 1; // +1 para incluir o '\0' da string

    fwrite(&tam_nome, sizeof(int), 1, file);
    fwrite(p[i]->nome, tam_nome, 1, file);

    fwrite(&p[i]->prop_usado, sizeof(int), 1, file);

    Propriedades_Escreve_Binario(file, p[i]->prop, p[i]->prop_usado);
  }
}

// ---------------- FUNCIONALIDADES (menu) ----------------

int *Cria_Ind_Docs(Palavras *palavras, int qtd_palavras)
{
  int *ind_docs = (int *)calloc(1, sizeof(int));

  int qtd_docs = 0;
  int ind;
  int flag_igual = 0;

  for (int i = 0; i < qtd_palavras; i++)
  {
    for (int j = 0; j < palavras[i]->prop_usado; j++)
    {

      ind = Propriedades_Retorna_Ind(palavras[i]->prop, j); // retornar prop->ind

      for (int k = 0; k < qtd_docs; k++)
      {
        if (ind == ind_docs[k])
        {
          flag_igual = 1;
          break;
        }
      }
      if (!flag_igual)
      {
        ind_docs[qtd_docs] = ind;

        qtd_docs += 1;
        ind_docs = (int *)realloc(ind_docs, (qtd_docs + 1) * sizeof(int));
      }
      flag_igual = 0;
    }
  }

  ind_docs[qtd_docs] = -1;
  return ind_docs;
}

int Relat_Palavras_Imprime(char *str, Palavras *p, int qtd_palavras)
{

  int indice = -1;

  Palavras *endereco = bsearch(&str, p, qtd_palavras, sizeof(Palavras), String_Compara);

  if (endereco != NULL)
  {
    indice = endereco - p;

    if (indice > -1)
    {

      printf("\n\n\n\033[1m========= RELATORIO DE PALAVRA =========\033[0m\n");
      printf("\nPalavra: \033[93m'%s'\n\033[0m", str);

      printf("\n\033[93m  ->\033[0m Encontrada no indice \033[93m%d\033[0m.\n", indice);
      printf("\n\033[93m  ->\033[0m Aparece em \033[93m%d\033[0m documento(s).\n", p[indice]->prop_usado);
      printf("\n\033[93m  ->\033[0m Aparece com maior frequencia no(s) documento(s):\n\n");

      Propriedades_Ordena(p[indice]->prop, p[indice]->prop_usado);
    }
  }
  else
  {
    printf("\033[91mA palavra '%s' nao foi encontrada. Tente novamente!\033[0m\n\n", str);
  }

  return indice;
}

void Palavras_busca(Palavras *palavras, int qtd_palavras, char nomes_docs[][100])
{

  int *ind_docs = (int *)calloc(1, sizeof(int));
  double *tf_idf = (double *)calloc(1, sizeof(double)); // faz copia, ordena e itera referenciando pela copia original
  int qtd_docs = 0;
  int ind;
  int flag_igual = 0;

  for (int i = 0; i < qtd_palavras; i++)
  {
    for (int j = 0; j < palavras[i]->prop_usado; j++)
    {

      ind = Propriedades_Retorna_Ind(palavras[i]->prop, j); // retornar prop->ind

      for (int k = 0; k < qtd_docs; k++)
      {
        if (ind == ind_docs[k])
        {

          // soma tf-idf
          tf_idf[k] += Propriedades_Retorna_tf_idf(palavras[i]->prop, j);
          flag_igual = 1;
          break;
        }
      }
      if (!flag_igual)
      {
        ind_docs[qtd_docs] = ind;
        tf_idf[qtd_docs] = Propriedades_Retorna_tf_idf(palavras[i]->prop, j);

        qtd_docs += 1;
        ind_docs = (int *)realloc(ind_docs, (qtd_docs + 1) * sizeof(int));
        tf_idf = (double *)realloc(tf_idf, (qtd_docs + 1) * sizeof(double));
      }
      flag_igual = 0;
    }
  }

  Ordena_tf_idf(ind_docs, tf_idf, qtd_docs, nomes_docs);

  free(ind_docs);
  free(tf_idf);
}

Palavras *Palavras_Retorna_Endereco(char *token, Palavras *palavras, int qtd_palavras)
{
  Palavras busca = (Palavras)calloc(1, sizeof(struct palavras));
  strcpy(busca->nome, token);
  Palavras *endereco = bsearch(&busca, palavras, qtd_palavras, sizeof(Palavras), String_Compara);

  free(busca);
  return endereco;
}

Palavras *Palavras_Indices_Buscados(Palavras *pal, int *vet_ind, int tam_vet, int qtd_docs)
{

  Palavras *buscadas = (Palavras *)calloc(tam_vet, sizeof(Palavras));

  for (int i = 0; i < tam_vet; i++)
  {
    buscadas[i] = (Palavras)calloc(1, sizeof(struct palavras));
    buscadas[i]->prop_usado = pal[vet_ind[i]]->prop_usado;
    buscadas[i]->prop = Propriedades_Vet_Cria(buscadas[i]->prop_usado);

    for (int j = 0; j < buscadas[i]->prop_usado; j++)
    {
      buscadas[i]->prop[j] = Documentos_Propriedade_Cria();
      buscadas[i]->prop[j] = Atribui_Auxiliar(buscadas[i]->prop[j], pal[vet_ind[i]]->prop[j]);
    }
  }

  return buscadas;
}

// ---------------- AUXILIARES ----------------

int Palavras_Retorna_Prop_Usado(Palavras p)
{
  return p->prop_usado;
}

void Palavras_imprime(Palavras *p, int qtd)
{

  for (int i = 0; i < qtd; i++)
  {
    printf("ind: %d; nome: %s; ", i, p[i]->nome);
    Propriedades_Imprime(p[i]->prop, p[i]->prop_usado);
  }

  printf("\n\n");
}

Palavras *Palavras_Ordena(Palavras *p, int qtd)
{
  qsort(p, qtd, sizeof(char *), String_Compara);
  return p;
}

void Palavras_imprime_uma(Palavras *p, int ind)
{
  Propriedades_Imprime(p[ind]->prop, p[ind]->prop_usado);
  printf("\n\n");
}

int Palavras_Retorna_Ind(Palavras p, int ind_doc)
{
  return Propriedades_Retorna_Ind(p->prop, ind_doc);
}

int Palavras_Retorna_Freq(Palavras p, int ind_doc)
{
  return Propriedades_Retorna_Freq(p->prop, ind_doc);
}

double Palavras_Retorna_tf_idf(Palavras p, int ind)
{
  return Propriedades_Retorna_tf_idf(p->prop, ind);
}

int Crescente_Inteiro(const void *a, const void *b)
{
  int x = *(int *)a;
  int y = *(int *)b;

  return (x > y) - (x < y);
}

int String_Compara(const void *str1, const void *str2)
{
  return strcmp(*(char **)str1, *(char **)str2);
}
