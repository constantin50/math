/*
classes Vector and Matrix
constantin werner
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Vector
{
private:
	
	int *data;
	int size;

	friend class Matrix;

  void clean()
  {
    delete[] this->data;
  }

	void copy(const Vector& that) 
	{
		this->size = that.size; 
		this->data = new int[this->size];
	}

public:

	// конструктор по-умолчанию, создает вектор размерности ноль
	Vector()
	{
	    size = 0;
	    data = new int[size];
	}
	

	// конструктор 2
	Vector(int size)
	{
		this->size = size;
		data = new int[size];
	}


	// деструктор
	~Vector()
	{ 
	    // динамически удаляем массив, который был выделен ранее
	    this->clean();
	}


	// конструктор копирования
	Vector(const Vector& that) 
	{
		this->copy(that);
	}

	// оператор присваивания
	Vector& operator=(const Vector& that)
	{
		if (this != &that)
		{
			this->clean();
			this->copy(that);
		}
		return *this;
	}

	// оператор для чтения
	int operator[](int index) const 
	{ 
		if (index >= size || index < 0)
		{
			throw out_of_range("index out of range");
		}
		return data[index]; 
	}

	// оператор для записи
	int& operator[](int index) 
	{ 
		if (index >= size || index < 0)
		{
			throw out_of_range("index out of range");
		}
		return data[index]; 
	}

	friend ostream &operator<<(ostream &output, const Vector &v)
	{ 
    for (int i = 0; i < v.size; i++)
		{
			output << v.data[i] << ' ';
		}
        return output;            
    }

};


class Matrix
{
private:
	int n;
	Vector* vectors;

	void clean()
	{
		delete[] vectors;
	}

  void copy(const Matrix& that)
	{
		this->n = that.n;
		this->vectors = new Vector[this->n];
		for (int i=0;i<n;i++)
		{
			this->vectors[i] = that.vectors[i];
		}
	}

public:
	
	// конструктор по-умолничаю, создает матрицу размерности ноль.
	Matrix() 
	{
		n = 0;
		vectors = new Vector[n];
	}

	// конструктор; создает квадратную единичную матрицу размера n
	Matrix(int n)
	{
		this->n = n;
		vectors = new Vector[n];
		for (int i = 0; i < this->n; i++)
		{
			vectors[i].size = n;
			vectors[i].data = new int[n]();
			vectors[i][i] = 1;
		}
	}


	// конструктор диагональной матрицы
	Matrix(int n, int*diag)
	{
		this->n = n;
		vectors = new Vector[n];
		for (int i = 0; i < this->n; i++)
		{
			vectors[i].size = n;
			vectors[i].data = new int[n];
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					vectors[i][j] = diag[i];
				}
				else
				{
					vectors[i][j] = 0;
				}
			}
		}
	}

	// конструктор копий
	Matrix(const Matrix& that)
	{
		this->copy(that);
	}


	// деструктор
	~Matrix()
	{
	    this->clean();
	}


	// взятие i-ой строки
	Vector& operator[](int i) 
	{ 
		if (i >= n || i < 0)
		{
			throw out_of_range("index out of range");
		}
		return vectors[i]; 
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
		{
			throw runtime_error("dimensions of matrices are not equel");
		}
		Matrix result(this->n);
		for (int i = 0; i < this->n; i++)
		{
			for (int j = 0; j<this->n; j++)
			{
				result.vectors[i][j] = this->vectors[i][j] + that.vectors[i][j];
			}
		}
		return result;
	}


	// оператор вычитания
	Matrix operator-(const Matrix& that) const
	{
		if (that.n != this->n)
		{
			throw runtime_error("dimensions of matrices are not equel");
		}
		Matrix result(this->n);
		for (int i = 0; i < this->n; i++)
		{
			for (int j = 0; j<this->n; j++)
			{
				result.vectors[i][j] = this->vectors[i][j] - that.vectors[i][j];
			}
		}
		return result;
	}


	// оператор равенства
	bool operator==(const Matrix& that) const
	{
		if (that.n != this->n)
			return false;
		for (int i = 0; i < this->n; i++)
		{
			for (int j = 0; j<this->n; j++)
			{
				if (this->vectors[i][j] != that.vectors[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}


	// оператор неравенства
	bool operator!=(const Matrix& that) const
	{
		return !(*this == that);
	}


	// оператор умножения
	Matrix operator*(const Matrix& that) const
	{
		if (that.n != this->n)
		{
			throw runtime_error("dimensions of matrices are not equel");
		}
		Matrix result(this->n);
		for (int i = 0; i < this->n; i++)
		{
			for (int j = 0; j<this->n; j++)
			{
				result.vectors[i].data[j] = 0;
				for (int k = 0; k < this->n; k++)
				{
					result.vectors[i][j] += this->vectors[i][k]*that.vectors[k][j];
				}
			}
		}
		return result;
	}

	
	//оператор транспонирования
	Matrix operator!()
	{
		Matrix result(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				result.vectors[i].data[j] = vectors[j].data[i]; 
			}
		}
		return result;
	}


	//оператор взятия минора
	Matrix operator()(const int i, const int j)
	{
		if (i >= n || i < 0)
		{
			throw out_of_range("the first index is out of range");
		}
		if (j >= n || j < 0)
		{
			throw out_of_range("the second index is out of range");
		}
		
		Matrix result(n - 1);

		for (int k = 0; k<n; k++)
		{
			for (int l = 0; l<n; l++)
			{
				if (k != i && l != j)
					result.vectors[i].data[j] = vectors[j].data[i]; 
			}
		}
		return result;
	}


	friend ostream &operator<<(ostream &output, const Matrix &M ) 
	{ 
        for (int i = 0; i < M.n; i++)
		{
			output << M.vectors[i] << endl;
		}
        return output;            
    }


	friend istream& operator>>(istream& in, Matrix &M)
	{
	    for (int j = 0; j < M.n; j++)
	  	{
	  		for (int k = 0; k < M.n; k++)
	  		{
		  		in >> M.vectors[j][k];
	  		}
	  	}
	  	return in;
	}
};


int main()
{
	return 0;
}
