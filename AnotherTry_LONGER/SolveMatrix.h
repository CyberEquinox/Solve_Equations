#ifndef SOLVEMATRIX_H
#define SOLVEMATRIX_H
#include"matrix.cpp"
#include<iostream>
#include<iomanip>
#include"double_matrix.h"
struct coordinate
{
    int x=0;//Row
    int y=0;//Col
    bool operator ==(coordinate & other) {return x==other.x&&y==other.y;}
    bool operator !=(coordinate & other) {return !(*this==other);}
};
coordinate NullCoordinate={-1,-1};
class SolveMatrix
{
private:
    matrix MAT;//待解的矩阵
    matrix Oth_Matrix;
    coordinate *mainptr=nullptr;//主元位置
    int CountOfMain=0;//主元的个数(从1开始)
    void MatSwap(int i,int j);//交换矩阵两行
    coordinate FindMainEle(int StartRow,int StartCol);
    void TurnAColToZero(int StartRow,int Col);
    bool Fist=0;//是否完成第一步
    bool Second=0;//是否完成第二步
    bool Third=0;
    fraction DET=1;//行列式的值
    void Ortho(matrix& max_matrix, ostream& os);
public:
    SolveMatrix(matrix& Oril);
    ~SolveMatrix();
    void FistStep(ostream& os);
    void SecondStep(ostream& os);
    void ThirdStep(ostream& os);
    void SolveEquations(ostream& os,int num);
    void Oth(ostream& os);
};

SolveMatrix::SolveMatrix(matrix& Oril):DET(1),MAT(Oril),Oth_Matrix(Oril)
{
    mainptr=new coordinate[MAT.GetCols()+2];
}
SolveMatrix::~SolveMatrix()
{
    delete [] mainptr;
}
//交换矩阵的两行,同时det*=-1
void SolveMatrix::MatSwap(int i,int j)
{
    if(i==j) return;
    std::swap(MAT[i],MAT[j]);
    DET=-DET;
}
coordinate SolveMatrix::FindMainEle(int StartRow,int StartCol)
{
    int r=StartRow,c=StartCol;
    for(c=StartCol;c<MAT.GetCols()&&c<MAT.GetRows();c++)
    {
        for(r=StartRow;r<MAT.GetRows();r++)
        {
            if(MAT[r][c]!=0)
            {
                MatSwap(r,StartRow);
                mainptr[CountOfMain].x=StartRow;
                mainptr[CountOfMain].y=c;
                CountOfMain++;
                return mainptr[CountOfMain-1];
            }
        }
        DET=0;
    }
    CountOfMain++;
    mainptr[CountOfMain-1]=NullCoordinate;
    return NullCoordinate;
}
void SolveMatrix::TurnAColToZero(int StartRow,int Col)
{
    int CountOfZero=0;
    for(int i=StartRow;i<MAT.GetRows()-CountOfZero;i++)
    {
        if(MAT[i][Col]!=0)
        {
            DET*=MAT[i][Col];
            break;
            //MAT[i]/=MAT[i][Col];
        }else
        {
            CountOfZero++;
            MatSwap(i,MAT.GetRows()-CountOfZero);
            i--;
        }
    }
    for(int i=StartRow+1;i<MAT.GetRows()-CountOfZero;i++)
    {
        MAT[i]-=MAT[StartRow]*(MAT[i][Col]/MAT[StartRow][Col]);
    }
}
void SolveMatrix::FistStep(std::ostream& os)
{
    Fist=1;
    FindMainEle(0,0);
    os<<"Start With:\n"<<MAT<<"####################\n";
    while(mainptr[CountOfMain-1]!=NullCoordinate)
    {
        TurnAColToZero(mainptr[CountOfMain-1].x,mainptr[CountOfMain-1].y);
        FindMainEle(mainptr[CountOfMain-1].x+1,mainptr[CountOfMain-1].y+1);
        os<<MAT<<"####################\n";
        os<<DET<<std::endl;//Debug
    }
    CountOfMain--;
}
void SolveMatrix::SecondStep(std::ostream& os)
{
    if(Fist==false)
    {
        throw std::runtime_error("ERROR:Not Finish FistStep");
    }else
    {
        Second=1;
        for(int i=CountOfMain-1;i>0;i--)
        {
            row &MAINROW=MAT[mainptr[i].x];
            int CurrentCol=mainptr[i].y;
            for(int j=mainptr[i].x-1;j>=0;j--)
            {
                MAT[j]-=MAINROW*(MAT[j][CurrentCol]/MAT[mainptr[i].x][mainptr[i].y]);
            }
            os<<MAT<<"####################\n";
            //os<<DET<<std::endl;//Debug
        }
    }
}
void SolveMatrix::ThirdStep(std::ostream& os)
{
    if(Second==0)
    {
        throw std::runtime_error("ERROR: Not Finish Second Step");
    }
    int CountOfRoot=MAT.GetCols()-CountOfMain;
    if(CountOfRoot==0)
    {
        row ZeroRoot(MAT.GetCols());
        os<<"Only Zero Root:\nX^T = \n";
        os<<"(\t"<<ZeroRoot<<")\n";
        return;
    }
    matrix Roots(CountOfRoot,MAT.GetCols());
    bool NotMain[MAT.GetCols()]={};
    for(int i=0;i<MAT.GetCols();i++)//检测第i列是否是主元列
    {
        NotMain[i]=1;
        for(int j=0;j<MAT.GetCols();j++)
        {
            if(mainptr[j].y==i)
            {
                NotMain[i]=0;
                break;
            }
        }
    }
    for(int i=0,Current_Count=0;i<MAT.GetCols();i++)
    {
        if(NotMain[i])
        {
            for(int j=0;j<MAT.GetRows();j++)
            {
                if(MAT[j][i]!=0)
                {
                    Roots[Current_Count][j]=MAT[j][i]/MAT[mainptr[j].x][mainptr[j].y];
                }
            }
            Roots[Current_Count][i]=-1;
            Current_Count++;
        }
    }
    os<<"For the Equations: Ax=0:\n";
    os<<"The equation has multiple roots\nThe common root is as follows (There t[i] is any value):\nX^T = \n";
    for(int i=0;i<CountOfRoot;i++)
    {
        os<<"t["<<i<<"] * (\t"<<Roots[i]<<")\n";
        if(i!=CountOfRoot-1) os<<"+\n";
    }
}

