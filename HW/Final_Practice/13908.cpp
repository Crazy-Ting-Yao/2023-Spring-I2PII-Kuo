#include<iostream>
#include<stack>
int main(){
    std::stack<std::pair<int,int>> stk;
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        std::cin>>k;
        while(!stk.empty()){
            if(stk.top().second>k){
                std::cout<<stk.top().first<<" ";
                break;
            }
            stk.pop();
        }
        if(stk.empty()) std::cout<<"0 ";
        stk.push(std::make_pair(i,k));
    }
    std::cout<<std::endl;
}