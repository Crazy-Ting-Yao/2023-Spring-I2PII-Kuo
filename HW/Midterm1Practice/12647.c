#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int edges;
    int *connected;
    short passed1;
    short passed2;
}Node;
Node** nodes;
Node* start;
int maxlen;
void first_recursion(Node* current,int depth){
    current->passed1=1;
    if(current!=nodes[1]&&current->edges==1){
        if(depth>maxlen){
            maxlen = depth;
            start = current;
        }
        return;
    }
    for(int i=0;i<current->edges;i++) 
        if(!nodes[current->connected[i]]->passed1) 
            first_recursion(nodes[current->connected[i]],depth+1);
}
void second_recursion(Node* current, int depth){
    current->passed2=1;
    if(current!=start&&current->edges==1){
        if(maxlen<depth) maxlen = depth;
        return;
    }
    for(int i=0;i<current->edges;i++){
        if(!nodes[current->connected[i]]->passed2) 
            second_recursion(nodes[current->connected[i]],depth+1);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    nodes=(Node**)malloc(sizeof(Node*)*(n+1));
    for(int i=1;i<=n;i++){
        nodes[i]=(Node*)malloc(sizeof(Node));
        nodes[i]->edges=0;
        nodes[i]->connected=NULL;
        nodes[i]->passed1=0;
        nodes[i]->passed2=0;
    }
    for(int i=1;i<n;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        nodes[a]->edges++;
        nodes[b]->edges++;
        nodes[a]->connected=(int*)realloc(nodes[a]->connected,sizeof(int)*nodes[a]->edges);
        nodes[b]->connected=(int*)realloc(nodes[b]->connected,sizeof(int)*nodes[b]->edges);
        nodes[a]->connected[nodes[a]->edges-1]=b;
        nodes[b]->connected[nodes[b]->edges-1]=a;
    }
    first_recursion(nodes[1],0);
    maxlen = 0;
    second_recursion(start, 0);
    printf("%d\n",maxlen);
    for(int i=1;i<=n;i++){
        free(nodes[i]);
    }
    free(nodes);
    return 0;
}