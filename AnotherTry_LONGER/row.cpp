#ifndef ROW_CPP
#define ROW_CPP
#include"matrix.h"
#include<iostream>
#include<iomanip>

bool row::operator ==(const row& obj) const
{
    if(size!=obj.size)
        return 0;
    else
    {
        for(int i=0;i<size;i++)
        {
            if(Row[i]!=obj[i])
                return 0;
        }
    }
    return 1;
}

row& row::operator=(const row &other)
{
    if(*this==other) return *this;
    if(Row!=nullptr)
    {
        delete [] Row;
        Row=nullptr;
    }
    size=other.size;
    Row=new fraction[size];
    for(int i=0;i<size;i++)
    {
        Row[i]=other.Row[i];
    }
    return *this;
}
//重载输出流函数
std::ostream& operator<<(std::ostream& os,const row& obj)
{
    for(int i=0;i<obj.size;i++)
    {
        os<<obj[i]<<"\t";
    }
    return os;
}
//重载输入流函数
std::istream& operator>>(std::istream& in,row& obj)
{
    for(int i=0;i<obj.size;i++)
    {
        in>>obj[i];
    }
    return in;
}
row row::operator + (const row& obj) const
{
    if(size!=obj.size)
    {
        throw std::runtime_error("ERROR: Different size in row + row!!");
    }
    row res(size);
    for(int i=0;i<size;i++)
    {
        res[i]=Row[i]+obj[i];
    }
    return res;
}
row row::operator - (const row& obj) const
{
    return *this+(-obj);
}
row row::operator * (const fraction& obj) const
{   
    row res(size);
    for(int i=0;i<size;i++)
    {
        res[i]=Row[i]*obj;
    }
    return res;    
}
row row::operator / (const fraction& obj) const
{
    return (*this)*(obj.T());
}


row row::operator += (const row& obj)
{
    return *this=*this+obj;
}
row row::operator -= (const row& obj)
{
    return *this=*this-obj;
}
row row::operator *= (const fraction& obj)
{
    return *this=*this*obj;
}
row row::operator /= (const fraction& obj)
{
    return *this=*this/obj;
}

row row::operator -() const
{
    row res(size);
    for(int i=0;i<size;i++)
    {
        res[i]=-Row[i];
    }
    return res;
}
row row::operator +() const
{
    return *this;
}

fraction row::operator * (const row& obj) const
{
    if(obj.size != size)
    {
        throw std::runtime_error("Size difference in row * row");
    }
    fraction res=0;
    for(int i=0;i<size;i++)
    {
        res += Row[i]*obj[i];
    }
    return res;
}

fraction row::abs_2() const
{
    fraction res=*this * *this; 
    return res;
}

#endif