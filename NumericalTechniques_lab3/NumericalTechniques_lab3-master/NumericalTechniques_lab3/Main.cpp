#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "MAtrix.h"
#include <cmath>
using namespace std;

const double e = 0.0001;

struct XY
{
	double x;
	double y;
	double norm()
	{
		return sqrt(x*x+y*y);
	}

	XY operator + (XY xy)
	{
		return { x + xy.x,y + xy.y };
	}

	XY operator - (XY xy)
	{
		return { x - xy.x,y - xy.y };
	}
	XY operator * (XY xy)
	{
		return { x * xy.x,y * xy.y };
	}
	XY operator * (double a)
	{
		return { x * a , y * a };
	}
	XY operator / (XY xy)
	{
		return { x / xy.x,y / xy.y };
	}

	XY operator ^ (double a)
	{
		return { pow(x, a) , pow(y,a) };
	}


	XY* print()
	{
		cout << "(" << x << "," << y << ")";
		return this;
	}
};

XY F_14(XY xy)
{
	return { cos(xy.y) + xy.x - 1.5 , 2 * xy.y - sin(xy.x - 0.5) - 1 }; 
}

XY F_20(XY xy)
{	
	return { sin(xy.y + 2) - xy.x - 1.5 , xy.y + cos(xy.x - 2) - 0.5 };
}

XY f_14(XY xy)
{
	return { 1.5 - cos(xy.y) , (1 + sin(xy.x - 0.5)) / 2 };
}

XY f_20(XY xy)
{
	return { sin(xy.y + 2) - 1.5 , 0.5 - cos(xy.x - 2) };
}

XY df_14(XY xy)
{
	return{ 2*(-1.5 + xy.x + cos(xy.y) - cos(0.5 - xy.x)*(-1 + 2*xy.y + sin(0.5 - xy.x))) ,  4*(-1 + 2*xy.y + sin(0.5 - xy.x)) - 2*(-1.5 + xy.x + cos(xy.y))*sin(xy.y) };
}

XY df_20(XY xy)
{
	return { 2*(-0.5 + xy.y + cos(2 - xy.x))*sin(2 - xy.x) - 2*(-1.5 - xy.x + sin(2 + xy.y)) , 2*(-0.5 + xy.y + cos(2 - xy.x)) + 2*cos(2 + xy.y)*(-1.5 - xy.x + sin(2 + xy.y)) };
}


double(*W[2][2])(XY) = {};
int K = 0;

XY IM(XY xy0, XY(F)(XY), XY(f)(XY));
XY Newton(XY xy0, XY(F)(XY), double(*W[2][2])(XY));
XY GradDescent(XY xy0, XY(F)(XY), XY(df)(XY), double alfa, double lambda);
double** init(int n, int m, bool fillByZero=false);
void main()
{
	XY(*F)(XY) = NULL;
	XY(*f)(XY) = NULL;
	XY(*df)(XY) = NULL;
	double alfa = 0, lambda = 0;
	
	XY xy0;
	switch (14)
	{
	case 14:
		F = F_14;
		f = f_14;
		df = df_14;
		xy0 = { 14, 0.5 };
		W[0][0] = [](XY a) -> double { return 1; };
		W[0][1] = [](XY a) -> double { return -sin(a.y); };
		W[1][0] = [](XY a) -> double { return -cos(a.x - 0.5); };
		W[1][1] = [](XY a) -> double { return 2; };
		alfa = 4.7;
		lambda = 0.14;
		break;
	case 20:
		F = F_20;
		f = f_20;
		df = df_20;
		xy0 = { -1.5, 1.5 }; 
		W[0][0] = [](XY a) -> double { return -1; };
		W[0][1] = [](XY a) -> double { return cos(a.y+2); };
		W[1][0] = [](XY a) -> double { return -sin(a.x-2); };
		W[1][1] = [](XY a) -> double { return 1; };
		alfa = 5.1;
		lambda = 0.46;
		break;
	}

	IM(xy0, F, f);
	cout << endl;
	Newton(xy0, F, W);
	cout << endl;
	GradDescent(xy0, F, df, alfa, lambda);
	/*int Kold = 100;
	double j = 0;
	double alfamin, lambdamin;
	double kf = (0.89 / 0.01)*((99.9 - 0.4) / 0.1) / 100;
	for (lambda = 0.01; lambda < 0.9; lambda += 0.01)
		for (alfa = 0.5; alfa < 100; alfa += 0.1)
		{
			j++;
			GradDescent(xy0, F, df, alfa, lambda);
			//cout << K << " ";
			
			cout << j / kf  << "%" << endl;
			if (K < Kold)
			{
				cout << alfa << " " << lambda << endl;
				Kold = K;
				alfamin = alfa;
				lambdamin = lambda;
			}
		}
	cout << "FINISH:"<< endl << "alfa: " << alfamin << " lambda: " << lambdamin;*/
	cout << endl;
	cin.get();
	cin.get();
}

