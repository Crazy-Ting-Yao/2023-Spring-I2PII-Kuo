#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
using namespace std;
int main(){
    vector<vector<string>> stk;
    vector<string> previous;
    vector<string> current;
    vector<string> home;
    string op;
    previous.push_back("root");
    current.push_back("root");
    home.push_back("root");
    while(getline(cin, op)){
        if(op.substr(0,2)=="cd"){
            if(op.size()==2){
                previous = current;
                current = home;
            }
            else{
                op.erase(0,3);
                if(op=="-") swap(previous, current);
                else{
                    previous = current;
                    if(op[0]=='/') {
                        current.clear();
                        op.erase(0,1);
                    }
                    stringstream ss(op);
                    op.clear();
                    while(getline(ss,op,'/')){
                        if(op==".") continue;
                        else if(op=="..") {
                            if(!current.empty()) 
                                current.pop_back();
                        }
                        else if(op=="~") current = home;
                        else current.push_back(op);
                    }
                }
            }
        }
        else if(op.substr(0,3)=="pwd"){
            if(current.empty()) cout<<"/";
            else{
                for(auto &it: current){
                    cout<<"/"<<it;
                }
            }
            cout<<endl;
        }
        else if(op.substr(0,4)=="popd"){
            if(stk.empty()) cout<< "popd: directory stack empty"<<endl;
            else{
                previous = current;
                current = stk.back();
                stk.pop_back();
            }
        }
        else if(op.substr(0,4)=="dirs"){
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
        else if(op.substr(0,5)=="pushd"){
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
                if(op=="-") swap(previous, current);
                else{
                    previous = current;
                    if(op[0]=='/') {
                        current.clear();
                        op.erase(0,1);
                    }
                    stringstream ss(op);
                    op.clear();
                    while(getline(ss,op,'/')){
                        if(op==".") continue;
                        else if(op=="..") {
                            if(!current.empty()) 
                                current.pop_back();
                        }
                        else if(op=="~") current = home;
                        else current.push_back(op);
                    }
                }
            }
        }
        op.clear();
    }
}