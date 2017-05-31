//
//  7_2.cpp
//
//  �R�N�U�g�R�Q�ԁ@�����V��
//
//
//

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define N 256

double function(double x)
{
  return 1/(1+25*x*x);
}

double newton(int num,double arg,double x[N], double y[N])
{
  double w[N];
  double a[N];
  double answer = 0.0;

  for (int i = 0; i < num; ++i)
  {
    w[i] = y[i];
    for (int j = i-1; j >= 0; --j)
    {
      w[j] = (w[j+1] - w[j])/(x[i] - x[j]);
    }
    a[i] = w[0];
  }

  answer = a[num-1];

  for (int i = num-2; i >=0; i--)
  {
    answer *= arg - x[i];
    answer += a[i];
  }

  return answer;
}

int main()
{
  const int num = 20;
  const double step = 0.01;
  double max = 1.0;
  double min = -1.0;
  double maxdiff = 0.0;
  double mindiff = 1e10;
  int maxn=0;
  int minn=0;
  int m = (max - min)/step;
  double x[N];
  double y[N];
  double maxx[N];
  double maxy[N];
  double diff = 0.0;

  FILE *fp=NULL;
  fp = fopen ("7_2.csv","wt");
  if(fp == NULL) {return 1;}

  for (int k = 3; k <= num; k++) {
    diff = 0;

    for (int i = 0; i < k; i++) {
      x[i] = min + (max-min)/k*i;
      y[i] = function(x[i]);
    }

    for (int i = 0; i < m; i++) {
      diff += fabs( function( min+i*step) - newton( k, min+i*step, x, y));
    }

    if(maxdiff<diff) {maxdiff=diff; maxn=k;}
    if(mindiff>diff) {mindiff=diff; minn=k;}

    printf("n = %2d, Diffrrence = % 10.3f\n",k,diff );
  }

  printf("n of maximum difference = %d\n",maxn );
  printf("n of minimum difference = %d\n",minn );

  for (int i = 0; i < minn; i++) {
    x[i] = min + (max-min)/minn*i;
    y[i] = function(x[i]);
  }

  for (int i = 0; i < maxn; i++) {
    maxx[i] = min + (max-min)/maxn*i;
    maxy[i] = function(maxx[i]);
  }

  for (int i = 0; i < m; i++) {
    fprintf(fp,"%f,%f,%f\n", min+i*step, newton( minn, min+i*step,x,y),newton( maxn, min+i*step, maxx, maxy));
  }

  fclose (fp);
  
  return 0;
}
