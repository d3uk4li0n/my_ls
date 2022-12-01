order *init_list(order *list, char *file_name, struct timespec st_mtim /*unsigned long long time*/){
    order *new_node;

    new_node = malloc(sizeof(order));
    new_node->file_name = file_name;
    new_node->st_mtim = st_mtim;
    // new_node->time_sec = time;

    new_node->next = list;

    return new_node;
}

order *node_swap(order *first, order *second){
    order *temp = second->next;
    second->next = first;
    first->next = temp;
    return second;
}

void print_list(order *list){
    order *temp = list;
    if (!temp){
        printf("list is empty!");
        return;
    }
    while (temp){
        printf("%s  ", temp->file_name);
        temp = temp->next;
    }
    printf("\n");
}

void alpha_sort(order **head, int nfiles){
    order **h;
    int i = 0, n, swapped;

    while (i <= nfiles){
        h = head;
        swapped = 0;
        n = 0;
        while (n < nfiles - i - 1){
            order *first = *h;
            order *second = first->next;

            if (my_strcmp(first->file_name, second->file_name) == 1){
                *h = node_swap(first, second);
                swapped = 1;
            }
            h = &(*h)->next;
            n++;
        }
        if (swapped == 0) break;
        i++;
    }
}

void modtime_sort(order **head, int nfiles){
    order **h;
    int i, n, swapped;

    i = 0;
    while (i <= nfiles){
        h = head;
        swapped = 0;
        n = 0;
        while (n < nfiles - i - 1){
            order *first = *h;
            order *second = first->next;
            int need_swap = 0;
            if (first->st_mtim.tv_sec < second->st_mtim.tv_sec ||
                (first->st_mtim.tv_sec == second->st_mtim.tv_sec &&
                 first->st_mtim.tv_nsec < second->st_mtim.tv_nsec)){
                need_swap = 1;
            }
            else if (first->st_mtim.tv_sec == second->st_mtim.tv_sec &&
                     first->st_mtim.tv_nsec == second->st_mtim.tv_nsec)
            {  // same same time, compare by file name
                if (my_strcmp(first->file_name, second->file_name) == 1){
                    need_swap = 1;
                }
            }
            if (need_swap == 1){
                *h = node_swap(first, second);
                swapped = 1;
            }
            h = &(*h)->next;
            n++;
        }
        if (swapped == 0) break;
        i++;
    }
}

void free_list(order *list){
    order *temp;
    while (list != NULL){
        temp = list;
        list = list->next;
        free(temp);
    }
}