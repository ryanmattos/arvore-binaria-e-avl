#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "tree.h"

int main(){
    int option;
    bTree *tree = NULL;

    while(1){
        printf("----------------MENU------------------\n");
        printf("1 - Ler o Arquivo\n");
        printf("2 - Listar Palavras em Ordem\n");
        printf("3 - Custo de Caminhamento\n");
        printf("4 - Custo de Busca\n");
        printf("7 - Sair\n");
        printf("--------------------------------------\n");
        printf("Selecione uma opcao: ");

        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Read file option\n");
                readFile(&tree);
                break;
            case 2:
                printf("List words in order\n");
                printTree(tree);
                break;
            case 3:
                printf("Walk through cost\n");
                break;
            case 4:
                printf("Search cost\n");
                break;
            case 7:
                printf("Exit program\n");
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    }


    return 0;
}