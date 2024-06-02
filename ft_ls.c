#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <stdlib.h>
#include "libft.h"

#define true 1
#define false 0

void qsortByName(struct dirent ***files, int left, int right);
void qsortByTime(struct dirent ***files, int left, int right);
int partitionByName(struct dirent*** files, int left, int right);

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

int getNumOfFile(char *path) {
    DIR *dir;
    struct dirent * dd;
    int len = 0;

    dir = opendir(path);
    while (1) {
        dd = readdir(dir);
        if (dd == NULL) break;
        len++;
    }
    closedir(dir);
    return len;
}

int getFiles(struct dirent*** files, char *path) {
    int len;
    struct dirent * dd;
    int index = 0;
    DIR *dir;

    len = getNumOfFile(path);
    
    *files = malloc(sizeof(struct dirent*) * len);

    dir = opendir(path);
    for (int i = 0; i < len; i++) {
        dd = readdir(dir);
        if (dd == NULL) break;
        (*files)[index++] = dd;
    }
    closedir(dir);
    return len;
}

void qsortByName(struct dirent*** files, int left, int right) {
    if (left < right) {
        int q = partitionByName(files, left, right);

        qsortByName(files, left, q - 1);
        qsortByName(files, q + 1, right);
    }
}

int ft_strcmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (*a > *b) - (*a < *b);
}

int nameCmp(struct dirent * a, struct dirent * b) {
        return ft_strcmp(a->d_name, b->d_name);
}

void dirSwap(struct dirent*** files, int low, int high) {
    struct dirent * tmp;

    tmp = (*files)[low];
    (*files)[low] = (*files)[high];
    (*files)[high] = tmp;
}

int partitionByName(struct dirent*** files, int left, int right) {
    struct dirent * pivot;
    int low, high;

    low = left;
    high = right + 1;
    pivot = (*files)[left];

    do {
        do {
            low++;
        } while (low <= right && nameCmp((*files)[low], pivot) < 0);

        do {
            high--;
        } while (high >= left && nameCmp((*files)[high], pivot) > 0);
            
        if (low < high) {
            dirSwap(files, low, high);        
        }
    } while (low <= high);
        dirSwap(files, left, high);
    return high;
}

void qsortByTime(struct dirent*** files, int left, int right) {
    left = 0;
    right = 0;
    files = 0;
}



void sortFileList(struct dirent*** files, int numOfFile, enum sort_type sort_type)
{
    switch (sort_type){
    case sort_name:
        qsortByName(files, 0, numOfFile - 1); break;
    case sort_time:
        qsortByTime(files, 0, numOfFile - 1); break;
    }
}

void printLongFormat(char *file) {
    struct stat statbuf;
    char *mode = "xwrxwrxwr";
    lstat(file, &statbuf);

    if (S_ISDIR(statbuf.st_mode)) {
        printf("d");
    } else if (S_ISLNK(sta`tbuf.st_mode)) {
        printf("l");
    } else {
        printf("-");
    }
    for (int i = 8; i >= 0; i--) {
        if ((1 << i) & statbuf.st_mode) {
            printf("%c", mode[i]);
        } else {
            printf("-");
        }
    }
    printf(" %s\n",file);
}

void printDir(char *path, enum format format, enum sort_type sort_type) 
{
    int numOfFile;
    struct dirent **files = NULL;

    numOfFile = getFiles(&files, path);
    sortFileList(&files, numOfFile, sort_type);

    if (format == only_file_name) {
        for (int i = 0; i < numOfFile; i++) {
            if (files[i]->d_name[0] == '.') continue;
            printf("%s ", files[i]->d_name);
        }
    } else if (format == long_format) {
        printf("numOfFile: %d\n", numOfFile);
        for (int i = 0; i < numOfFile; i++) {
            if (files[i]->d_name[0] == '.') continue;
            printLongFormat(files[i]->d_name);
        }
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
