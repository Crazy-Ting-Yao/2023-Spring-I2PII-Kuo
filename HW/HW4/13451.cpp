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
            std::multiset<unsigned>::iterator it = ms.lower_bound(a);
            if(it==ms.end()) {
                std::cout<<"-1"<<std::endl;
                continue;
            }
            for(int i=1;i<b;i++){
                it++;
                if(it==ms.end()){
                    std::cout<<"-1"<<std::endl;
                    break;
                }
            }                
            if(it!=ms.end()) std::cout<<*it<<std::endl;
        }
    }
    return 0;
}