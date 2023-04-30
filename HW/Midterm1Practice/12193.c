#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int val;
    struct node *left, *right;
}Node;
int sum=0,num=0, max=0;
void BuildTree(Node** root,int x){
    if(!(*root)){
        (*root) = malloc(sizeof(Node));
        (*root)->val = x;
        (*root)->right = (*root)->left = NULL;
        return;
    }
    if((*root)->val==x) return;
    if((*root)->val>x) BuildTree(&(*root)->left,x);
    else BuildTree(&(*root)->right,x);
}
void PrintTree(Node* root){
    if(root){
        PrintTree(root->left);
        printf("%d ",root->val);
        PrintTree(root->right);
    }
}
void SumLevel(Node* head, int level, int current_level){
    if(!head) return;
    if(current_level==level){
        sum+=head->val;
        num++;
        return;
    }
    else{
        SumLevel(head->left, level, current_level+1);
        SumLevel(head->right, level, current_level+1);
    }
}
void GetMax(int current, Node* head){
    if(!head){
        if(max<(current-1)) max = current-1;
        return;
    }
    GetMax(current+1, head->right);
    GetMax(current+1, head->left);
}
void FreeTree(Node* head){
    if(head){
        FreeTree(head->left);
        FreeTree(head->right);
        free(head);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    Node* head = NULL;
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        BuildTree(&head, x);
    }
    GetMax(1,head);
    int t;
    scanf("%d",&t);
    while(t--){
        char s[10];
        scanf("%s",s);
        if(!strcmp(s,"P")){
            if(!head)printf("NULL\n");
            else{
                PrintTree(head);
                printf("\n");
            }
        }
        else if(!strcmp(s,"GetMax")){
            printf("%d\n",max);
        }
        else if(!strcmp(s,"AverLevel")){
            int level;
            scanf("%d",&level);
            if(!level) printf("0\n");
            else{
                sum = num = 0;
                SumLevel(head, level, 1);
                if(num) printf("%.3f\n",(float)sum/num);
                else printf("0\n");
            }
        }
        else if(!strcmp(s,"SumLevel")){
            int level;
            scanf("%d",&level);
            if(!level) printf("0\n");
            else{
                sum = num = 0;
                SumLevel(head, level, 1);
                printf("%d\n",sum);
            }
        }
    }
    FreeTree(head);
}