#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int val;
    struct node *left, *right;
}Node;
int main(){
    int t;
    scanf("%d",&t);
    do{
        int n;
        scanf("%d",&n);
        Node** arr = malloc(sizeof(Node*)*(n+1));
        for(int i=0;i<=n;i++){
            arr[i] = malloc(sizeof(Node));
            arr[i]->val = i;
            arr[i]->left = arr[i]->right = NULL;
        }
        Node* leftmost = arr[0];
        for(int i=1;i<=n;i++){
            char c;
            scanf(" %c",&c);
            if(c=='L'){
                Node* left = arr[i-1]->left;
                arr[i-1]->left = arr[i];
                arr[i]->left = left;
                arr[i]->right = arr[i-1];
                if(arr[i-1]==leftmost) leftmost = arr[i];
                else left->right = arr[i];
            }
            else{
                Node* right = arr[i-1]->right;
                arr[i-1]->right = arr[i];
                arr[i]->left = arr[i-1];
                arr[i]->right = right;
                if(right) right->left = arr[i];
            }
        }
        while(leftmost){
            Node* tmp = leftmost;
            printf("%d ",leftmost->val);
            leftmost = leftmost->right;
            free(tmp);
        }
        printf("\n");
    }while (--t);
}