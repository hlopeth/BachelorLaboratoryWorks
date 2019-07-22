#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
#define VARIANT 20

void Print(double* a, int n, string info = "");
void SrednekvDiskret(double *x, double *F);
void SrednekvNepr(double *x, double *F);
void reverse(double(*f)(double), double *x);
double* GetFuncTable(double(*f)(double), const double a, const double b, const int n);
double** DividedDeltaTable(double* functTable, const double a, const double b, const int n);
double** GetFiniteDeltaTable(double* functTable, const double a, const double b, const int n);
double* GetFiniteDeltaTablePolinom(double** finiteDeltaTable, const double a, const double b, const int n);
double** GetErrorTable(double(*f)(double), double(*df6)(double), double** finiteDeltaTable, const double a, const double b, const int n);
double** GetSoLE();
double* GetRightPart(double(*f)(double), double(*df)(double), double* functTable, const double a, const double b, const int n);
double** init(int n, int m, bool fillByZero = false);
double* Solve(double** A, double* b, int n);
double** GetMateForSpline(double(*f)(double), double(*df4)(double), double(*df5)(double), double* M, const double a, const double b, const int n);
int factorial(int i);
void PrintInterpStr(double** finiteDeltaTable);

const int a = 1;
const int b = 2;
const int n = 5;
double f_14(double x)
{
	return 2 * exp(x) - 3 * x + 1;
}
double f_20(double x)
{
	return 2 * atan(x) - x + 3;
}
double f_t(double x)
{
	//return (pow(3.0, x - 1) + 4 - x);
	return pow(3, x) - 2 * x + 5;
}
double df_t(double x)
{
	//return (pow(3.0, x - 1)*log(3) - 1);
	return pow(3, x) * log(3) - 2;
}
double df_14(double x)
{
	return -3 + 2 * exp(x);
}
double df_20(double x)
{
	return -1 + 2 / (1 + x*x);
}
double df4_t(double x)
{
	//return (pow(3.0, 2 - 1)*(pow(log(3), 4)));
	return pow(3, x) * pow(log(3), 4);
}
double df4_14(double x)
{
	return 2 * exp(x);
}
double df4_20(double x)
{
	return -(48 * x *(-1 + x*x)) / pow((1 + x*x), 4);
}
double df5_t(double x)
{
	//return (pow(3.0, 2 - 1)*(pow(log(3), 5)));
	return pow(3, x) * pow(log(3), 5);
}
double df5_14(double x)
{
	return 2 * exp(x);
}
double df5_20(double x)
{
	return (48 * (1 - 10 * x*x + 5 * x*x*x*x)) / pow((1 + x*x), 5);
}
double df6_t(double x)
{
	//return (pow(3.0, 2 - 1)*(pow(log(3), 6)));
	return pow(3, x) * pow(log(3), 6);
}
double df6_14(double x)
{
	return 2 * exp(x);
}
double df6_20(double x)
{
	return -(480 * x*(3 - 10 * x*x + 3 * x*x*x*x)) / pow((1 + x*x), 6);
}
void main()
{
	setlocale(LC_ALL, "Russian");
	const int a = 1;
	const int b = 2;
	const int n = 5;
	double h = ((double)(b - a)) / n;
	double(*f)(double) = NULL;
	double(*df)(double) = NULL;
	double(*df4)(double) = NULL;
	double(*df5)(double) = NULL;
	double(*df6)(double) = NULL;
	switch (VARIANT)
	{
	case 14:
		f = f_14;
		df = df_14;
		df4 = df4_14;
		df5 = df5_14;
		df6 = df6_14;
		break;
	case 20:
		f = f_20;
		df = df_20;
		df4 = df4_20;
		df5 = df5_20;
		df6 = df6_20;
		break;
	default:
		f = f_t;
		df = df_t;
		df4 = df4_t;
		df5 = df5_t;
		df6 = df6_t;
		break;
	}
	double *w = new double[6]; 
	double *F = new double[6];
	double *x = new double[6];
	for (int i = 0; i < 6; i++)
	{
		w[i] = 0;
		x[i] = 1 + i*0.2;
		F[i] = f(x[i]);
	}
	std::cout << "df(a) = " << df(a) << endl;
	std::cout << "df(b) = " << df(b) << endl;
	std::cout << "Интерполяционная формула Ньютона  для равноотстоящих узлов\n";
	double* functTable = GetFuncTable(f, a, b, n);
	Print(functTable, n + 1, "\nТаблица значений функции");
	double** finiteDeltaTable = GetFiniteDeltaTable(functTable, a, b, n);
	std::cout << "\nТаблица конечных разностей:\n";
	for (int i = 0; i < n + 1; i++, std::cout <<endl)
		Print(finiteDeltaTable[i], n + 2);
	std::cout << "\nИнтерполяционная формула Ньютона для равноотстоящих узлов:\n";
	PrintInterpStr(finiteDeltaTable);
	double** errorTable = GetErrorTable(f,df6,finiteDeltaTable, a, b, n);
	for (int i = 0; i < 5; i++, std::cout <<endl)
		Print(errorTable[i], n);

	std::cout << "\nИнтерполяционный кубический сплайн\n";
	double** SoLE = GetSoLE();
	for (int i = 0; i < n - 1; i++, std::cout<<endl)
		Print(SoLE[i], n - 1);
	double* rPart = GetRightPart(f, df, functTable, a, b, n);
	Print(rPart, n - 1);
	double* M = new double[n + 1];
	M[0] = df(a);
	M[n] = df(b);
	rPart[0] -= 0.5 * M[0];
	rPart[3] -= 0.5 * M[n];
	double* ans = Solve(SoLE, rPart,n-1);
	for (int i = 1; i < n; i++)
		M[i] = ans[i - 1];
	Print(M, n+1,"\nОтвет M[], найденный с помощью метода прогонки");
	double M5 = fabs(df5(a));
	double M4 = fabs(df4(a));
	for (double i = a + h; i <= b; i += h)
	{
		double temp = fabs(df5(i));
		if (temp > M5)
			M5 = temp;
		temp = fabs(df4(i));
		if (temp > M4)
			M4 = temp;
	}
	std::cout << "\nM4 = " << M4 << "\nM5 = " << M5 << endl;
	double** MateForSpline = GetMateForSpline(f, df4, df5, M, a, b, n);
	for (int i = 0; i < 5; i++, std::cout << endl)
	{
		Print(MateForSpline[i], n);
	}
	std::cout << endl << "Вторая оценка:" << endl;
	double* ocenka = new double[6];
	for (int i = 0; i < 5; i++)
		ocenka[i] = abs(df(finiteDeltaTable[i][0]) - M[i]);
	std::cout << *max_element(ocenka, ocenka + 6) << "<=" << M5 / 60 * pow(h, 4);


	std::cout << endl << "Среднеквадратичное приближение (дискретный вариант)" << endl;
	SrednekvDiskret(x, F);

	std::cout << endl << "Среднеквадратичное приближение (интегральный вариант)" << endl;
	SrednekvNepr(x, F);
	cout << endl << "Обратное интерполирование:" << endl;
	reverse(f,x);
	cin.get();
}

