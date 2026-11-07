#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
struct Counts
{
    long lines;
    long words;
    long bytes;
};

struct Counts lwc(FILE *fp, bool *arr);
void print_counts(struct Counts c, bool *arr, const char *name);

int main(int argc, char *argv[])
{

    bool saw_flags[] = {false, false, false};
    bool no_flags = true;
    struct Counts c;

    // Detect l w c
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {

            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                no_flags = false;
                if (argv[i][j] == 'l')
                    saw_flags[0] = true;

                else if (argv[i][j] == 'w')
                    saw_flags[1] = true;

                else if (argv[i][j] == 'c')
                    saw_flags[2] = true;

                else
                {
                    fprintf(stderr, "mywc: unexpected argument %c found\n", argv[i][j]);
                    return EXIT_FAILURE;
                }
            }
        }
    }

    if (no_flags)
    {
        for (int i = 0; i < 3; i++)
        {
            saw_flags[i] = true;
        }
    }

    bool fp_failed = false;

    long count_files = 0;
    struct Counts total;
    total.lines = 0;
    total.words = 0;
    total.bytes = 0;

    // detect file / stdin
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            count_files++;

            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                fp_failed = true;
                fprintf(stderr, "mywc: ");
                perror(argv[i]);
                continue;
            }

            c = lwc(fp, saw_flags);
            total.lines += c.lines;
            total.words += c.words;
            total.bytes += c.bytes;

            if (ferror(fp))
            {
                fprintf(stderr, "mywc: ");
                perror(argv[i]);
                fp_failed = true;
                fclose(fp);
                continue;
            }

            print_counts(c, saw_flags, argv[i]);
            fclose(fp);
        }
    }

    if (count_files > 1)
    {
        print_counts(total, saw_flags, "total");
    }


    if (fp_failed)
        return EXIT_FAILURE;

    if (count_files == 0)
    {
        c = lwc(stdin, saw_flags);
        print_counts(c, saw_flags, NULL);
    }
    return EXIT_SUCCESS;
}

struct Counts lwc(FILE *fp, bool *arr)
{
    struct Counts c = {0, 0, 0};
    int ch;
    bool in_word = false;

    while ((ch = getc(fp)) != EOF)
    {

        if (arr[2])
            c.bytes++;

        if (arr[0] && ch == '\n')
        {
            c.lines++;
        }

        if (isspace(ch))
        {
            in_word = false;
        }
        else if (arr[1] && !in_word)
        {
            in_word = true;
            c.words++;
        }
    }

    return c;
}

void print_counts(struct Counts c, bool *arr, const char *name)
{

    long counts[] = {c.lines, c.words, c.bytes};
    bool printed = false;

    for (int i = 0; i < 3; i++)
    {
        if (arr[i])
        {
            if (printed)
            {
                putchar(' ');
            }
            printf("%ld", counts[i]);
            printed = true;
        }
    }

    if (name != NULL)
    {
        putchar(' ');
        printf("%s", name);
    }

    putchar('\n');
}
