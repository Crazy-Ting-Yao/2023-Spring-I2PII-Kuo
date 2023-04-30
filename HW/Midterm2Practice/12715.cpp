#include <cstdio>
#include <cstring>
#include <cstdlib>
namespace oj {
    class BigInt {
        char* _val;

    public:
        BigInt(char* s);
        ~BigInt();
        BigInt& operator++();
        BigInt operator++(int);
        BigInt& operator--();
        BigInt operator--(int);
        char* to_s();
    };
}  // namespace oj
using namespace oj;

int main() {
    static char s[1024];

    int T;
    std::scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        BigInt B(s);

        int Q;
        std::scanf("%d", &Q);

        while (Q--) {
            char op[5];
            scanf("%s", op);
            if (!strcmp(op, "++B")) std::printf("%s\n", (++B).to_s());
            if (!strcmp(op, "B++")) std::printf("%s\n", (B++).to_s());
            if (!strcmp(op, "--B")) std::printf("%s\n", (--B).to_s());
            if (!strcmp(op, "B--")) std::printf("%s\n", (B--).to_s());
        }
    }

    return 0;
}

oj::BigInt::BigInt(char* s){
    int len = strlen(s);
    _val = (char*)malloc(sizeof(char)*(len+1));
    for(int i=0;i<len;i++){
        _val[i] = s[i];
    }
    _val[len]=0;
}

oj::BigInt::~BigInt(){
    free(_val);
}

oj::BigInt& oj::BigInt::operator++(){
    int len = strlen(_val);
    int flag=0;
    for(int i=len-1;i>=0;i--){
        if(_val[i]!='9'){
            _val[i]++;
            flag=1;
            break;
        }
        else{
            _val[i]='0';
        }
    }
    if(!flag){
        char* temp = (char*)malloc(sizeof(char)*(len+2));
        temp[0] = '1';
        temp[1] = 0;
        strcat(temp, _val);
        free(_val);
        _val = temp;
    }
    return *this;
}

oj::BigInt oj::BigInt::operator++(int){
    BigInt temp(this->_val);
    this->operator++();
    return temp;
}

oj::BigInt& oj::BigInt::operator--(){
    int len = strlen(_val);
    if(len==1){
        if(_val[0]!='0') _val[0]--;
        return *this;
    }
    for(int i=len-1;i>=0;i--){
        if(_val[i]!='0'){
            _val[i]--;
            break;
        }
        else{
            _val[i]='9';
        }
    }
    if(_val[0]=='0'){
        char* temp = (char*)malloc(sizeof(char)*len);
        for(int i=0;i<len-1;i++){
            temp[i] = '9';
        }
        temp[len-1] = 0;
        free(_val);
        _val = temp;
    }
    return *this;
}

oj::BigInt oj::BigInt::operator--(int){
    BigInt temp(this->_val);
    this->operator--();
    return temp;
}

char* oj::BigInt::to_s(){
    return _val;
}