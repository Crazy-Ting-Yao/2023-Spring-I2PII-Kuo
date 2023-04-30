#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int val;
    int route_num;
    int* routes;
    struct node* parent;
}Node;
Node** list;
int* p;
int n;
void recursion(int n,int p){
    if(n&&list[n]->route_num==1){
        free(list[n]->routes);
        return;
    }
    for(int i=0;i<list[n]->route_num;i++){
        if(list[n]->routes[i]!=p){
            list[list[n]->routes[i]]->parent = list[n];
            recursion(list[n]->routes[i],n);
        }
    }
    free(list[n]->routes);
}
int main(){
    int q;
    scanf("%d %d",&n,&q);
    list = malloc(sizeof(Node*)*n);
    p = calloc(sizeof(int),n);
    for(int i=0;i<n;i++){
        list[i] = malloc(sizeof(Node));
        list[i]->route_num = 0;
        list[i]->val = i;
        list[i]->parent = NULL;
    }
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        list[a]->routes = realloc(list[a]->routes,sizeof(int)*(++list[a]->route_num));
        list[a]->routes[list[a]->route_num-1] = b;
        list[b]->routes = realloc(list[b]->routes,sizeof(int)*(++list[b]->route_num));
        list[b]->routes[list[b]->route_num-1] = a;
    }
    recursion(0,-1);
    while (q--){
        int a;
        int path[1001];
        int idx=0;
        scanf("%d",&a);
        Node* current = list[a];
        while(current){
            path[idx++] = current->val;
            current = current->parent;
        }
        for(int i=idx-1;i>0;i--){
            printf("%d ",path[i]);
        }
        printf("%d\n",a);
    }
    for(int i=0;i<n;i++){
        free(list[i]);
    }
    free(list);
}