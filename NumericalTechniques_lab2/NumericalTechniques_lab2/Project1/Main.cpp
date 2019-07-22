#include <iostream>
#include <iomanip>
#include "Matrix.h"
using namespace std;
double** init(int n, int m, bool fillByZero);
double* ValueIterationMethod(Matrix C, double* X);
void copy(double* A, double* B, int n);
double Max(double* E, int n);
double Norm(double** M, int n);
double scalar(double* A, double* B, int n);
double GetQ(double* X_1, double* X0, double* X, int n);
double* VIM(Matrix C, double* X);  // - методом простой итерации
double* SOR(Matrix C, double* X);  //- методом ПВР
double* CGM(Matrix C, double* X);  //- методом сопряженных градиентов
double* SDM(Matrix C, double * X); //- градиентным методом наискорейшего спуска

const double c_delta = 0.001;
double teta;
const bool OUT_VIM = true;
const bool OUT_SOR = true;
const bool OUT_CGM = true;
const bool OUT_SDM = true;
double w = 1.7;
double K = 0;
int main()
{
	Matrix A("input.txt");
	teta = 0.9 * (2 / Norm(A.value, A.n));

	cout << "A:\n";
	A.Print();

	cout << "b = ";
	for (int i = 0; i < A.n; i++)
		cout << A.b[i] << " ";
	cout << endl;

	double* X = new double[A.n]; 
	
		for (int i = 0; i < A.n; i++)
			X[i] = A.b[i];
		X = VIM(A, X);

	cout << "VIM X = ";
	for (int i = 0; i < A.n; i++)
		cout << fixed << setprecision(5) << X[i] << " ";
	cout << endl;

	for (int i = 0; i < A.n; i++)
		X[i] = A.b[i];
	X = SDM(A, X);

	cout << "SDM X = ";
	for (int i = 0; i < A.n; i++)
		cout << fixed << setprecision(5) << X[i] << " ";
	cout << endl;

	/*for (w = 0.1; w <= 2; w += 0.1)
	{
		K = 0;*/
	for (int i = 0; i < A.n; i++)
		X[i] = A.b[i];
	X = SOR(A, X);
	/*cout << "w = " << w << " k = " << K << endl;
	}*/

	cout << "SOR X = ";
	for (int i = 0; i < A.n; i++)
		cout << fixed << setprecision(5) << X[i] << " ";
	cout << endl;
	

	for (int i = 0; i < A.n; i++)
		X[i] = A.b[i];
	X = CGM(A, X);

	cout << "CGM X = ";
	for (int i = 0; i < A.n; i++)
		cout << fixed << setprecision(5) << X[i] << " ";
	cout << endl;

	delete[] X;
	A.Delete();
	cin.get();
	cin.get();
	return 0;
}

double* ValueIterationMethod(Matrix C, double* X)
{
	int n = C.n;
	double* X0 = new double[n];
	copy(X0, X, n);
	double* E = new double[n];
	cout << endl;
	double delta;
	do 
	{
		for (int i = 0; i < n; i++)
		{
			X[i] = 0;
			for (int j = 0; j < n; j++)
			{
				X[i] += C.value[i][j] * X0[j];
			}
			X[i] += C.b[i];
			E[i] = abs(X[i] - X0[i]);
		}
			delta = Max(E,n);
			cout << "X = ";
			for (int i = 0; i < n; i++)
				cout << setw(5) << setprecision(5) << X[i] << " ";
			cout << setw(15)  << " E = ";
			for (int i = 0; i < n; i++)
				cout << setw(5) << setprecision(5) << E[i] << " ";
			cout << " delta = " << delta << endl;

			copy(X0, X, n);
		
	} while (delta > c_delta);
	delete[] E;
	delete[] X0;
	return X;
}