void Print(double* a, int n, string info)
{
	std::cout << info;
	if (info != "")
		std::cout << ":\n	";
	for (int i = 0; i < n; i++)
	{
		//cout << fixed;
		std::cout.precision(10);
		std::cout << a[i] << " ";
	}
}

double** init(int n, int m, bool fillByZero)
{
	double** A = new double*[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[m];
	if (fillByZero)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				A[i][j] = 0.0;
	return A;
}

int factorial(int i)
{
	if (i == 0) return 1;
	else return i*factorial(i - 1);
}

void del(double** M, int n)
{
	for (int i = 0; i < n; i++)
		delete[] M[i];
	delete[] M;
}

double* GetFuncTable(double(*f)(double), const double a, const double b, const int n)
{
	double h = (b - a) / n;
	double t = a;
	double* funcTable = new double[n + 1];
	for (int i = 0; t <= b; i++, t += h)
	{
		funcTable[i] = f(t);
		//cout << "f(" << t << ") = " << f(t) << endl;
	}
	return funcTable;
}

double** DividedDeltaTable(double* functTable, const double a, const double b, const int n)
{
	double** newtonTable = init(n + 1, n + 2,true);
	double h = (b - a) / n;
	for (int i = 0; i < n + 1; i++)
	{
		newtonTable[i][0] = a + h*i;
		newtonTable[i][1] = functTable[i];
	}
	for (int j = 2; j < n + 2; j++)
		for (int i = 0; i < (n + 1) - j + 1; i++)
			newtonTable[i][j] = (newtonTable[i + 1][j - 1] - newtonTable[i][j - 1]) / (newtonTable[j + i - 1][0] - newtonTable[i][0]);
	return newtonTable;
}

double** GetFiniteDeltaTable(double* functTable, const double a, const double b, const int n)
{
	double** finiteDeltaTable = init(n + 1, n + 2, true);
	double h = (b - a) / n;
	for (int i = 0; i < n + 1; i++)
	{
		finiteDeltaTable[i][0] = a + h*i;
		finiteDeltaTable[i][1] = functTable[i];
	}
	for (int j = 2; j < n + 2; j++)
		for (int i = 0; i < (n + 1) - j + 1; i++)
			finiteDeltaTable[i][j] = finiteDeltaTable[i + 1][j - 1] - finiteDeltaTable[i][j - 1];
	return finiteDeltaTable;
}

void PrintInterpStr(double** finiteDeltaTable)
{
	std::cout << finiteDeltaTable[0][1] << " + " << finiteDeltaTable[0][2] << "*q";
	for (int i = 3; i < n + 2; i++)
	{
		std::cout << " + ";
		std::cout << finiteDeltaTable[0][i] << "*q";
		for (int j = 1; j + 1 < i; j++)
			std::cout << "(q - " << j << ")";
		std::cout << "/" << i - 1 << "!";
	}
	std::cout << endl;
}


double* GetFiniteDeltaTablePolinom(double** finiteDeltaTable, const double a, const double b, const int n)
{
	double* dividedDeltaTable = new double[n];
	double h = (b - a) / n;
	int i = 0;
	for (double x = a+0.5*h; x <= b ; x+=h,i++)
	{
		dividedDeltaTable[i] = finiteDeltaTable[0][1];
		double qpoly = 1.0;
		double q = (x - a) / h;
		for (int j = 0; j < n; j++)
		{
			qpoly *= (q - j);
			dividedDeltaTable[i] += qpoly * finiteDeltaTable[0][j + 2] / factorial(j + 1);
		}
	}
	return dividedDeltaTable;
}

double** GetErrorTable(double(*f)(double), double(*df6)(double), double** finiteDeltaTable, const double a, const double b, const int n)
{
	double** errorTable = init(n, 5);
	double h = (b - a) / n;
	int i = 0;
	for (double x = a + 0.5*h; x <= b && i<n; x += h, i++)
	{
		errorTable[0][i] = x;
		errorTable[1][i] = f(x);
	}
	errorTable[2] = GetFiniteDeltaTablePolinom(finiteDeltaTable, a, b, n);
	double M6 = df6_t(a);
	for (double i = a + h; i <= b; i += h)
	{
		double temp = df6(i);
		if (temp > M6)
			M6 = temp;
	}
	for (int i = 0; i < n; i++)
	{
		errorTable[3][i] = fabs(errorTable[1][i] - errorTable[2][i]);
		double omega = 1;
		for (int j = 0; j < n+1; j++)
			omega *= errorTable[0][i] - finiteDeltaTable[j][0];
		errorTable[4][i] = (fabs(M6) * fabs(omega))/factorial(n+1);
	}
	return errorTable;
}

double** GetSoLE()
{
	double** SoLE = init(n - 1, n - 1, true);
	double mu = 0.5;
	double lambda = mu;
	for (int i = 0; i < n - 1; i++)
	{
		if (i - 1 >= 0) SoLE[i][i - 1] = lambda;
		SoLE[i][i] = 2;
		if (i + 1 < n - 1) SoLE[i][i + 1] = mu;
	}
	return SoLE;
}

double* GetRightPart(double(*f)(double), double(*df)(double), double* functTable, const double a, const double b, const int n)
{
	double* rPart = new double[n - 1];
	double mu = 0.5;
	double lambda = mu;
	double h = (b - a) / n;
	for (int i = 1; i < n; i++)
		rPart[i - 1] = 3 * lambda * (functTable[i] - functTable[i - 1]) / h + 3 * mu * (functTable[i + 1] - functTable[i]) / h;
	return rPart;
}

double* Solve(double** matrix, double* rPart, int n)
{
	n = n + 1;
	double* alpha = new double[n-1];
	double* betta = new double[n-1];
	int N1 = n - 2;
	double y = matrix[0][0];
	alpha[0] = (-matrix[0][1])/ y;
	betta[0] = rPart[0] / y;

	for (int i = 1; i < n-1; i++)
	{
		y = matrix[i][i] + matrix[i][i - 1] * alpha[i - 1];
		alpha[i] = (-matrix[i][i + 1]) / y;
		betta[i] = (rPart[i] - matrix[i][i - 1] * betta[i - 1]) / y;
	}
	betta[N1] = (rPart[N1] - matrix[N1][N1 - 1] * betta[N1 - 1]) / (matrix[N1][N1] + matrix[N1][N1 - 1] * alpha[N1 - 1]);
	double* x = new double[n];
	x[N1] = (rPart[N1] - matrix[N1][N1 - 1] * betta[N1 - 1]) / (matrix[N1][N1] + matrix[N1][N1 - 1] * alpha[N1 - 1]);
	for (int i = N1-1; i >= 0; i--)
		x[i] = alpha[i] * x[i + 1] + betta[i];
	delete[] alpha;
	delete[] betta;
	return x;
}

double z0(double x)
{
	return (1 + 2 * x) * (1 - x) * (1 - x);
}
double z1(double x)
{
	return x * (1 - x) * (1 - x);
}

double fi0(double tau)
{
	return (1 + 2 * tau)*(1 - tau)*(1 - tau);
}

double fi1(double tau)
{
	return tau*(1 - tau)*(1 - tau);
}

void splainRes(double *f, double *m, double *s)
{
	double tau = 0.5, h = 0.2;
	for (int i = 0; i<5; i++)
		s[i] = fi0(tau)*f[i] + fi0(1 - tau)*f[i + 1] + h*(fi1(tau)*m[i] - fi1(1 - tau)*m[i + 1]);
}
double** GetMateForSpline(double(*f)(double), double(*df4)(double), double(*df5)(double), double* M, const double a, const double b, const int n)
{
	double** mateForSpline = init(n, 5);
	double h = (b - a) / n;
	double t = a;
	int i = 0;
	for (double x = a + 0.5 * h; x <= b; x += h, i++)
	{
		mateForSpline[0][i] = x;
		mateForSpline[1][i] = f(x);
	}
	int k = 0;
	double *F = new double[5];
	int j = 0;
	for (double i = 1; i < 2; i += 0.2, j++)
		F[j] = f(i);
	splainRes(F, M, mateForSpline[2]);
	for (double x = a + 0.5 * h; x <= b; x += h, k++)
	{
		double t = (x - mateForSpline[0][k]) / h;
		//double b = 2;// mateForSpline[0][4];
		mateForSpline[3][k] = fabs(mateForSpline[1][k] - mateForSpline[2][k]);
		mateForSpline[4][k] = (fabs(df4(b)) / 384 + fabs(df5(b)) * h / 240) * powf(h, 4);///!!!!
	}
	return mateForSpline;
}

void Initialize(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
}

void SwapRows(double** M, int a, int b)
{
	double* t = M[a];
	M[a] = M[b];
	M[b] = t;
}
void SwapL(double** L, int a, int b)
{
	double t;
	for (int i = 0; i < b; i++)
	{
		t = L[b][i];
		L[b][i] = L[a][i];
		L[a][i] = t;
	}
}

void LUP(double** A, double** U, double**L, int* P, int n, int count)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			U[i][j] = A[i][j];

	for (int i = 0; i < n; i++)
	{
		double maxVal = 0;
		int swap = -1;
		for (int row = i; row < n; row++)
		{
			if (fabs(U[row][i]) > maxVal)
			{
				maxVal = fabs(U[row][i]);
				swap = row;
			}
		}

		if (maxVal != 0)
		{
			int t = P[swap]; P[swap] = P[i]; P[i] = t;

			SwapRows(U, swap, i);
			SwapL(L, swap, i);
			count++;
			L[i][i] = U[i][i];
			for (int j = i + 1; j < n; j++)
				L[j][i] = U[j][i];
			for (int k = i; k < n; k++)
			{
				U[i][k] /= L[i][i];
				for (int j = i + 1; j < n; j++)
				{

					U[j][k] = U[j][k] - U[i][k] * L[j][i];
				}
			}
		}
	}
}

