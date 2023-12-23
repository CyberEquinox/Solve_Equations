#ifndef FRACTION_CPP
#define FRACTION_CPP
#include<iostream>
#include<sstream>
#include<string>
#include <stdexcept>
#include<iomanip>
#include"fraction.h"
using namespace std;

int DISTANCE=0;


string int128ToString(__int128_t num) {
    if (num == 0) {
        return "0";
    }

    std::string result;
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    while (num > 0) {
        char digit = '0' + (num % 10);
        result = digit + result;
        num /= 10;
    }

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}

__int128_t stringToInt128(const std::string& str) {
    bool isNegative = false;
    size_t start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }

    __int128_t result = 0;
    for (size_t i = start; i < str.size(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            throw std::invalid_argument("Invalid character in input string");
        }
    }

    if (isNegative) {
        result = -result;
    }

    return result;
}

fraction stringToFraction(const std::string& str) {
    fraction resultFraction;
    size_t slashPos = str.find('/');

    // 如果没有斜杠，整个字符串都是分子
    if (slashPos == std::string::npos) {
        resultFraction.num = stringToInt128(str);
        resultFraction.den = 1;
    } else {
        // 分子是斜杠前的部分
        std::string numStr = str.substr(0, slashPos);
        resultFraction.num = stringToInt128(numStr);

        // 分母是斜杠后的部分
        std::string denStr = str.substr(slashPos + 1);
        if (!denStr.empty()) {
            resultFraction.den = stringToInt128(denStr);
        } else {
            throw std::invalid_argument("Missing denominator after slash");
        }
    }

    resultFraction.Simplify();
    return resultFraction;
}



// 你的代码中应该已经有了 stringToInt128 的实现






inline __int128_t fraction::GCD()
{
    __int128_t a=num,b=den;
    if (a<0) a=-a;
    if(b<0) b=-b;
    while(b != 0){
        __int128_t temp = a % b;
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
    __int128_t temp=GCD();
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
    if(DISTANCE!=0)
    {
        if(obj.den==1)
        {
            string numstr=int128ToString(obj.num);
            os<<right<<setw(DISTANCE)<<numstr<<" "<<left<<setw(DISTANCE)<<"     ";
        }else
        {
            string numstr=int128ToString(obj.num);
            string denstr=int128ToString(obj.den);
            os<<right<<setw(DISTANCE)<<numstr<<"/"<<left<<setw(DISTANCE)<<denstr;
        }
    }else
    {
        if(obj.den==1)
        {
            string numstr=int128ToString(obj.num);
            os<<numstr;
        }else
        {
            string numstr=int128ToString(obj.num);
            string denstr=int128ToString(obj.den);
            os<<numstr<<"/"<<denstr;
        }
    }
    return os;
}
//重载输入流
std::istream& operator>>(std::istream& in,fraction &obj)
{
    char slash;
    string numstr;
    in>>numstr;
    obj=stringToFraction(numstr);
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