#include<iostream>
#include"SolveMatrix.h"
#include"matrix.h"
#include"create.h"
#include<fstream>
#include<vector>
using namespace std;
int main()
{
    ofstream file("out.txt");
    matrix Equations(13,13);
    cout<<"Input your ID(12 numbers)##Please separate them with spaces##:";
    int ID[12]={};
    for(int i=0;i<12;i++)
    {
        cin>>ID[i];
    }
    generateMatrix(ID,Equations,12);
    SolveMatrix Solve(Equations);
    Solve.SolveEquations(file);
    double_matrix A(Equations+Equations.Trans());
    vector<double> eigenvalues=jacobi_rotation(A,0.1);
    file<<"Eigenvalues are:"<<endl;
    int nege=0,posi=0;
    for(double eigen:eigenvalues)
    {
        file<<eigen<<"\t";
        if(eigen>0)
        {
            posi++;
        }else if(eigen<0)
        {
            nege++;
        }
    }
    file << "\nPositive inertia index:"<<posi<<"\tNegative inertia index:"<<nege;
    file.close();
    cout<<"Output in file : \"./out.txt\"\n";
    system("pause");
    return 0;
}