double* VIM(Matrix A, double* X)
{
	int n = A.n;
	double* X0 = new double[n];
	copy(X0, X, n);
	double* X_1 = new double[n];
	double* r = new double[n];
	double* E = new double[n];
	double delta;
	int k = 0;
	do
	{
		for (int i = 0; i < n; i++)
		{
			X[i] = X0[i];
			double sum = 0;
			for (int j = 0; j < n; j++)
			{
				sum += A.value[i][j] * X0[j];
			}
			X[i] += teta*(A.b[i] - sum);
		}
		for (int i = 0; i < n; i++)
		{
			r[i] = fabs(X[i] - X0[i]);
			E[i] = -A.b[i];
			for (int j = 0; j < n; j++)
				E[i] += A.value[i][j] * X[j];
		}
		delta = Max(E, n);
		if (OUT_VIM)
		{
			if (k >= 2)
			{
				cout << "q = " << GetQ(X_1, X0, X, n) << " ";
			}
			cout << k++ << " X = ";
			for (int i = 0; i < n; i++)
			{
				if (X[i] > 0)
					cout << " ";
				cout << fixed << setprecision(5) << X[i] << " ";
			}
			cout << "||r|| = " << Max(r,n);
			cout << " ||A*x-b|| = " << delta << endl;
			
		}

		copy(X_1, X0, n);
		copy(X0, X, n);

	} while (delta > c_delta);

	delete[] E;
	delete[] X0;
	delete[] X_1;
	return X;
}

double* SOR(Matrix A, double* X)
{
	int k = 0;
	int n = A.n;
	double* X0 = new double[n];
	copy(X0, X, n);
	double* X_1 = new double[n];
	double* L = new double[n];
	double* r = new double[n];
	double* E = new double[n];
	double delta;
	do
	{
		K++;
		for (int i = 0; i < n; i++)
		{
			L[i] = A.b[i];
			for (int j = 0; j < i; j++)
				L[i] -= A.value[i][j] * X[j];

			for (int j = i + 1; j < n; j++)
				L[i] -= A.value[i][j] * X0[j];
			L[i] /= A.value[i][i];
			X[i] = X0[i] + w*(L[i] - X0[i]);
		}
		for (int i = 0; i < n; i++)
		{
			r[i] = fabs(X[i] - X0[i]);
			E[i] = -A.b[i];
			for (int j = 0; j < n; j++)
				E[i] += A.value[i][j] * X[j];
		}
		delta = Max(E, n);
		if (OUT_SOR)
		{
			if (k >= 2)
			{
				cout << "q = " << fixed << GetQ(X_1, X0, X, n) << " ";
			}
			cout << k++ << " X = ";
			for (int i = 0; i < n; i++)
			{
				if (X[i] > 0)
					cout << " ";
				cout << fixed << setprecision(5) << X[i] << " ";
			}
			cout << "||r|| = " << Max(r, n);
			cout << " ||A*x-b|| = " << delta << endl;
		}


		copy(X_1, X0, n);
		copy(X0, X, n);
	} while (delta > c_delta);

	delete[] E;
	delete[] X0;
	delete[] X_1;

	return X;
}

double* CGM(Matrix A, double* X)
{
	int n = A.n;
	int k = 0;
	double* X0 = new double[n];
	copy(X0, X, n);
	double* X_1 = new double[n];
	double* E = new double[n];
	double* _r = new double[n];
	double* r = new double[n];
	double* z = new double[n];
	double* Az = new double[n];
	for (int i = 0; i < n; i++)
	{
		_r[i] = A.b[i];
		for (int j = 0; j < n; j++)
			_r[i] -= A.value[i][j] * X0[j];
		z[i] = _r[i];
	}
	double delta;
	double a = 1;
	double b = 1;
	do
	{
		for (int j = 0; j < n; j++)
		{
			Az[j] = A.value[j][0] * z[0];
			for (int t = 1; t < n; t++)
				Az[j] += A.value[j][t] * z[t];
		}
		a = scalar(_r, _r, n) / scalar(Az, z, n);
		b = 1 / scalar(_r, _r, n);

		for (int i = 0; i < n; i++)
		{
			X[i] = X0[i] + a*z[i];
			_r[i] -= a*Az[i];
		}
		for (int i = 0; i < n; i++)
		{
			r[i] = fabs(X[i] - X0[i]);
			E[i] = -A.b[i];
			for (int j = 0; j < n; j++)
				E[i] += A.value[i][j] * X[j];
		}
		b *= scalar(_r, _r, n);
		for (int i = 0; i < n; i++)
		{
			z[i] = _r[i] + b*z[i];
		}
		delta = Max(E, n);
		if (OUT_CGM)
		{
			if (k >= 2)
			{
				cout << "q = " << GetQ(X_1, X0, X, n) << " ";
			}
			cout << k++ << " X = ";
			for (int i = 0; i < n; i++)
			{
				if (X[i] > 0)
					cout << " ";
				cout << fixed << setprecision(5) << X[i] << " ";
			}
			cout << " ||r|| = " << Max(r, n);
			cout << " ||A*x-b|| = " << delta << endl;
		}

		copy(X_1, X0, n);
		copy(X0, X, n);
	} while (delta > c_delta);

	delete[] E;
	delete[] X0;
	delete[] X_1;
	delete[] _r;
	delete[] z;
	delete[] Az;
	return X;
}

