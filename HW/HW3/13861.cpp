#include <iostream>
#include <cstdlib>
#include <string.h>
struct song{
    int num;
    song *pre, *next;
};

void print(song *st, song *en);

class ordering_system{
    private:
        song *head, *tmp1, *tmp2;
    public:
        void initialize();
        void order(int k);
        void play();
        void show();
        void insert(int k);
        void destroy();
};

using namespace std;

void print(song *st, song *en){
    song *now = st;
    while(now != en){
        cout << now -> num << ' ';
        now = now -> next;
    }
    cout << "\n";
}

void solve(){
    int n;
    cin >> n;
    ordering_system os;
    os.initialize();
    while(n--){
        string op;
        int x;
        cin >> op;
        if(op == "order"){
            cin >> x;
            os.order(x);
        }else if(op == "insert"){
            cin >> x;
            os.insert(x);
        }else if(op == "play"){
            os.play();
        }else{
            os.show();
        }
    }
    os.destroy();
}

signed main(){
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--)
        solve();
    return 0;
}

void print2(song *st, song *en){
    song *now = st;
    while(now != en){
        std::cout << now -> num << ' ';
        now = now -> next;
    }
}

song* songs;
char type[1000001];
bool inserted[1000001];
void ordering_system::initialize(){
    songs = new song[1000001];
    for(int i=0;i<1000001;i++){
        type[i]='n';
        songs[i].num = i;
        inserted[i]=false;
    }
    head = new song;
    head->next = head->pre = head;
    tmp1 = new song;
    tmp1->next = tmp1->pre = tmp1;
    tmp2 = new song;
    tmp2->next = tmp2->pre = tmp2;
}

void ordering_system::destroy(){
    delete [] songs;
    delete head;
    delete tmp1;
    delete tmp2;
}

void ordering_system::order(int k){
    type[k] = 'o';
    song* temp = tmp2->pre;
    temp->next = &songs[k];
    songs[k].pre = temp;
    tmp2->pre = &songs[k];
    songs[k].next = tmp2;
}

void ordering_system::insert(int k){
    if(type[k]=='o'||type[k]=='p'){
        song* temp1 = songs[k].pre;
        song* temp2 = songs[k].next;
        temp1->next = temp2;
        temp2->pre = temp1;
        if(inserted[k]){
            tmp1->next->pre = &songs[k];
            songs[k].next = tmp1->next;
            tmp1->next = &songs[k];
            songs[k].pre = tmp1;
        }
        else{
            tmp1->pre->next = &songs[k];
            songs[k].pre = tmp1->pre;
            tmp1->pre = &songs[k];
            songs[k].next = tmp1;
        }
    }
    else if(type[k]=='i'){
        song* temp1 = songs[k].pre;
        song* temp2 = songs[k].next;
        temp1->next = temp2;
        temp2->pre = temp1;
        tmp1->next->pre = &songs[k];
        songs[k].next = tmp1->next;
        tmp1->next = &songs[k];
        songs[k].pre = tmp1;
    }
    else if(type[k]=='n'){
        tmp1->pre->next = &songs[k];
        songs[k].pre = tmp1->pre;
        tmp1->pre = &songs[k];
        songs[k].next = tmp1;
    }
    type[k] = 'i';
    inserted[k] = true;
}

void ordering_system::play(){
    if(tmp1->next == tmp1){
        if(tmp2->next == tmp2){
            std::cout<<"All songs are played.\n";
        }
        else{
            std::cout<<tmp2->next->num<<std::endl;
            song* temp = tmp2->next;
            tmp2->next->next->pre = tmp2;
            tmp2->next = temp->next;
            head->pre->next = temp;
            temp->pre = head->pre;
            head->pre = temp;
            temp->next = head;
            type[temp->num]='p';
        }
    }
    else{
        std::cout<<tmp1->next->num<<std::endl;
        song* temp = tmp1->next;
        tmp1->next->next->pre = tmp1;
        tmp1->next = temp->next;
        head->pre->next = temp;
        temp->pre = head->pre;
        head->pre = temp;
        temp->next = head;
        type[temp->num]='p';
    }
}

void ordering_system::show(){
    print(head->next,head);
    print2(tmp1->next,tmp1);
    print(tmp2->next,tmp2);
}