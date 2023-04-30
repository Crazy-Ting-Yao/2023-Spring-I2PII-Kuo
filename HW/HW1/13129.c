#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node* createList(int n);
void solveJosephus(int n, int k);

int main(){

    int n, k;

    while(scanf("%d%d", &n, &k)!=EOF){
        head = createList(n);
        solveJosephus(n, k);
        head->prev->next = NULL;
        while(head){
            //printf("%d\n",head->number);
            Node* tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    return 0;
}
Node* createList(int n){
    Node* current = malloc(sizeof(Node));
    current->number = 1;
    Node* start = current;
    for(int i=2;i<=n;i++){
        current->next = malloc(sizeof(Node));
        current->next->prev = current;
        current->next->number = i;
        current = current->next;
    }
    current->next = start;
    start->prev = current;
    return start;
}
void solveJosephus(int n, int k){
    Node* p = head;
    Node* Nnext = head;
    while(k--){
        int lucky;
        scanf("%d",&lucky);
        if(lucky%2){
            lucky%=n;
            if(!lucky) lucky = n;
            head = Nnext;
            while(--lucky)
                head = head->next;
            p = head->prev;
            Nnext = head->next;
            p->next = Nnext;
            Nnext->prev = p;
            if(head->number) printf("%d\n",head->number);
            free(head);
            n--;
        }
        else{
            lucky%=n;
            if(!lucky) lucky = n;
            head = p;
            while(--lucky) head = head->prev;
            p = head->prev;
            Nnext = head->next;
            p->next = Nnext;
            Nnext->prev = p;
            printf("%d\n",head->number);
            free(head);
            n--;
        }
    }
    head = Nnext;
    return;
}