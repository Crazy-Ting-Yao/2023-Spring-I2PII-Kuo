#include<stdio.h>
#include<stdlib.h>
int *arr;
int cmps=0,swaps=0;
void iter_swap(int *a,int *b){
    int c = *a;
    *a = *b;
    *b = c;
}
void bubble_sort(int *begin, int *end)
{
    for (; begin < end; end--){
        int flag = 0;
        for (int *ptr = begin + 1; ptr < end; ptr++){
            cmps++;
            if (*(ptr - 1) > *ptr){
                swaps++;
                flag = 1;
                iter_swap(ptr - 1, ptr);
            }
        }
        if(!flag) return;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    arr = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    bubble_sort(arr,arr+n);
    printf("%d %d\n",cmps,swaps);
    free(arr);
    return 0;
}