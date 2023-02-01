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

void Palavras_Libera(Palavras pal) {
   Propriedades_Libera(pal->prop, pal->prop_usado);
   free(pal);
 }


// ---------------- INDEXADORES ----------------

int Palavra_le (Palavras* pal, FILE* f, int ind_doc, int ind_palavra){

  char nome[100];
  fscanf(f, "%[^ ] ", nome);

  int indice_vetor = 0;

  for (int i=ind_palavra-1; i>=0; i--){
    if (!strcmp(nome, pal[i]->nome)){
      
      //busca o indice no vetor de propriedades do documento de indice = ind
      indice_vetor = Propriedades_busca(pal[i]->prop, ind_doc, pal[i]->prop_usado); //bsearch?
      
      //se o indice do documento não existir no vetor de propriedades, ou seja, a função retornar <0, criamos outra "casinha" para o novo indice
      if (indice_vetor < 0){
        if (pal[i]->prop_alocado == pal[i]->prop_usado) {
          Propriedades_realoca (pal[i]);
        }
          
        pal[i]->prop[pal[i]->prop_usado] = Propriedades_cria (ind_doc);
        pal[i]->prop_usado++;
      }  

      return 0; //retornar 0 indica que a palavra lida já existia no vetor.
    
    }
  }

  //se a palavra for nova, criamos outra posição para ela ocupar
  pal[ind_palavra] = Palavra_cria();
  strcpy(pal[ind_palavra]->nome, nome);
  pal[ind_palavra]->prop[pal[ind_palavra]->prop_usado] = Propriedades_cria (ind_doc);
  pal[ind_palavra]->prop_usado++;
  
   return 1; //retornar 1 significa que foi criada uma palavra nova.
 }

double Calcula_IDF(int tot_doc, Palavras pal) {
  
  double idf;

  double num = 0.0, denom = 0.0;

  num = 1 + tot_doc;
  denom = 1 + pal->prop_usado;

  idf = log(num/denom) + 1;

  return idf;
}

Palavras Calcula_TF_IDF(double idf, Palavras pal, int ind_prop) {
  pal->prop[ind_prop] = Atribui_TF_IDF(idf, pal->prop[ind_prop]);

  return pal;
}


// ---------------- BINARIO ----------------

void Palavras_Le_Binario(FILE* file, Palavras* pal, int qtd_pal) {

  for (int i = 0; i < qtd_pal; i++) {

    pal[i] = Palavra_cria();

    int tam_string = 0;
    fread(&tam_string, sizeof(int), 1, file);            
    fread(pal[i]->nome, tam_string, 1, file);
    fread(&pal[i]->prop_usado, sizeof(int), 1, file);

    //printf("[%d] - nome: %s; prop_usado: %d;\n", i, pal[i]->nome, pal[i]->prop_usado);
      
    pal[i]->prop = (Propriedades*)realloc(pal[i]->prop, pal[i]->prop_usado* sizeof(Propriedades));

    Propriedades_Le_Binario(file, pal[i]->prop, pal[i]->prop_usado);
  }
  
} 

void Palavras_Escreve_Binario(FILE* file, Palavras* pal, int qtd_pal) {

  for (int i = 0; i < qtd_pal; i++) {
    int tam_nome = strlen(pal[i]->nome) + 1; // +1 para incluir o '\0' da string

    fwrite(&tam_nome, sizeof(int), 1, file);
    fwrite(pal[i]->nome, tam_nome, 1, file);

    fwrite(&pal[i]->prop_usado, sizeof(int), 1, file);

    Propriedades_Escreve_Binario(file, pal[i]->prop, pal[i]->prop_usado);
    
  }
}

// ---------------- FUNCIONALIDADES (menu) ----------------

void Palavras_busca (Palavras* pal, int qtd, char* str){
  
  //quebrar 'str' na quantidade de palavras q tiverem sido escritas

  const char separador[] = " ";
  char* token;

  //retira o primeiro 'token'
  token = strtok(str, separador);

  while (token != NULL)
  {
    //printf("token: %s\n", token);

    Palavras busca = (Palavras)calloc(1, sizeof(struct palavras));

    strcpy(busca->nome, token);

    Palavras* endereco = bsearch(&busca, pal, qtd, sizeof(Palavras), String_Compara);

    if (endereco != NULL) {
      int indice = endereco - pal;
<<<<<<< HEAD

      Propriedades_Algo(pal[indice]->prop, pal[indice]->prop_usado);
      /*
        *pal = endereco da primeira casa (indice 0) do vetor
        *endereco = endereco da palavra encontrada no vetor
        *endereco - pal = diferenca de "casas" do vetor entre os endereços
      */

=======
      /*
        *pal = endereco da primeira casa (indice 0) do vetor
        *endereco = endereco da palavra encontrada no vetor
        *endereco - pal = diferenca de "casas" do vetor entre os endereços
      */

>>>>>>> 0b64b0d95d2f50d6b205465321562490f5961c55
      printf("Palavra '%s' encontrada no indice %d.\n", token, indice);
      //acessar o indice de cada palavras para calcular os atributos
    } 
    
    else {
      printf("Palavra '%s' nao encontrada.\n", token);
    }

    free(busca); 
    token = strtok(NULL, separador);
  }
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

int Palavras_Retorna_Ind(Palavras p, int ind) {
  return Propriedades_Retorna_Ind(p->prop, ind);
}

int Palavras_Retorna_Freq(Palavras p, int ind) {
  return Propriedades_Retorna_Freq(p->prop, ind);
}

void Palavras_imprime_uma (Palavras* p, int ind){

    printf ("ind: %d; %s; ", ind, p[ind]->nome);
    Propriedades_Imprime (p[ind]->prop, p[ind]->prop_usado);
    printf ("\n\n");
 }

Palavras* Palavras_Ordena(Palavras* pal, int qtd) {
  //int n = sizeof(pal) / sizeof(pal[0]);

  qsort(pal, qtd, sizeof(char*), String_Compara);

  //Palavras_imprime(pal, qtd);

  return pal;
}

double Palavras_Retorna_tf_idf(Palavras p, int ind) {
  return Propriedades_Retorna_tf_idf(p->prop, ind);
}

int String_Compara(const void *str1, const void *str2) {
  //return strcmp(((Palavras)str1)->nome,((Palavras)str2)->nome);
  return strcmp(*(char **)str1, *(char **)str2);
}
