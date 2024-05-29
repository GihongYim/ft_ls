#include <stdio.h>
#include <dirent.h>
#include "libft.h"

enum fileType {
    file,
    directory,
};


int main(int argc, char* argv[])
{
    char *target = ".";
    if (argc > 3)
        return 0;
    if (argc == 2) {
        target = argv[1];
    }
    DIR * dir = opendir(target);
    struct dirent *dd;
    while (1) {
        dd = readdir(dir);
        if (dd == NULL)
            break;
        printf("%s ", dd->d_name);
        printf("i_no :%llu \n", dd->d_ino);
        printf("namlen: %hu \n", dd->d_namlen);
        printf("reclen: %hu \n", dd->d_reclen);
        printf("d_type: %hhu \n", dd->d_type);

    }
    return 0;
}