void Pb(double *b, int* P, int n)
{
	double* fakeb = new double[n];
	for (int i = 0; i < n; i++)
		fakeb[i] = b[i];
	for (int i = 0; i < n; i++)
	{
		b[i] = fakeb[P[i]];
	}
}

void Findx(double b[], double x[], double **L, double **U, int n)
{
	double *y = new double[n];
	double sum;
	y[0] = b[0] / L[0][0];
	for (int i = 1; i < n; i++)
	{
		sum = 0.0;
		for (int j = 0; j < i; j++)
			sum += L[i][j] * y[j];
		y[i] = ((-1)*sum + b[i]) / L[i][i];
	}
	x[n - 1] = y[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		sum = 0;
		for (int j = n - 1; j >i; j--)
			sum += U[i][j] * x[j];
		x[i] = ((-1)*sum + y[i]);
	}
	delete[] y;
}

void findc(double **gmatrix, double *c)
{

	double **A, *b, *b2, *x, *x2;
	A = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		A[i] = new double[3];
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A[i][j] = gmatrix[i][j];
	b = new double[3];  b2 = new double[3];
	x = new double[3];
	x2 = new double[3];
	for (int i = 0; i < 3; i++)
		b[i] = gmatrix[3][i];
	double **L = new double*[3];
	Initialize(L, 3);
	double **U = new double*[3];
	Initialize(U, 3);
	int *P = new int[3];
	for (int i = 0; i < 3; i++)
		P[i] = i;
	int count = 0;
	for (int i = 0; i < 3; i++)
		b2[i] = b[i];

	LUP(A, U, L, P, 3, count);
	int* fakeP = new int[3];
	for (int i = 0; i<3; i++)
		fakeP[i] = P[i];
	Pb(b, fakeP, 3);
	Findx(b, x2, L, U, 3);
	std::cout << endl << " Решение с помощью LU разложения: " << endl;
	std::cout << "   c1" << "       " << "   c2" << "       " << "   c3" << endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << fixed << setprecision(6) << x2[i] << "    ";
		c[i] = x2[i];
	}
	std::cout << endl;
}

