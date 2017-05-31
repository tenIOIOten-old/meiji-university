//
// 5_2.cpp 
//
//  3年6組32番白鳥天太
//  更新履歴
// 2017.05.15 ... ver 1.0 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10
#define EPS 1e-6
#define MAX 10

typedef double Matrix[N][N+1];

void print_matrix(int num,Matrix a)
{
  for (int i=0;i<num;i++)
  {
    for (int j=0;j<num;j++)
    {
      printf("%8.3f",a[i][j]);
    }
    printf("|%8.3f\n",a[i][num]);
  }
  printf("\n");
}

void change_array(int num, Matrix origin,const int a,const int b)
{
  double array = 0;
  for (int i = 0; i < num+1; ++i)
  {
    array= origin[a][i]; 
    origin[a][i] = origin[b][i];
    origin[b][i] = array;
  }
}

void gauss_jordan(int num,Matrix a)
{
  for (int i=0;i<num;i++)
  {
    double pivot=a[i][i];
    if(fabs(pivot)<EPS)
    {
      int m=i;

      do{
        pivot = a[m][i];
        m++;
      }while(fabs(pivot)<EPS);
      if (m>num)return;
        
      change_array(num,a,i,m);
      pivot = a[i][i];
    }
    
    for (int j=i;j<num+1;j++)
    {
      a[i][j]/=pivot;
    }
    
    for (int k=0;k<num; k++)
    {
      if(k!=i)
      {
        double d=a[k][i];
    
        for (int j = 0; j < num+1; j++)
        {
          a[k][j]-=d*a[i][j];
        }
      }
    }
    
    print_matrix(num,a);
  }
}

void print_result(int num,Matrix a)
{
  printf("========results=======\n");
  if (fabs(a[0][0])<EPS)
  {
    printf("no real number solution\n");
    return;
  }
  for (int i = 0; i < num; i++)
  {
    printf("x%d = %9.3lf\n", i+1, a[i][num]);
  }
}

 int main(int argc, char const *argv[])
{
  Matrix A;
  if(argc != 2)
  {
    printf("Error: Invalud Argement!\n");
    return 1;
  }
  int arg = atoi(argv[1]);
  if( !arg || arg > MAX )
  {
    printf("Error: Invalud Argement!\n");
    return 2;
  }
  int num = atoi(argv[1]); 

  srand((unsigned)time(NULL));


  for (int i = 0; i < num; ++i)
  {
    
    for(int j=0;j<num+1;++j){
      int random_value;
      int max = 10;
      int min = -10;

      random_value = min + rand() % (max - min);
      A[i][j] = random_value;
    }
  }
  print_matrix(num,A);
  gauss_jordan(num,A);
  print_result(num,A);
  return 0;
}
