#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node
{
    int val;
    struct _node *next;
} node;

bool is_palindrome(node *head); // return true value if the linked list is a palindrome, otherwise false

int main()
{
    int n;
    while (~scanf("%d", &n))
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
        putchar(is_palindrome(head) ? 'T' : 'F');
        while (head)
        {
            node *tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    putchar('\n');
    return 0;
}

bool is_palindrome(node *head){
    int c[100001];
    int i;
    for(i=0;head!=NULL;i++){
        c[i] = head->val;
        head = head->next;
    }
    for(int j=0;j<=(i/2);j++){
        if(c[j]!=c[i-j-1]) return false;
    }
    return true;
}