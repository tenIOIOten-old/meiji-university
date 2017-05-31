//
// 3_1.cpp 
//
// 作成者:3年6組32番 白鳥 天太
// 更新履歴:
// 2017.04.24 ... ver 1.0 作成


#include <stdio.h>
#include <math.h>
#define X_MIN 1.0
#define X_MAX 10.0

double function(double x)
{
	return log(x)/x;
}

double rectangle(int n)
{
	double a = X_MIN;
	double b = X_MAX;
	double s = 0.0;
	double h = (b-a)/n;
	for (int i = 0; i<n; i++)
	{
		s += function(a + h*i);
	}
	s *= h;
	return s;
}

double trapezoid(int n)
{
	double a = X_MIN;
	double b = X_MAX;
	double s = 0.0;
	double h = (b-a)/n;

	for (int i = 0; i < n; i++) {

		s +=	function(a + h*i)+function(a + h*(i+1));
	}
	s *= h/2;
	return s;
}

double simpson(int n)
{
	double a = X_MIN;
	double b = X_MAX;
	double s = 0.0;
	double h = (b-a)/n; 

	for (int i = 0; i < n; i++)
	{
		s += function(a + h*i) + 4*function(a + h*(i + 1.0/2.0)) + function(a + h*(i + 1));
	}
	s *= h / 6;
	return s;
}

int main(int argc,char* argv[])
{
	int n = 0.0;
	double ans = pow( log(10), 2) / 2;
	
	if (argc != 2 || (n = atof(argv[1])) == 0.0){
		printf("ArgumentError");
	}

	printf("Analystic Solution = %f\n",ans);
	printf("\n");

  for(int i = 0; i < 3; i++)
	{
		double r = rectangle(n);
		double t = trapezoid(n);
		double s = simpson(n);
		printf("DivisionNumber = %d\n",n);
		printf("Rectangle: %f (%.3f\%)\n", r,100 - r / ans * 100);
		printf("Trapezoid: %f (%.3f\%)\n", t,100 - t / ans * 100);
		printf("Simpson:   %f (%.3f\%)\n", s,100 - s / ans * 100);
		printf("\n");

		n *= 10;
	}
}