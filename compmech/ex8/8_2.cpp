#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 32
#define EPS 1e-6
typedef double Matrix[N][N + 1];

double ipow(double p, int n)
//ベキ乗
{
  double s = 1;
  for (int k = 0; k < n; k++)
    s *= p;
  return s;
}
void print_matrix(Matrix a, int M)
{
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < M; j++)
    {
      printf("%10.3f", a[i][j]);
    }
    printf("|%10.3f\n", a[i][M]);
  }
  printf("\n");
}

void change_row(Matrix origin, const int a, int M)
{
  int change = a;
  double array;
  double max_value = origin[a][a];
  for (int k = a; k < M; k++)
  {
    if (fabs(max_value) < fabs(origin[k][a]))
    {
      max_value = origin[k][a];
      change = k;
    }
  }
  printf("Max value: %7.3f\n", fabs(max_value));
  printf("Max row: %d\n", change);
  if (change == a)
    return;
  for (int i = 0; i < M + 1; ++i)
  {
    array = origin[a][i];
    origin[a][i] = origin[change][i];
    origin[change][i] = array;
  }
  printf("Row %d changed with row %d \n\n", a, change);
}

void forward_elimination(Matrix a, int M)
{
  for (int i = 0; i < M; i++)
  {

    change_row(a, i, M);
    double pivot = a[i][i];

    if (fabs(pivot) <= EPS)
      return;

    for (int j = i; j < M + 1; j++)
    {
      a[i][j] /= pivot;
    }
    for (int k = i; k < M; k++)
    {
      if (k != i)
      {
        double d = a[k][i];
        for (int j = 0; j < M + 1; j++)
        {
          a[k][j] -= d * a[i][j];
        }
      }
    }
    print_matrix(a, M);
  }
}

void backward_substitution(Matrix a, int M)
{

  for (int i = M - 1; i >= 0; i--)
  {
    if (fabs(a[i][i]) <= EPS)
      break;
    for (int j = M - 1; j > i; j--)
    {
      a[i][M] -= a[i][j] * a[j][M];
      a[i][j] -= a[i][j];
    }
    print_matrix(a, M);
  }
}

void gauss_elimination(Matrix A, int M)
{
  forward_elimination(A, M);
  backward_substitution(A, M);
}

double findS(double x[N], int n, int num)
{
  double s = 0.0;
  for (int i = 0; i < num; i++)
  {
    s += ipow(x[i], n);
  }
  return s;
}

double findT(double x[N], double y[N], int n, int num)
{
  double t = 0.0;
  for (int i = 0; i < num; i++)
  {
    t += y[i] * ipow(x[i], n);
  }
  return t;
}
double func(Matrix A, int M, double x)
{
  double y = 0.0;
  for (int i = 0; i < M; i++)
  {
    y += A[i][M] * ipow(x, i);
  }
  return y;
}
void neary(Matrix A,int M, double x[N], double y[N], int num){
  double s = 0.0;
  for (int i = 0; i < M; i++)
  {
    s = findS(x, i, num);
    for (int j = 0; j < i + 1; j++)
    {
      A[i - j][j] = s;
    }

    s = findS(x, i + M, num);
    for (int j = M - 1; j > i; j--)
    {
      A[i + M - j][j] = s;
    }
  }

  for (int i = 0; i < M; i++)
    A[i][M] = findT(x, y, i, num);

  print_matrix(A, M);
  gauss_elimination(A, M);
 
}

int main(int argc, char const *argv[])
{
  const int M1 = 4;
  const int M2 = 6;
  const int M3 = 8;
  double x[N];
  double y[N];
  Matrix A1;
  Matrix A2;
  Matrix A3;
  int num = 0;
  FILE *ifp;
  ifp = fopen("data.csv", "rt");
  if (ifp != NULL)
  {
    while (fscanf(ifp, "%lf,%lf", &x[num], &y[num]) != EOF)
      num++;
    fclose(ifp);
  }
  neary(A1,M1,x,y,num);
  neary(A2,M2,x,y,num);
  neary(A3,M3,x,y,num);
  FILE *ofp;
  ofp = fopen("output_2.csv","wt");
  if (ofp!=NULL)
  {
    double max = 2.0;
    double min = -2.0;
    double step = 0.05;
    double dx = min;
    int rengenum =  (max-min)/step;
    for (int i = 0; i <= rengenum; i++)
    {
      fprintf(ofp,"%lf,%lf,%lf,%lf\n", dx, func(A1,M1,dx), func(A2,M2,dx), func(A3,M3,dx));
      dx += step;
    }
    fclose (ofp);
  }
  return 0;
}
