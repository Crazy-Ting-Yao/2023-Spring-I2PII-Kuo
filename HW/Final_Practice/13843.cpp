#include<iostream>
#include<map>
int main(){
    int t;
    std::cin>>t;
    while(t--){
        int n, k, count = 0;
        long long total = 0;
        std::cin>>n>>k;
        std::map<long long, unsigned> m;
        for(int i=0;i<n;i++){
            int a;
            std::cin>>a;
            total+=a;
            if(total==k) count++;
            if(m.find(total-k)!=m.end()) count+=m.at(total-k);
            if(m.find(total)!=m.end()) m.at(total)++;
            else m.insert(std::make_pair(total,1));
        }
        std::cout<<count<<std::endl;
    }
}