#include <stdio.h>
#include <dirent.h>
#include "libft.h"
#include "flag.h"

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
    }
    return 0;
}