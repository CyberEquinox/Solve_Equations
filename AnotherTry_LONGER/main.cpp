#include"SolveMatrix.h"
#include<iostream>
using namespace std;
int main()
{
    cout<<"Solve Equations like:\n\tMatrix(m,n)*X=0\nInput the size of Equations Matrix(m,n):";
    int m=0,n=0;
    cin>>m>>n;
    matrix Equation(m,n);
    cout<<"Input the Equations Matrix("<<m<<","<<n<<"):\n";
    cin>>Equation;
    SolveMatrix Sol(Equation);
    Sol.SolveEquations();
    system("pause");
    return 0;
}