/*

In numerical linear algebra, a Givens rotation is a rotation in the plane spanned by two coordinates axes. 
perform two iterations of the Givens rotation (note that the Givens rotation algorithm used here differs slightly from above) 
to yield an upper triangular matrix in order to compute the QR decomposition.

*/


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;
typedef vector< vector<double> > Matrix;

// utility functions 

// calculate euclidean norm of vector or matrix
double length(Matrix A, int n)
{
    double result = 0;
    for (int i=0;i<n;i++)
    {
        result += A[i][0]*A[i][0];
    }
    result = sqrt(result);
    return result;
}

// multiplication of Matrix A by Matrix B
Matrix multiply(Matrix A, Matrix B, int n)
{
    Matrix result(n, vector<double>(n,0));
    for (size_t i=0;i<n;i++)
        {
            for (size_t j=0;j<n;j++)
            {
                for (size_t k=0;k<n;k++)
                {
                    result[i][j] += A[i][k]*B[k][j];
                    if (fabs(result[i][j]) < 0.001) result[i][j] = 0;
                }
            }
        }
        return result;
    }

// multiplication of Matrix A by scalar k
Matrix multiply(Matrix A,double k,int n)
{
    Matrix result(n, vector<double>(n,0));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            result[i][j] = k*A[i][j];
            if (fabs(result[i][j]) < 0.001) result[i][j] = 0;
        }
    }
    return result;
}

// division of Matrix A by scalar k 
Matrix divide(Matrix A,double k,int n)
{
    Matrix result(n, vector<double>(n,0));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            result[i][j] = A[i][j]/k;
            if (fabs(result[i][j]) < 0.001) result[i][j] = 0;
        }
    }
    return result;
}


Matrix transpose(Matrix A, int n)
{
    Matrix result(n, vector<double>(n,0.0));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            result[j][i] = A[i][j];
    }
    return result;
}


Matrix Givens(Matrix A, int n, int k, Matrix result)
{
    Matrix a(n,vector<double>(n,0));
    a[0][0] = A[0+k][0+k], a[1][0] = A[1+k][0+k];

    cout << "vector a " << endl;
    print(a,n);

    double r = length(a,n);

    // calculate sin(x) and cos(x)

    cout << a[0][0] << " and " << a[1][0] << endl;

    double t = a[0][0]/a[1][0];
    double c = (1) / sqrt(1 + pow(t,2));
    double s = t*c;

    cout << "tan(x) is " << t << endl;
    cout << "cos(x) is " << c << endl;
    cout << "sin(x) is " << s << endl;

    // define matrix of rotation G
    Matrix G(n,vector<double>(n,0));
    for (int i=0;i<n;i++) G[i][i] = 1;

    G[0+k][0+k] = s, G[0+k][1+k] = c;
    G[1+k][0+k] = -c, G[1+k][1+k] = s;

    cout << k << " G: ";
    print(G,n);

    cout << k << " transpose(G): " << endl;
    print(transpose(G,n),n);
    cout << endl;

    // calculcate A1 = G*A
    Matrix A1(n, vector<double>(n,0));
    A1 = multiply(G, A, n);

    cout << k << " G*A: " << endl;
    print(A1,n);

    if (k==0)
        result = transpose(G,n);
    else
        result = multiply(result, transpose(G,n), n);
    
    cout << "result" << endl;
    print(result,n);

    if (n-2 != k) 
        return Givens(A1,n,k+1,result);
    else
        return result;


}
