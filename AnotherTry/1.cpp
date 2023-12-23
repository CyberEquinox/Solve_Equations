#include<iostream>
#include"SolveMatrix.h"
#include"matrix.cpp"
#include"create.h"
using namespace std;
int main()
{
    matrix Equations(13,13);
    int ID[]={5,2,3,0,3,1,9,1,0,0,1,8};
    generateMatrix(ID,Equations,2);
    SolveMatrix Solve(Equations);
    Solve.SolveEquations();
    return 0;
}