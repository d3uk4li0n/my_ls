#include "../include/my_ls.h"
#include "../include/sort.h"
#include "../include/utils.h"

void list_dir_content(char *ppath, struct flags f){
    int path_len = my_strlen(ppath);
    char *path = (char *)malloc(path_len + 2);

    my_strcpy(path, ppath);

    DIR *dirp = open_dir(path);
    if (dirp == NULL) return;
    order *list = NULL;
    struct dirent *rd;
    struct stat st;
    int nfiles = 0;

    if (path[path_len - 1] != '/') my_strcat("/", path);

    while ((rd = readdir(dirp))){
        if ((my_strcmp(rd->d_name, ".") == 0 ||
             my_strcmp(rd->d_name, "..") == 0 || rd->d_name[0] == '.') &&
            !f.a_flag)
            continue;
        else{
            char *temp_d = rd->d_name;
            char *temp = (char *)malloc(sizeof(char *) * 50);  // reallocate it every time
            my_strcpy(temp, path);
            my_strcat(temp_d, temp);
            lstat(temp, &st);
            list = init_list(list, rd->d_name, st.st_mtim);
            nfiles++;
            free(temp);
        }
    }
    if (f.t_flag) modtime_sort(&list, nfiles);
    else alpha_sort(&list, nfiles);

    print_list(list);
    free_list(list);
    closedir(dirp);

    free(path);
}

void find_flags(int argc, char **argv, struct flags *f){
    if(!f) return;
    f->a_flag = false;
    f->t_flag = false;
    for (int i = 1; i < argc; i++){
        if (my_strcmp(argv[i], "-a") == 0) f->a_flag = true;
        else if (my_strcmp(argv[i], "-t") == 0) f->t_flag = true;
        else if ((my_strcmp(argv[i], "-at") == 0) || (my_strcmp(argv[i], "-ta") == 0)){f->a_flag = true; f->t_flag = true;}
        else continue;
    }
}

void handle_cmdline_errors(int argc, char **argv){
    for (int i = 1; i < argc; i++){
        if (!isdir(argv[i]) && !is_file(argv[i]) &&
            !(my_strcmp(argv[i], "-a")) == 0 &&
            !(my_strcmp(argv[i], "-t")) == 0 &&
            !(my_strcmp(argv[i], "-at") == 0 || my_strcmp(argv[i], "-ta") == 0))
            printf("cannot access: %s no such file or directory\n", argv[i]);
    }
    //printf("\n");
}

void handle_cmdline(int argc, char **argv){
    struct flags f;
    find_flags(argc, argv, &f);
    if (argc == 2){
        if (f.a_flag || f.t_flag){
            list_dir_content(".", f);
            return;
        }else if (isdir(argv[1])){
            list_dir_content(argv[1], f);
            return;
        }else if (is_file(argv[1])){
            printf("%s\n", argv[1]);
            return;
        }
        else{}
    }
    if (argc == 3){
        if(f.a_flag || f.t_flag){
            if(f.a_flag && f.t_flag && !isdir(argv[2])){list_dir_content(".", f); return;}
            if(isdir(argv[1]) || isdir(argv[2])){
                isdir(argv[1]) ? list_dir_content(argv[1], f) : list_dir_content(argv[2], f);
                return;
            }
        }
    }
    handle_cmdline_errors(argc, argv);
    for (int i = 1; i < argc; i++){
        if (isdir(argv[i])){
            printf("%s:\n", argv[i]);
            list_dir_content(argv[i], f);
            if (i < argc - 1) printf("\n");
        }
    }
    for (int i = 1; i < argc; i++) if (is_file(argv[i])) printf("%s\t\n", argv[i]);
}

int main(int argc, char **argv){
    struct flags f;
    find_flags(argc, argv, &f);
    // printf("%d %d\n", f.a_flag, f.t_flag);
    if (argc < 2){
        list_dir_content(".", f);
        return 0;
    }
    else{
        handle_cmdline(argc, argv);
    }
    return 0;
}