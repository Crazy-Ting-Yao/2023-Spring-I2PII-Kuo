#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int val;
    struct _node *next;
} node;

node *partition_linked_list(node *head, int pivot){
    node* bigger = NULL;
    node* end_of_bigger = NULL;
    node* smaller = NULL;
    node* end_of_smaller = NULL;
    node* current = head;
    while(current){
        if(current->val<pivot){
            if(!smaller){
                smaller = current;
                end_of_smaller = current;
            }
            else{
                end_of_smaller->next = current;
                end_of_smaller  = end_of_smaller->next;
            }
        }
        else{
            if(!bigger){
                bigger = current;
                end_of_bigger = current;
            }
            else{
                end_of_bigger->next = current;
                end_of_bigger = end_of_bigger->next;
            }
        }
        current = current->next;
    }
    end_of_bigger->next = NULL;
    if(!smaller) return bigger;
    end_of_smaller->next = bigger;
    return smaller;
}
int main()
{
    int n, pivot;
    while (~scanf("%d%d", &n, &pivot))
    {
        node *head = malloc(sizeof(node)), *cur = head;
        while (n--)
        {
            scanf("%d", &(cur->val));
            if (n)
                cur = cur->next = malloc(sizeof(node));
            else
                cur->next = NULL;
        }
        head = partition_linked_list(head, pivot);
        for (cur = head; cur; cur = cur->next)
            printf("%d%c", cur->val, " \n"[!cur->next]);
        while (head)
        {
            node *tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    return 0;
}
