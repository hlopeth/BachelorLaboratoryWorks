#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
void fillLU(double**, double**, int);
void print(double**, int);
double** mult(double**, double**, int);
double det(double**, int);
double** trans(double**, int, int);
double** init(int, int, bool=false);
void SwapRows(double**, int, int);
void LUP(double**, double**, int*, int);
double* Solve(double**, double*, int);
double** GetInvert(double**, int);
void del(double**, int);
double norm(double**, int);
void printLU(double**, int);
double fractionalError(double** A, double* X, double* b, int n);
bool flag = false;
int main()
{
	ifstream fin("input14.txt");
	int n = 0;
	fin >> n;
	double** A = init(n, n);
	double* b = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fin >> A[i][j];

	for (int i = 0; i < n; i++)
		fin >> b[i];
	cout << "A:" << endl;
	print(A, n);
	double deter = det(A, n);
	cout << "determinant = " << deter << endl;

	double** InvA = GetInvert(A, n);
	cout << "Inverse matrix" << endl;
	print(InvA, n);
	double conditionNumber = norm(A, n) * norm(InvA, n);
	cout << "condition number = " << conditionNumber << endl << endl;

	flag = true;
	double* x = Solve(A, b, n);
	flag = false;
	cout << "x: ";
	for (int i = 0; i < n; i++)
		cout << x[i] << " ";
	cout << endl;
	cout << "fractional error = " << fractionalError(A, x, b, n) <<endl;


	cin.get();
	cin.get();
	return 0;
}
//3 5 1 6 7 9 -4 8 0 4 1 1 1
//3 2 1 3 1 1 1 3 1 1 13 6 8
// 4 -2 3.6 6.7 2.2 -3.2 0.2 -8.0 -2.1 -0.5 9.9 -8.3 4.2 -6.4 -1.9 8.9 -3.8 34.1 -35.2 11.2 1.3
// 4 6.0 -3.1 -9.7 -6.8 4.0 9.4 -5.7 -8.3 8.1 -5.5 -3.8 -8.7 3.0 -9.5 -6.1 2.0 -56.5 -27.5 -49.099999 -26.299999

void fillLU(double** LU, double** A, int n)
{
	LU[0][0] = A[0][0];
	for (int j = 1; j < n; j++)
	{
		LU[j][0] = A[j][0];
		LU[0][j] = A[0][j] / LU[0][0];
	}

	for (int i = 1; i < n; i++)
		for (int j = i; j < n; j++)
		{
			double sum = 0;
			for (int k = 0; k < i; k++)
				sum += LU[j][k] * LU[k][i];
			LU[j][i] = A[j][i] - sum; 
			if (i != j)
			{
				sum = 0;
				for (int k = 0; k < i; k++)
					sum += LU[i][k] * LU[k][j];
				LU[i][j] = (A[i][j] - sum) / LU[i][i];
			}
		}
}

void print(double** M, int n)
{
	cout.setf(ios::left);
	for (int i = 0; i < n; i++, cout << endl)
		for (int j = 0; j < n; j++)
			cout << setw(8) << setprecision(5) << M[i][j] << " ";
	cout.unsetf(ios::left);
}

void printLU(double** LU, int n)
{
	cout.setf(ios::left);
	double** L = init(n, n, true);
	double** U = init(n, n, true);
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			if (i <= j)
				L[j][i] = LU[i][j];
			if (i > j)
				U[j][i] = LU[i][j];
			if (i == j)
				U[i][i] = 1;
		}
	cout << "L" << endl;
	print(L, n);
	cout << "U" << endl;
	print(U, n);
	del(L, n);
	del(U, n);
	cout.unsetf(ios::left);
}

double** mult(double** A, double** B, int n)
{
	double** C = new double*[n];
	for (int i = 0; i < n; i++)
		C[i] = new double[n];
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			double sum = 0;
			for (int k = 0; k < n; k++)
				sum += A[i][k] * B[k][j];
			C[i][j] = sum;
		}
	return C;
}


