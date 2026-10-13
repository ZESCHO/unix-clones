#include <stdio.h>
#include <stdlib.h>

void copy(FILE *fp)
{
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
}

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        copy(stdin);
        return EXIT_SUCCESS;
    }

    int status = EXIT_SUCCESS;

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            fprintf(stderr, "mycat: ");
            perror(argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        copy(fp);
        fclose(fp);
    }

    return status;
}