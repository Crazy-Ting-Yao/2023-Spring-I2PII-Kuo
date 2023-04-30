#include<iostream>
#include<string>
using namespace std;
class special_power{
public:
    int n;
    special_power(int n);
    int fpow(int x);
    int fpow(int x, int m);
    int fpow();
    string fpow(string s);
    string fpow(string s, int m);
};
using namespace std;
int main(){
    int x, n, m;
    string s;
    cin >> x >> n >> m >> s;
    special_power sp(n);
    cout << sp.fpow(x) << "\n";
    cout << sp.fpow(x, m) << "\n";
    cout << sp.fpow() << "\n";
    cout << sp.fpow(s) << "\n";
    cout << sp.fpow(s, m) << "\n";
}
special_power::special_power(int n){
    this->n = n;
}
int special_power::fpow(int x){
    long long ret = 1;
    long long temp = x%880301;
    int tmpn = n;
    for(;tmpn;tmpn>>=1,temp = (temp*temp)%880301){
        if(tmpn&1) ret = (ret*temp)%880301;
    }
    return (int)ret;
}

int special_power::fpow(int x, int m){
    int ret = 1;
    int temp = x%m;
    int tmpn = n;
    for(;tmpn;tmpn>>=1,temp = (temp*temp)%m){
        if(tmpn&1) ret = (ret*temp)%m;
    }
    return ret;
}

int special_power::fpow(){
    int ret = 1;
    int temp = 2;
    int tmpn = n;
    for(;tmpn;tmpn>>=1,temp = (temp*temp)%880301){
        if(tmpn&1) ret = (ret*temp)%880301;
    }
    return ret;
}

string special_power::fpow(string s){
    string ret="";
    for(int i=0;i<s.size();i++){
        char c = s[i];
        ret.append(n,c);
    }
    return ret;
}

string special_power::fpow(string s, int m){
    string ret;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        ret.append(n,c);
        if(ret.size()>=m){
            return ret.substr(0,m);
        }
    }
    return ret;
}