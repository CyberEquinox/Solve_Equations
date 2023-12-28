#ifndef __double_matrix_h_
#define __double_matrix_h_
#include"matrix.h"
#include<iostream>
#include <vector>
#include <cmath> // 对于数学函数
#include <limits> // 对于数值限制
class double_matrix
{
    friend vector<double> jacobi_rotation(double_matrix& A, double tolerance);
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
    double_matrix Trans()const;
    int size()
    {
        if(rows!=cols)
        {
            throw runtime_error("ERROR: in size(): rows!=cols");
        }
        return rows;
    }
    static double_matrix Identity(int size)
    {
        double_matrix I(size,size);
        for(int i=0;i<size;i++)
        {
            I[i][i] = 1;
        }
        return I;
    }
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

double_matrix double_matrix::Trans()const
{
    double_matrix res(cols,rows);
    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<rows;j++)
        {
            res[i][j]=Matrix[j][i];
        }
    }
    return res;
}

vector<double> jacobi_rotation(double_matrix& A, double tolerance) {
    int n = A.size(); // 假设A是方阵，且double_matrix.size()返回矩阵的大小
    double_matrix J(n, n); // 旋转矩阵
    double_matrix A_prime = A; // A的副本，用于迭代

    while (true) {
        int p, q;
        double max_val = 0;

        // 找到最大的非对角元素
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(A_prime[i][j]) > max_val) {
                    max_val = abs(A_prime[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        // 检查是否达到了收敛条件
        if (max_val < tolerance) {
            break;
        }

        // 计算旋转角度theta
        double theta = 0.5 * atan2(2 * A_prime[p][q], A_prime[q][q] - A_prime[p][p]);

        // 构造旋转矩阵J
        J = double_matrix::Identity(n); // 假设double_matrix有一个创建单位矩阵的静态方法
        J[p][p] = cos(theta);
        J[q][q] = cos(theta);
        J[p][q] = -sin(theta);
        J[q][p] = sin(theta);

        // 应用旋转矩阵到A_prime
        A_prime = J.Trans() * A_prime * J;
    }

    // 返回对角线元素作为特征值
    std::vector<double> eigenvalues(n);
    for (int i = 0; i < n; ++i) {
        eigenvalues[i] = A_prime[i][i];
    }
    return eigenvalues;
}

#endif