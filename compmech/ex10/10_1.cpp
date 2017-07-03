//
//	10_1.cpp
//
//	�쐬�ҁF3�N6�g32�� �ŗt ����
//	�X�V�����F
//	2017.07.03 ... ver 1.0 ����
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void bin2dec(int x)
{
    //�����^�̃q?�b�g�T�C�X?���Z�o
    const int BitSize = 8;
    const int bit = 1;
    int i;
    int c;
    int a[BitSize];

    for (int i = 0; i < BitSize; i++)
    {
        if (x % 10 > 1)
        {
            fprintf(stderr, "Usage : %d InputIntegerNumber\n", x);
            exit(2);
        }
        a[i] = x % 10;
        x /= 10;
    }
    // �����Ȃ��\���̂��߂̌v�Z
    for (i = 0; i < BitSize; i++)
    {
        c += a[i] * pow(2, i);
    }

    //�v�Z���ʂ̕\��
    printf("Unsigned Decimal: %5d\t", c); // 10�i����?�\��
    printf(" Hexadecimal:%10x\n", c);     // 16�i����?�\��
    if (a[BitSize - 1] == 1)
    {
        // �����t���\���̂��߂̌v�Z
        {
            c = 0;
            for (i = 0; i < BitSize - 1; i++)
            {
                c += (-1 * a[i] + 1) * pow(2, i);
            }
            c = -1 * c - 1;
        }
    }
    printf("Signed Decimal:   %5d\t", c); // 10�i����?�\��
    printf(" Hexadecimal:%10x\n", c);     // 16�i����?�\��
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strlen(argv[1]) != 8)
    { // ���s��������?2��?�Ȃ�������G���[�\��
        fprintf(stderr, "Usage : %s InputIntegerNumber\n", argv[1]);
        exit(1);
    }
    int x = atoi(argv[1]);
    printf("Input integer number : %d\n\n", x);
    bin2dec(x);

    return 0;
}
