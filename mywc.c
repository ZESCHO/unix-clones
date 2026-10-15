#include <stdio.h>
#include <stdlib.h>

void count(FILE *fp, long *byte_counter, long *line_counter)
{
    int ch;
    while ((ch = getc(fp)) != EOF)
    {

        if (ch == '\n')
            (*line_counter)++;

        (*byte_counter)++;
    }
}

int main(int argc, char *argv[])
{
    long line_counter = 0;
    long byte_counter = 0;

    if (argc == 1)
    {
        count(stdin, &byte_counter, &line_counter);
        printf("%ld %ld\n", line_counter, byte_counter);
        return EXIT_SUCCESS;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        fprintf(stderr, "mywc: ");
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    count(fp, &byte_counter, &line_counter);

    printf("%ld %ld %s\n", line_counter, byte_counter, argv[1]);
    fclose(fp);

    return EXIT_SUCCESS;
}