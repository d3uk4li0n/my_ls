int my_strlen(const char *s){
    if (s == NULL) return -1;
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

char *my_strcat(char *src, char *dst){
    int i;
    int dst_len = my_strlen(dst);

    for (i = 0; src[i] != '\0'; i++){
        dst[dst_len] = src[i];
        dst_len += 1;
    }
    dst[dst_len] = '\0';
    return dst;
}

int my_strcmp(char *s1, char *s2){
    int i = 0;
    while ((s1[i] != '\0') || (s2[i] != '\0')){
        if (s1[i] > s2[i]) return 1;
        if (s1[i] < s2[i]) return -1;
        i++;
    }
    return 0;
}

char *my_strcpy(char *dst, char *src){
    int i;
    for (i = 0; i < my_strlen(src) && src[i] != '\0'; i++){
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}

DIR *open_dir(char *path){
    DIR *dirp = opendir(path);
    if (dirp == NULL) printf("error opening %s: No such file or directory\n", path);
    return dirp;
}

bool is_file(char *filename){
    struct stat st;
    if (stat(filename, &st) != 0){
        // printf("error: %s doesn't exist\n", filename);
        return false;
    }
    if ((st.st_mode & S_IFMT) == S_IFDIR) return false;
    return true;
}

bool isdir(char *path){
    struct stat st;
    if (stat(path, &st) != 0) return false;
    if (S_ISDIR(st.st_mode)) return true;
    return false;
}