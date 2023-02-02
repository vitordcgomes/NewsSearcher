#include "palavras.h"
#include "propriedades.h"

#define QTD_INICIAL 100

struct palavras {

    char nome[101];
    Propriedades* prop;

    int prop_alocado;
    int prop_usado;
};

// ---------------- MEMORIA ----------------

Palavras* Palavras_vetor_cria (){

    Palavras* palavra = (Palavras*)calloc(QTD_INICIAL, sizeof(Palavras));
    return palavra;
}

 Palavras Palavra_cria (){

   Palavras palavra = (Palavras)calloc(1, sizeof(struct palavras));
   palavra->prop = Propriedades_vetor_cria();
   palavra->prop_alocado = QTD_INICIAL;
   palavra->prop_usado = 0;

   return palavra;
 }

void Propriedades_realoca (Palavras p){

    p->prop_alocado*=2;
    p->prop = (Propriedades*)realloc(p->prop, p->prop_alocado* sizeof(Propriedades));
    
}

void Palavras_Libera(Palavras p) {
   Propriedades_Libera(p->prop, p->prop_usado);
   free(p);
 }


// ---------------- INDEXADORES ----------------

int Palavra_le (Palavras* p, FILE* f, int ind_doc, int ind_palavra){

  char nome[100];
  fscanf(f, "%[^ ] ", nome);

  int indice_vetor = 0;

  for (int i=ind_palavra-1; i>=0; i--){
    if (!strcmp(nome, p[i]->nome)){
      
      //busca o indice no vetor de propriedades do documento de indice = ind
      indice_vetor = Propriedades_busca(p[i]->prop, ind_doc, p[i]->prop_usado); //bsearch?
      
      //se o indice do documento não existir no vetor de propriedades, ou seja, a função retornar <0, criamos outra "casinha" para o novo indice
      if (indice_vetor < 0){
        if (p[i]->prop_alocado == p[i]->prop_usado) {
          Propriedades_realoca (p[i]);
        }
          
        p[i]->prop[p[i]->prop_usado] = Propriedades_cria (ind_doc);
        p[i]->prop_usado++;
      }  

      return 0; //retornar 0 indica que a palavra lida já existia no vetor.
    
    }
  }

  //se a palavra for nova, criamos outra posição para ela ocupar
  p[ind_palavra] = Palavra_cria();
  strcpy(p[ind_palavra]->nome, nome);
  p[ind_palavra]->prop[p[ind_palavra]->prop_usado] = Propriedades_cria (ind_doc);
  p[ind_palavra]->prop_usado++;
  
   return 1; //retornar 1 significa que foi criada uma palavra nova.
 }

double Calcula_IDF(int tot_doc, Palavras p) {
  
  double idf;

  double num = 0.0, denom = 0.0;

  num = 1 + tot_doc;
  denom = 1 + p->prop_usado;

  idf = log(num/denom) + 1;

  return idf;
}

Palavras Calcula_TF_IDF(double idf, Palavras p, int ind_prop) {

  p->prop[ind_prop] = Atribui_TF_IDF(idf, p->prop[ind_prop]);
  return p;
}


// ---------------- BINARIO ----------------

void Palavras_Le_Binario(FILE* file, Palavras* p, int qtd_palavras) {

  for (int i = 0; i < qtd_palavras; i++) {

    p[i] = Palavra_cria();

    int tam_string = 0;
    fread(&tam_string, sizeof(int), 1, file);            
    fread(p[i]->nome, tam_string, 1, file);
    fread(&p[i]->prop_usado, sizeof(int), 1, file);

    //printf("[%d] - nome: %s; prop_usado: %d;\n", i, p[i]->nome, p[i]->prop_usado);
      
    p[i]->prop = (Propriedades*)realloc(p[i]->prop, p[i]->prop_usado* sizeof(Propriedades));

    Propriedades_Le_Binario(file, p[i]->prop, p[i]->prop_usado);
  }
  
} 

void Palavras_Escreve_Binario(FILE* file, Palavras* p, int qtd_palavras) {

  for (int i = 0; i < qtd_palavras; i++) {
    int tam_nome = strlen(p[i]->nome) + 1; // +1 para incluir o '\0' da string

    fwrite(&tam_nome, sizeof(int), 1, file);
    fwrite(p[i]->nome, tam_nome, 1, file);

    fwrite(&p[i]->prop_usado, sizeof(int), 1, file);

    Propriedades_Escreve_Binario(file, p[i]->prop, p[i]->prop_usado);
    
  }
}

// ---------------- FUNCIONALIDADES (menu) ----------------

void Palavras_busca (Palavras* palavras, int qtd, char* str, int qtd_tot_docs){
  
  //quebrar 'str' na quantidade de palavras q tiverem sido escritas
  int cont_palavras = 0;

  int* vet_ind = (int*)calloc(1, sizeof(int));

  const char separador[] = " ";
  char* token;

  //retira o primeiro 'token'
  token = strtok(str, separador);

  int aux = 0;
  while (token != NULL)
  {
    //printf("token: %s\n", token);

    Palavras busca = (Palavras)calloc(1, sizeof(struct palavras));

    strcpy(busca->nome, token);

    Palavras* endereco = bsearch(&busca, palavras, qtd, sizeof(Palavras), String_Compara);

    if (endereco != NULL) {
      cont_palavras+=1;
      vet_ind = (int*)realloc(vet_ind, (cont_palavras+1)*sizeof(int));
      int indice = endereco - palavras;

      vet_ind[aux] = indice;
      aux++;
      /*
        *pal = endereco da primeira casa (indice 0) do vetor
        *endereco = endereco da palavra encontrada no vetor
        *endereco - pal = diferenca de "casas" do vetor entre os endereços
      */

      printf("Palavra '%s' encontrada no indice %d.\n", token, indice);
      //acessar o indice de cada palavras para calcular os atributos
    } 
    
    else {
      printf("Palavra '%s' nao encontrada.\n", token);
    }

    free(busca); 
    token = strtok(NULL, separador);
  }


  qsort(vet_ind, cont_palavras, sizeof(int), Ordena_Inteiro); //ordena vet_ind em ordem crescente
  Palavras_Indices_Buscados(palavras, vet_ind, cont_palavras, qtd_tot_docs);

  /*
  for (int i = 0; i < cont_pal; i++) {
    free(vet_ind[i]);
  }
  free(vet_ind);
  */
}

