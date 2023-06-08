#include<iostream>
#include<set>

int main(){
    std::multiset<int> mm;
    int t;
    std::cin>>t;
    while(t--){
        int k;
        std::cin>>k;
        mm.insert(k);
    }
    unsigned counter = 0;
    while (!mm.empty()){
        int n = *mm.begin();
        mm.erase(mm.begin());
        std::multiset<int>::iterator it = mm.find(++n);
        while(it!=mm.end()){
            mm.erase(it);
            it = mm.find(++n);
        }
        counter++;
    }
    std::cout<<counter<<std::endl;
}