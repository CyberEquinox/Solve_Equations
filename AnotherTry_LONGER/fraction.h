#ifndef FRACTION_H
#define FRACTION_H
#include<iostream>
//如果DISTANCE=0则默认输出，否则以DISTANCE对齐;
extern int DISTANCE;
class fraction{
    friend fraction stringToFraction(const std::string& str);
    friend double operator*(double n,const fraction &obj) {return (n*obj.num/obj.den);}
    friend double operator*=(double n,const fraction &obj) {n=n*obj;return n;}
<<<<<<< HEAD
    friend std::ostream& operator<<(std::ostream& os,const fraction &obj);
    friend std::istream& operator>>(std::istream& is,fraction &obj);
=======
    friend fraction abs(fraction obj) {if(obj.num<0) obj.num=-obj.num; return obj;}
>>>>>>> 19fd565e6fe4fedb0c6a27df09c4a03c6b81f43e
    private:
    __int128_t num;
    __int128_t den;
    void Simplify();
    __int128_t GCD(); 
    public:
    fraction(__int128_t n=0,__int128_t d=1):num(n),den(d)
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

    double value() const
    {
        double res = (num / den);
        return res;
    }
};
#endif