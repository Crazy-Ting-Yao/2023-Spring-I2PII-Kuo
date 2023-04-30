#include<iostream>
#include<string>
#include<set>
int main(){
    std::string s;
    std::multiset<unsigned int> ms;
    int a, b;
    while (std::cin>>s){
        if(s=="Insert"){
            std::cin>>a;
            ms.insert(a);
        }
        else if(s=="Query"){
            std::cin>>a>>b;
            int i;
            unsigned int val[5];
            for(i=0;i<b;i++){
                std::multiset<unsigned>::iterator it = ms.find(a);
                if(it==ms.end()) it = ms.upper_bound(a);
                if(it==ms.end()) {std::cout<<"-1"<<std::endl; break;}
                val[i] = *it;
                ms.erase(it);
            }
            if(i==b) std::cout<<val[b-1]<<std::endl;
            for(int j=0;j<i;j++){
                ms.insert(val[j]);
            }
        }
    }
    return 0;
}