void SrednekvDiskret(double *x, double *F)
{
	
	double **gmatrix;
	gmatrix = new double*[4];
	for (int i = 0; i < 4; i++)
		gmatrix[i] = new double[3];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			gmatrix[i][j] = 0;
	/*for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			for (double k = 1; k <= 2; k += 0.2)
				gmatrix[i][j] += g(i, k)*g(j, k);*/
	gmatrix[0][0] = 6;
	gmatrix[0][1] = 9;
	gmatrix[0][2] = 14.2;
	gmatrix[1][0] = 9;
	gmatrix[1][1] = 14.2;
	gmatrix[1][2] = 23.4;
	gmatrix[2][0] = 14.2;
	gmatrix[2][1] = 23.4;
	gmatrix[2][2] = 39.9664;
	gmatrix[3][0] = 0;
	gmatrix[3][1] = 0;
	gmatrix[3][2] = 0;
	for (int i = 0; i < 6; i++)
	{
		gmatrix[3][0] += F[i];
		gmatrix[3][1] += x[i] * F[i];
		gmatrix[3][2] += x[i] * x[i] * F[i];
	}
	cout << endl << "Таблица среднеквадратичных приближений:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << gmatrix[i][j] << " ";
		cout << endl;
	}
	double *c = new double[3];
	double *gx = new double[6];
	double normf = 0, normg = 0;
	findc(gmatrix, c);
	std::cout << endl << "Коэффициенты ci:" << endl;
	for (int i = 0; i < 3; i++)
		std::cout << c[i] << endl;
	for (int i = 0; i < 6; i++)
		gx[i] = c[0] + c[1] * x[i] + c[2] * x[i] * x[i];

	std::cout << endl << setw(3) << "x" << " " << setw(10) << "f(x)" << " " << setw(15) << "g(x)";
	for (int i = 0; i < 6; i++)
	{
		cout << endl << fixed << setprecision(2) << x[i] << " " << fixed << setprecision(9) << setw(10) << F[i] << " " << setw(15) << gx[i];
		normf += F[i] * F[i];
		normg += gx[i] * gx[i];
	}
	cout << endl << "Оценка погрешности: " << sqrt(normf - normg) << endl;
}

