#ifndef __double_matrix_h_
#define __double_matrix_h_
#include"matrix.h"
#include<iostream>
class double_matrix
{
    friend ostream& operator<<(ostream& os,const double_matrix& matrix);
private:
    int rows;
    int cols;
    double **Matrix;
public:
    explicit double_matrix(const matrix mat);
    double_matrix(const double_matrix& other);
    double_matrix(int row=1,int col=1);
    ~double_matrix();
    double_matrix operator= (const double_matrix& other);
    double_matrix operator* (const double_matrix& obj) const;
    double_matrix operator*= (const double_matrix& obj);
    double* operator[] (int row)const {return Matrix[row];}
    double* operator[] (int row) {return Matrix[row];}
};
double_matrix::double_matrix(int row,int col):rows(row),cols(col)
{
    Matrix = new double* [rows];
    for(int i=0;i<rows;i++)
    {
        Matrix[i] = new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            Matrix[i][j] = 0;
        }
    }
}
double_matrix::double_matrix(const matrix mat):rows(mat.GetRows()),cols(mat.GetCols())
{
    Matrix = new double* [rows];
    for(int i=0;i<rows;i++)
    {
        Matrix[i] = new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            Matrix[i][j] = mat[i][j].value();
        }
    }
}
double_matrix::double_matrix(const double_matrix& other):rows(other.rows),cols(other.cols)
{
    Matrix = new double* [rows];
    for(int i=0;i<rows;i++)
    {
        Matrix[i] = new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            Matrix[i][j] = other[i][j];
        }
    }
}

double_matrix::~double_matrix()
{
    for(int i=0;i<rows;i++)
    {
        delete [] Matrix[i];
    }
    delete [] Matrix;
}

double_matrix double_matrix::operator= (const double_matrix& other)
{
    if(this == &other)
    {
        return *this;
    }
    for(int i=0;i<rows;i++)
    {
        delete [] Matrix[i];
    }
    delete [] Matrix;
    rows = other.rows;
    cols = other.cols;
    Matrix = new double* [rows];
    for(int i=0;i<rows;i++)
    {
        Matrix[i] = new double[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            Matrix[i][j] = other[i][j];
        }
    }
    return *this;
}
double_matrix double_matrix::operator* (const double_matrix& obj) const
{
    if(cols != obj.rows)
    {
        throw runtime_error("ERROR: (double) matrix1 * matrix2 :1.cols!=2.rows");
    }
    double_matrix res(rows,obj.cols);
    for(int i=0;i<res.rows;i++)
    {
        for(int j=0;j<res.cols;j++)
        {
            double value = 0;
            for(int k=0;k<cols;k++)
            {
                value += Matrix[i][k]*obj[k][j];
            }
            res[i][j]=value;
        }
    }
    return res;
}

double_matrix double_matrix::operator*= (const double_matrix& obj)
{
    *this = *this * obj;
    return *this;
}

ostream& operator<<(ostream& os,const double_matrix& thematrix)
{
    for(int i=0;i<thematrix.rows;i++)
    {
        for(int j=0;j<thematrix.cols-1;j++)
        {
            os<<thematrix[i][j]<<"\t";
        }
        os<<thematrix[thematrix.cols-1]<<endl;
    }
    return os;
}
#endif