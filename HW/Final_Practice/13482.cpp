#include<iostream>
#include<queue>
#include<set>
int main(){
    int t;
    std::cin>>t;
    while(t--){
        int n, max = 0, pos = 0;
        std::cin>>n;
        std::queue<int> q;
        std::set<int> s;
        for(int i=0;i<n;i++){
            int a;
            std::cin>>a;
            q.push(a);
            if(!s.insert(a).second){
                max = std::max(max, i-pos);
                while(q.front()!=a){
                    s.erase(q.front());
                    q.pop();
                    pos++;
                }
                q.pop();
                pos++;
            }
        }
        max = std::max(max, n-pos);
        std::cout<<max<<std::endl;
    }
}