#include <stdio.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void printInfix(Node *root){
    if(root){
        printInfix(root->left);
        printf("%c",root->data);
        if(root->right){
            if(root->right->data=='&'||root->right->data=='|'){
                printf("(");
                printInfix(root->right);
                printf(")");
            }
            else printInfix(root->right);
        }
    }
}