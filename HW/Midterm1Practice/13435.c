#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int connections;
    int passed1;
    int passed2;
    int *connected;
}Node;

Node **nodes;
int length;
Node* second_start;
void first_recursion(Node* root,int depth){
    root->passed1 = 1;
    if(root!=nodes[1]&&root->connections==1){
        if(depth>length){
            length = depth;
            second_start = root;
        }
    }
    else{
        for(int i=0;i<root->connections;i++){
            if(!nodes[root->connected[i]]->passed1)
                first_recursion(nodes[root->connected[i]],depth+1);
        }
    }
}
void second_recursion(Node* root,int depth){
    root->passed2 = 1;
    if(root!=second_start&&root->connections==1){
        if(depth>length){
            length = depth;
        }
    }
    else{
        for(int i=0;i<root->connections;i++){
            if(!nodes[root->connected[i]]->passed2)
                second_recursion(nodes[root->connected[i]],depth+1);
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);
    do{
        int n;
        scanf("%d",&n);
        nodes = malloc(sizeof(Node*)*(n+1));
        for(int i=1;i<=n;i++){
            nodes[i] = malloc(sizeof(Node));
            nodes[i]->connections = 0;
            nodes[i]->passed1 = 0;
            nodes[i]->passed2 = 0;
            nodes[i]->connected = NULL;
        }
        for(int i=0;i<n-1;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            nodes[a]->connections++;
            nodes[b]->connections++;
            nodes[a]->connected = realloc(nodes[a]->connected,sizeof(int)*nodes[a]->connections);
            nodes[b]->connected = realloc(nodes[b]->connected,sizeof(int)*nodes[b]->connections);
            nodes[a]->connected[nodes[a]->connections-1] = b;
            nodes[b]->connected[nodes[b]->connections-1] = a;
        }
        length = 0;
        first_recursion(nodes[1],0);
        length = 0;
        second_recursion(second_start,0);
        printf("%d\n",length);
        for(int i=1;i<=n;i++){
            free(nodes[i]->connected);
            free(nodes[i]);
        }
        free(nodes);
    }while(--t);
}
