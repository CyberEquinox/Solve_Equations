#ifndef FRACTION_CPP
#define FRACTION_CPP
#include<iostream>
#include"fraction.h"

inline long long fraction::GCD()
{
    long long a=num,b=den;
    if (a<0) a=-a;
    if(b<0) b=-b;
    while(b != 0){
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

inline void fraction::Simplify()
{
    if(den==0)
    {
        throw std::runtime_error("###Denominator CAN'T be 0!###");
    }
    if(den<0)
    {
        num=-num;
        den=-den;
    }
    if(num==0)
    {
        den=1;
        return;
    }
    long long temp=GCD();
    num/=temp;
    den/=temp;
}

fraction fraction::T() const
{
    if(num==0)
    {
        throw std::runtime_error("ERROR: There is no T for 0");
    }
    return fraction(den,num);
}

//重载输出流
std::ostream& operator<<(std::ostream& os, const fraction& obj)
{
    if(obj.den==1)
    {
        os<<obj.num;
    }else
    {
        os<<obj.num<<"/"<<obj.den;
    }
    return os;
}
//重载输入流
std::istream& operator>>(std::istream& in,fraction &obj)
{
    char slash;
    in>>obj.num;
    if(in.peek()=='/')
    {
        in>>slash>>obj.den;
    }else
    {
        obj.den==1;
    }
    obj.Simplify();
    return in;
}

//重载四则运算
//重载加法
fraction fraction::operator + (const fraction &other) const
{
    fraction res;
    res.num=num*other.den+den*other.num;
    res.den=den*other.den;
    res.Simplify();
    return res;
}
//重载减法
fraction fraction::operator - (const fraction &other) const
{
    return *this+(-other);  
}
//重载乘法
fraction fraction::operator * (const fraction &other) const
{
    fraction res(num*other.num,den*other.den);
    return res;
}
//重载除法
fraction fraction::operator / (const fraction &other) const
{
    return *this * (fraction(other.den,other.num));
}


//重载复合运算
//重载+=
fraction fraction::operator += (const fraction &other)
{
    *this = *this + other;
    return *this;
}
//重载-=
fraction fraction::operator -= (const fraction &other)
{
    *this = *this - other;
    return *this;    
}
//重载*=
fraction fraction::operator *= (const fraction &other)
{
    *this = *this * other;
    return *this; 
}
//重载/=
fraction fraction::operator /= (const fraction &other)
{
    *this = *this / other;
    return *this; 
}


//重载逻辑运算
bool fraction::operator == (const fraction &other) const
{
    return num==other.num&&den==other.den;
}
bool fraction::operator != (const fraction &other) const
{
    return !(*this==other);
}
bool fraction::operator > (const fraction &other) const
{
    return (*this-other).num>0;
}
bool fraction::operator < (const fraction &other) const
{
    return (*this-other).num<0;
}
bool fraction::operator >= (const fraction &other) const
{
    return !(*this<other);
}
bool fraction::operator <= (const fraction &other) const
{
    return !(*this>other);
}
#endif