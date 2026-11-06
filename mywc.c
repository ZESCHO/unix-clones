#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct Counts lwc(FILE *fp, bool lines, bool words, bool bytes);

struct Counts
{
    long lines;
    long words;
    long bytes;
};

int main(int argc, char *argv[])
{

    bool saw_l = false;
    bool saw_w = false;
    bool saw_c = false;

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

    struct Counts c = lwc(stdin, true, true, true);

    if (saw_l)
    {
        printf("%ld", c.lines);
        if (saw_w || saw_c)
            putchar(' ');
        else
            putchar('\n');
    }

    if (saw_w)
    {
        printf("%ld", c.words);
        if (saw_c)
            putchar(' ');
        else
            putchar('\n');
    }

    if (saw_c)
        printf("%ld\n", c.bytes);

    if (!saw_l && !saw_w && !saw_c)
        printf("%ld %ld %ld\n", c.lines, c.words, c.bytes);

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
