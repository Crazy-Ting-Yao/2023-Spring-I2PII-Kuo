#include<stdio.h>
#include<stdlib.h>
int* arr;
int pos;
int n;
void recursion(int min, int max){
    if(pos==n) return;
    if(arr[pos]>max||arr[pos]<min) return;
    int val = arr[pos++];
    recursion(min,val);
    recursion(val,max);
    printf("%d ",val);
}
int main(){
    scanf("%d",&n);
    arr = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    recursion(0,1e9+1);
    free(arr);
}