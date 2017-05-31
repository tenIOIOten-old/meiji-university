//
// 3_2.cpp 
//
// 作成者:3年6組32番 白鳥 天太
// 更新履歴:
// 2017.04.24 ... ver 1.0 作成




#include <stdio.h>
#include <stdlib.h>
#include <math.h>



double trapezoid(double* n,int N)
{
	double s = 0.0;
	double h = 1.0/1000.0;
	for (int i = 0; i<N; i++) {
		s += n[i] + n[i+1];
	}

	s *= h/2.0;
	return s;
}


int main(void)
{
	const int Hz = 1000;
	const int s  = 6;
	FILE* ifp = NULL;
	FILE* ofp = NULL;
	char* ifile = "ang_vel.txt";
	char* ofile = "output.csv";
	double n[ s * Hz];
	char str[15];
	
	for (int i =0 ; i < s * Hz; i++)n[i] = 0;

	if((ifp = fopen(ifile,"rt"))== NULL || (ofp = fopen(ofile,"wt"))==NULL)
	{
		printf("Could Not Open File!");
		exit(1);
	}
		
	fprintf(ofp,"%f,%f,%f\n",0,0,0);

	for(int i =1;i <= s * Hz;i++)
	{
		fscanf(ifp,"%s",str);
		n[i] = atof(str);
		fprintf(ofp,"%f,%f,%f\n",(double)i / Hz,n[i],trapezoid(n,i));
	}

	fclose(ifp);
	fclose(ofp);
	
	return 0;
}