double* SDM(Matrix A, double * X)
{
	int n = A.n;
	int k = 0;
	double* X0 = new double[n];
	copy(X0, X, n);
	double* X_1 = new double[n];
	double* E = new double[n];
	double* _r = new double[n];
	double* r = new double[n];
	double* Ar = new double[n];
	double delta;
	double t = 1;
	do
	{
		for (int i = 0; i < n; i++)
		{
			_r[i] = -A.b[i];
			for (int j = 0; j < n; j++)
				_r[i] += A.value[i][j] * X0[j];
		}
		for (int i = 0; i < n; i++)
		{
			Ar[i] = A.value[i][0] * _r[0];
			for (int j = 1; j < n; j++)
			{
				Ar[i] += A.value[i][j] * _r[j];
			}
		}

		t = scalar(_r, _r, n) / scalar(Ar, _r, n);

		for (int i = 0; i < n; i++)
		{
			X[i] = X0[i]- t * _r[i];
		}

		for (int i = 0; i < n; i++)
		{
			r[i] = fabs(X[i] - X0[i]);
			E[i] = -A.b[i];
			for (int j = 0; j < n; j++)
				E[i] += A.value[i][j] * X[j];
		}

		delta = Max(E, n);
		if (OUT_SDM)
		{
			if (k >= 2)
			{
				cout << "q = " << GetQ(X_1, X0, X, n) << " ";
			}
			cout << k++ << " X = ";
			for (int i = 0; i < n; i++)
			{
				if (X[i] > 0)
					cout << " ";
				cout << fixed << setprecision(5) << X[i] << " ";
			}
			cout << "tau = " << t;
			cout << " ||r|| = " << Max(r, n);
			cout << " ||A*x-b|| = " << delta << endl;
		}

		copy(X_1, X0, n);
		copy(X0, X, n);
	} while (delta > c_delta);

	delete[] E;
	delete[] X0;
	delete[] X_1;
	delete[] _r;
	delete[] Ar;
	return X;
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

void copy(double* A, double* B, int n)
{
	for (int i = 0; i < n; i++)
		A[i] = B[i];
}

double Max(double* E, int n)
{
	double res = fabs(E[0]);
	for (int i = 1; i < n; i++)
		if (res < fabs(E[i]))
		{
			res = fabs(E[i]);
		}
	return res;
}

double Norm(double** M, int n)
{
	double sum = 0;
	for (int j = 0; j < n; j++)
		sum += fabs(M[0][j]);
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


double scalar(double* A, double* B, int n)
{
	double sum = A[0] * B[0];
	for (int i = 1; i < n; i++)
		sum += A[i] * B[i];
	return sum;
}

double GetQ(double* X_1, double* X0, double* X, int n)
{
	double* a = new double[n];
	double* b = new double[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = X[i] - X0[0];
		b[i] = X0[i] - X_1[0];
	}
	double res = Max(a, n) / Max(b, n);
	delete[] a;
	delete[] b;
	return res;
}