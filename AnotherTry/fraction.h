#ifndef FRACTION_H
#define FRACTION_H
#include<iostream>
class fraction{
    friend double operator*(double n,const fraction &obj) {return (n*obj.num/obj.den);}
    friend double operator*=(double n,const fraction &obj) {n=n*obj;return n;}
    private:
    long long num;
    long long den;
    void Simplify();
    long long GCD(); 
    public:
    fraction(long long n=0,long long d=1):num(n),den(d)
    {
        this->Simplify();
    }
    
    fraction T() const;

    fraction operator + (const fraction &other) const;
    fraction operator - (const fraction &other) const;
    fraction operator * (const fraction &other) const;
    fraction operator / (const fraction &other) const;
    fraction operator += (const fraction &other);
    fraction operator -= (const fraction &other);
    fraction operator *= (const fraction &other);
    fraction operator /= (const fraction &other);

    fraction operator -() const {return fraction(-num,den);}
    fraction operator +() const {return *this;}

    bool operator == (const fraction &other) const;
    bool operator != (const fraction &other) const;
    bool operator > (const fraction &other) const;
    bool operator < (const fraction &other) const;
    bool operator >= (const fraction &other) const;
    bool operator <= (const fraction &other) const;

    friend std::ostream& operator<<(std::ostream& os,const fraction &obj);
    friend std::istream& operator>>(std::istream& is,fraction &obj);
};
#endif