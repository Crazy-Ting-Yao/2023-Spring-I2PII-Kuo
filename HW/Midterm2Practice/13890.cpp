#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

class Function{
    public:
    static Function *parse(stringstream &ss);
    virtual double eval(double) = 0;
};

class Constant;
class Variable;
class Polynomial;
class Arithmetic;
class Sin;
class Cos;

void solve(){
    string tmp;
    getline(cin, tmp);
    stringstream ss(tmp);
    Function *now = Function::parse(ss);
    int q; cin >> q;
    while(q--){
        double x; cin >> x;
        cout << fixed << setprecision(2) << now -> eval(x) << endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
    return 0;
}

class Constant : public Function{
    public:
        Constant(){ val = 0; }
        Constant(double &d){ val = d; }
        double eval(double d) override{ return val; }
        static Constant* create(double d){
            Constant* r = new Constant(d);
            return r;
        }
    private:
        double val;
};
class Variable : public Function{
    public:
        Variable(){ s = ""; }
        Variable(string &x){ s = x; }
        double eval(double d) override{ return d; }
        static Variable* create(string &s){
            Variable* r = new Variable(s);
            return r;
        }
    private:
        string s;
};
class Polynomial : public Function{
    public:
        Polynomial(){ base = power = NULL; }
        Polynomial(Function *a, Function *b){ base = a; power = b; }
        double eval(double d) override{ return pow(base->eval(d) ,power->eval(d)); }
        static Polynomial* create(Function *a, Function *b){
            Polynomial* r = new Polynomial(a,b);
            return r;
        }
    private:
        Function* base;
        Function* power;    
};
class Arithmetic: public Function{
    public:
        Arithmetic(){ lhs = rhs = NULL; op = 0; }
        Arithmetic(Function *a, char c, Function *b){ lhs = a; rhs = b; op = c; }
        double eval(double d) override{ 
            double a = lhs->eval(d);
            double b = rhs->eval(d);
            switch(op){
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return a / b;
                default: return 0;
            }
        }
        static Arithmetic* create(Function *a, char c, Function *b){
            Arithmetic* r = new Arithmetic(a,c,b);
            return r;
        }
    private:
        Function* lhs;
        Function* rhs;     
        char op;
};
class Sin : public Function{
    public:
        Sin(){ input = NULL; }
        Sin(Function *a){ input = a; }
        double eval(double d) override{ return sin(input->eval(d)); }
        static Sin* create(Function *a){
            Sin* r = new Sin(a);
            return r;
        }
    private:
        Function* input;  
};
class Cos : public Function{
    public:
        Cos(){ input = NULL; }
        Cos(Function *a){ input = a; }
        double eval(double d) override{ return cos(input->eval(d)); }
        static Cos* create(Function *a){
            Cos* r = new Cos(a);
            return r;
        }
    private:
        Function* input;  
};


Function* Function::parse(stringstream &ss){
    string s;
    ss >> s;
    if(s == "+" || s == "-" || s == "*" || s == "/"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Arithmetic::create(a, s[0], b);
        return now;
    }else if(s[0] == 'x'){
        Function *now = Variable::create(s);
        return now;
    }else if(s == "**"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Polynomial::create(a, b);
        return now;
    }else if(s == "sin"){
        Function *a = parse(ss);
        Function *now = Sin::create(a);
        return now;
    }else if(s == "cos"){
        Function *a = parse(ss);
        Function *now = Cos::create(a);
        return now;
    }else{
        Function *now = Constant::create(atoi(s.c_str()));
        return now;
    }
}

