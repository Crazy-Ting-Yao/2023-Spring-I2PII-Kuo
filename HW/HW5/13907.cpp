#include<iostream>
#include<vector>
#include<utility>
#include<cstdio>
using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
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
                    while(!op.empty()){
                        string s;
                        if(op.find('/')!=op.npos){
                            s = op.substr(0, op.find('/'));
                            op.erase(0,s.size()+1);
                        }
                        else {
                            s = op;
                            op.clear();
                        } 
                        if(s==".") continue;
                        else if(s=="..") {
                            if(!current.empty()) 
                                current.pop_back();
                        }
                        else if(s=="~") current = home;
                        else current.push_back(s);
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
                else for(auto &it2 : *it){
                    cout<<"/"<<it2;
                }
            }
            cout<<endl;
        }
        else if(op.substr(0,5)=="pushd"){
            if(op.size()==5){
                if(stk.empty()) cout<< "pushd: directory stack empty"<<endl;
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
                    current.clear();
                    if(op[0]=='/') op.erase(0,1);
                    while(!op.empty()){
                        string s;
                        if(op.find('/')!=op.npos){
                            s = op.substr(0, op.find('/'));
                            op.erase(0,s.size()+1);
                        }
                        else {
                            s = op;
                            op.clear();
                        } 
                        if(s==".") continue;
                        else if(s==".."){
                            if(!current.empty()) 
                                current.pop_back();
                        }
                        else if(s=="~") current = home;
                        else current.push_back(s);
                    }
                }
            }
        }
        op.clear();
    }
}