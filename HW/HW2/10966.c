#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum { ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR } TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;
BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
BTNode* EXPR() {
    BTNode* right = FACTOR();
    if (!pos || expr[--pos] == '(') return right;
    BTNode* head = makeNode(expr[pos--]);
    head->right = right;
    head->left = EXPR();
    //return head;
}
BTNode* FACTOR() {
    if (expr[pos] == ')') {
        pos--;
        return EXPR();
    }
    //return makeNode(expr[pos]);
}
BTNode* makeNode(char c) {
    BTNode* node = malloc(sizeof(BTNode));
    node->left = node->right = NULL;
    switch (c) {
        case 'A':
            node->data = ID_A;
            break;
        case 'B':
            node->data = ID_B;
            break;
        case 'C':
            node->data = ID_C;
            break;
        case 'D':
            node->data = ID_D;
            break;
        case '|':
            node->data = OP_OR;
            break;
        case '&':
            node->data = OP_AND;
            break;
    }
    //return node;
}