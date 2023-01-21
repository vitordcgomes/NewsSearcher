#include "palavras.h"
#include "propriedades.h"

#define QTD_INICIAL 100

struct palavras {

    char nome[101];
    Propriedades* prop;
    double tf_idf;

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

   palavra->prop_alocado = 100;
   palavra->prop_usado = 0;

   return palavra;
 }

 int Palavra_le (Palavras* pal, FILE* f, int ind_doc, int ind_palavra){

  char nome[100];
  fscanf(f, "%[^ ] ", nome);

  /*if (ind_palavra == 0){

    pal[ind_palavra] = Palavra_cria();
    strcpy(pal[ind_palavra]->nome, nome);

    pal[ind_palavra]->prop[pal[ind_palavra]->prop_usado] = Propriedades_cria (ind_doc);
    pal[ind_palavra]->prop_usado++;
    
    return 1; //retornar 1 significa que foi criada uma palavra nova.
  }*/
  int indice_vetor = 0;

  for (int i=ind_palavra-1; i>=0; i--){

    if (!strcmp(nome, pal[i]->nome)){
      printf ("\nSou igual! I: %d\n", i);
      
      //busca o indice no vetor de propriedades do documento de indice = ind
      //indice_vetor = Propriedades_busca(pal[i]->prop, 2, pal[i]->prop_usado);
      int j;
      for ( j=0; j<pal[i]->prop_usado; j++){
        indice_vetor = Propriedades_busca(&pal[i]->prop[j], ind_doc, pal[i]->prop_usado);
        printf ("\nIndice Vetor: %d\n", indice_vetor); 
        if (indice_vetor == 1){
          break;
        }
      }
      
      //se o indice do documento não existir no vetor de propriedades, ou seja, a função retornar <0, criamos outra "casinha" para o novo indice
      if (j == 0){
        Propriedades_realoca (pal[ind_palavra]);
        pal[ind_palavra]->prop[pal[ind_palavra]->prop_usado] = Propriedades_cria (ind_doc);
        pal[ind_palavra]->prop_usado++;
      }

      //se o indice existir, só aumentamos a frequência da propriedade desse indice no vetor
      else {
      printf("\nvou atualizar\n");
        pal[ind_palavra]->prop = Propriedade_Atualiza_Freq (pal[ind_palavra]->prop, j);
        printf ("\nJa atualizei\n");
      }


      return 0; //retornar 0 indica que a palavra lida já existia no vetor.
    }

  }

  //se a palavra for nova, criamos outra posição para ela ocupar
  pal[ind_palavra] = Palavra_cria();
  strcpy(pal[ind_palavra]->nome, nome);

  pal[ind_palavra]->prop = Propriedades_cria (ind_doc);
  pal[ind_palavra]->prop_usado++;
  
   return 1; //retornar 1 significa que foi criada uma palavra nova.
 }

 void Propriedades_realoca (Palavras p){
    if (p->prop_alocado == p->prop_usado){
        p->prop_alocado*=2;
        p->prop = (Propriedades*)realloc(p->prop, p->prop_alocado* sizeof(Propriedades));
    }
}

 void Palavras_imprime (Palavras* p, int qtd){

    for (int i=0; i<qtd; i++){
        printf ("%s ", p[i]->nome);
    }
    
    printf ("\n\n");

 }

 void Palavras_Libera(Palavras pal) {
   Propriedades_Libera(pal->prop);
   free(pal);
 }
