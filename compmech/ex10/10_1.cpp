//
//	10_1.cpp
//
//	作成者：3年6組32番 椎葉 太一
//	更新履歴：
//	2017.07.03 ... ver 1.0 完成
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void bin2dec(int x)
{
    //整数型のヒ?ットサイス?を算出
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
    // 符号なし表示のための計算
    for (i = 0; i < BitSize; i++)
    {
        c += a[i] * pow(2, i);
    }

    //計算結果の表示
    printf("Unsigned Decimal: %5d\t", c); // 10進数て?表示
    printf(" Hexadecimal:%10x\n", c);     // 16進数て?表示
    if (a[BitSize - 1] == 1)
    {
        // 符号付き表示のための計算
        {
            c = 0;
            for (i = 0; i < BitSize - 1; i++)
            {
                c += (-1 * a[i] + 1) * pow(2, i);
            }
            c = -1 * c - 1;
        }
    }
    printf("Signed Decimal:   %5d\t", c); // 10進数て?表示
    printf(" Hexadecimal:%10x\n", c);     // 16進数て?表示
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strlen(argv[1]) != 8)
    { // 実行時引数か?2個て?なかったらエラー表示
        fprintf(stderr, "Usage : %s InputIntegerNumber\n", argv[1]);
        exit(1);
    }
    int x = atoi(argv[1]);
    printf("Input integer number : %d\n\n", x);
    bin2dec(x);

    return 0;
}
