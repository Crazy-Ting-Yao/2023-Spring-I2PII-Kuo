#include <assert.h>
#include <iostream>
#include <string>
struct Node {
    Node *prev;
    Node *next;
    int val;
    int tag;
};

class KuoYangPresent {
   public:
    KuoYangPresent(int k);
    ~KuoYangPresent();
    void Push(int x);
    void Pop();
    void Reverse();
    void ProgrammingTanoshi();
    void KuoYangTeTe();
    void PrintList();

   private:
    Node *head, *mid, *tail;
    int sz, k;
    int now;
    bool reverse;
};

using namespace std;

int n, k, q;

int main() {
    cin >> n >> k >> q;
    assert(k <= 4000);
    KuoYangPresent present = KuoYangPresent(k);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        assert(x <= 10000);
        present.Push(x);
    }
    while (q--) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            assert(x <= 10000);
            present.Push(x);
        } else if (op == "pop") {
            present.Pop();
        } else if (op == "reverse") {
            present.Reverse();
        } else {
            cin >> op;
            present.ProgrammingTanoshi();
        }
    }
    present.KuoYangTeTe();
    present.PrintList();
}

KuoYangPresent::KuoYangPresent(int k) {
    head = mid = tail = NULL;
    sz = 0;
    this->k = k;
    reverse = false;
}
void KuoYangPresent::Push(int x) {
    sz++;
    if(!head){
        head = tail = mid = new Node;
        head->next = head->prev = NULL;
        head->val = x;
        head->tag=0;
        sz = 1;
    }
    else{
        if(!reverse){
            tail->next = new Node;
            tail->next->prev = tail;
            tail = tail->next;
            tail->next = NULL;
            tail->val = x;
            tail->tag=0;
            if(sz&1){
                mid = mid->next;
            }
        }
        else{
            tail->prev = new Node;
            tail->prev->next = tail;
            tail = tail->prev;
            tail->prev = NULL;
            tail->val = x;
            tail->tag=0;
            if(!(sz&1)){
                mid = mid->prev;
            }
        }
    }
}
void KuoYangPresent::Pop() {
    if(sz==1){
        delete head;
        sz--;
        head = tail = mid = NULL;
    }
    else{
        Node* temp = mid->prev;
        mid->next->prev = mid->prev;
        mid->prev->next = mid->next;
        delete mid;
        mid = temp;
        sz--;
    }
}
void KuoYangPresent::Reverse() {
    Node* temp = head;
    head = tail;
    tail = temp;
    reverse = (reverse) ? false:true;
}
void KuoYangPresent::ProgrammingTanoshi() {
    head->tag = tail->tag = 1;
}
void KuoYangPresent::KuoYangTeTe() {
    if(reverse){
        Node* front = head;
        Node* back = tail;
        while(front!=NULL&&!front->tag){
            front = front->prev;
        }
        if(front==NULL) return;
        while(!back->tag){
            back = back->next;
        }
        while(back!=front){
            back->val%=k;
            back = back->next;
        }
        front->val%=k;
    }
    else{
        Node* front = head;
        Node* back = tail;
        while(front!=NULL&&!front->tag){
            front = front->next;
        }
        if(front==NULL) return;
        while(!back->tag){
            back = back->prev;
        }
        while(back!=front){
            front->val%=k;
            front = front->next;
        }
        front->val%=k;
    }
}
void KuoYangPresent::PrintList() {
    cout<<head->val<<" ";
    if(reverse){
        Node* temp = head->prev;
        while(temp){
            cout<<temp->val<<" ";
            temp = temp->prev;
        }
    }
    else{
        Node* temp = head->next;
        while(temp){
            cout<<temp->val<<" ";
            temp = temp->next;
        }
    }
    cout<<endl;
}

KuoYangPresent::~KuoYangPresent(){
    Node* temp = (reverse)?tail:head;
    while(temp){
        Node* del = temp;
        temp = temp->next;
        delete del;
    }
}