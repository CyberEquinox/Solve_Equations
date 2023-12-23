#include<iostream>
#include"SolveMatrix.h"
#include"matrix.cpp"
#include"create.h"
#include<fstream>
using namespace std;
int main()
{
    ofstream file("out.txt");
    matrix Equations(13,13);
    int ID[]={5,2,3,0,3,1,9,1,0,0,1,8};
    generateMatrix(ID,Equations,12);
    SolveMatrix Solve(Equations);
    Solve.SolveEquations(file,12);
    file.close();
    return 0;
}