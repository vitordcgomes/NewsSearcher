#include <stdio.h>
#include <stdlib.h>
#include "tads/indices.h"

void Menu_Funcionalidades();
void Imprime_Menu ();

typedef enum {
    BUSCA = '1',
    CLASSIFICA = '2',
    RELAT_PAL = '3',
    RELAT_DOC = '4',
    ENCERRA = '0'
} Operacao;

int main(int argc, char** argv) {

    Indices ind = Indices_cria();
    ind = Le_Binario(ind, argv[1]);
    Menu_Funcionalidades(ind);
    Indices_Libera(ind);
    printf("\033[1m----Ate a proxima!----\033[0m\n\n");

    return 0;
}

// ---------------- FUNCOES LOCAIS ----------------

void Menu_Funcionalidades(Indices ind){

    char op;
    int flag_encerra = 0;

    while(1){

        Imprime_Menu ();
        scanf ("%c%*c", &op);
        printf ("\033[0m");

        switch (op)
        {
            case BUSCA:
                Texto_Busca(ind);
            break;

            case CLASSIFICA:
            break;

            case RELAT_PAL:
            break;

            case RELAT_DOC:
            break;

            case ENCERRA:
                flag_encerra = 1;
            break;

            default:
                printf ("\n\033[91mFavor digitar apenas \033[1mnumeros\033[0m\033[91m correspondentes as opcoes do menu.\n");
                flag_encerra = 1;
            break;
                
        }

        if (flag_encerra) {
            printf ("\n\033[3m\033[91mEncerrando \033[1m# NewsSearcher #\033[0m\n\n");
            break;
        }

    }
}

void Imprime_Menu (){

    printf ("\n\033[95m\033[1m # \033[96mNewsSearcher\033[95m #\n\033[0m");
    printf ("\n\t\033[95m1.\033[0m Buscar noticias");
    printf ("\n\t\033[95m2.\033[0m Classificar noticias");
    printf ("\n\t\033[95m3.\033[0m Imprimir relatorio de palavras");
    printf ("\n\t\033[95m4.\033[0m Imprimir relatorio de documentos");
    printf ("\n\t\033[91m0.\033[0m Encerrar programa\033[0m\n\n");
    printf ("Digite a operacao desejada:\033[96m ");

}
