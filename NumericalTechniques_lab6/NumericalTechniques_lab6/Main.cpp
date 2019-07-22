#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std; 
double getApro(double S, double S0_5, double S0_25);
double QuadratureFormula(double(*f)( double), const int N, const double h, const double a, const double b);
double QuadratureFormulaSplain(double(*f)(double), double(*df)(double), const int N, const double h, const double a, const double b);
double Simson(double(*f)(double), const int N, const double h, const double a, const double b);
double Gauss(double(*f)(double), const int n, const double h, const double A, const double B);

#define VARIANT 14
const double E = 0.00000001;
 double f_14( double x)
{
	return 2 * exp(x) - 3 * x + 1;
}
double df_14(double x)
{
	return -3 + 2 *exp(x);
}

double f_20(double x)
{
	return 2 * atanf(x) - x + 3;
}
double df_20(double x)
{
	return -1 + 2 / (1 + x * x);
}

void main()
{
	double(*f)(double) = NULL;
	double(*df)(double) = NULL;
	double a = 1;
	double b = 2;
	double N = 2;
	switch (VARIANT)
	{
	case 14:
		f = f_14;
		df = df_14;
		break;
	case 20:
		f = f_20;
		df = df_20;
		break;
	default:
		break;
	}
	double e = 0;
	do
	{
		double h = (b - a) / N;
		long double S = QuadratureFormula(f, N, h, a, b);
		long double S0_5 = QuadratureFormula(f,  2*N, 0.5*h , a, b);
		long double S0_25 = QuadratureFormula(f, 4*N, 0.25*h , a, b);
		long double apro = getApro(S, S0_5, S0_25);
		e = fabs(S0_5 - S) / S0_5;
		N *= 2;
		cout << setprecision(10);
		cout << "QuadratureFormula: " << S << " apro: " << apro << " " << N <<endl;
	} while (e > E);
	cout << endl;
	N = 2;
	do
	{
		double h = (b - a) / N;
		double S = QuadratureFormulaSplain(f, df, N, h, a, b);
		double S0_5 = QuadratureFormulaSplain(f, df, 2 * N, 0.5*h, a, b);
		double S0_25 = QuadratureFormulaSplain(f, df, 4 * N, 0.25*h, a, b);
		double apro = getApro(S, S0_5, S0_25);
		e = fabs(S0_5 - S) / S0_5;
		N *= 2;
		cout << setprecision(10);
		cout << "QuadratureFormula(Splain): " << S << " apro: " << apro << " " << N << endl;
	} while (e > E);
	cout << endl;
	N = 2;
	do
	{
		double h = (b - a) / N;
		double S = Simson(f,  N, h, a, b);
		double S0_5 = Simson(f,  2 * N, 0.5*h, a, b);
		double S0_25 = Simson(f,  4 * N, 0.25*h, a, b);
		double apro = getApro(S,S0_5,S0_25);
		e = fabs(S0_5 - S) / S0_5;
		N *= 2;
		cout << setprecision(10);
		cout << "Simson: " << S << " apro: " << apro << " " << N << endl;
	} while (e > E);

	cout << endl;
	N = 2;
	do
	{
		double h = (b - a) / N;
		double S = Gauss(f, N, h, a, b);
		double S0_5 = Gauss(f, 2 * N, 0.5*h, a, b);
		double S0_25 = Gauss(f, 4 * N, 0.25*h, a, b);
		double apro = getApro(S, S0_5, S0_25);
		e = fabs(S0_5 - S) / S0_5;
		N *= 2;
		cout << setprecision(10);
		cout << "Gauss: " << S << " apro: " << apro << " " << N << endl;
	} while (e > E);
	cin.get();
	cin.get();

}

double getApro(double S, double S0_5,  double S0_25)
{
	long double a = S0_25 - S;
	long double b = S0_5 - S;
	long double c = a / b;
	return log(c-1)  / log(0.5);
}

double QuadratureFormula(double(*f)(double),const int N, const double h, const double a,const double b)
{
	long  double S = 0.5*(f(a)+f(b));

	for (int j = 1; j < N; j++)
	{
		S += f(a + j*h);
	}
	return h*S;
}

double QuadratureFormulaSplain(double(*f)(double), double(*df)(double), const int N, const double h, const double a, const double b)
{
	double S = 0.5*(f(a) + f(b));

	for (int j = 1; j < N; j++)
	{
		S += f(a + j*h);
	}
	return h*S+((h*h)/12)*(df(a)-df(b));
}

double Simson(double(*f)(double), const int N, const double h, const double a, const double b)
{
	double S1 = 0;
	double S2 = 0;

	for (int j = 1; j <= N/2; j++)
	{
		double i = 2 * j - 1;
		S1 += f(a + i*h);
	}
	for (int j = 1; j < N/2; j++)
	{
		double i = 2 * j ;
		S2 += f(a + i*h);
	}
	return (h / 3)*((f(a) + f(b)) + 4 * S1 + 2 * S2);
}

double Gauss(double(*f)(double), const int n,  const double h, const double A, const double B)
{
	double res = 0, a = 0, b = 0;
	for (int i = 0; i < n; i++)
	{
		a = A + h * i;
		b = A + h * (i + 1);
		res += (b - a) / 2 *
			(5.0 / 9 * f(0.5 * (a + b + (b - a) * -sqrt(3.0 / 5))) +
				8.0 / 9 * f(0.5 * (a + b)) +
				5.0 / 9 * f(0.5 * (a + b + (b - a) * sqrt(3.0 / 5))));
	}
	return res;
}