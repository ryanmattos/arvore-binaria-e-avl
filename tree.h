//
// Created by Ryan on 06/12/2020.
//

#ifndef TREE_H
#define TREE_H
#define inserted 1
#define notInserted 0
#define error -1

typedef struct binary{
    int occurrence;
    struct binary *left;
    struct binary *right;
    char word[15];
} bTree; //binary Tree;

typedef struct avl{
    int b;
    int occurrence;
    struct avl *left;
    struct avl *right;
    char word[15];
} aTree; //AVL Tree

void readFile(bTree **tree, aTree **avl, char *fn);

int insertIntoBinaryTree(bTree **tree, char *w);

int insertIntoAvlTree(aTree **tree, char *w);

void rotateRight (aTree **tree);

void rotateLeft (aTree **tree);

void rotateRightLeft (aTree **tree);

void rotateLeftRight (aTree **tree);

int printTree(aTree *avl);

int compareStrings(char w1[], char w2[]);

int walkThroughBinaryCost(bTree *tree);

int walkThroughAvlCost(aTree *tree);

int searchOnAvlTree(aTree **tree, char *w);

int searchOnBinaryTree(bTree **tree, char *w);

#endif //TREE_H