void SrednekvNepr(double *x, double *F)
{
	double **gmatrix;
	gmatrix = new double*[4];
	for (int i = 0; i < 4; i++)
		gmatrix[i] = new double[3];
	gmatrix[0][0] = 1;
	gmatrix[0][1] = 1.5;
	gmatrix[0][2] = 2.333333333;
	gmatrix[1][0] = 1.5;
	gmatrix[1][1] = 2.333333333;
	gmatrix[1][2] = 3.75;
	gmatrix[2][0] = 2.333333333;
	gmatrix[2][1] = 3.75;
	gmatrix[2][2] = 6.2;
	gmatrix[3][0] = 3.441507812507310;//t7.461435359761024//14 5.841548540943209//20 3.441507812507310327653412937306385646731504662009915208426
	gmatrix[3][1] = 5.131613928842222;//t11.51570903459456//14 9.278112197861300//20 5.131613928842222562520672275919600424918320193986276989561
	gmatrix[3][2] = 7.936624629928235;//t18.39848325815298//14 15.202994072137843//20 7.936624629928235498075084294328284090157426282214543968043

	cout << endl << "Таблица среднеквадратичных приближений:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << gmatrix[i][j] << " ";
		cout << endl;
	}
	double *c = new double[3];
	double *gx = new double[6];
	double normf = 0, normg = 0;
	findc(gmatrix, c);
	cout << endl << "Коэффициенты ci:" << endl;
	for (int i = 0; i < 3; i++)
		cout << c[i] << endl;
	for (int i = 0; i < 6; i++)
		gx[i] = c[0] + c[1] * x[i] + c[2] * x[i] * x[i];
	cout << endl << setw(3) << "x" << " " << setw(10) << "f(x)" << " " << setw(15) << "g(x)";
	for (int i = 0; i < 6; i++)
	{
		cout << endl << fixed << setprecision(2) << x[i] << " " << fixed << setprecision(9) << setw(10) << F[i] << " " << setw(15) << gx[i];
		normf += F[i] * F[i];
		normg += gx[i] * gx[i];
	}
	cout << endl << "Оценка погрешности14: " << sqrt(37.43261176314579494247509791456102868274932999690982591091 - 37.4318) << endl;
	cout << endl << "Оценка погрешности20: " << sqrt(11.8557 - 11.8557) << endl;
}

