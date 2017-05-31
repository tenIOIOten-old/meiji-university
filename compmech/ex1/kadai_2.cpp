//
//ex01/kadai_2.cpp
//
//2017.04.10
//

#include <stdio.h>
#include <stdlib.h>

// �s��̐ς̊֐��̒�`
void operation(FILE* a_fp, FILE* b_fp,FILE* out_fp)
{
	// �s����i�[����ϐ��̒�`
	float a[3][2], b[2][4],c[3][4];
	
	// �t�@�C���̑��݂��m�F
	if ( ( a_fp == NULL ) || ( b_fp == NULL ) || (out_fp == NULL )){
		fprintf( stderr, "[Error] null file pointer detected.\n");
		exit(-1);
	}

	// �t�@�C������l��ǂݍ��ݕϐ��Ɋi�[
	for(int i = 0; i < 3 ; i++){

		// EOF�́@end of file�@�̗��Ńt�@�C���̏I�_��\���Ă���
		// �܂�EOF��fscanf�֐�����Ԃ��Ă���Γǂݍ��݂��I��������Ƃ�\��
		if(fscanf( a_fp, "%f,%f", &a[i][0], &a[i][1]) == EOF) 
			break;
	} 
	for(int i = 0; i < 2 ; i++){
		if(fscanf( b_fp, "%f,%f,%f,%f",&b[i][0], &b[i][1], &b[i][2], &b[i][3]) == EOF) 
			break;
	}

	//�@�s��̐ς̌v�Z�@i�@�͍s�@j�@�͗��\��
	for( int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			c[i][j] = a[i][0] * b[0][j] + a[i][1] *  b[1][j]; 
		// �t�@�C���ɏo��
			fprintf( out_fp, "%g,", c[i][j]);
		}
		//�@���s
		fprintf( out_fp, "\n");
	}
}

// main�֐�
int main()
{
	// �t�@�C���ϐ��̒�`
	FILE* a_fp = NULL;
	FILE* b_fp = NULL;
	FILE* out_fp = NULL;

	// �t�@�C�������i�[�����ϐ��̒�`
	char* a_file = "a_mat.csv";;
	char* b_file = "b_mat.csv";
	char* out_file = "output/output_mat.csv";
;
	
	// �t�@�C�����J���A�t�@�C�������݂��Ȃ��ꍇ�A�G���[��W���o�͂ɏo��
	// rt�̓t�@�C����ǂݍ��ݗp���e�L�X�g���[�h�ŊJ���A�t�@�C�������݂��Ȃ���΃G���[�ɂȂ�NULL��Ԃ�
	// ��t�̓t�@�C�����������ݗp���e�L�X�g���[�h�ŊJ���A�t�@�C�������݂��Ȃ���΍쐬
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
	
	// �֐��̌Ăяo��
	operation(a_fp,b_fp,out_fp);
	
	// �t�@�C�������@
	fclose(out_fp);
	fclose(b_fp);
	fclose(a_fp);
	
	// �v���O�����̏I��
	return(0);
}