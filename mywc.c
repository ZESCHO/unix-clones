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

    // FILE *fp;
    printf("%s\n", argv[0]);

    if (argc == 1)
    {
        struct Counts c = lwc(stdin, true, true, true);

        printf("%ld %ld %ld", c.lines, c.words, c.bytes);
    }

    // fclose(fp);

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
