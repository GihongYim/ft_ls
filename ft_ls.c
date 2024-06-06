#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <pwd.h>
#include <stdlib.h>
// for maxos
// #include <sys/dirent.h> 
// #include "libft.h"

// for linux
#include <dirent.h>
#include "./libft/libft.h"

#define true 1
#define false 0

void qsortByName(struct dirent ***files, int left, int right);
void qsortByTime(struct dirent ***files, int left, int right);
int partitionByName(struct dirent*** files, int left, int right);
int partitionByTime(struct dirent*** files, int left, int right);

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

int timeCmp(struct dirent *a, struct dirent *b) {
    struct stat abuf;
    struct stat bbuf;

    time_t        aTime;
    time_t        bTime;


    if (lstat(a->d_name, &abuf) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (lstat(b->d_name, &bbuf) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    aTime = abuf.st_mtime;
    bTime = bbuf.st_mtime;

    if (aTime < bTime) {
        return -1;
    } else if (aTime > bTime) {
        return 1;
    } else {
        return 0;
    }
}

void dirSwap(struct dirent*** files, int low, int high) {
    struct dirent * tmp;

    tmp = (*files)[low];
    (*files)[low] = (*files)[high];
    (*files)[high] = tmp;
}

// int partitionByName(struct dirent*** files, int left, int right) {
//     struct dirent * pivot;
//     int low, high;

    // low = left;
    // high = right + 1;
    // pivot = (*files)[left];

    // do {
    //     do {
    //         low++;
    //     } while (low <= right && nameCmp((*files)[low], pivot) < 0);

    //     do {
    //         high--;
    //     } while (high >= left && nameCmp((*files)[high], pivot) > 0);
            
    //     if (low < high) {
    //         dirSwap(files, low, high);        
    //     }
    // } while (low <= high);
//     dirSwap(files, left, high);
//     return high;
// }

int partitionByName(struct dirent*** files, int left, int right) {
    struct dirent * pivot;
    int low, high;

    low = left;
    high = right;
    pivot = (*files)[left];

    while (low < high) {
        while (low <= right && nameCmp((*files)[low], pivot) <= 0) {
            low++;
        }
        while (nameCmp((*files)[high], pivot) > 0) {
            high--;
        }
        if (low < high) {
            dirSwap(files, low, high);
        }
    }
    dirSwap(files, left, high);
    return high;
}

void qsortByTime(struct dirent*** files, int left, int right) {
    if (left < right) {
        int q = partitionByTime(files, left, right);

        qsortByTime(files, left, q - 1);
        qsortByTime(files, q + 1, right);
    }
}

int partitionByTime(struct dirent*** files, int left, int right) {
    struct dirent * pivot;
    int low ,high;

    low = left;
    high = right;
    pivot = (*files)[left];

    while (low < high) {
        while (low <= right && nameCmp((*files)[low], pivot) <= 0) {
            low++;
        }
        while (nameCmp((*files)[high], pivot) > 0) {
            high--;
        }
        if (low < high) {
            dirSwap(files, low, high);
        }
    }
    dirSwap(files, left, high);
    return high;
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
    nlink_t numOfLinks;
    struct passwd *userBuf;


    lstat(file, &statbuf);

    // file type and permissions
    if (S_ISDIR(statbuf.st_mode)) {
        write(STDOUT_FILENO, "d", 1);
    } else if (S_ISLNK(statbuf.st_mode)) {
        write(STDOUT_FILENO, "l", 1);
    } else {
        write(STDOUT_FILENO, "-", 1);
    }
    for (int i = 8; i >= 0; i--) {
        if ((1 << i) & statbuf.st_mode) {
            write(STDOUT_FILENO, &mode[i], 1);
        } else {
            write(STDOUT_FILENO, "-", 1);
        }
    }
    write(STDOUT_FILENO, " ", 1);

    // number of links

    numOfLinks = statbuf.st_nlink;

    ft_putnbr_fd(numOfLinks, STDOUT_FILENO);
    ft_putchar_fd(' ', STDOUT_FILENO);
    
    // owner of the files

    userBuf = getpwuid(statbuf.st_uid);
    ft_putstr_fd(userBuf->pw_name, STDOUT_FILENO);
    ft_putchar_fd(' ', STDOUT_FILENO);

    // group associated with file

    // file size in bytes

    // last modification data and time

    // file name
    write(STDOUT_FILENO, file, ft_strlen(file));
    write(STDOUT_FILENO, "\n", 1);
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
            write(STDOUT_FILENO, files[i]->d_name, ft_strlen(files[i]->d_name));
            write(STDOUT_FILENO, " ", 1);
        }
    } else if (format == long_format) {
        write(STDOUT_FILENO, "numOfFile: ", ft_strlen("numOfFile: "));
        ft_putnbr_fd(numOfFile, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        for (int i = 0; i < numOfFile; i++) {
            if (files[i]->d_name[0] == '.') continue;
            printLongFormat(files[i]->d_name);
        }
    }
}

int main(int argc, char *argv[])
{
    // unsigned int option = 0;
    enum format format = only_file_name;
    enum sort_type sort_type = sort_name;
    
    // option = 1;
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
    ft_putendl_fd("", STDOUT_FILENO);
    return 0;
}
