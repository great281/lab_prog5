#include <stdlib.h>

int is_letter(char c)
{
    if((c > 172 || c < 141) && (c < 101 || c > 132))
        return -1;
    return 0;
}

int slen(char *str)
{
    if(str == NULL)
        return 0;
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}

int sspn(char *str1, char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int size1 = slen(str1), size2 = slen(str2);
    for(int i = 0; i < size1; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            if(str1[i] == str2[j])
                return i;
        }
    }
    return size1;
}


int scmp(char *str1, char *str2)
{
    int size1 = slen(str1), size2 = slen(str2), size;

    if(size1 > size2)
        size = size1;
    else
        size = size2;

    for(int i = 0; i < size; i++)
    {
        if(str1[i] != str2[i])
            return str1[i] - str2[i];
    }
    return 0;
}

char *scpy(char *dest, char *src)
{
    if(src == NULL || dest == NULL)
        return NULL;

    int size = slen(src);
    for(int i = 0; i < size; i++)
        dest[i] = src[i];
    dest[size] = '\0';
    return dest;
}

int scout(char *str, char delim)
{
    if(str == NULL)
        return -1;

    int cout = 0, size = slen(str);
    for(int i = 0; i < size; i++)
    {
        if(str[i] == delim)
            cout++;
    }
    return cout;
}

char *stok(char *str, char delim)
{
    if(str == NULL)
        return NULL;

    int size = slen(str);
    for(int i = 0; i < size + 1; i++)
    {
        if(str[i] == delim)
        {
            str[i] = '\0';
            return str;
        }
        else if(str[i] == '\0')
            return str;
    }
    
    return NULL;
}

char *concat (char *dest, char *append)
{
    if(dest == NULL || append == NULL)
        return NULL;

    int size_dest = slen(dest);
    int size_append = slen(append);
    int j = 0;
    for(int i = size_dest; i < size_dest + size_append; i++)
    {
        dest[i] = append[j];
        j++;
    }
    return dest;
}