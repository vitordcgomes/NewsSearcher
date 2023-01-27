#include <stdio.h>
#include <stdlib.h>
#include "tads/indices.h"

void Funcionalidades();
void Imprime_Menu ();
void Le_Binario(char* caminho);


typedef enum {
    BUSCA = '1',
    CLASSIFICA = '2',
    RELAT_PAL = '3',
    RELAT_DOC = '4',
    ENCERRA = '0'
} Operacao;

int main(int argc, char** argv) {

    Le_Binario(argv[1]);
    Funcionalidades();
    //Libera_Memoria();
    printf("\033[1m----Ate a proxima!----\033[0m\n\n");
    //Deleta_Binario();

    return 0;
}

void Funcionalidades(){

    char op;
    int flag_erros = 0;
    int flag_encerra = 0;

    while(1){

        Imprime_Menu ();
        scanf ("%c%*c", &op);
        printf ("\033[0m");

        switch (op)
        {
            case BUSCA:
            break;

            case CLASSIFICA:
            break;

            case RELAT_PAL:
            break;

            case RELAT_DOC:
            break;

            case ENCERRA:
                printf ("\n\033[3m\033[91mEncerrando \033[1m# NewsSearcher #\033[0m\n\n");
                flag_encerra = 1;
            break;

            default:
                printf ("\n\033[91m\033[3mEssa entrada nao eh valida!\033[0m\033[91m\nFavor digitar um dos numeros presentes no menu.\n\n\033[0m");
                flag_erros++; 

                if (flag_erros>3){
                    printf ("\033[91mVoce esgotou suas tentativas! Favor reiniciar o programa.\n");
                    printf ("\n\033[3m\033[91mEncerrando \033[1m# NewsSearcher #\033[0m\n\n");
                    flag_encerra = 1;
                }
                else {
                    printf ("\033[91mVoce tem \033[1m%d\033[0m\033[91m tentativa(s) restante(s)!\033[0m\n", 4-flag_erros);

                }
            break;
                
        }

        if (flag_encerra) break;
    }

}

void Imprime_Menu ()
{
    printf ("\n\033[95m\033[1m # \033[96mNewsSearcher\033[95m #\n\033[0m");
    printf ("\n\t\033[95m1.\033[0m Buscar noticias");
    printf ("\n\t\033[95m2.\033[0m Classificar noticias");
    printf ("\n\t\033[95m3.\033[0m Imprimir relatorio de palavras");
    printf ("\n\t\033[95m4.\033[0m Imprimir relatorio de documentos");
    printf ("\n\t\033[91m0.\033[0m Encerrar programa\033[0m\n\n");
    printf ("Digite a operacao desejada:\033[96m ");

}

void Le_Binario(char* caminho){
    
    FILE* file = fopen (caminho, "rb");
    
    
    //leitura de palavras

    
    long int qtd_pal = 0;
    fread (&qtd_pal, sizeof(long int), 1, file);
    //printf ("qtd_pal: %ld\n", qtd_pal);

    char* vet_nomes[qtd_pal];

    for (int i = 0; i < qtd_pal; i++) {
        int tam_string = 0;
        fread(&tam_string, sizeof(int), 1, file);

        vet_nomes[i] = (char*)malloc(tam_string);
            
        fread(vet_nomes[i], tam_string, 1, file);
        printf("nome: %s\n", vet_nomes[i]);

        int qtd_prop = 0;
        fread(&qtd_prop, sizeof(int), 1, file);
        int pal_freq[qtd_prop];
        int pal_ind[qtd_prop];
        double pal_tf_idf[qtd_prop];

        
        for (int j = 0; j < qtd_prop; j++) {

            fread(&pal_freq[j], sizeof(int), 1, file);
            printf("freq: %d; ", pal_freq[j]);

            fread(&pal_ind[j], sizeof(int), 1, file);
            printf("ind: %d; ", pal_ind[j]);

            fread(&pal_tf_idf[j], sizeof(double), 1, file);
            printf("tf-idf: %.2lf;\n", pal_tf_idf[j]);
        }
        

    }

/*******************************************************************/

    //leitura documentos

    int qtd_doc = 0;
    fread (&qtd_doc, sizeof(long int), 1, file);
    //printf ("qtd_doc: %d\n", qtd_doc);

    char* vet_nomes_doc[qtd_doc];
    char* vet_classe_doc[qtd_doc];

    for (int i = 0; i < qtd_doc; i++) {
        int tam_string_doc = 0;
        fread(&tam_string_doc, sizeof(int), 1, file);

        vet_nomes_doc[i] = (char*)malloc(tam_string_doc);
            
        fread(vet_nomes_doc[i], tam_string_doc, 1, file);
        printf("nome_doc: %s; ", vet_nomes_doc[i]);

        vet_classe_doc[i] = (char*)malloc(4); //tamanho da string classe eh fixo e == 4

        fread(vet_classe_doc[i], 4, 1, file);
        printf("classe: %s;\n", vet_classe_doc[i]);

        int qtd_prop_doc = 0;
        fread(&qtd_prop_doc, sizeof(int), 1, file);
        int doc_freq[qtd_prop_doc];
        int doc_ind[qtd_prop_doc];

        for (int j = 0; j < qtd_prop_doc; j++) {
            fread(&doc_freq[j], sizeof(int), 1, file);
            printf("freq: %d; ", doc_freq[j]);

            fread(&doc_ind[j], sizeof(int), 1, file);
            printf("ind: %d;\n", doc_ind[j]);
        }
    }

    

    fclose (file);
}