XY IM(XY xy0, XY(F)(XY), XY(f)(XY))
{
	double delta; 
	double Fdelta;
	int k = 1;
	XY xy = xy0;
	do
	{
		xy = f(xy);
		cout << k++ << " XY0 ";
		xy0.print();
		cout << " XY "; 
		xy.print();
		delta = (xy - xy0).norm();
		cout << " ||XY-XY0|| " << delta; 
		Fdelta = F(xy).norm();
		cout << " ||F(x,y)|| " << Fdelta;
		xy0 = xy;
		cout << endl;

	} while (e < delta && e < Fdelta);
	return xy;
}

XY Newton(XY xy0, XY(F)(XY), double(*W[2][2])(XY))
{
	double delta;
	XY xy = xy0;
	double invW[2][2] = {};
	double Fdelta;
	int k = 1;
	do
	{
		double q = W[0][0](xy);
		q = W[0][1](xy);
		q = W[1][0](xy);
		q = W[1][1](xy);
		invW[0][0] = -W[1][1](xy) / (W[0][1](xy) * W[1][0](xy) - W[0][0](xy) * W[1][1](xy));
		invW[0][1] = W[0][1](xy) / (W[0][1](xy) * W[1][0](xy) - W[0][0](xy) * W[1][1](xy));
		invW[1][0] = W[1][0](xy) / (W[0][1](xy) * W[1][0](xy) - W[0][0](xy) * W[1][1](xy));
		invW[1][1] = -W[0][0](xy) / (W[0][1](xy) * W[1][0](xy) - W[0][0](xy) * W[1][1](xy));
		XY b = F(xy);
		XY sub_res = { invW[0][0]*F(xy).x+invW[0][1]*F(xy).y , invW[1][0] * F(xy).x + invW[1][1] * F(xy).y };
		cout << k++ << " XY0 ";	 
		xy0.print();
		cout << " XY ";
		xy = xy0 - sub_res;
		xy.print(); 
		cout << " invW*F(x,y) ";
		sub_res.print();
		delta = (xy - xy0).norm();
		cout << " ||XY-XY0|| " << delta;
		Fdelta = F(xy).norm();
		cout << " ||F(x,y)|| " << Fdelta;
		xy0 = xy;
		cout << endl;

	} while (e < delta && e < Fdelta);
	return xy;
}

XY GradDescent(XY xy0, XY(F)(XY), XY(df)(XY), double alfa, double lambda)
{
	double delta;
	XY xy = xy0;
	double Fdelta;
	int k = 1;
	double alfak = alfa;
	do
	{
		alfak = alfa;
		while ( (F(xy0 - df(xy0) * alfak)^2).x  + (F(xy0 - df(xy0) * alfak)^2).y >= (F(xy0)^2).x + (F(xy0)^2).y)
		{
			alfak = alfak * lambda;
		}
		xy = xy0 - df(xy0) * alfak;
		
		cout << k++ << " XY0 ";
		//k++;
		xy0.print();
		cout << " XY ";
		xy.print();
		cout << " df ";
		df(xy0).print();
		cout << " alfa " << alfak;
		delta = (xy - xy0).norm();
		cout << " ||XY-XY0|| " << delta;
		Fdelta = F(xy).norm();
		cout << " ||F(x,y)|| " << Fdelta;
		cout << " |f(x,y)| " << fabs((F(xy) ^ 2).x + (F(xy) ^ 2).y);
		xy0 = xy;
		cout << endl;
	} while (e < delta && e < Fdelta);
	K = k;
	return xy;
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