#include "palavras.h"
#include "propriedades.h"

#define QTD_INICIAL 100

struct palavras {

    char nome[101];
    Propriedades* prop;

    int prop_alocado;
    int prop_usado;
};


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

 int Palavra_le (Palavras* pal, FILE* f, int ind_doc, int ind_palavra){

  char nome[100];
  fscanf(f, "%[^ ] ", nome);

  int indice_vetor = 0;

  for (int i=ind_palavra-1; i>=0; i--){
    if (!strcmp(nome, pal[i]->nome)){
      
      //busca o indice no vetor de propriedades do documento de indice = ind
      indice_vetor = Propriedades_busca(pal[i]->prop, ind_doc, pal[i]->prop_usado);
      
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

 void Propriedades_realoca (Palavras p){

    p->prop_alocado*=2;
    p->prop = (Propriedades*)realloc(p->prop, p->prop_alocado* sizeof(Propriedades));
    
}

 void Palavras_imprime (Palavras* p, int qtd){

    for (int i=0; i<30; i++){
        printf ("nome: %s; ", p[i]->nome);
        Propriedades_Imprime (p[i]->prop, p[i]->prop_usado);
    }
    
    printf ("\n\n");
 }

  void Palavras_imprime_uma (Palavras* p, int ind){

    printf ("ind: %d; %s; ", ind, p[ind]->nome);
    Propriedades_Imprime (p[ind]->prop, p[ind]->prop_usado);
    printf ("\n\n");
 }

 void Palavras_Libera(Palavras pal) {
   Propriedades_Libera(pal->prop, pal->prop_usado);
   free(pal);
 }

int Palavras_Retorna_Ind(Palavras p, int ind) {
  return Propriedades_Retorna_Ind(p->prop, ind);
}

int Palavras_Retorna_Freq(Palavras p, int ind) {
  return Propriedades_Retorna_Freq(p->prop, ind);
}

int Palavras_Retorna_Prop_Usado(Palavras p) {
  return p->prop_usado;
}

double Calcula_IDF(int tot_doc, Palavras pal) {
  //pal->prop_usado;
  
  double idf;

  double num = 0.0, denom = 0.0;

  num = 1 + tot_doc;
  denom = 1 + pal->prop_usado;

  //printf("\nlog: %.2lf\n", log(num/denom));

  idf = log(num/denom) + 1;

  //printf("idf: %.2lf\n", idf);

  return idf;
}

Palavras Calcula_TF_IDF(double idf, Palavras pal, int ind_prop) {
  pal->prop[ind_prop] = Atribui_TF_IDF(idf, pal->prop[ind_prop]);

  return pal;
}
