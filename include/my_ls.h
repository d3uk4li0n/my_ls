#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stddef.h>

struct flags{
    bool a_flag;
    bool t_flag;
};

typedef struct sort{
    char *file_name;
    //unsigned long long time_sec;
    struct timespec st_mtim;
    struct sort *next;
}order; 

#ifndef MY_LS_C
#define MY_LS_C

void list_dir_content(char *, struct flags);
void find_flags(int, char **, struct flags *);
void handle_cmdline_errors(int, char **);
void handle_cmdline(int, char **);

#endif

#ifndef SORT_H
#define SORT_H

order *init_list(order *, char *, struct timespec st_mtim);
order *node_swap(order *, order *);
void print_list(order *);
void alpha_sort(order **, int);
void modtime_sort(order **, int);
void free_list(order *);

#endif

#ifndef UTILS_H
#define UTILS_H

int my_strlen(const char *);
char *my_strcat(char *, char *);
int my_strcmp(char *, char *);
char *my_strcpy(char *, char *);
DIR *open_dir(char *);
bool is_file(char *);
bool isdir(char *);

#endif
