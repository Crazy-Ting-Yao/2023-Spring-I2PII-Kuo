#include<iostream>
#include<map>
#include<set>
int main(){
    std::map<int, unsigned long long> mp;
    std::map<unsigned long long, std::set<int> > reverse_mp;
    int t, op, x;
    unsigned long long k;
    unsigned long long int max;
    int id = -1;
    std::cin>>t;
    while(t--){
        std::cin>>op;
        switch(op){
            case 1:
                std::cin>>k>>x;
                if(mp.find(x) == mp.end()) {
                    mp.insert(std::pair<int, unsigned long long>(x, k));
                    reverse_mp[k].insert(x);
                }
                else {
                    reverse_mp[mp[x]].erase(x);
                    mp[x] += k;
                    reverse_mp[mp[x]].insert(x);
                }
                if(id!=-1 && (max<mp[x]||(mp[x]==max&&id<x))){
                    max = mp[x];
                    id = x;
                }
                break;
            case 2:
                std::cin>>k>>x;
                if(mp.find(x) == mp.end()) break;
                else {
                    reverse_mp[mp[x]].erase(x);
                    if(mp[x] <= k) {
                        mp.erase(x);
                        if(reverse_mp[mp[x]].empty()) reverse_mp.erase(mp[x]);
                    }
                    else {
                        mp[x] -= k;
                        reverse_mp[mp[x]].insert(x);
                    }
                }
                if(id==x) id=-1;
                break;
            case 3:
                std::cin>>x;
                if(mp.find(x) == mp.end()) std::cout<<0<<std::endl;
                else std::cout<<mp[x]<<std::endl;
                break;
            case 4:
                if(mp.empty()) {
                    std::cout<<"The box is empty."<<std::endl;
                    break;
                }
                std::cout<<mp.rbegin()->first<<std::endl;
                break;
            case 5:
                if(mp.empty()) {
                    std::cout<<"The box is empty."<<std::endl;
                    break;
                }
                std::cout<<mp.begin()->first<<std::endl;
                break;
            case 6:
                if(mp.empty()) {
                    std::cout<<"The box is empty."<<std::endl;
                    break;
                }
                if(id!=-1) std::cout<<id<<" "<<max<<std::endl;
                else std::cout<<*(reverse_mp.rbegin()->second.rbegin())<<" "<<reverse_mp.rbegin()->first<<std::endl;
                break;
        }
    }
}