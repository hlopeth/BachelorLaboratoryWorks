#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
class Matrix
{
private:

public:
	double** value;
	double* b;
	int n;

	Matrix(int n, bool fillByZero = false)
	{
		this->n = n;
		value = new double*[n];
		for (int i = 0; i < n; i++)
			value[i] = new double[n];

		b = new double[n];

		if (fillByZero)
		{
			for (int i = 0; i < n; i++, b[i] = 0)
				for (int j = 0; j < n; j++)
					value[i][j] = 0;
		}
	}

	Matrix(const char* fileName)
	{
		std::ifstream fin(fileName);
		fin >> n;
		value = new double*[n];
		for (int i = 0; i < n; i++)
			value[i] = new double[n];

		b = new double[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				fin >> value[i][j];

		for (int i = 0; i < n; i++)
			fin >> b[i];

		fin.close();
	}

	void Print()
	{
		using std::cout;
		using std::endl;
		using std::setprecision;
		using std::ios;
		using std::setw;
		using std::fixed;
		cout.setf(ios::left);
		for (int i = 0; i < n; i++, cout << endl)
			for (int j = 0; j < n; j++)
			{
				if (value[i][j] > 0)
					cout << " ";
				cout << fixed << setprecision(1) << value[i][j] << " ";
			}
		cout.unsetf(ios::left);
	}

	void Delete()
	{
		for (int i = 0; i < n; i++)
			delete[] value[i];
		delete[] value;
		delete[] b;
	}

};
