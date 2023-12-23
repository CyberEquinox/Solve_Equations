#ifndef MATRIX_CPP
#define MATRIX_CPP
#include"row.cpp"

int matrix::GetRows() const
{
    return rows;
}
int matrix::GetCols() const
{
    return cols;
}

//重载赋值号
matrix& matrix::operator=(const matrix& obj)
{
    if(Matrix!=nullptr)
    {
        delete [] Matrix;
        Matrix=nullptr;
    }
    rows=obj.rows;
    cols=obj.cols;
    Matrix=new row[rows];
    for(int i=0;i<rows;i++)
    {
        Matrix[i]=obj[i];
    }
    return *this;
}

matrix matrix::operator+(const matrix& obj) const
{
    if(cols!=obj.cols||rows!=obj.rows)
    {
        throw std::runtime_error("##Size ERROR in matrix + matrix##");
    }
    matrix res(rows,cols);
    for(int i=0;i<obj.rows;i++)
    {
        res[i]=Matrix[i]+obj[i];
    }
    return res;
}

//转置函数(第一次使用时创造并记录T,多次使用时直接调用T)
matrix& matrix::Trans()
{
    if(T!=nullptr) return *T;
    T = new matrix(cols,rows);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            T->Matrix[i][j]=Matrix[j][i];
        }
    }
    T->T=this;
    return *T;
}

//重载输出流函数
std::ostream& operator<<(std::ostream& os,const matrix& obj)
{
    for(int i=0;i<obj.rows;i++)
    {
        os<<obj[i]<<std::endl;
    }
    return os;
}
//重载输入流函数
std::istream& operator>>(std::istream& in,matrix& obj)
{
    for(int i=0;i<obj.rows;i++)
    {
        in>>obj[i];
    }
    return in;
}

#endif