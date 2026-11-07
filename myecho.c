#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        putchar('\n');
        return EXIT_SUCCESS;
    }

    printf("%s", argv[1]);
    for (int i = 2; i < argc; i++)
    {
        printf(" %s", argv[i]);
    }

    putchar('\n');
    return EXIT_SUCCESS;
}