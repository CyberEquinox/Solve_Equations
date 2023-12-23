#ifndef SOLVEMATRIX_H
#define SOLVEMATRIX_H
#include"matrix.cpp"
#include<iostream>
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
    coordinate *mainptr=nullptr;//主元位置
    int CountOfMain=0;//主元的个数(从1开始)
    void MatSwap(int i,int j);//交换矩阵两行
    coordinate FindMainEle(int StartRow,int StartCol);
    void TurnAColToZero(int StartRow,int Col);
    bool Fist=0;//是否完成第一步
    bool Second=0;//是否完成第二步
    double DET=1;//行列式的值
public:
    SolveMatrix(matrix& Oril);
    ~SolveMatrix();
    void FistStep();
    void SecondStep();
    void ThirdStep();
    void SolveEquations();
};

SolveMatrix::SolveMatrix(matrix& Oril):DET(1),MAT(Oril)
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
void SolveMatrix::FistStep()
{
    Fist=1;
    FindMainEle(0,0);
    std::cout<<"Start With:\n"<<MAT<<"####################\n";
    while(mainptr[CountOfMain-1]!=NullCoordinate)
    {
        TurnAColToZero(mainptr[CountOfMain-1].x,mainptr[CountOfMain-1].y);
        FindMainEle(mainptr[CountOfMain-1].x+1,mainptr[CountOfMain-1].y+1);
        std::cout<<MAT<<"####################\n";
        //std::cout<<DET<<std::endl;//Debug
    }
    CountOfMain--;
}
void SolveMatrix::SecondStep()
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
            std::cout<<MAT<<"####################\n";
            //std::cout<<DET<<std::endl;//Debug
        }
    }
}
void SolveMatrix::ThirdStep()
{
    if(Second==0)
    {
        throw std::runtime_error("ERROR: Not Finish Second Step");
    }
    int CountOfRoot=MAT.GetCols()-CountOfMain;
    if(CountOfRoot==0)
    {
        row ZeroRoot(MAT.GetCols());
        std::cout<<"Only Zero Root:\nX^T = \n";
        std::cout<<"(\t"<<ZeroRoot<<")\n";
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
    std::cout<<"The equation has multiple roots\nThe common root is as follows (There t[i] is any value):\nX^T = \n";
    for(int i=0;i<CountOfRoot;i++)
    {
        std::cout<<"t["<<i<<"] * (\t"<<Roots[i]<<")\n";
        if(i!=CountOfRoot-1) std::cout<<"+\n";
    }
}
void SolveMatrix::SolveEquations()
{
    FistStep();
    SecondStep();
    if(MAT.GetCols()==MAT.GetRows())
    {
        std::cout<<"Det = "<<DET<<std::endl;
    }
    //std::cout<<DET<<endl;//Debug
    ThirdStep();
}
#endif