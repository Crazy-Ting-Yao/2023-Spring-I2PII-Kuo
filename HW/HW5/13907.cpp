#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
using namespace std;
vector<vector<string>> stk;
vector<string> previous;
vector<string> current;
vector<string> home;


void search_path(string path){
    if(path=="-") {
        swap(previous, current); 
        return;
    }
    previous = current;
    if(path[0]=='/') {
        current.clear();
        path.erase(0,1);
    }
    stringstream ss(path);
    path.clear();
    while(getline(ss,path,'/')){
        if(path==".") continue;
        else if(path=="..") {
            if(!current.empty()) 
                current.pop_back();
        }
        else if(path=="~") current = home;
        else current.push_back(path);
    }
}

void cd(string op){
    if(op.size()==2){
        previous = current;
        current = home;
    }
    else{
        op.erase(0,3);
        search_path(op);
    }
}

void pwd(){
    if(current.empty()) {
        cout<<"/";
        cout<<endl;
        return;
    }
    for(auto &it: current){
        cout<<"/"<<it;
    }
    cout<<endl;
}

void popd(){
    if(stk.empty()) cout<< "popd: directory stack empty"<<endl;
    else{
        previous = current;
        current = stk.back();
        stk.pop_back();
    }
}

void dirs(){
    if(current.empty()) cout<<"/";
    else for(auto &it:current) cout<<"/"<<it;
    if(!stk.empty())
    for(auto it = stk.rbegin();it!=stk.rend();it++){
        cout<<" ";
        if(it->empty()) cout<<"/";
        else for(auto &it2 : *it) cout<<"/"<<it2;
    }
    cout<<endl;
}

void pushd(string op){
    if(op.size()==5){
        if(stk.empty()) cout<< "pushd: no other directory"<<endl;
        else{
            previous = current;
            swap(stk.back(),current);
        }
    }
    else{
        op.erase(0,6);
        stk.push_back(current);
        search_path(op);
    }
}

int main(){
    string op;
    previous.push_back("root");
    current.push_back("root");
    home.push_back("root");
    while(getline(cin, op)){
        if(op.substr(0,2)=="cd") cd(op);
        else if(op.substr(0,3)=="pwd") pwd();
        else if(op.substr(0,4)=="popd") popd();
        else if(op.substr(0,4)=="dirs") dirs();
        else if(op.substr(0,5)=="pushd") pushd(op);
        op.clear();
    }
}