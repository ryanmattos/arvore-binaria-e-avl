//
// Created by Ryan on 06/12/2020.
//

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readFile(bTree **tree) {
    FILE *fp;
    char c, word[15];
    int i = 0;

    //abre o arquivo do jogo
    fp = fopen("archive.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    while (!feof(fp)) {
        c = fgetc(fp);

        if (c == ' ' || c == '\n' || c == EOF) {
            insertIntoBinaryTree(&(*tree), word);
            memset(word, 0, 15);
            i = 0;
        } else {
            word[i] = c;
            ++i;
        }
    }
}

int insertIntoBinaryTree(bTree **tree, char *w) {
    bTree *new, *left, *right;

    if ((*tree) == NULL) {
        new = (bTree *) malloc(sizeof(bTree));
        strcpy(new->word, w);
        //for(int i = 0; i < strlen(w); i++)
        //    new->word[i] = w[i];
        new->occurrence = 0;
        new->left = NULL;
        new->right = NULL;
        //new->b = 0;
        (*tree) = new;
        return 1;
    }

    //verifica se a palavra é igual, independente de letra maiuscula ou minuscula
    if (strcmpi(w, (*tree)->word) == 0 ) {
        printf("Palavra ja existe no texto\nIncrementando sua ocorrencia\n");
        (*tree)->occurrence++;
    }

    if (compareStrings(w, (*tree)->word)) { //novo no 'maior' que no atual, insere a direita
        insertIntoBinaryTree((&(*tree)->right), w);
        //if (response == notInserted || response == error)
        //    return response;

        //if (response == inserted) {

        //}
    } else {
        insertIntoBinaryTree((&(*tree)->left), w);
    }

}

int printTree(bTree *tree) {
    bTree *temp;
    temp = tree;

    if (temp == NULL)
        return 0;
    else {
        printf("Word: %s\tOccurrences: %d\n", tree->word, tree->occurrence);
        return printTree(temp);
    }
}

int compareStrings(char w1[], char w2[]) {
    int len1 = strlen(w1);
    int len2 = strlen(w2);

    for (int i = 0; i < (len1 > len2) ? len1 : len2; i++) { //verifica qual a maior palavra para percorrer o loop
        if (w1[i] > w2[i])
            return 1;
        else if(w1[i] < w2[i])
            return 2;
    }
}

