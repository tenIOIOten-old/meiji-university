//
//ex01/filetest.cpp
//
//2017.04.10
//

#include <stdio.h>
#include <stdlib.h>
//ŒvZˆ—‚ğs‚¤ŠÖ”
void operation(FILE* ifp, FILE* ofp)
{
	float a, b;
	const int LOOPLIMIT = 10000;
	
	if ( ( ifp == NULL ) || ( ofp == NULL ) ){
		fprintf( stderr, "[Error] null file pointer detected.\n");
		exit(-1);
	}
	
	for( int i = 0; i < LOOPLIMIT; i++){
		if(fscanf( ifp, "%f%f", &a, &b) == EOF) 
			break;
		float c = a * b;
		fprintf( ofp, "%g, %g, %g\n", a, b, c);
		printf("%g * %g = %g\n",a,b,c);
	}
}

int main( int argc,char* argv[])
{
	FILE* ifp = NULL;
	FILE* ofp = NULL;
	char* ifile = NULL;
	char* ofile = NULL;
	
	if(argc != 3){
		fprintf( stderr, "usage: %s inputfile outputfile\n",argv[0]);
		exit(1);
	}
	ifile = argv[1];
	ofile = argv[2];
	
	if( ( ifp = fopen(ifile, "rt")) == NULL ){
		fprintf(stderr, "Can't open file %s\a\n", ifile);
		exit(2);
	}
	if( ( ofp = fopen(ofile, "wt")) == NULL ){
		fprintf(stderr, "Can't open file %s\a\n", ofile);
		exit(3);
	}
	
	operation(ifp,ofp);
	
	fclose(ofp);
	fclose(ifp);
	
	return(0);
}