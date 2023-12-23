#ifndef MATRIX_H
#define MATRIX_H
#include"fraction.cpp"
#include<iostream>
class row
{
    private:
    fraction *Row=nullptr;
    int size;
    public:
    explicit row(int s=0):size(s)
    {
        Row=new fraction[size];
    }
    row(const row &other):size(other.size)
    {
        Row=new fraction[size];
        for(int i=0;i<size;++i)
        {
            Row[i]=other.Row[i];
        }
    }
    ~row()
    {
        delete [] Row;
    }


    int GetSize(){return size;};

    row& operator=(const row &other);

    fraction& operator[](int idx) const {return Row[idx];}
    fraction& operator[](int idx) {return Row[idx];}

    row operator + (const row& obj) const;
    row operator - (const row& obj) const;
    row operator * (const fraction& obj) const;
    row operator / (const fraction& obj) const;


    row operator += (const row& obj);
    row operator -= (const row& obj);
    row operator *= (const fraction& obj);
    row operator /= (const fraction& obj);

    row operator -() const;
    row operator +() const;

    bool operator ==(const row& obj) const;

    friend std::ostream& operator<<(std::ostream& os,const row& obj);
    friend std::istream& operator>>(std::istream& in,row& obj);
};
class matrix
{
    
    private:
    row *Matrix=nullptr;
    matrix *T=nullptr;
    int rows;
    int cols;
    public:
    explicit matrix(int r=0,int c=0):rows(r),cols(c)
    {
        Matrix = new row[rows];
        for(int i=0;i<rows;i++)
        {
            Matrix[i]=row(cols);
        }
    }
    matrix(const matrix& other):rows(other.rows),cols(other.cols)
    {
        Matrix = new row[rows];
        for(int i=0;i<rows;i++)
        {
            Matrix[i]=other[i];
        }
    }
    ~matrix()
    {
        if(T!=nullptr)
        {
            T->T=nullptr;
            delete T;
        }
        delete [] Matrix;
        T=nullptr;
        Matrix=nullptr;
    }

    matrix& Trans();
    int GetRows() const;
    int GetCols() const;
    row& operator[](int idx) const {return Matrix[idx];}
    row& operator[](int idx) {return Matrix[idx];}

    matrix& operator=(const matrix& obj);
    matrix operator+(const matrix& obj) const;

    friend std::ostream& operator<<(std::ostream& os,const matrix& obj);
    friend std::istream& operator>>(std::istream& in,matrix& obj);

};
#endif