#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Function {
   public:
    static Function* parse(stringstream& ss);
    virtual Function* differential() = 0;
    virtual double eval(double) = 0;
};

using namespace std;
void solve() {
    string tmp;
    getline(cin, tmp);
    stringstream ss(tmp);
    Function* now = Function::parse(ss);
    Function* now2 = now->differential();
    int q;
    cin >> q;
    while (q--) {
        double x;
        cin >> x;
        cout << fixed << setprecision(2) << now->eval(x) << ' ' << now2->eval(x) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}

class Constant : public Function {
   public:
    Constant(double x);
    static Constant* create(double x);
    Function* differential();
    double eval(double d);
    double val;
};

class Arithmetic : public Function {
   public:
    Arithmetic(Function* a, char op, Function* b);
    static Arithmetic* create(Function* a, char op, Function* b);
    Function* differential();
    double eval(double d);
    Function* left;
    Function* right;
    char op;
};

class Variable : public Function {
   public:
    Variable(string s);
    static Variable* create(string s);
    Function* differential();
    double eval(double d);
    string var;
};

class Polynomial : public Function {
   public:
    Polynomial(Function* a, Function* b);
    static Polynomial* create(Function* a, Function* b);
    Function* differential();
    double eval(double d);
    Function* base;
    Function* power;
};

class Sin : public Function {
   public:
    Sin(Function* a);
    static Sin* create(Function* a);
    Function* differential();
    double eval(double d);
    Function* para;
};

class Cos : public Function {
   public:
    Cos(Function* a);
    static Cos* create(Function* a);
    Function* differential();
    double eval(double d);
    Function* para;
};

Function* Function::parse(stringstream& ss) {
    string s;
    ss >> s;
    if (s == "+" || s == "-" || s == "*" || s == "/") {
        Function *a = parse(ss), *b = parse(ss);
        Function* now = Arithmetic::create(a, s[0], b);
        return now;
    } 
    else if (s[0] == 'x') {
        Function* now = Variable::create(s);
        return now;
    } 
    else if (s == "**") {
        Function *a = parse(ss), *b = parse(ss);
        Function* now = Polynomial::create(a, b);
        return now;
    } 
    else if (s == "sin") {
        Function* a = parse(ss);
        Function* now = Sin::create(a);
        return now;
    } 
    else if (s == "cos") {
        Function* a = parse(ss);
        Function* now = Cos::create(a);
        return now;
    } 
    else {
        Function* now = Constant::create(atoi(s.c_str()));
        return now;
    }
}


Constant::Constant(double x) { val = x; }

Constant* Constant::create(double x) { return new Constant(x); }

Function* Constant::differential() { return Constant::create(0); }

double Constant::eval(double d) { return val; }


Arithmetic::Arithmetic(Function* a, char op, Function* b) {
    left = a; right = b; this->op = op;
}

Arithmetic* Arithmetic::create(Function* a, char op, Function* b) {
    return new Arithmetic(a, op, b);
}

Function* Arithmetic::differential() {
    if (op == '+' || op == '-')
        return Arithmetic::create(left->differential(), op, right->differential());
    else if (op == '*') {
        Arithmetic* l = Arithmetic::create(left->differential(), '*', right);
        Arithmetic* r = Arithmetic::create(left, '*', right->differential());
        return Arithmetic::create(l, '+', r);
    } 
    else {
        Arithmetic* denominator = Arithmetic::create(right, '*', right);
        Arithmetic* l = Arithmetic::create(left->differential(), '*', right);
        Arithmetic* r = Arithmetic::create(left, '*', right->differential());
        Arithmetic* numerator = Arithmetic::create(l, '-', r);
        return Arithmetic::create(numerator, '/', denominator);
    }
}

double Arithmetic::eval(double d) {
    switch (op) {
        case '+': return left->eval(d) + right->eval(d);
        case '-': return left->eval(d) - right->eval(d);
        case '*': return left->eval(d) * right->eval(d);
        case '/': return left->eval(d) / right->eval(d);
    }
    return 0;
}


Variable::Variable(string s) { var = s; }

Variable* Variable::create(string s) { return new Variable(s); }

Function* Variable::differential() { return Constant::create(1); }

double Variable::eval(double d) { return d; }


Polynomial::Polynomial(Function* a, Function* b) {
    base = a;
    power = b;
}

Polynomial* Polynomial::create(Function* a, Function* b) {
    return new Polynomial(a, b);
}

Function* Polynomial::differential() {
    Arithmetic* npow = Arithmetic::create(power, '-', Constant::create(1));
    return Arithmetic::create(
        base->differential(), '*',
        Arithmetic::create(power, '*', Polynomial::create(base, npow)));
}

double Polynomial::eval(double d) { return pow(base->eval(d), power->eval(d)); }


Sin::Sin(Function* a) { para = a; }

Sin* Sin::create(Function* a) { return new Sin(a); }

Function* Sin::differential() {
    return Arithmetic::create(para->differential(), '*', Cos::create(para));
}
double Sin::eval(double d) { return sin(para->eval(d)); }


Cos::Cos(Function* a) { para = a; }

Cos* Cos::create(Function* a) { return new Cos(a); }

Function* Cos::differential() {
    return Arithmetic::create(Constant::create(0), '-',Arithmetic::create(para->differential(), '*', Sin::create(para)));
}
double Cos::eval(double d) { return cos(para->eval(d)); }
