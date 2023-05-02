#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#define MAX_PATH 260

void free_paths(char **paths, int size)
{
    int i;
    for(i = 0; i < size + 1; i++)
    {
        free(paths[i]);
    }
    free(paths);
}

char *input()
{
    char *str, c;
    int i = 0, k = 2, size = 64;
    str = calloc(sizeof(char), size);
    if(str == NULL)
        return NULL;
    while((c = getchar()) != '\n')
    {
        str[i] = c;
        i++;
        if(i == size - 1)
        {
            str = realloc(str, sizeof(char) * size * k);
            size *= 2;
            if(str == NULL)
                return NULL;
        }
    }
    str[i] = '\0';
    return str;
}

int check(char *str, int *num)
{
    int i = 0;
    if(str == NULL)
        return -4;
    while(str[i] != '\0')
    {
        if(i == MAX_PATH)
            return -1;
        if(str[i] == ':' && (is_letter(str[i - 1]) == -1 || str[i + 1] != '/'))
            return -2;
        if(sspn(str[i]) == -1)
            return -3;
        
        *num = ++i;
    }
    return 0;
}

char **procces(char *dir, char *str, char delim, int *i)
{
    char **new_paths;
    int size_str = slen(str), change, change_it = 0, last = 0;

    change = stok(str, delim);

    new_paths = malloc(sizeof(char *) * change);
        
    for(int j = 0; j < size_str; j++)
    {
        if(str[j] == '\0')
        {
            new_paths[change_it] = scpy(str, last);
            last = j + 1;
            change_it++;
        }
    }
    new_paths[change_it] = scpy(str, last);

    for(int i = 0; i < change; i++)
    {
        for(int j = 0; new_paths[i][j] != '\0'; j++)
        {
            if(new_paths[i][j] == '~' && new_paths[i][j + 1] == '/')
                new_paths[i] = concat(dir, new_paths[i], '~');
        }
    }
    *i = change - 1;
    return new_paths;
}

void output(char **str, char delim, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%s%c", str[i], delim);
    }
    printf("%s", str[i]);
}

void show_error(char *str, int column)
{
    printf("%s\n", str);
    for(int j = 0; j < column; j++)
        printf(" ");
    printf("^\n");
}

void output_error(char *str, int mode, int column)
{
    if(mode == -1)
        printf("Path length limit exceeded ( < 260)\n");
    if(mode == -2)
    {
        show_error(str, column);
        printf("Use rule violated for ':' in %d column\n", column);
    }
    if(mode == -3)
    {
        show_error(str, column);
        printf("Illegal character for filename\n");
    }
    if(mode == -4)
        printf("Error in memory allocation function\n");
}

int main()
{
    char *name, *dir, *paths, **new_paths;
    char delim;
    int i, check_str, size;

    printf("delim: ");
    delim = getchar();
    while(getchar() != '\n')
        continue;

    printf("user name: ");
    name = input();
    if((check_str = check(name, &i)) != 0)
    {
        output_error(name, check_str, i);
        return -1;
    }

    printf("dir: ");
    dir = input();
    if((check_str = check(dir, &i)) != 0)
    {
        output_error(dir, check_str, i);
        return -1;
    }

    printf("paths: ");
    paths = input();
    if((check_str = check(paths, &i)) != 0)
    {
        output_error(paths, check_str, i);
        return -1;
    }

    new_paths = procces(dir, paths, delim, &size);
    for(int j = 0; j < size; j++)
    {
        if((check_str = check(new_paths[j], &i)) != 0)
        {
            output_error(new_paths[j], check_str, i);
            return -1;
        }
    }


    printf("new paths: ");
    output(new_paths, delim, size);

    free(name);
    free(dir);
    free(paths);
    free_paths(new_paths, size);
    printf("\nEnd.\n");

    return 0;
}