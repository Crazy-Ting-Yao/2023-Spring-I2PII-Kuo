#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int val;
    struct _node *next;
} node;

node *merge_linked_list(node *, node *);

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        node *lhs = malloc(sizeof(node)), *rhs, *cur = lhs;
        while (n--)
        {
            scanf("%d", &(cur->val));
            if (n)
                cur = cur->next = malloc(sizeof(node));
            else
                cur->next = NULL;
        }
        rhs = cur = malloc(sizeof(node));
        while (m--)
        {
            scanf("%d", &(cur->val));
            if (m)
                cur = cur->next = malloc(sizeof(node));
            else
                cur->next = NULL;
        }
        lhs = merge_linked_list(lhs, rhs);
        for (cur = lhs; cur; cur = cur->next)
            printf("%d%c", cur->val, " \n"[!cur->next]);
        while (lhs)
        {
            node *tmp = lhs;
            lhs = lhs->next;
            free(tmp);
        }
    }
    return 0;
}

node *merge_linked_list(node *l, node *r){
    node* dummy_head = malloc(sizeof(node));
    node* current = dummy_head;
    node* current_l = l;
    node* current_r = r;
    while (current_l&&current_r){
        if(current_l->val>current_r->val){
            current->next = current_r;
            current = current->next;
            current_r = current_r->next;
        }
        else{
            current->next = current_l;
            current = current->next;
            current_l = current_l->next;
        }
    }
    if(current_l) current->next = current_l;
    else current->next = current_r;
    node* head = dummy_head->next;
    free(dummy_head);
    return head;
}