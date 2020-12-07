//
// Created by Ryan on 06/12/2020.
//

#ifndef TREE_H
#define TREE_H
#define inserted 1
#define notInserted 0
#define error -1

typedef struct binary{
    //int b;
    int occurrence;
    struct binary *left;
    struct binary *right;
    char word[];
} bTree; //binary Tree;

typedef struct avl{
    int b;
    int occurrence;
    struct avl *left;
    struct avl *right;
    char *word;
} aTree; //AVL Tree

void readFile(bTree **tree);

int insertIntoBinaryTree(bTree **tree, char *w);

int printTree(bTree *tree);

int compareStrings(char w1[], char w2[]);

#endif //TREE_H