void reverse(double (*f)(double),double *x)
{
	double *y = GetFuncTable(f, 1, 2, n);
	double ** matr = init(6, 6, true);
	
	for (int i = 0; i < 6; i++)
		matr[i][0] = x[i];
	int k = 6;
	for (int j = 1; j < 6; j++)
	{
		k--;
		for (int i = 0; i < k; i++)
			matr[i][j] = (matr[i + 1][j - 1] - matr[i][j - 1]) / (y[(i + j)] - y[i]);
	}
	for (int i = 0; i < 6; i++, std::cout << endl)
	{
		cout << y[i] << " ";
		Print(matr[i], n + 1);
	}
	double c, res = 0;
	c = 8;
	//c = 3.5;
	cout << "P=" << matr[0][0] << " + " << matr[0][1] << " * (" << c << "-" << y[0] << ") + " << matr[0][2] << " * (" << c << " - " << y[0] << ")*(" << c << " - " << y[1] << ") + " << matr[0][3]<<" * (" << c << " - " << y[0] << ")*(" << c << " - " << y[1] << ")*(" << c << " - " << y[2] << ") + " << matr[0][4] << " * (" << c << " - " << y[0] << ")*(" << c << " - " << y[1] << ")*(" << c << " - " << y[2] << ")*(" << c << " - " << y[3] << ") + " << matr[0][5] << " * (" << c << " - " << y[0] << ")*(" << c << " - " << y[1] << ")*(" << c << " - " << y[2] << ")*(" << c << " - " << y[3] << ")*(" << c << " - " << y[4] << ")";
	res = matr[0][0] + matr[0][1] * (c - y[0]) + matr[0][2] * (c - y[0])*(c - y[1]) + matr[0][3] * (c - y[0])*(c - y[1])*(c - y[2]) + matr[0][4] * (c - y[0])*(c - y[1])*(c - y[2])*(c - y[3]) + matr[0][5] * (c - y[0])*(c - y[1])*(c - y[2])*(c - y[3])*(c - y[4]);
	cout << endl << "Пусть с = " << c << endl << "Решение уравнения = " << res;
	cout << endl << "Погрешность:" << abs(f(res) - c) << endl;
}