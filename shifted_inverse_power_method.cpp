/*


Shifted inverse power method

This algoritm uses power method and inverse power method to find
the middle eigenvalue of a given matrix; alpha is a parametr that is approximation to eigenvalue 

discription of algoritm:
en.wikiversity.org/wiki/Shifted_inverse_iteration


example of input.txt 

3 // dimension of a matrix

0 11 -5
-2 17 -7
-4 26 -10

4.2 // alpha


*/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;
typedef vector< vector<double> > Matrix;


void print(Matrix A)
{
    int n = A.size();
    int m = A[0].size();
    for (int i=0;i<n;i++)
    {
        cout << endl;
        for (int j=0;j<m;j++)
            cout << setprecision(8) << A[i][j] << ' ';
    }
    cout << endl;
    cout << endl;
}

void print(vector<double> v)
{
    for (int i=0;i<v.size();i++)
        cout << v[i] << endl;
    cout << endl;
    cout << endl;
}

vector<double> gauss(vector< vector<double> > B, vector<double> b, int n)
{
    int m = n+1;
    vector< vector<double> > A(n, vector<double>(m));

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            A[i][j] = B[i][j];
    }

    for (int i=0;i<n;i++)
        A[i][m-1] = b[i];;

    for (int i=0;i<n;i++)
    {
        double maxCoff = abs(A[i][i]);
        int maxRow = i; 
        for (int k=i+1; k<n; k++)  // найдем наибольший элемент в i столбце
        {
            if (abs(A[k][i]) > maxCoff)
            {
                maxCoff = abs(A[k][i]);
                maxRow = k;
            }
        }

        for (int k=i; k<m;k++) // поменяем местами две строки
        {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }


        for (int k=i+1; k<n; k++) // запускаем прямой ход
        {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<m; j++)
            {
                if (i==j)
                    A[k][j] = 0;
                else
                    A[k][j] += c*A[i][j];
            }
        }
    }

    vector<double> x(n);
    for (int i=n-1; i>=0;i--)
    {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1; k>=0; k--)
            A[k][n] -= A[k][i]*x[i];
    }
    return x;
}


// calculate minor of element A[i][j]
void getMinor(Matrix A, Matrix &temp, int i, int j, int n)
{
    int r = 0, s = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != i && col != j)
            {
                temp[r][s++] = A[row][col];

                if (s == n-1)
                {
                    s = 0;
                    r++;
                }
            }
        }
    }

}

// calculate determinant of Matrix A
double det(Matrix A, int n)
{
    double result = 0;

    if (n==1) return A[0][0];
    
    Matrix minor(n, vector<double>(n,0.0));
    int sign = 1;

    for (int i=0;i<n;i++)
    {
        getMinor(A,minor,0,i,n);
        result += sign * A[0][i] * det(minor,n-1);
        sign = -sign;
    }
    return result;
}

// calculate adjoint matrix of A
void adjoint(Matrix A,Matrix &ADJ, int n) 
{ 
    if (n == 1) 
    { 
        ADJ[0][0] = 1; 
        return; 
    } 
  
    int sign = 1;
    Matrix minor(n,vector<double>(n, 0.0)); 
  
    for (int i=0; i<n; i++) 
    { 
        for (int j=0; j<n; j++) 
        { 
            getMinor(A, minor, i, j, n); 
  
            sign = ((i+j)%2==0)? 1: -1; 
  
            ADJ[j][i] = (sign)*(det(minor, n-1)); 
        } 
    } 
} 

Matrix inverse(Matrix A, int n) 
{ 
    int d = det(A, n); 
    
    Matrix result(n, vector<double>(n,0.0)); 

    Matrix ADJ(n, vector<double>(n,0.0)); 
    adjoint(A, ADJ, n); 
   
    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++) 
            result[i][j] = ADJ[i][j]/d; 
    }
    return result;
}

// calculate norm of vector or matrix
double norm(vector<double> v)
{
    int n = v.size();
    double result = 0.0;
    for (int i=0;i<n;i++)
    {
        if (abs(v[i]) > abs(result)) 
            result = v[i];
    }
    return abs(result);
}


Matrix substract(Matrix A, Matrix B, int n)
{
    Matrix result(n, vector<double>(n,0));
    for (int i=0;i<n;i++)
    {

        for (int j=0;j<n;j++)
        {
            result[i][j] = A[i][j] - B[i][j];
            if (abs(result[i][j]) < 0.001) result[i][j] = 0;
        }
    }
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
                    if (abs(result[i][j]) < 0.001) result[i][j] = 0;
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
            if (abs(result[i][j]) < 0.001) result[i][j] = 0;
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
            if (abs(result[i][j]) < 0.001) result[i][j] = 0;
        }
    }
    return result;
}

// division of vector v by scalar k 
vector<double> divide(vector<double> v,double k,int n)
{
    vector<double> result(n, 0.0);
    for (int i=0;i<n;i++)
    {
        result[i] = v[i]/k;
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


// compute Rayleigh quotient
double Rayleigh(vector<double> y, vector<double> x)
{
    double temp1 = 0.0;
    double temp2 = 0.0;

    for (int i=0;i<x.size();i++)
    {
        temp1 += x[i]*x[i];
        temp2 += x[i]*y[i];
    }

    return temp2/temp1;

}


float shifted_inverse_power_method(Matrix A, double alpha)
{
    int n = A.size();
    Matrix E(n, vector<double>(n,0.0));
    for (int i=0;i<n;i++)
    {
        E[i][i] = 1.0;
    }

    // counter of iterations
    int k = 1;

    // initial vector x
    vector<double> x0(n, 1.0);

    // coefficient of Rayleigh quotient on k and k+1 steps
    double c1, c2;

    Matrix A1 = substract(A, multiply(E, alpha,n),n);

    // until the coefficient c on k step will not equal 
    // to the coefficient of k+1 step 
    while(true)
    {
        vector<double> y0 = gauss(A1,x0,n);
        c1 = Rayleigh(y0,x0);
        vector<double> x1 = divide(y0,norm(y0),n);
        
        cout << "coefficient of Rayleigh quotient on " << k << " iteration" << endl;
        cout << setprecision(8) << c1;
        cout << endl;

        if ((float)c1 == (float)c2) 
            break;

        x0 = x1;
        c2 = c1;
        k++;
    }

    float eigenval = (1/c1) + alpha;
    return eigenval; 


}

int main()
{
    ifstream input("C:\\1\\input.txt");
    int n;
    input >> n;
    
    Matrix A(n, vector<double>(n,0.0));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            input >> A[i][j];
        }
    }


    // coefficient alpha
    double alpha;

    input >> alpha;

    float eig1 = shifted_inverse_power_method(A,alpha);
    cout << "eigenvalue is: " << endl;
    cout << eig1;
}