void Palavras_Indices_Buscados(Palavras* pal, int* vet_ind, int tam_vet, int qtd_tot_docs) {

  Palavras* buscadas = (Palavras*)calloc(tam_vet, sizeof(Palavras));
  Palavras aux = (Palavras)calloc(1, sizeof(struct palavras));
  aux->prop = Propriedades_Vet_Cria(qtd_tot_docs);

  for (int i = 0; i < tam_vet; i++) {
    buscadas[i] = (Palavras)calloc(1, sizeof(struct palavras));
    buscadas[i]->prop_usado = pal[vet_ind[i]]->prop_usado;
    buscadas[i]->prop = Propriedades_Vet_Cria(buscadas[i]->prop_usado);

    for (int j = 0; j < buscadas[i]->prop_usado; j++) {
      buscadas[i]->prop[j] = Documentos_Propriedade_Cria();
      buscadas[i]->prop[j] = Atribui_Auxiliar(buscadas[i]->prop[j], pal[vet_ind[i]]->prop[j]);
      
    }

    //Propriedades_Imprime(buscadas[i]->prop, buscadas[i]->prop_usado);
  }

  for (int i = 0; i < tam_vet; i++) {
    aux->prop = Busca_Indices_Docs(buscadas[i]->prop, buscadas[i]->prop_usado, aux->prop);
  }

  /*for (int i = 0; i < qtd_docs; i++) {
    for (int j = 0; j < buscadas[i]->prop_usado; j++) {
      //soma
   }

   //atribui

  }
  */
  
  printf("\ncont_pal = %d", tam_vet);
  printf("\nind: ");
  for (int i = 0; i < tam_vet; i++) {
    printf("%d ", vet_ind[i]);
  }
  printf("\n");

  for (int i = 0; i < tam_vet; i++) {
    printf("Palavra de indice '%d' aparece nos seguinte documentos:\n", vet_ind[i]);
    Propriedades_Imprime(buscadas[i]->prop, buscadas[i]->prop_usado);
  }
  
}


int Relat_Palavras_Imprime (char* str, Palavras* p, int qtd_palavras){

  int indice = -1;

  Palavras* endereco = bsearch(&str, p, qtd_palavras, sizeof(Palavras), String_Compara);
    
  if (endereco != NULL){
    indice = endereco - p;
    
    if (indice > -1){

      printf ("\n\n\n\033[1m========= RELATORIO DE PALAVRA =========\033[0m\n");
      printf ("\nPalavra: \033[93m'%s'\n\033[0m", str);

      printf ("\n\033[93m  ->\033[0m Encontrada no indice \033[93m%d\033[0m.\n", indice);
      printf ("\n\033[93m  ->\033[0m Aparece em \033[93m%d\033[0m documento(s).\n", p[indice]->prop_usado);
      printf ("\n\033[93m  ->\033[0m Aparece com maior frequencia no(s) documento(s):\n\n");

      Propriedades_Ordena (p[indice]->prop, p[indice]->prop_usado);
      printf ("\n\033[93m  ->\033[0m Frequencia por classe:\n\n");

      //Verifica_classe (p[indice]->prop, p[indice]->prop_usado);


    }
  }
    else {
      printf ("\033[91mA palavra '%s' nao foi encontrada. Tente novamente!\033[0m\n\n", str);
    }
  
  return indice;
}


// ---------------- AUXILIARES ----------------

int Palavras_Retorna_Prop_Usado(Palavras p) {
  return p->prop_usado;
}

void Palavras_imprime (Palavras* p, int qtd){

    for (int i=0; i<qtd; i++){
        printf ("ind: %d; nome: %s; ", i, p[i]->nome);
        Propriedades_Imprime (p[i]->prop, p[i]->prop_usado);
    }
    
    printf ("\n\n");
 }

int Palavras_Retorna_Ind(Palavras p, int ind_doc) {
  return Propriedades_Retorna_Ind(p->prop, ind_doc);
}

int Palavras_Retorna_Freq(Palavras p, int ind_doc) {
  return Propriedades_Retorna_Freq(p->prop, ind_doc);
}

void Palavras_imprime_uma (Palavras* p, int ind){

    printf ("ind: %d; %s; ", ind, p[ind]->nome);
    Propriedades_Imprime (p[ind]->prop, p[ind]->prop_usado);
    printf ("\n\n");
 }

Palavras* Palavras_Ordena(Palavras* p, int qtd) {
  //int n = sizeof(pal) / sizeof(pal[0]);

  qsort(p, qtd, sizeof(char*), String_Compara);

  //Palavras_imprime(pal, qtd);

  return p;
}

double Palavras_Retorna_tf_idf(Palavras p, int ind) {
  return Propriedades_Retorna_tf_idf(p->prop, ind);
}

int String_Compara(const void *str1, const void *str2) {
  //return strcmp(((Palavras)str1)->nome,((Palavras)str2)->nome);
  return strcmp(*(char **)str1, *(char **)str2);
}

int Ordena_Inteiro(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;

    return (x > y) - (x < y);
}
