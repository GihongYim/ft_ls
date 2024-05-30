#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include "libft.h"

#define true 1
#define false 0

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

static int recursive = false;
static int allOption = false;

int getFiles(struct dirent** files, char *path) {
    int len = 0;
    struct dirent * dd;
    int index = 0;

    DIR *dir = opendir(path);

    while (1) {
        dd = readdir(dir);
        if (dd == NULL) break;
        len++;
    }
    closedir(dir);
    *files = malloc(sizeof(struct dirent) * len);

    dir = opendir(path);
    for (int i = 0; i < len; i++) {
        dd = readdir(dir);
        if (dd == NULL) break;
        files[index++] = dd;
        printf("%p\n", files[index - 1]);
    }
    closedir(dir);
    return len;
}

void printDir(char *path, enum format format, enum sort_type sort_type) 
{
    // DIR *dir = opendir(path);
    // struct dirent *curr;
    // char *next = NULL;
    int numOfFile;
    struct dirent *files = NULL;

    numOfFile = getFiles(&files, path);
    printf("numOfFile: %d\n", numOfFile);
    for (int i = 0; i < numOfFile; i++) {
        printf("%d: %s\n", i, files[i].d_name);
    }

    sort_type = sort_name;
    format = only_file_name;
    // while (1) {
    //     curr = readdir(dir);
    //     if (curr == NULL)
    //         break;
    //     if (!allOption && curr->d_name[0] == '.') continue;
    //     if (recursive && curr->d_type == DT_DIR) continue;
    //     printf("%s ", curr->d_name);
    // }
    // closedir(dir);
    // if (!recursive) return;
    // dir = opendir(path);
    // while (1) {
    //     curr = readdir(dir);
    //     if (curr == NULL)
    //         break;
    //     if (!allOption && curr->d_name[0] == '.') continue;
    //     if (curr->d_type == DT_DIR)  {
    //         next = ft_strjoin(path, "/");
    //         next = ft_strjoin(next, curr->d_name);
    //         printf("\n");
    //         printDir(next, format, sort_type);
    //     }
    // }
    // closedir(dir);
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
                switch (argv[i][j]) {
                    case 'l':
                    format = long_format;
                    break;
                    case 'R':
                    recursive = 1;
                    break;
                    case 'a':
                    allOption = true;
                    break;
                    case 'r':
                    break;
                    case 't':
                    break;
                }
            }
        }
    }
    printDir(".", format, sort_type);
    printf("\n");
    return 0;
}