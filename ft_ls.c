#include <stdio.h>
#include <dirent.h>
#include <sys/dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include "libft.h"


// int main(int argc, char* argv[])
// {
//     char *target = ".";
//     if (argc > 3)
//         return 0;
//     if (argc == 2) {
//         target = argv[1];
//     }
//     DIR * dir = opendir(target);
//     struct dirent *dd;
//     while (1) {
//         dd = readdir(dir);
//         if (dd == NULL)
//             break;
//         printf("%s ", dd->d_name);
//         printf("i_no :%llu \n", dd->d_ino);
//         printf("namlen: %hu \n", dd->d_namlen);
//         printf("reclen: %hu \n", dd->d_reclen);
//         printf("d_type: %hhu \n", dd->d_type);
//         DT_UNKNOWN
//     }
//     return 0;
// }


// only implement option -l -R -a -r -t
// option flag unsigned int (32bits)

enum format 
{
    only_file_name,
    long_format
};

enum sort_type
{
    sort_name,
    sort_time
};

void printDir(char *path, enum format format, enum sort_type sort_type) 
{
    DIR *dir = opendir(path);
    struct dirent *curr;
    char *next = NULL;
    sort_type = sort_name;
    format = only_file_name;
    printf("directory: %s\n", path);
    while (1) {
        curr = readdir(dir);
        if (curr == NULL)
            break;
        if (curr->d_name[0] == '.') continue;
        if (curr->d_type == DT_DIR)  {
            next = ft_strjoin(path, "/");
            next = ft_strjoin(next, curr->d_name);
            printf("\n");
            printDir(next, format, sort_type);
        }
        printf("%s ", curr->d_name);
    }
}


int main(int argc, char *argv[])
{
    unsigned int option = 0;
    enum format format = only_file_name;
    enum sort_type sort_type = sort_name;

    option = 1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int len = ft_strlen(argv[i]);
            for (int j = 1; j < len; j++) {

            }
        }
    }
    printDir(".", format, sort_type);
}