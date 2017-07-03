#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 'A'; i < 'Z'; i++)
    {
        printf("%c= %x\n", i, i);
    }
    return 0;
}