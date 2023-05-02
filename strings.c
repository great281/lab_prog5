#include <stdlib.h>

int is_letter(char c)
{
    if((c > 172 || c < 141) && (c < 101 || c > 132))
        return -1;
    return 0;
}

int slen(char *str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}

int sspn(char c)
{
    if(c == '"' || c == '*' || c == ':' || c == '<' || c == '>' || c == '?' || c == '\\' || c == '|')
        return -1;
    return 0;
}

int scmp(char *str1, char *str2)
{
    int j = 0, size_str1, size_str2;

    size_str1 = slen(str1);
    size_str2 = slen(str2);

    for(int i = 0; i < size_str1; i++)
    {
        if(str1[i] == str2[j])
        {
            i++;
            j++;
            while(str1[i] == str2[j] && j < size_str2)
            {
                i++;
                j++;
            }
            if((j + 1) == size_str2)
                return i - j;
        }
    }

    return -1;
}

char *scpy(char *str, int i)
{
    int j = 0, size = 64, k = 2;      
    char *strcpy;

    strcpy = calloc(sizeof(char), size);
    if(strcpy == NULL)
        return NULL;

    while(str[i] != '\0')
    {
        strcpy[j] = str[i];
        i++;
        j++;
        if(j == size - 1)
        {
            strcpy = realloc(str, sizeof(char) * size * k);
            size *= 2;
            if(strcpy == NULL)
                return NULL;
        }
    }
    strcpy[j] = '\0';

    return strcpy;
}

int stok(char *str, char sim)
{
    int size, change = 1;
    size = slen(str);
    for(int i = 0; i < size; i++)
    {
        if(str[i] == sim)
        {
            str[i] = '\0';
            change++;
        }
    }
    return change;
}

char *concat(char *str1, char *str2, char sim)
{
    char *concat;
    int size1, size2, sizecat = 64, i = 0, k = 2;
    size1 = slen(str1);
    size2 = slen(str2);

    if(str1 == NULL || str2 == NULL)
        return NULL;
    
    concat = calloc(sizeof(char), sizecat);
    if(concat == NULL)
        return NULL;

    for(i = 0; i < size1; i++)
    {
        concat[i] = str1[i];
         if(i == sizecat - 1)
        {
            concat = realloc(concat, sizeof(char) * sizecat * k);
            sizecat *= k;
            if(concat == NULL)
                return NULL;
        }
    }
    for(int j = 0; j < size2; j++)
    {
        if(str2[j] == sim)
            continue;
        concat[i] = str2[j];
        i++;
        if(i == sizecat - 1)
        {
            concat = realloc(concat, sizeof(char) * sizecat * k);
            sizecat *= k;
            if(concat == NULL)
                return NULL;
        }
    }
    concat[i] = '\0';

    return concat;
}