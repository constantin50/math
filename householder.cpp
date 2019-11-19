/*
Householder transformation (also known as a Householder reflection or elementary reflector)
is a linear transformation that describes a reflection about a plane or hyperplane containing the origin.
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;
typedef vector< vector<double> > Matrix;

void print(Matrix A, int n)
{
	for (int i=0;i<n;i++)
	{
		cout << endl;
		for (int j=0;j<n;j++)
			cout << A[i][j] << ' ';
	}
	cout << endl;
}

float length(Matrix A, int n)
{
	float result = 0;
	for (int i=0;i<n;i++)
		result += A[i][0]*A[i][0];
	result = sqrt(result);
	return result;
}


// функция вычитания матрицы B из матрицы A 
Matrix substract(Matrix A, Matrix B, int n)
{
	Matrix result(n, vector<double>(n,0));
	for (int i=0;i<n;i++)
	{

		for (int j=0;j<n;j++)
		{
			result[i][j] = A[i][j] - B[i][j];
			if (fabs(result[i][j]) < 0.001) result[i][j] = 0;
		}
	}
	return result;
}

// функция умножения матриц A и B
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

// функция умножения матрицы A на скаляр k 
Matrix multiply(Matrix A,float k,int n)
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

// функция деления матрицы A на скаляр k 
Matrix divide(Matrix A,float k,int n)
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

// метод Гаусса
vector<double> gausse(Matrix A, Matrix b, int n)
{
	// составим расширенную матрицу A|b
	Matrix A1(n, vector<double>(n+1,0));

	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n+1;j++)
		{
			if (j!=n)
				A1[i][j] = A[i][j];
			if (j==n)
				A1[i][j] = b[i][0];
		}
	}

	vector<double> x(n);
	for (int i=n-1; i>=0;i--)
	{
		x[i] = A1[i][n]/A1[i][i];
		if (fabs(x[i]) < 0.00001) x[i] = 0;
		for (int k=i-1; k>=0; k--)
			A1[k][n] -= A1[k][i]*x[i];
	}
	return x;
}


vector<double> programm(Matrix A, Matrix b, int n, int size, int k=0)
{ 

	// рассмотрим подматрицу A
	Matrix A1(n,vector<double>(n,0));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
			A1[i][j] = A[i+k][j+k];
	}

	Matrix b1(n,vector<double>(n,0));
	for (int i=0;i<n;i++)
		b1[i][0] = b[i+k][0];
	

	// рассмотрим первый столбец a матрицы A
	Matrix a(n,vector<double>(n,0));
	for (int i=0;i<n;i++)
		a[i][0] = A[i+k][k];
	


	// проверим первый элемент вектора и вычислим длину вектора 
	float r = length(a,n);
	float element = a[0][0];




	// первый случай: длина не ноль, первый элемент не ноль
	if (r != 0 && element != 0)
	{
		// получим единичный вектор e
		Matrix e(n,vector<double>(n,0));
		e[0][0] = 1;
		// вычислим вектор столбец w1 и вектор-строку w2
		Matrix w1(n,vector<double>(n,0));
		Matrix w2(n,vector<double>(n,0));
		// вычислим знак
		int sgn = -r/abs(r);

		w1 = (substract(a,multiply(e,r*sgn,n),n));
		w1 = divide(w1, length(w1,n), n);
		for (int i=0;i<n;i++)
			w2[0][i] = w1[i][0];

		// вычислим оператор отражения H

		Matrix E(n, vector<double>(n,0));
		for (int i=0;i<n;i++)
			E[i][i] = 1;
			
		Matrix H(n, vector<double>(n,0));
		H = substract(E, multiply(multiply(w1,w2,n), 2, n),n);

		// получим матрицу A1 = H*A
		A1 = multiply(H,A1,n);
		// получим вектор столбец b1 = H*b
		b1 = multiply(H,b1,n);

		// вставим матрицу A1 в A, а b1 - в b;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
				A[i+k][j+k] = A1[i][j];
		}

		for (int i=0;i<n;i++)
			b[i+k][0] = b1[i][0];
		// повторяем процедуру для n-1
		if (n-1 != 1) return programm(A, b, n-1, size, k+1);
	}

	// случай второй: длина не ноль, первый элемент ноль
	if (r != 0 && element == 0)
	{
		// получим единичный вектор e
		Matrix e(n,vector<double>(n,0));
		e[0][0] = 1;

		// вычислим вектор столбец w1 и вектор-строку w2
		Matrix w1(n,vector<double>(n,0));
		Matrix w2(n,vector<double>(n,0));
		w1 = (substract(a,multiply(e,r,n),n));
		w1 = divide(w1, length(w1,n), n);
		for (int i=0;i<n;i++)
			w2[0][i] = w1[i][0];

		// вычислим оператор отражения H
		Matrix E(n, vector<double>(n,0));
		for (int i=0;i<n;i++)
			E[i][i] = 1;
		
		print(multiply(w1,w2,n),n);

		Matrix H(n, vector<double>(n,0));
		H = substract(E, multiply(multiply(w1,w2,n), 2, n),n);

		// получим матрицу A1 = H*A
		A1 = multiply(H,A1,n);
		// получим вектор столбец b1 = H*b
		b1 = multiply(H,b1,n);

		// вставим матрицу A1 в A, а b1 - в b;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
				A[i+k][j+k] = A1[i][j];
		}

		for (int i=0;i<n;i++)
			b[i+k][0] = b1[i][0];

		if (n-1 != 1) return programm(A, b, n-1, size, k+1);
	}

	// случай третий: длина ноль или все элементы - ноль
	if (r == 0)
	{
		
		// вычислим вектор столбец w1 и вектор-строку w2
		Matrix w1(n,vector<double>(n,0));
		Matrix w2(n,vector<double>(n,0));

		// вычислим оператор отражения H
		Matrix E(n, vector<double>(n,0));
		for (int i=0;i<n;i++)
			E[i][i] = 1;

		Matrix H(n, vector<double>(n,0));
		H = substract(E, multiply(multiply(w1,w2,n), 2, n),n);
		
		// получим матрицу A1 = H*A
		A1 = multiply(H,A1,n);
		// получим вектор столбец b1 = H*b
		b1 = multiply(H,b1,n);

		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
				A[i+k][j+k] = A1[i][j];
		}

		for (int i=0;i<n;i++)
			b[i+k][0] = b1[i][0];

		if (n-1 != 1) return programm(A, b, n-1, size, k+1);
	}

	cout << "matrices after transformation:" << endl;
	print(A,size);
	print(b,size);
	cout << endl;

	// применим метод Гаусса
	vector<double> x = gausse(A,b,size);
	return x;
}




int main()
{
	ifstream input("input.txt");
	int n;
	input >> n;


	// читаем исходную матрицу A и вектор-столбец b
	Matrix A(n, vector<double>(n,0));
	Matrix b(n, vector<double>(n,0));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			input >> A[i][j];
		}
	}
	for (int i=0;i<n;i++)
	{
		input >> b[i][0];
	}
	vector<double> x = programm(A,b,n,n);
	cout << "solution:" << endl;
	for (int i=0;i<n;i++)
		cout << setprecision(8) << x[i] << endl;

	return 0;
}
