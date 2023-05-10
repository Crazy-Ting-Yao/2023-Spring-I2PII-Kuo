#include <iostream>
#include <string>
struct Node{
    Node *prev;
    Node *next;
    int val;
    int tag;
};

class KuoYangPresent {
public:
	KuoYangPresent(int k);
	void Push(int x);
	void Pop();
	void ProgrammingTanoshi();
	void KuoYangTeTe();
	void PrintList(); 
	
private:
	Node *head, *mid, *tail;
	int sz, k;
};


using namespace std;

int n, k, q;

int main() {
	cin >> n >> k >> q;
	KuoYangPresent present = KuoYangPresent(k);
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		present.Push(x);
	}
	while (q--) {
		string op;
		cin >> op;
		if (op == "push") {
			int x;
			cin >> x;
			present.Push(x);
		}
		else if (op == "pop") {
			present.Pop();
		}
		else {
			cin >> op;
			present.ProgrammingTanoshi();
		}
	}
	present.KuoYangTeTe();
	present.PrintList();
}
KuoYangPresent::KuoYangPresent(int k){
    this->k = k;
    head = mid = tail = nullptr;
    sz=0;
}
void KuoYangPresent::Push(int x){
    if(!head){
        sz=1;
        head = tail = mid = new Node;
        head->next = head->prev = nullptr;
        head->val = x;
        head->tag = 0;
        return;
    }
    sz++;
    tail->next = new Node;
    tail->next->prev = tail;
    tail = tail->next;
    tail->val = x;
    tail->tag = 0;
    tail->next = nullptr;
    if(sz&1) mid = mid->next;
}
void KuoYangPresent::Pop(){
    mid = mid->prev;
    mid->next = mid->next->next;
    delete mid->next->prev;
    mid->next->prev = mid;
    sz--;
    if(!(sz&1)) mid = mid->next;
}
void KuoYangPresent::ProgrammingTanoshi(){
    head->tag = tail->tag = 1;
}
void KuoYangPresent::KuoYangTeTe(){
    Node* start = head;
    while (start){
        if(start->tag) break;
        start = start->next;
    }
    if(!start) return;
    Node* end = tail;
    while (end){
        if(end->tag) break;
        end = end->prev;
    }
    while(start!=end){
        start->val%=k;
        start = start->next;
    }
    start->val%=k;
}
void KuoYangPresent::PrintList(){
    while (head->next){
        std::cout<<head->val<<" ";
        head = head->next;
        delete head->prev;
    }
    std::cout<<head->val<<" "<<std::endl;
    delete head;
}