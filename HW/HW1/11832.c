#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    int num;
    struct node* next;
}Node;
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    Node* head =malloc(sizeof(Node));
    Node* tail = head;
    scanf("%d",&head->num);
    head->next = NULL;
    for(int i=1;i<n;i++){
        tail->next = malloc(sizeof(Node));
        tail = tail->next;
        tail->next = NULL;
        scanf("%d",&tail->num);
    }
    char op[4];
    while(m--){
        scanf("%s",op);
        if(!strcmp(op,"ADD")){
            Node* new = malloc(sizeof(Node));
            int id;
            scanf("%d %d",&id,&new->num);
            if(id==0){
                new->next = head;
                head = new;
                continue;
            }
            Node* put = head;
            while(--id) put = put->next;
            new->next = put->next;
            put->next = new;
        }
        else if(!strcmp(op,"CUT")){
            int a,b;
            scanf("%d %d",&a,&b);
            if(!a) continue;
            a--;
            Node* one_before_start=head;
            Node* end;
            while(a--) one_before_start = one_before_start->next;
            end = one_before_start;
            while(b--) end = end->next;
            Node* start = one_before_start->next;
            one_before_start->next = end->next;
            end ->next = head;
            head = start;
        }
    }
    tail = head;
    while(tail){
        printf("%d\n",tail->num);
        Node* tmp = tail;
        tail = tail->next;
        free(tmp);
    }
}