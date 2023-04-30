#include<iostream>
#include<map>

int main(){
    std::map<int, unsigned long long> mm;
    int N;
    std::cin>>N;
    while(N--){
        int op, k, x;
        std::cin>>op;
        std::map<int, unsigned long long>::iterator it;
        switch (op) {
        case 1:
            std::cin>>k>>x;
            it = mm.find(x);
            if(it == mm.end()) mm.insert( std::pair<int, unsigned long long>(x,k));
            else mm[x]+=k;
            break;
        case 2:
            std::cin>>k>>x;
            it = mm.find(x);
            if(it == mm.end()) break;
            if(mm[x]<=k) mm.erase(x);
            else mm[x]-=k;
            break;
        case 3:
            std::cin>>x;
            it = mm.find(x);
            if(it == mm.end()) std::cout<<"0"<<std::endl;
            else std::cout<< mm[x] <<std::endl;
            break;
        case 4:
            if(mm.empty()) std::cout<<"The box is empty."<<std::endl;
            else std::cout<< mm.rbegin()->first <<std::endl;
            break;
        case 5:
            if(mm.empty()) std::cout<<"The box is empty."<<std::endl;
            else std::cout<< mm.begin()->first << std::endl;
            break;
        default:
            break;
        }
    }
}
