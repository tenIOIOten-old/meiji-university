//
//ex01/kadai_2.cpp
//
//2017.04.10
//

#include <stdio.h>
#include <stdlib.h>

// 行列の積の関数の定義
void operation(FILE* a_fp, FILE* b_fp,FILE* out_fp)
{
	// 行列を格納する変数の定義
	float a[3][2], b[2][4],c[3][4];
	
	// ファイルの存在を確認
	if ( ( a_fp == NULL ) || ( b_fp == NULL ) || (out_fp == NULL )){
		fprintf( stderr, "[Error] null file pointer detected.\n");
		exit(-1);
	}

	// ファイルから値を読み込み変数に格納
	for(int i = 0; i < 3 ; i++){

		// EOFは　end of file　の略でファイルの終点を表している
		// つまりEOFがfscanf関数から返ってくれば読み込みが終わったことを表す
		if(fscanf( a_fp, "%f,%f", &a[i][0], &a[i][1]) == EOF) 
			break;
	} 
	for(int i = 0; i < 2 ; i++){
		if(fscanf( b_fp, "%f,%f,%f,%f",&b[i][0], &b[i][1], &b[i][2], &b[i][3]) == EOF) 
			break;
	}

	//　行列の積の計算　i　は行　j　は列を表す
	for( int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			c[i][j] = a[i][0] * b[0][j] + a[i][1] *  b[1][j]; 
		// ファイルに出力
			fprintf( out_fp, "%g,", c[i][j]);
		}
		//　改行
		fprintf( out_fp, "\n");
	}
}

// main関数
int main()
{
	// ファイル変数の定義
	FILE* a_fp = NULL;
	FILE* b_fp = NULL;
	FILE* out_fp = NULL;

	// ファイル名を格納した変数の定義
	char* a_file = "a_mat.csv";;
	char* b_file = "b_mat.csv";
	char* out_file = "output/output_mat.csv";
;
	
	// ファイルを開く、ファイルが存在しない場合、エラーを標準出力に出力
	// rtはファイルを読み込み用かつテキストモードで開く、ファイルが存在しなければエラーになりNULLを返す
	// ｗtはファイルを書き込み用かつテキストモードで開く、ファイルが存在しなければ作成
	if( ( a_fp = fopen(a_file, "rt")) == NULL ){
		fprintf(stderr, "Can't open file %s\a\n", a_file);
		exit(2);
	}
	if( ( b_fp = fopen(b_file, "rt")) == NULL ){
		fprintf(stderr, "Can't open file %s\a\n", b_file);
		exit(3);
	}
	if( ( out_fp = fopen(out_file, "wt")) == NULL ){
		fprintf(stderr, "Can't open file %s\a\n", out_file);
		exit(4);
	}
	
	// 関数の呼び出し
	operation(a_fp,b_fp,out_fp);
	
	// ファイルを閉じる　
	fclose(out_fp);
	fclose(b_fp);
	fclose(a_fp);
	
	// プログラムの終了
	return(0);
}