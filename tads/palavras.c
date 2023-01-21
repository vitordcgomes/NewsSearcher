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
      //printf ("\nSou igual! I: %d\n", i);
      
      //busca o indice no vetor de propriedades do documento de indice = ind
      indice_vetor = Propriedades_busca(pal[i]->prop, ind_doc, pal[i]->prop_usado);
      
      //se o indice do documento não existir no vetor de propriedades, ou seja, a função retornar <0, criamos outra "casinha" para o novo indice
      if (indice_vetor < 0){
        //printf ("preciso reallocar\n");
        if (pal[i]->prop_alocado == pal[i]->prop_usado)
        {
          printf ("ok?\n");
          Propriedades_realoca (pal[ind_palavra]);
        }
          

        pal[i]->prop[pal[i]->prop_usado] = Propriedades_cria (ind_doc);
        pal[i]->prop_usado++;
      }

      //se o indice existir, só aumentamos a frequência da propriedade desse indice no vetor
     

      return 0; //retornar 0 indica que a palavra lida já existia no vetor.
    
    }

  }

  //se a palavra for nova, criamos outra posição para ela ocupar
  pal[ind_palavra] = Palavra_cria();
  strcpy(pal[ind_palavra]->nome, nome);

  pal[ind_palavra]->prop[pal[ind_palavra]->prop_usado] = Propriedades_cria (ind_doc);
  pal[ind_palavra]->prop_usado++;

  //Propriedades_Imprime(pal[ind_palavra]->prop, pal[ind_palavra]->prop_usado);
  
   return 1; //retornar 1 significa que foi criada uma palavra nova.
 }

 void Propriedades_realoca (Palavras p){
  printf ("sera q posso?\n");
    if (p->prop_alocado == p->prop_usado){
      printf ("posso!, vamos tentar");
        p->prop_alocado*=2;
        printf ("Vamos realloc!");
        p->prop = (Propriedades*)realloc(p->prop, p->prop_alocado* sizeof(Propriedades));
        printf ("Realloc!");
    
    }
    printf ("Não preciso!");

}

 void Palavras_imprime (Palavras* p, int qtd){

    for (int i=0; i<qtd; i++){
        printf ("%s \n", p[i]->nome);
        Propriedades_Imprime (p[i]->prop, p[i]->prop_usado);
    }
    
    printf ("\n\n");

    

 }

 void Palavras_Libera(Palavras pal) {
   Propriedades_Libera(pal->prop);
   free(pal);
 }
