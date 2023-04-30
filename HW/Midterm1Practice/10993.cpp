#include <iostream>
#include <stdio.h>
#include <string>
class Polynomial
{
public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial
Polynomial::Polynomial(){}
Polynomial::Polynomial(const int power, const int coeff[51]){
    greatestPower = power;
    for(int i=0;i<=greatestPower;i++){
        coefficients[i] = coeff[i];
    }
}
Polynomial Polynomial::add( const Polynomial b ) const{
    Polynomial ans;
    if(greatestPower>b.greatestPower){
        ans.greatestPower = greatestPower;
        for(int i=0;i<=b.greatestPower;i++){
            ans.coefficients[i] = coefficients[i]+b.coefficients[i];
        }
        for(int i=b.greatestPower+1;i<=greatestPower;i++){
            ans.coefficients[i] = coefficients[i];
        }
    }
    else{
        ans.greatestPower = b.greatestPower;
        for(int i=0;i<=greatestPower;i++){
            ans.coefficients[i] = coefficients[i]+b.coefficients[i];
        }
        for(int i=greatestPower+1;i<=b.greatestPower;i++){
            ans.coefficients[i] = b.coefficients[i];
        }
    }
    return ans;
}

Polynomial Polynomial::subtract(Polynomial b) const{
    Polynomial ans;
    if(greatestPower!=b.greatestPower){
        if(greatestPower>b.greatestPower){
            ans.greatestPower = greatestPower;
            for(int i=0;i<=b.greatestPower;i++){
                ans.coefficients[i] = coefficients[i]-b.coefficients[i];
            }
            for(int i=b.greatestPower+1;i<=greatestPower;i++){
                ans.coefficients[i] = coefficients[i];
            }
        }
        else{
            ans.greatestPower = b.greatestPower;
            for(int i=0;i<=greatestPower;i++){
                ans.coefficients[i] = coefficients[i]-b.coefficients[i];
            }
            for(int i=greatestPower+1;i<=b.greatestPower;i++){
                ans.coefficients[i] = -b.coefficients[i];
            }
        }
    }
    else{
        ans.greatestPower = greatestPower;
        while (ans.greatestPower&&coefficients[ans.greatestPower]==b.coefficients[ans.greatestPower]) ans.greatestPower--;
        for(int i=0;i<=ans.greatestPower;i++){
            ans.coefficients[i] = coefficients[i]-b.coefficients[i];
        }
    }
    return ans;
}
Polynomial Polynomial::multiplication(Polynomial b) const{
    Polynomial ans;
    ans.greatestPower = greatestPower+b.greatestPower;
    for(int i=0;i<=ans.greatestPower;i++) ans.coefficients[i]=0;
    for(int i=0;i<=greatestPower;i++){
        for(int j=0;j<=b.greatestPower;j++){
            ans.coefficients[i+j]+=coefficients[i]*b.coefficients[j];
        }
    }
    return ans;
}
void Polynomial::output() const{
    for(int i=greatestPower;i;i--){
        std::cout<<coefficients[i]<<" ";
    }
    std::cout<<coefficients[0];
}
using namespace std;

int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

} // end main