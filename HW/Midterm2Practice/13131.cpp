#include <iostream>
#include <math.h>
using namespace std;

class MAX_HEAP{
public:
    MAX_HEAP():Count(0){}
    virtual ~MAX_HEAP() {}
    virtual void PUSH(const int &) = 0;
    virtual int MAX() const = 0;
    virtual int POP() = 0;
    int count() const { return Count; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Count;
};

class Array_MAX_HEAP : public MAX_HEAP{
public:
    Array_MAX_HEAP();
    virtual ~Array_MAX_HEAP() {}
    virtual void PUSH(const int &) override; //root node is stored at index 1.
    virtual int MAX() const override;
    virtual int POP() override;

private:
    int array[1025];
};

class ListNode{
    friend class List_MAX_HEAP; //make List_BST a friend

public:
    ListNode(const int &info):value( info ),left( NULL ),right( NULL ), parent(NULL) //constructor
    {
    }//end ListNode constructor

private:
    int value;
    ListNode *left;
    ListNode *right;
    ListNode *parent;
};//end class ListNode

class List_MAX_HEAP : public MAX_HEAP{
public:
    List_MAX_HEAP();
    virtual ~List_MAX_HEAP()
    {
        deleteTree(root);
    }
    virtual void PUSH(const int &) override;
    virtual int MAX() const override;
    virtual int POP() override;

private:
    ListNode *root;
    /* clean a tree.*/
    void deleteTree(ListNode *root);
    ListNode* findparent(int cnt, ListNode* root){//find the parent of node cnt
        //cout << "enter\n"; 

        if(cnt <= 1) return root;
        string s = "";
        int n = 1;
        while(cnt !=0){
            s += cnt%2 +'0';
            cnt/=2;
        }ListNode *now = root;
        for(int i = s.size()-2; i > 0; i--){
            if(s[i] == '0'){
                now = now->left;
                n = n*2;
            }else{
                now = now->right;
                n = n*2+1;
            }
        }
        return now;
    }
};

int main(){
    int n, a;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "A_push"){
            cin >> a;
            A_heap.PUSH(a);
        }else if(s == "L_push"){
            cin >> a;
            B_heap.PUSH(a);
        }
        else if(s == "max"){
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        }
        else if(s == "A_pop"){
            cout << A_heap.POP() << "\n";
        }
        else if(s == "L_pop"){
            cout << B_heap.POP() << "\n";
        }
        else if(s == "size"){
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}
Array_MAX_HEAP::Array_MAX_HEAP(){}
void Array_MAX_HEAP::PUSH(const int &x){
    array[++Count] = x;
    for(int i=Count;i>1;i/=2){
        if(array[i]>array[i/2]){
            swap(array[i], array[i/2]);
        }
        else break;
    }
}
int Array_MAX_HEAP::MAX() const{
    if(Count==0) return -1;
    else return array[1];
}
int Array_MAX_HEAP::POP() {
    if(!Count) return -1;
    int p = array[1];
    Count--;
    if(!Count) return p;
    array[1] = array[Count+1];
    int i = 1;
    while((i*2)<=Count){
        if(i*2==Count){
            if(array[i*2]>array[i]){
                swap(array[i*2],array[i]);
            }
            break;
        }
        int maxpos = (array[i*2]>array[i*2+1])?i*2:i*2+1;
        if(array[i]<array[maxpos]){
            swap(array[i],array[maxpos]);
            i = maxpos;
        }
        else break;
    }
    return p;
}

void List_MAX_HEAP::deleteTree(ListNode *root){
    if(root){
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}
List_MAX_HEAP::List_MAX_HEAP(){}
void List_MAX_HEAP::PUSH(const int &x){
    Count++;
    if(Count==1){
        root = new ListNode(x);
        return;
    }
    ListNode* parent = findparent(Count,root);
    ListNode* temp = new ListNode(x);
    temp->parent = parent;
    if(Count&1) parent->right = temp;
    else parent->left = temp;
    while(temp->parent){
        if(temp->value>temp->parent->value){
            swap(temp->value,temp->parent->value);
            temp = temp->parent;
        }
        else break;
    }
}
int List_MAX_HEAP::MAX() const{
    if(!Count) return -1;
    else return root->value;
}
int List_MAX_HEAP::POP(){
    if(!Count) return -1;
    int r = root->value;
    if(Count==1){
        delete root;
        root=NULL;
        Count=0;
        return r;
    }
    ListNode* parent = findparent(Count, root);
    if(Count&1){
        root->value = parent->right->value;
        delete parent->right;
        parent->right = NULL;
    }
    else{
        root->value = parent->left->value;
        delete parent->left;
        parent->left = NULL;
    }
    Count--;
    ListNode* cur = root;
    while(cur->left){
        if(!cur->right){
            if(cur->left->value>cur->value){
                swap(cur->left->value,cur->value);
            }
            break;
        }
        ListNode* maxpos = (cur->left->value>cur->right->value)?cur->left:cur->right;
        if(maxpos->value>cur->value){
            swap(maxpos->value,cur->value);
            cur = maxpos;
        }
        else break;
    }
    return r;
}