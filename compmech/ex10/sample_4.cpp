#include <stdio.h>

#include <stdlib.h>

void dec2bin(int x)
{
    //整数型のビットサイズを算出
    const int BitSize = sizeof(int) * 8;
    const int bit = 1;
    int i;
    char c[BitSize];

    printf(" Hexadecimal: %x\n", x); // 16進数で表示
    printf(" Decimal: %d\n", x);     // 10進数で表示

    // 2進数表示のための計算
    for (i = 0; i < BitSize; i++)
    {
        c[i] = x & bit;
        x >>= 1;
    }

    //計算結果の表示
    printf(" Binary: ");
    for (i = BitSize - 1; i >= 0; i--)
    {
        printf("%d", c[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
/* code */
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    printf("x:"); dec2bin(x);
    printf("y:"); dec2bin(y);
    printf("x&y"); dec2bin(x&y);
    printf("\n"); 
    printf("x:"); dec2bin(x);
    printf("y:"); dec2bin(y);
    printf("x|y"); dec2bin(x|y);
    printf("\n"); 
    printf("x:"); dec2bin(x);
    printf("NOT x:"); dec2bin(~x);
    printf("\n"); 
 return 0;
}