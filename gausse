/*
gausse algorithm for solving linear equations
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;


vector<double> gauss(vector< vector<double> > A, int n, int m)
{
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

double det(vector< vector<double> > A, int n)
{
	vector<double> gauss(vector< vector<double> > A, int n, int m)
{
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

		for (int i=0;i<n;i++)
		{
			cout << endl;
			for (int j=0;j<n;j++)
				cout << A[i][j] << ' ';
		}
	}
}


int main()
{
	ifstream input("C:\\1\\input.txt");
	int n, m;
	double value;
	input >> n, input >> m;
	vector< vector<double> > A(n, vector<double>(m));

	for (int i=0;i<n;i++)
	{
		for (int j=0; j<m; j++)
		{
			input >> value;
			A[i][j] = value; 
		}
	}

	cout << "Matrix A:";
	for (int i=0;i<n;i++)
	{
		cout << endl;
		for (int j=0; j<m-1; j++)
		{
			cout << A[i][j] << " "; 
		}
	}
	cout << endl;
	cout << endl; 
	cout << "Vector b:";

	cout << endl;
	for (int i=0; i<n; i++)
	{
		cout << A[i][m-1] << " "; 
	}

	cout << endl;
	cout << endl;

	cout << "Solution:" << endl;

	vector<double> x = gauss(A, n, m);
	cout.precision(8);
	for (auto &i : x)
		cout << i << ' ';

	return 0;
}
