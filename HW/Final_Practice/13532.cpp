#include<iostream>
#include<set>
int main(){
    int n;
    std::cin>>n;
    std::set<int> s;
    while(n--){
        int k;
        std::cin>>k;
        if(s.empty()||*(--s.end())<k) s.insert(k);
        else{
            auto it = s.lower_bound(k);
            s.erase(it);
            s.insert(k);
        }
    }
    std::cout<<s.size()<<std::endl;
}