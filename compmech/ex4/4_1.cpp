//
// 4_1.cpp
//
// ?3�N6�g32�Ԕ����V��
// ?�X�V����
// 2017.04.24 ... ver 1.0 ?



#include <stdio.h>
#include <math.h>

typedef double fp(double);

double dfunc(double x)
{
	return 6.0*x*x - 4.0;
}

double func(double x)
{
	return 2.0*x*x*x - 4.0*x + 1;
}

void  show_func(fp* func, const double a, const double b, const int n,double res[])
{
	double x = (b-a)/n;
	int k = 0;

	for(int i = 0; i<=n; i++)
	{
		if(func(a+x*(i-1))*func(a+x*i) < 0.0)
		{
			res[k] = a+x*i;
			k++;
		}
		printf("x = %6.3f, f(x) = %6.3f\n",a+x*i,func(a+x*i));
	}

}

int solve_bisection(fp* func, fp* dfunc, double &ans, double b)
{
	const double EPS = 1e-6;
	const int limit = 100;
	double x = b;
	double dx = 0.0;

	for(int k=1;k<=limit;k++)
	{
		 dx= x;
		x = x-func(x)/dfunc(x);
		if (fabs(x-dx)<fabs(dx)*EPS)
		{
			ans = x;
			return k;
		}
	}
	return -1;
}
int main()
{
	double ans = 0.0;
	double a = -2.0;
	double b = 2.0;
	double x[10];
	for (int i = 0; i < 10; ++i) x[i] = 0.0;

	show_func(func, a, b, 100, x);

	printf("\n---------- Answers 'f(x) = 0.0' ----------\n");
	for (int i = 0; x[i] != 0.0; ++i)
	{
		int ret = solve_bisection(func, dfunc, ans, x[i]);
		if(ret > 0)
		{
			printf("x[%d] = %6.3f (initial value: %4.2f --> iteration: %d times)\n",i+1, ans,x[i], ret);
		}else {
			printf("error: the root_x cannot be found.\n");
		}
	}
	return 0;
}