double** trans(double** A, int n,int m)
{
	double** B = new double*[m];
	for (int i = 0; i < m; i++)
		B[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			B[j][i] = A[i][j];
	return B;
}
double** init(int n, int m, bool fillByZero)
{
	double** A = new double*[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[m];
	if (fillByZero)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				A[i][j] = 0.0;
	return A;
}

void del(double** M, int n)
{
	for (int i = 0; i < n; i++)
		delete[] M[i];
	delete[] M;
}


double det(double** A, int n)
{
	double** LU = init(n, n);//для экономии памяти марици L и U объеденены
	int* P = new int[n];
	for (int i = 0; i < n; i++)
		P[i] = i;
	LUP(A, LU, P, n);
	double res = 1; 
	for (int i = 0; i < n; i++) 
	res *= LU[i][i]; 
	delete[] P;
	delete[] LU;
	return res; 
}

double* Solve(double** A, double* b, int n)
{
	double** LU = init(n, n);//для экономии памяти марици L и U объеденены
	int* P = new int[n];
	for (int i = 0; i < n; i++)
		P[i] = i;
	LUP(A, LU, P, n);

	double* y = new double[n];
	double* x = new double[n];
	double s = 0;
	for (int i = 0; i < n; i++)
	{
		s = 0;
		for (int j = 0; j < i; j++)
			s += LU[i][j] * y[j];
		y[i] = b[P[i]] - s;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		s = 0;
		for (int j = i + 1; j < n; j++)
			s += LU[i][j] * x[j];
		x[i] = (y[i] - s) / LU[i][i];
	}
	delete[] y;
	delete[] P;
	del(LU, n);
	return x;
}

void LUP(double** A, double** LU, int* P, int n) 
{
	double** debug = NULL;
	if (flag)
	{
		debug = init(n, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				debug[i][j] = A[i][j];
	}
	for (int i = 0; i < n; i++) //LU = A;
		for (int j = 0; j < n; j++)
			LU[i][j] = A[i][j];
	int r = 0;
	for (int i = 0; i < n; i++) 
	{
		if (flag)
		{
			cout << ">>step: " << i << endl;
			cout << "A[" << i << "] before swap" << endl;
			print(debug, n);
		}

		//поиск опорного элемента
		double pivotValue = 0;
		int pivot = -1;
		for (int row = i; row < n; row++) 
		{
			if (fabs(LU[row][i]) > pivotValue) 
			{
				pivotValue = fabs(LU[row][i]);
				pivot = row;
			}
		}
		if (pivotValue != 0) 
		{
			//меняем местами i-ю строку и строку с опорным элементом
			int t = P[pivot]; P[pivot] = P[i]; P[i] = t;
			SwapRows(LU,pivot, i);
			if (flag)
			{
				SwapRows(debug, pivot, i);
				cout << ">>main element " << pivot << endl;
				if (pivot != i)
					cout << ">>swapping " << i << " and " << pivot << " lines" << endl;
				else
					cout << ">>no need to swap" << endl;
				cout << "r = " << r++ << endl;
			}
			for (int j = i + 1; j < n; j++) 
			{
				LU[j][i] /= LU[i][i];
				for (int k = i + 1; k < n; k++)
					LU[j][k] -= LU[j][i] * LU[i][k];
			}
		}
		if (flag)
		{
			cout << "A[" << i << "] after swap" << endl;
			print(debug, n);
			printLU(LU, n);
			cout << endl;
		}
	}
}

void SwapRows(double** M, int a, int b)
{
	double* t= M[a];
	M[a] = M[b];
	M[b] = t;
}

double** GetInvert(double** A, int n)
{
	double** Invert = init(n, n);
	double* E = new double[n];
	for (int i = 0; i < n; i++)
		E[i] = 0;

	for (int i = 0; i < n; i++)
	{
		E[i]++;
		Invert[i] = Solve(A, E, n);
		E[i]--;
	}
	for (int i = 0; i<n; i++)
		for (int j = i + 1; j < n; j++)
		{
			double t = Invert[i][j];
			Invert[i][j] = Invert[j][i];
			Invert[j][i] = t;
		}
	delete[] E;
	return Invert;
}

double norm(double** M, int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += fabs(M[0][i]);
	double norm = sum;

	for (int i = 1; i < n; i++)
	{
		sum = 0;
		for (int j = 0; j < n; j++)
			sum += fabs(M[i][j]);
		if (sum > norm)
			norm = sum;
	}
	return norm;
}


double fractionalError(double** A, double* X, double* b, int n)
{
	double error = 0;
	for (int i = 0; i < n; i++)
	{
		double c = b[i];
		for (int j = 0; j < n; j++)
			c -= A[i][j] * X[j];
		if (fabs(c) > error)
			error = fabs(c);
	}
	return error;
}