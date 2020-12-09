//
// Created by Ryan on 06/12/2020.
//

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readFile(bTree **tree, aTree **avl) {
    FILE *fp;
    char c, word[15];
    int i = 0;

    //tira o lixo da variavel
    memset(word, 0, 15);

    //abre o arquivo do jogo
    fp = fopen("archive.txt", "r");

    //se o arquivo nao existir, ou tiver um erro, sai do programa
    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    while (!feof(fp)) { //enquanto nao for o final do arquivo

        c = fgetc(fp); //pega caractere por caractere e armazena em c

        //caso seja encontrado um espaco, quebra de linha, ou o final do arquivo inclui a palavra nas duas arvores
        if (c == ' ' || c == '\n' || c == EOF) {
            //printf("Inserindo: %s\n", word);
            insertIntoBinaryTree(&(*tree), word);
            insertIntoAvlTree(&(*avl), word);
            memset(word, 0, 15);
            i = 0;
        } else {
            word[i] = c; //armazena na posicao i de word o caractere encontrado
            ++i;
        }
    }
}

//insere palavra na arvore binaria
int insertIntoBinaryTree(bTree **tree, char *w) {
    bTree *new;

    if ((*tree) == NULL) {
        new = (bTree *) malloc(sizeof(bTree));
        if (new != NULL) {
            strcpy(new->word, w);
            new->occurrence = 1;
            new->left = NULL;
            new->right = NULL;
            (*tree) = new;
            return inserted;
        } else
            return notInserted;
    }

    //verifica se a palavra é igual, independente de letra maiuscula ou minuscula
    if (strcmpi(w, (*tree)->word) == 0 ) {
        //printf("Palavra ja existe no texto\nIncrementando sua ocorrencia\n");
        (*tree)->occurrence++;
    } else if (strcmpi(w, (*tree)->word) > 0) { //novo no 'maior' que no atual, insere a direita
        insertIntoBinaryTree((&(*tree)->right), w);
    } else {
        insertIntoBinaryTree((&(*tree)->left), w);
    }

}

//insere palavra na arvore avl
int insertIntoAvlTree(aTree **tree, char *w) {
    aTree *new, *left, *right;
    int response;

    if ((*tree) == NULL) {
        new = (aTree *) malloc(sizeof(aTree));
        if (new != NULL) {
            strcpy(new->word, w);
            new->occurrence = 1;
            new->left = NULL;
            new->right = NULL;
            new->b = 0;
            (*tree) = new;
            return inserted;
        } else
            return notInserted;
    }

    //verifica se a palavra é igual, independente de letra maiuscula ou minuscula
    if (strcmpi(w, (*tree)->word) == 0 ) {
        //printf("Palavra ja existe no texto\nIncrementando sua ocorrencia\n");
        (*tree)->occurrence++;
        return notInserted;
    } else if (strcmpi(w, (*tree)->word) > 0) { //novo no 'maior' que no atual, insere a direita
        response = insertIntoAvlTree((&(*tree)->right), w);

        if (response == notInserted) return response;

        if (response == inserted) { //se voltar na recursao e tiver sido inserido alguma palavra
            (*tree)->b += 1; //incrementa o balanceamento em 1, pois foi inserido na direita
            if ((*tree)->b == 2) { // se a arvore estiver desbalanceada
                right = (aTree *)(*tree)->right;
                if (right->b == 1) { //verifica se eh preciso fazer uma rotacao simples ou dupla
                    rotateLeft(tree); // LL
                    return 0;
                } else if (left->b == -1) {
                    rotateRightLeft(tree); // RL
                    return 0;
                }
            }
            if((*tree)->b == -1) return 1;
            if((*tree)->b == 0) return 0;
        }
    } else {
        response = insertIntoAvlTree((&(*tree)->left), w);

        if (response == notInserted) return response;

        if (response == inserted) { //se voltar na recursao e tiver sido inserido alguma palavra
            (*tree)->b -= 1; //decrementa o balanceamento em 1, pois foi inserido na esquerda
            if ((*tree)->b == -2) { //se a arvore estiver desbalanceada
                left = (aTree *)(*tree)->left;
                if (left->b == 1) { //verifica se eh preciso fazer uma rotacao simples ou dupla
                    rotateLeftRight(tree); //LR
                    return 0;
                } else if (left->b == -1) {
                    rotateRight(tree); //RR
                    return 0;
                }
            }
            if((*tree)->b == -1) return 1;
            if((*tree)->b == 0) return 0;
        }
    }
}

//rotaciona pra direita
void rotateRight (aTree **tree) {
    aTree *aux1, *aux2;
    aux1 = *tree;
    aux2 = (*tree)->left;
    aux1->left = aux2->right;
    aux2->right = (void *)aux1;
    (*tree) = aux2;
    if(aux2->b == -1) aux1->b += 2;
    aux2->b += 1;
}

//rotaciona pra esquerda
void rotateLeft (aTree **tree) {
    aTree *aux1, *aux2;
    aux1 = *tree;
    aux2 = (aTree *)((*tree)->right);
    aux1->right = aux2->left;
    aux2->left = (void *)aux1;
    (*tree) = aux2;
    if(aux2->b == 1) aux1->b -= 2;
    aux2->b -= 1;
}

//rotaciona primeiramente para a direita e depois esquerda
void rotateRightLeft (aTree **tree) {
    rotateRight((aTree **)&((*tree)->right));
    rotateLeft(tree);

}

//rotaciona primeiramente para a esquerda e depois direita
void rotateLeftRight (aTree **tree) {
    rotateLeft((aTree **)&((*tree)->left));
    rotateRight(tree);
}

//imprime a arvore
int printTree(aTree *avl) {
    aTree *temp;
    temp = avl;

    if (temp == NULL)
        return 0;

    printTree(temp->left);
    printf("Word: %s\tOccrrences: %d\n", avl->word, avl->occurrence);
    printTree(temp->right);
}

//caminha por todos os nos da arvore binaria
int walkThroughBinaryCost(bTree *tree) {
    bTree *temp;
    temp = tree;

    if (temp == NULL)
        return 0;

    walkThroughBinaryCost(temp->left);
    walkThroughBinaryCost(temp->right);
}

//caminha por todos os nos da arvore avl
int walkThroughAvlCost(aTree *tree) {
    aTree *temp;
    temp = tree;

    if (temp == NULL)
        return 0;

    walkThroughAvlCost(temp->left);
    walkThroughAvlCost(temp->right);
}

//pesquisa termo na arvore avl
int searchOnAvlTree(aTree **tree, char *w){
    if((*tree) == NULL) return -1;
    if(strcmpi(w, (*tree)->word) < 0) return searchOnAvlTree((aTree **)&((*tree)->left), w);
    if(strcmpi(w, (*tree)->word) > 0) return searchOnAvlTree((aTree **)&((*tree)->right),w);
    if(strcmpi(w, (*tree)->word) == 0) return 1;
}

//pesquisa termo na arvore binaria
int searchOnBinaryTree(bTree **tree, char *w) {
    if((*tree) == NULL) return -1;
    if(strcmpi(w, (*tree)->word) < 0) return searchOnBinaryTree((bTree **)&((*tree)->left), w);
    if(strcmpi(w, (*tree)->word) > 0) return searchOnBinaryTree((bTree **)&((*tree)->right),w);
    if(strcmpi(w, (*tree)->word) == 0) return 1;
}