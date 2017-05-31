//
// 4_2.cpp 
//
// ?3年6組32番白鳥天太
//  更新履歴
// 2017.05.9 ... ver 1.0 ?


#include <stdio.h>
#include <math.h>

typedef double fp(double);

double dfunc(double theta)
{
	return -1*sin(theta) + 1/sqrt( 4- sin(theta)*sin(theta))*sin(theta)*cos(theta);
}

double func(double theta)
{
	return cos(theta) + sqrt( 4 - sin(theta)*sin(theta) );
}

void show_func(fp* func, const double a, const double b, const int n,double res[],double ini)
{
	double x = (b-a)/n; 
	int k = 0;

	for(int i = 0; i<=n; i++)
	{
		if((func(a+x*(i-1))-ini)*(func(a+x*i)-ini) < 0.0)
		{
			res[k] = a+x*i;
			k++;
		}
		printf("theta = %6.3f, x = %6.3f\n",a+x*i,func(a+x*i));
	}

}

int solve_bisection(fp* func, double &ans, double low, double high,double ini)
{
	const double y = ini;
	const double EPS = 1e-6;
	const int limit = 100;

	for (int i = 0; i < limit; ++i)
	{
		double x = (low + high) / 2.0;

		if ( (func(low)-y)*(func(x)-y) < 0.0)
		{
			high = x;
		}else {
			low =  x;
		}

		if (fabs(high - low) < EPS){
			ans = x;
			return (i);
		}
	}
	return (-1);
}

int solve_newton(fp* func, fp* dfunc, double &ans, double b,double ini)
{
	const double EPS = 1e-6;
	const int limit = 100;
	double x = b;
	double dx = 0.0;
	double y = ini;
	for(int k=1;k<=limit;k++)
	{
		 dx= x;
		x = x-(func(x)-y)/dfunc(x);
		if (fabs(x-dx)<fabs(dx)*EPS)
		{
			ans = x;
			return k;
		}
	}
	return -1;
}

int main(void)
{
	const double PI = 3.141592;
	double ans = 0;
	double ini = 1.5;
	double a = 0.0;
	double b = 2.0*PI;
	double x[10];
	for (int i = 0; i < 10; ++i) x[i] = 0.0;

	show_func(func, a, b, 100, x,ini);

	printf("\n---------- Answers 'x = 0.0' ----------\n");
	
	printf("<Bisectional Method>\n");
	for (int i = 0; x[i] != 0.0; ++i)
	{
		double a2=x[i]-(b-a)/100,b2=x[i];
		int ret = solve_bisection(func, ans, a2, b2,ini);
		if(ret > 0)
		{

			printf("theta[%d] = %4.3f (low: %4.2f, high: %4.2f --> iteration: %d times)\n",i+1, ans,a2,b2, ret);
		}else {
			printf("error: the root_x cannot be found.\n");
		}
	}

	printf("<Newton Method>\n");
	for (int i = 0; x[i] != 0.0; ++i)
	{
		int ret = solve_newton(func, dfunc, ans, x[i],ini);
		if(ret > 0)
		{
			printf("theta[%d] = %4.3f (initial value: %4.2f --> iteration: %d times)\n",i+1, ans,x[i], ret);
		}else {
			printf("error: the root_x cannot be found.\n");
		}
	}
	return 0;
}