/*默认为cout输出，如果想要其他输出就给一个ostream参数
默认数字间隔为"\t",如果想要自定义格式化输出就给入num参数一个非0的数值d,分子分母给定d的空间*/
void SolveMatrix::SolveEquations(ostream& os=std::cout,int num=0)
{
    if(num<0)
    {
        std::cout<<"\nERROR : DISTANCE < 0"<<endl;
        return;
    }
    Third = 1;
    int temp=DISTANCE;
    DISTANCE=num;
    os << "Here are the steps to simplify\n";
    FistStep(os);
    SecondStep(os);
    if(MAT.GetCols()==MAT.GetRows())
    {
        os<<"Det = "<<DET<<std::endl;
    }
    os<<"H = \n"<<MAT<<"The steps are as above"<<endl;
    //os<<DET<<endl;//Debug
    ThirdStep(os);
    Oth(os);
    DISTANCE=temp;
}

void SolveMatrix::Oth(ostream& os)
{
    if(CountOfMain == 0)
    {
        os<<"ERROR:No main ele";
        return;
    }
    matrix Max_independence(CountOfMain,Oth_Matrix.GetRows());
    for(int i=0;i<CountOfMain;i++)
    {
        for(int j=0;j<Oth_Matrix.GetRows();j++)
        {
            Max_independence[i][j] = Oth_Matrix[j][mainptr[i].y];
        }
    }
    os<<"Maximal linearly independent subset:"<<std::endl;
    for(int i=0;i<Max_independence.GetRows();i++)
    {
        os << "alpha["<<i+1<<"]=(\t"<<Max_independence[i]<<")"<<endl;
    }
    Ortho(Max_independence,os);
}

void SolveMatrix::Ortho(matrix& max_matrix,ostream& os)
{   
    row max_matrix_abs2s(max_matrix.GetRows());
    max_matrix_abs2s[0] = max_matrix[0].abs_2();
    for(int i=1;i<max_matrix.GetRows();i++)
    {
        row add_row(max_matrix.GetCols());
        for(int j=0;j<i;j++)
        {
            add_row += max_matrix[j] * ((max_matrix[j] * max_matrix[i]) / (max_matrix[j].abs_2()));
        }
        max_matrix[i] -= add_row;
        max_matrix_abs2s[i] = max_matrix[i].abs_2();
    }
    os << "Maximal linearly independent subset after schmidt orthogonalization:" <<endl;
    for(int i = 0; i < max_matrix.GetRows(); i++)
    {
        os << "Beta["<<i+1<<"]=sqrt("<<max_matrix_abs2s[i].T()<<")"<<setw(DISTANCE)<<"*"<<setw(DISTANCE)<<"("<<max_matrix[i]<<")"<<endl;
    }
}


#endif