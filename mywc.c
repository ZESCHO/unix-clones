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

struct Counts lwc(FILE *fp, bool lines, bool words, bool bytes);
void print_counts(struct Counts c, bool saw_l, bool saw_w, bool saw_c, const char *name);

int main(int argc, char *argv[])
{

    bool saw_l = false;
    bool saw_w = false;
    bool saw_c = false;
    bool saw_files = false;

    struct Counts c;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == 'l')
                    saw_l = true;
                else if (argv[i][j] == 'w')
                    saw_w = true;
                else if (argv[i][j] == 'c')
                    saw_c = true;
                else
                {
                    fprintf(stderr, "mywc: unexpected argument %c found\n", argv[i][j]);
                    return EXIT_FAILURE;
                }
            }
        }
    }

    if (!saw_l && !saw_w && !saw_c)
    {
        saw_l = true;
        saw_w = true;
        saw_c = true;
    }

    bool fp_failed = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            saw_files = true;
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                fp_failed = true;
                fprintf(stderr, "mywc: ");
                perror(argv[i]);
                continue;
            }

            c = lwc(fp, saw_l, saw_w, saw_c);
            if (ferror(fp))
            {
                fprintf(stderr, "mywc: ");
                perror(argv[i]);
                fp_failed = true;
                fclose(fp);
                continue;
            }

            print_counts(c, saw_l, saw_w, saw_c, argv[i]);
            fclose(fp);
        }
    }

    if (fp_failed)
        return EXIT_FAILURE;

    if (!saw_files)
    {
        c = lwc(stdin, saw_l, saw_w, saw_c);
        print_counts(c, saw_l, saw_w, saw_c, NULL);
    }
    return EXIT_SUCCESS;
}

struct Counts lwc(FILE *fp, bool lines, bool words, bool bytes)
{

    struct Counts c = {0, 0, 0};
    int ch;
    bool in_word = false;

    while ((ch = getc(fp)) != EOF)
    {

        if (bytes)
            c.bytes++;

        if (lines && ch == '\n')
        {
            c.lines++;
        }

        if (isspace(ch))
        {
            in_word = false;
        }
        else if (words && !in_word)
        {
            in_word = true;
            c.words++;
        }
    }

    return c;
}

void print_counts(struct Counts c, bool saw_l, bool saw_w, bool saw_c, const char *name)
{
    if (saw_l)
    {
        printf("%ld", c.lines);
    }

    if (saw_w)
    {
        if (saw_l)
            putchar(' ');
        printf("%ld", c.words);
    }

    if (saw_c)
    {
        if (saw_w || saw_l)
            putchar(' ');
        printf("%ld", c.bytes);
    }

    if (name != NULL)
    {
        putchar(' ');
        printf("%s\n", name);
    }

    else
    {
        putchar('\n');
    }
}