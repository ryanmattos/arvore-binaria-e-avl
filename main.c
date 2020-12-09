#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "tree.h"

int main(){
    clock_t start_t, end_t, total_t;
    int option, response;
    char search[15];
    bTree *tree = NULL;
    aTree *avl = NULL;

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
                printf("\nLendo o arquivo...\n");
                readFile(&tree, &avl);
                break;
            case 2:
                printf("\nListando as palavras em ordem alfabetica...\n");
                printTree(avl);
                break;
            case 3:
                printf("\nVerificando custo de caminhamento...\n");
                time(&start_t);
                walkThroughBinaryCost(tree);
                //apenas para testar se estava contando o tempo corretamente
                //for(long int i = 0; i < 500000; i++)
                //  printf("%ld\n", i);
                time(&end_t);
                printf("Custo de Caminhamento Arvore Binaria:\t%.2lf segundos\n", difftime(end_t, start_t));
                time(&start_t);
                walkThroughAvlCost(avl);
                time(&end_t);
                printf("Custo de Caminhamento Arvore AVL:\t%.2lf segundos\n\n", difftime(end_t, start_t));
                break;
            case 4:
                printf("\nVerificando custo de busca...\n");
                printf("Insira um termo para ser buscado: ");
                scanf("%s", search);
                time(&start_t);
                response = searchOnAvlTree(&avl, search);
                time(&end_t);
                if(response == -1)
                    printf("\nTermo nao encontrado\n");
                else
                    printf("Encontrado na arvore binaria em:\t%.2lf segundos\n", difftime(end_t, start_t));

                time(&start_t);
                response = searchOnBinaryTree(&tree, search);
                time(&end_t);
                if(response == -1)
                    printf("Termo nao encontrado\n\n");
                else
                    printf("Encontrado na arvore avl em:\t%.2lf segundos\n\n", difftime(end_t, start_t));
                break;
            case 7:
                printf("Exit program\n");
                return 0;
            default:
                printf("Opcao invalida!\n\n");
                break;
        }
    }


    return 0;
}