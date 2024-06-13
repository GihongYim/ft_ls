#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <time.h>
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
static int reverse = false;
static int allOption = false;
int linkWidth = 0;
int userNameWidth = 0;
int groupNameWidth = 0;
int sizeWidth = 0;

int getNumOfFile(char *path) {
    DIR *dir;
    struct dirent * dd = NULL;
    int len = 0;

    dir = opendir(path);
    if (dir == NULL) {
        return -1;
    }
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
    if (len == -1)
        return -1;
    *files = malloc(sizeof(struct dirent*) * len);
    if (*files == NULL) {
        perror("malloc");
        exit(1);
    }

    dir = opendir(path);
    if (dir == NULL) {
        free(*files);
        return -1;
    }
    for (int i = 0; i < len; i++) {
        dd = readdir(dir);
        if (dd == NULL) break;
        (*files)[index] = malloc(sizeof(struct dirent));
        if ((*files)[index] == NULL) {
            perror("malloc");
            closedir(dir);
            for (int i = 0; i < index; i++) {
                free((*files)[i]);
            }
            free(*files);
            exit(1);
        }
        ft_memcpy((*files)[index], dd, sizeof(struct dirent));
        index++;
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

int partitionByName(struct dirent*** files, int left, int right) {
    struct dirent * pivot;
    int             low;
    int             high;

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
    int             low;
    int             high;

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

char *padding(char *str, int len, char *option)
{
    int     slen;
    char*   pad;
    char*   padded;

    slen = ft_strlen(str);
    if (slen >= len) {
        return ft_strdup(str);
    }

    pad = ft_calloc(sizeof(char), len - slen + 1);
    ft_memset(pad, ' ', len - slen + 1);
    pad[len-slen] = '\0';

    if (ft_strcmp(option, "left") == 0)
        padded = ft_strjoin(str, pad);
    else
        padded = ft_strjoin(pad, str);
    free(pad);
    return padded;
}
void printLongFormat(char *dir, char *file) {
    struct stat     statbuf;
    char            *mode = "xwrxwrxwr";
    nlink_t         numOfLinks;
    struct passwd   *userBuf;
    struct group    *groupBuf;
    time_t          mtime;
    char            *timeStr;
    char            *column;
    char            *padded;
    char            *absPath;

    absPath = ft_strjoin(dir, file);

    if (lstat(absPath, &statbuf) == -1) {
        perror("lstat");
        exit(1);
    }

    // file type and permissions
    if (S_ISDIR(statbuf.st_mode)) {
        ft_putchar_fd('d', STDOUT_FILENO);
    } else if (S_ISLNK(statbuf.st_mode)) {
        ft_putchar_fd('l', STDOUT_FILENO);
    } else {
        ft_putchar_fd('-', STDOUT_FILENO);

    }
    for (int i = 8; i >= 0; i--) {
        if ((1 << i) & statbuf.st_mode) {
            ft_putchar_fd(mode[i], STDOUT_FILENO);
        } else {
            ft_putchar_fd('-', STDOUT_FILENO);
        }
    
    }
    ft_putchar_fd(' ', STDOUT_FILENO);

    // number of links

    numOfLinks = statbuf.st_nlink;

    column = ft_itoa(numOfLinks);
    padded = padding(column, linkWidth + 1, "right");
    ft_putstr_fd(padded, STDOUT_FILENO);
    ft_putchar_fd(' ', STDOUT_FILENO);

    free(column);
    free(padded);
    
    // owner of the files

    userBuf = getpwuid(statbuf.st_uid);
    padded = padding(userBuf->pw_name, userNameWidth + 2, "left");
    ft_putstr_fd(padded, STDOUT_FILENO);

    free(padded);

    // group associated with file

    groupBuf = getgrgid(statbuf.st_gid);
    padded = padding(groupBuf->gr_name, groupNameWidth + 1, "left");
    ft_putstr_fd(padded, STDOUT_FILENO);

    free(padded);

    column = ft_itoa(statbuf.st_size);
    padded = padding(column, sizeWidth + 1, "right");
    ft_putstr_fd(padded, STDOUT_FILENO);
    ft_putchar_fd(' ', STDOUT_FILENO);
    
    free(column);

    // last modification data and time
    mtime = statbuf.st_mtime;
    timeStr = ft_substr(ctime(&mtime), 4, 12);
    ft_putstr_fd(timeStr, STDOUT_FILENO);
    ft_putchar_fd(' ', STDOUT_FILENO);
    free(timeStr);

    // file name
    ft_putstr_fd(file, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    free(absPath);
}

void setWidth(char *path)
{
    DIR             *dir;
    struct dirent   *dd;
    struct stat     fileStat;
    char            *str;
    int             lengthOfStr;
    struct passwd   *userBuf;
    struct group    *groupBuf;
    char            *folderPath;
    char            *filePath;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    folderPath = ft_strjoin(path, "/");
    while (1) {
        dd = readdir(dir);
        if (dd == NULL) break;
        filePath = ft_strjoin(folderPath, dd->d_name);
        if (lstat(filePath, &fileStat) == -1) {
            perror(dd->d_name);
            free(folderPath);
            exit(EXIT_FAILURE);
        }
        free(filePath);
        str = ft_itoa(fileStat.st_nlink);
        lengthOfStr = ft_strlen(str);
        if (lengthOfStr > linkWidth) {
            linkWidth = lengthOfStr;
        }
        free(str);
        userBuf = getpwuid(fileStat.st_uid);
        lengthOfStr = ft_strlen(userBuf->pw_name);
        if (lengthOfStr > userNameWidth) {
            userNameWidth = lengthOfStr;
        }

        groupBuf = getgrgid(fileStat.st_gid);
        lengthOfStr = ft_strlen(groupBuf->gr_name);
        if (lengthOfStr > groupNameWidth) {
            groupNameWidth = lengthOfStr;
        }

        str = ft_itoa(fileStat.st_size);
        lengthOfStr = ft_strlen(str);
        if (lengthOfStr > sizeWidth) {
            sizeWidth = lengthOfStr;
        }
        free(str);
    }
    free(folderPath);
}

void printDir(char *path, enum format format, enum sort_type sort_type, int start)
{
    int             numOfFile;
    struct dirent   **files = NULL;
    struct stat     fileStat;
    char            *folderPath;
    char            *filePath;

    numOfFile = getFiles(&files, path);
    sortFileList(&files, numOfFile, sort_type);
    if (format == only_file_name) {
        for (int i = 0; i < numOfFile; i++) {
            if (files[i]->d_name[0] == '.' && allOption == false) continue;
            ft_putstr_fd(files[i]->d_name, STDOUT_FILENO);
            ft_putchar_fd(' ', STDOUT_FILENO);
        }
    } else if (format == long_format) {
        setWidth(path);
        folderPath = ft_strjoin(path, "/");
        for (int i = 0; i < numOfFile; i++) {
            if (files[i]->d_name[0] == '.' && allOption == false) continue;
            printLongFormat(folderPath, files[i]->d_name);
        }
        free(folderPath);
    }
    if (recursive) {
        ft_putchar_fd('\n', STDOUT_FILENO);
        folderPath = ft_strjoin(path, "/");
        for (int i = 0; i < numOfFile; i++) {
            filePath = ft_strjoin(folderPath, files[i]->d_name);
            if (stat(filePath, &fileStat) == -1) {
                perror(files[i]->d_name);
                free(filePath);
                continue;
            }
            if (!S_ISDIR(fileStat.st_mode)) {
                free(filePath);
                continue;
            }
            if (files[i]->d_name[0] == '.' && allOption == false) {
                free(filePath);
                continue;
            }
            if (files[i]->d_name[0] == '.' && start == false) {
                free(filePath);
                continue;
            }
            
            ft_putstr_fd(path, STDOUT_FILENO);
            ft_putchar_fd('/', STDOUT_FILENO);
            ft_putstr_fd(files[i]->d_name, STDOUT_FILENO);
            ft_putstr_fd(":\n", STDOUT_FILENO);
            printDir(ft_strjoin(folderPath, files[i]->d_name), format, sort_type, false);
            perror("ft_ls");
            if (i != numOfFile - 1)
                ft_putchar_fd('\n', STDOUT_FILENO);
            free(filePath);
        }
        free(folderPath);
    }
    for (int i = 0; i < numOfFile; i++) {
        free(files[i]);
    }
    free(files);
}

int main(int argc, char *argv[])
{
    enum format format = only_file_name;
    enum sort_type sort_type = sort_name;
    char *path = NULL;
    
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
                        reverse = true;
                        break;
                    case 't':
                        sort_type = sort_time;
                        break;
                }
            }
        }
    }
    if (argc >= 2 && argv[argc - 1][0] != '-') {
        path = ft_strdup(argv[argc - 1]);
    }
    if (path == NULL) {
        printDir(".", format, sort_type, true);
    } else {
        DIR *dir;

        dir = opendir(path);
        if (dir == NULL) {
            char *errorMessage = NULL;
            errorMessage = ft_strjoin("ft_ls:", path);
            perror(errorMessage);
            free(errorMessage);
        } else {
            printDir(path, format, sort_type, true);
        }
        free(path);
    }
    return 0;
}
