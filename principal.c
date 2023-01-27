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
    long int qtd_pal = 0;

    FILE* file = fopen (caminho, "rb");
    
    
    fread (&qtd_pal, sizeof(long int), 1, file);
    printf ("qtd_pal: %ld\n", qtd_pal);

    fclose (file);
}