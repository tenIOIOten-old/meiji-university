#include <stdio.h>
int main(int argc, char const *argv[])
{
    char name[] = "shiratori";
    for (int i = 0; name[i] != '\0'; i++)
    {
        printf("%c=%x\t%c -> %c\n", name[i], name[i], name[i], name[i] - 0x20);
    }
    return 0;
}