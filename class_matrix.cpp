
/*
classes of Vector and Matrix
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Vector
{
private:

	void rawClean() { delete[] this->data; }
	void rawCopy(const Vector& that) 
	{
		this->size = that.size; 
		this->data = new int[this->size];
	}
public:
	int *data;
	int size;

	// конструктор 1
	Vector ( ) : data(nullptr), size(0) {};

	// конструктор 2
	Vector ( int size )
	{
		this->size = size;
		this->data = new int[size];
	}

	// конструктор 3
	Vector ( int size, int arr[] )
	{
		this->size = size;
		this->data = new int[size];
		for (size_t i=0;i<this->size;i++)
			this->data[i] = arr[i];
	}


	// конструктор копирования
	Vector (const Vector& that)
	{
		this->size = that.size;
		this->data = new int[this->size];
		for (size_t i=0;i<this->size;i++)
			this->data[i] = that.data[i];
	}

	// деструктор
	~Vector() { delete[] this->data; }

	// оператор присваивания
	Vector& operator= (const Vector& that)
	{
		if (this != &that)
		{
			this->rawClean();
			this->rawCopy(that);
		}
		return *this;
	}

	// оператор для чтения
	int operator[](int index) const 
	{ 
		if (index >= this->size || index < 0)
			throw out_of_range("index out of range");
		return this->data[index]; 
	}
	// оператор для записи
	int& operator[](int index) 
	{ 
		if (index >= size || index < 0)
			throw out_of_range("index out of range");
		return this->data[index]; 
	}

	// оператор сложения
	Vector operator+(const Vector& that) const
	{
		Vector result(this->size);
		for (size_t i=0;i<this->size;i++)
			result[i] = (*this)[i] + that[i];
		return result;
	}

	void print()
	{
		for (size_t i=0;i<this->size;i++)
			cout << this->data[i] << ' ';
	}

};


class Matrix
{
private:
	int n;
	Vector* vectors;

	void clean()
	{
		delete[] this->vectors;
	}
	void copy(const Matrix& that)
	{
		this->n = that.n;
		this->vectors = new Vector[this->n];
		for (int i=0;i<n;i++)
		{
			this->vectors[i].size = n;
			this->vectors[i].data = new int[n];
			for (int j=0;j<n;j++)
				this->vectors[i][j] = that.vectors[i][j];
		}
	}

public:
	
	Matrix () { } 

	// конструктор
	Matrix ( int n )
	{
		this->n = n;
		this->vectors = new Vector[n];
		for (size_t i=0;i<this->n;i++)
		{
			this->vectors[i].size = n;
			this->vectors[i].data = new int[n];
			for (int j=0;j<n;j++)
				this->vectors[i][j] = rand()%10;
		}
	}

	// конструктор диагональной матрицы
	Matrix ( int n, int*diag )
	{
		this->n = n;
		this->vectors = new Vector[n];
		for (size_t i=0;i<this->n;i++)
		{
			this->vectors[i].size = n;
			this->vectors[i].data = new int[n];
			for (int j=0;j<n;j++)
			{
				if (i == j)
					this->vectors[i][j] = diag[i];
				else
					this->vectors[i][j] = 0;
			}
		}
	}

	// конструктор копирования
	Matrix(const Matrix& that)
	{
		this->n = that.n;
		this->vectors = new Vector[this->n];
		for (size_t i=0;i<this->n;i++)
		{
			this->vectors[i].size = n;
			this->vectors[i].data = new int[n];
			for (int j=0;j<n;j++)
				this->vectors[i][j] = that.vectors[i][j];
		}
	}


	void print()
	{
		for (size_t i=0;i<this->n;i++)
		{
			this->vectors[i].print();
			cout << endl;
		}
	}


	Vector& operator[](size_t index) 
	{ 
		if (index >= n || index < 0)
			throw out_of_range("index out of range");
		return this->vectors[index]; 
	}


	//оператор присваивания
	Matrix& operator=(const Matrix& that)
	{
		if (this != &that)
		{
			this->clean();
			this->copy(that);
		}
		return *this;
	}


	// оператор сложения
	Matrix operator+(const Matrix& that) const
	{
		if (that.n != this->n)
			throw runtime_error("dimensions of matrices are not equel");
		Matrix result(this->n);
		for (size_t i=0;i<this->n;i++)
		{
			for (size_t j=0;j<this->n;j++)
				result.vectors[i][j] = this->vectors[i][j] + that.vectors[i][j];
		}
		return result;
	}

	// оператор умножения
	Matrix operator*(const Matrix& that) const
	{
		if (that.n != this->n)
			throw runtime_error("dimensions of matrices are not equel");
		Matrix result(this->n);
		for (size_t i=0;i<this->n;i++)
		{
			for (size_t j=0;j<this->n;j++)
			{
				result.vectors[i].data[j] = 0;
				for (size_t k=0;k<this->n;k++)
					result.vectors[i][j] += this->vectors[i][k]*that.vectors[k][j];
			}
		}
		return result;
	}

	//оператор транспонирования
	Matrix transpose()
	{
		Matrix result(this->n);
		for (size_t i=0;i<this->n;i++)
		{
			for (size_t j=0;j<this->n;j++)
			{
				result.vectors[i].data[j] = this->vectors[j].data[i]; 
			}
		}
		return result;
	}

};



int main()
{
	Matrix A(3);
	Matrix B(3);
	Matrix C = A*B;
	C.print();
	
	return 0;
}
