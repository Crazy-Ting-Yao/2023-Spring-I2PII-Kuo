#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int count, total;
} Node;
Node nodes[200001];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        if(k>=(n+1)/2){
            for(int i=0;i<n-1;i++){
                int a,b;
                scanf("%d %d",&a,&b);
            }
            printf("0\n");
            continue;
        }
        int t = n, N = n-1;
        memset(nodes,0,sizeof(Node)*(n+1));
        for(int i=0;i<N;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            nodes[a].count++;
            nodes[b].count++;
            nodes[a].total+=b;
            nodes[b].total+=a;
        }
        int deletes[n];
        while (k--) {
            int id = 0;
            for (int i = 1; i <= n; i++) 
                if (nodes[i].count!=-1&&nodes[i].count <= 1) deletes[id++] = i;
            for (int i = 0; i < id; i++) {
                int del = deletes[i];
                int a = nodes[del].total;
                if(a){
                    nodes[a].count--;
                    nodes[a].total-=del;
                }
                nodes[del].count=-1;
            }
            t -= id;
            if(!t) break;
        }
        printf("%d\n", t);
    }
}