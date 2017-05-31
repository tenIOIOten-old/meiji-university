//
//ex02/2_1.cpp
//
// 作成者: 3年6組32番白鳥天太
// 更新履歴:
// 2017.04.17 ... var 1.0 作成
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	double x;
	double y;
	double theta;
} Point;

void func(Point p[],int N, double PI)
{
	Point maxpoint;
  double max = 0.0;
	double h = 2*PI/N;

  p[0].theta = 0.0;
	printf("\n");
	for(int i = 0; i < N; i++)
	{
		p[i].x = (1+cos(p[i].theta))*cos(p[i].theta);
		p[i].y = (1+cos(p[i].theta))*sin(p[i].theta);
		if( max < p[i].x + p[i].y )
		{
			maxpoint.x = p[i].x;
			maxpoint.y = p[i].y;
			maxpoint.theta = p[i].theta;
      max = maxpoint.x + maxpoint.y;
		}
		
		p[i+1].theta = p[i].theta + h;
	}
	
	printf("x + y の最大値 = %g\n(theta, x, y) = (%g,%g,%g)", max, maxpoint.theta, maxpoint.x, maxpoint.y);
	
}

int main()
{
	const int N =  1000;
	const double PI = 3.141592;
  Point p[N];
	FILE* ofp = NULL;
	char* ofile = "output.csv";
	
	
	if( (ofp = fopen(ofile,"wt")) == NULL )
	{
		fprintf(stderr, "Can't open file %s\a\n", ofile);
		exit(1);
	}

	func(p,N,PI);

  for(int i = 0; i < N; i++)
  {
    fprintf(ofp,"%g,%g,%g\n",p[i].theta,p[i].x,p[i].y);
	}

	fclose(ofp);
	
	return(0);
}