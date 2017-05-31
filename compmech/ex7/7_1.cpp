//
//  7_2.cpp
//
//  �R�N�U�g�R�Q�ԁ@�����V��
//
#include "stdio.h"
#include "stdlib.h"

#define N 256

double lagrange(int num,double arg,double x[N], double y[N])
{
  double tmp    = 1.0;
  double answer = 0.0;

  for(int i = 0; i < num; i++)
  {
    tmp = 1.0;
    for (int j = 0; j < num; j++)
    {
      if (i != j) tmp *= ( arg - x[j] ) / ( x[i] - x[j] );
    }
    answer += tmp * y[i];
  }
  return answer;
}

double newton(int num,double arg,double x[N], double y[N]){
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
  const int count = 50;
  int num = 0;
  double arg = 0.0;
  double max = 0.0;
  double min = 0.0;
  double x[N];
  double y[N];
  FILE  *ifp = NULL;
  FILE  *ofp = NULL;
  ofp = fopen ("7_1.csv","wt");
  ifp = fopen("data.txt","rt");

  if (ifp==NULL||ofp==NULL) {
    printf("%s\n","Error!" );
    return 1;
  }
  while(fscanf(ifp,"%lf %lf\n", &x[num],&y[num]) != EOF) num++;
  for (int i = 0; i < num; i++) {
    if (max<x[i]) max = x[i];
    if (min>x[i]) min = x[i];
  }

  
  double dx = (max-min)/count;
  arg = min;
  for (int i = 0; i <= count; i++) {
    fprintf(ofp, "%f,%f,%f\n",arg+i*dx,lagrange(num,arg+dx*i,x,y),newton(num,arg+dx*i,x,y));
  }

  fclose (ifp);
  fclose (ofp);
  return 0;
}
