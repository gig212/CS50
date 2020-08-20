#include "dictionary.h"
#include <string.h>
#include <stdio.h>
#define N 85000
#define M 3

char t[N][M][45];

unsigned int cn = 0;

unsigned int hash(const char *s)
{
    unsigned long h = 0;
    while (*s)
    {
        h = 101 * h + *s++;
    }
    return (h ^ (h >> 16)) % N;
}

bool check(const char *word)
{

    char lw[LENGTH + 1];
    char *p;
    strcpy(lw, word);

    for (p = lw; *p; p++)
        if (*p > 64 && *p < 91)
            *p = *p + 32;

    int i = hash(lw), j = 0;

    while (t[i][j][0] != 0)
    {
        if (strcmp(t[i][j++], lw) == 0)
            return true;
    }

    return false;
}

bool load(const char *dictionary)
{

    FILE *dc = fopen(dictionary, "r");
    if (dc == NULL)
        return false;

    char bf[LENGTH + 1];
    int i, j;

    while (fscanf(dc, "%s", bf) != EOF)
    {
        i = hash(bf);
        j = 0;

        while (t[i][j][0])
            j++;

        strcpy(t[i][j], bf);
        cn++;
    }
    fclose(dc);

    return true;
}

unsigned int size(void)
{
    return cn;
}

bool unload(void)
{
    return true;
}