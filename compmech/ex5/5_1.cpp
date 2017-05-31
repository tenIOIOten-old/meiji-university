//
// 5_1.cpp 
//
// 3年6組32番白鳥天太
// 更新履歴
// 2017.05.15 ... ver 1.0 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4
#define EPS 1e-6
typedef double Matrix [N][N+1];

void print_matrix(Matrix a)
{
  for (int i=0;i<N;i++)
  {
    for (int j=0;j<N;j++)
    {
      printf("%8.3f",a[i][j]);
    }
    printf("|%8.3f\n",a[i][N]);
  }
  printf("\n");
}

void change_array(Matrix origin,const int a,const int b)
{
  double array[N+1];
  for (int i = 0; i < N+1; ++i)array[i]=0;
  for (int i = 0; i < N+1 ; ++i)
  {
    array[i]= origin[a][i]; 
    origin[a][i] = origin[b][i];
    origin[b][i] = array[i];
  }

}

void gauss_jordan(Matrix a)
{
  for (int i=0;i<N;i++)
  {
    double pivot=a[i][i];
   if(fabs(pivot)<EPS)
    {
 /*   int m = 0;
      for ( m = i+1; m < N; ++m)
      {
        if(fabs(a[m][i])>EPS)break;
      }
      change_array(a,i,m);
    	pivot=a[i][i];
*/    	int k=i+1;
    	do{ 
    		pivot = a[k][i];
    		k++;
    	}while(fabs(pivot)<EPS);
    	change_array(a,i,k);
    	pivot=a[i][i];
    }

	 for (int j=i;j<N+1;j++)
    {
      a[i][j]/=pivot;
    }
    for (int k=0;k<N; k++)
    {
      if(k!=i)
      {
        double d=a[k][i];
        for (int j = 0; j < N+1; j++)
        {
          a[k][j]-=d*a[i][j];
        }
      }
    }
    print_matrix(a);
  }
}

void print_result(Matrix a)
{
  printf("========results=======\n");
  for (int i = 0; i < N; i++)
  {
    printf("x%d = %9.3lf\n", i+1, a[i][N]);
  }
}

 int main(void)
{
  Matrix A = {
              {0,1,2,2,2},
              {3,3,2,3,4},
              {2,1,3,2,1},
              {3,1,2,1,2}
              };
  print_matrix(A);
  gauss_jordan(A);
  print_result(A);
  return 0;
}