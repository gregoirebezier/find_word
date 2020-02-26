/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** brute_force.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return (i);
}

int get_size(char *filepath)
{
    int size = 0;
    struct stat *memory = NULL;

    memory = malloc(sizeof(struct stat));
    stat(filepath, memory);
    size = memory->st_size;
    free(memory);
    return (size);
}

char *read_map(char *filepath)
{
    int size = get_size(filepath);
    char *buffer = NULL;
    int fd = open(filepath, O_RDONLY);

    buffer = malloc(sizeof(char) * (size + 1));
    read(fd, buffer, size);
    close(fd);
    if (buffer == NULL)
        return (NULL);
    return (buffer);
}

int my_strcmp(char *s1, char *s2, int size)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] && s2[i] && size > i)
        i = i + 1;
    if (s1[i] == '\0' && s2[i] == '\0')
        return (0);
    else
        return (s1[i] - s2[i]);
}

char **str_to_world_array(int *a, char *buffer)
{
    int k = 0, i = 0, r = 0;
    char **a_position = NULL;
    char *temp = NULL;

    a_position = malloc(sizeof(char * ) * *a + 1);
    while (r < *a) {
        temp = malloc(sizeof(char) * 25 + 1);
        while (buffer[i] != '\n' && buffer[i] != '\0') {
            temp[i] = buffer[i];
            i++;
        }
        buffer = &buffer[i+1];
        a_position[k] = temp;
        i = 0;
        k++;
        r++;
    }
    a_position[k] = NULL;
    return (a_position);
}

int get_size_line(char *map)
{
    static int i = 0;
    int a = 0;

    while (map[i] != '\0') {
        if (map[i] == '\n')
            a++;
        i++;
    }
    return (a);
}

int sort_word(char *line_parsed, char *name)
{
    int i = 0;
    int a = 0;

    while (line_parsed[i+1] != '\0') {
        while (line_parsed[i] != name[a]) {
            if (name[a] == '\0')
                return (1);
            a++;
        }
        if (line_parsed[i] == name[a]) {
            a = 0;
            i++;
        }
    }
    a = 0;
    i = 0;
    while (name[a] != '\0') {
        while (name[a] != line_parsed[i]) {
            if (line_parsed[i] == '\0')
                return (1);
            i++;
        }
        if (line_parsed[i] == name[a]) {
            i = 0;
            a++;
        }
    }
    return (0);
}

int compare_name(char **line_parsed, char *name)
{
    int i = 0;
    int a = 0;
    int j = 0;
    int size = 0;

    while (line_parsed[a] != NULL) {
        size = my_strlen(line_parsed[a]);
        while (i < size) {
            if (my_strlen(name) != my_strlen(line_parsed[a] + 1))
                break;
            if (sort_word(line_parsed[a], name) == 0) {
                j++;
                printf("name : %s\n", line_parsed[a]);
                break;
            }
            else
                break;
        }
        i = 0;
        a++;
    }
    if (j == 0)
        printf("No words found..\n");
    return (0);
}

int brute_force(char *map, char *name)
{
    int i = 0;
    char **arg_parsed = NULL;
    i = get_size_line(map);

    while (1) {
        arg_parsed = str_to_world_array(&i, map);
        if (compare_name(arg_parsed, name) == 1)
            return (0);
        break;
    }
}

void help()
{
    printf("    USAGE\n");
    printf("gcc find_word\n");
    printf("./a.out [DICO] [WORDS_TO_SEARCH]\n       --------------\n");
    printf("example : ./a.out liste_francais.txt rreoad");
    printf("\nname : adorer\n");
}

int main(int ac, char **argv)
{
    char *map = NULL;

    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        help();
        return (84);
    }
    if (ac != 3)
        return 84;
    map = read_map(argv[1]);
    if (map == NULL)
        return (84);
    brute_force(map, argv[2]);
}