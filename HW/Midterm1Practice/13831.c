#include<stdio.h>
#include<stdlib.h>
int cmp(const void* pa, const void *pb){
    return *(int*)pa-*(int*)pb;
}
int main(){
    int n;
    scanf("%d",&n);
    int* arr = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr,n,sizeof(int),cmp);
    int pos = arr[(n-1)/2];
    long long distance=0;
    for(int i=0;i<n;i++) distance+=llabs(pos-arr[i]);
    printf("%d %lld\n",pos,distance);
    free(arr);
    return 0;
}