//
//	10_2.cpp
//
//	作成者：3年6組32番 椎葉 太一
//	更新履歴：
//	2017.07.03 ... ver 1.0 完成
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000
#define BitSize 12

int bin2dec(long x)
{
    //整数型のヒ?ットサイス?を算出
    int base = 1;
    int d = 0;
    int a[BitSize];

    for (int i = 0; i < BitSize; i++)
    {
        a[i] = x % 10;
        x /= 10;
    }

    if (a[BitSize - 1] == 0)
    {
        for (int i = 0; i < BitSize; i++)
        {
            d += a[i] * base;
            base*=2;
        }
    }
    else
    {   
        // 符号付き表示のための計算
        for (int i = 0; i < BitSize - 1; i++)
        {
            d += (-1*a[i]+1) * base ;
            base*=2;
        }
        d = d * -1;
    }
    return d;
}

int main(int argc, char const *argv[])
{
    long data[N];
    float maxV = 5;
    float minV = -5;
    float step = 0.0;
    int size = 0;
    FILE *ofp = NULL;
    FILE *ifp = NULL;
    char *ofname = "./output.csv";
    char *ifname = "./data.txt";

    ofp = fopen(ofname, "wt");
    ifp = fopen(ifname, "rt");
    if (ifp == NULL || ofp == NULL)
    {
        printf("%s\n", "Error!");
        return 1;
    }

    while (fscanf(ifp, "%ld\n", &data[size]) != EOF)
    {
        size++;
    }
    step = (maxV - minV) / (size-1);
    for (int i = 0; i < size; i++)
    {
        fprintf(ofp, "%f,%d\n", minV + step * i, bin2dec(data[i]));
    }
    return 0;
}