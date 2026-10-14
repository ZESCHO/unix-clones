#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void head(FILE *fp, int n)
{
    int ch;
    int counter = 0;

    while (counter != n && (ch = getc(fp)) != EOF)
    {
        putchar(ch);

        if (ch == '\n')
            counter++;
    }
}

int main(int argc, char *argv[])
{

    int n = 10;
    int first = 1;

    if (argc >= 3 && strcmp(argv[1], "-n") == 0)
    {
        n = atoi(argv[2]);
        first = 3;
    }

    int status = EXIT_SUCCESS;

    if (first == argc)
    {
        head(stdin, n);
        return status;
    }

    int printed_any = 0;

    for (int i = first; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            fprintf(stderr, "myhead: ");
            perror(argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (argc - first > 1)
        {
            if (printed_any)
                putchar('\n');

            printf("==> %s <==\n", argv[i]);
            printed_any = 1;
        }
        head(fp, n);
        fclose(fp);
    }

    return status;
}