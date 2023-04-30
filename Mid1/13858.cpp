#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
//13858
class Node{
    public:
        int val;
        vector<int> connects;
        vector<long long> weights;
};

Node* start_node;
Node* end_node;
Node* nodes;
long long max_weight,ans;
int n, *passed;
void DFS(Node* current, long long weight){
    passed[current->val] = 1;
    if(current->connects.size()==1 && current!=start_node){
        if(weight>max_weight){
            max_weight = weight;
            end_node = current;
        }
        return;
    }
    passed[current->val] = 1;
    for(int i=0;i<current->connects.size();i++){
        if(!passed[current->connects[i]]){
            DFS(&nodes[current->connects[i]],weight+current->weights[i]);
        }
    }
}
int DFS2(Node* current){
    passed[current->val] = 1;
    if(current->connects.size()==1 && current!=start_node){
        if(current==end_node) return 1;
        else return 0;
    }
    passed[current->val] = 1;
    for(int i=0;i<current->connects.size();i++){
        if(!passed[current->connects[i]]){
            if(DFS2(&nodes[current->connects[i]])){
                ans-=current->weights[i];
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    cin>>n;
    nodes = new Node[n];
    passed = new int[n];
    for(int i=0;i<n;i++) nodes[i].val = i;
    memset(passed,0,sizeof(int)*n);
    for(int i=1;i<n;i++){
        int a,b;
        long long weight;
        cin>>a>>b>>weight;
        nodes[a].connects.push_back(b);
        nodes[a].weights.push_back(weight);
        nodes[b].connects.push_back(a);
        nodes[b].weights.push_back(weight);
        ans+=(weight*2);
    }
    max_weight = 0;
    start_node = &nodes[0];
    DFS(start_node,0);
    start_node = end_node;
    end_node = NULL;
    max_weight = 0;
    memset(passed,0,sizeof(int)*n);
    DFS(start_node,0);
    memset(passed,0,sizeof(int)*n);
    DFS2(start_node);
    cout<<ans<<endl;
    delete[] nodes;
    delete[] passed;
    return 0;
}