#include <stdio.h>
#include <unistd.h>
#include <grp.h>

int main(int argc, char **argv) {
    struct group *gr = NULL;

    gr = getgrgid(getgid());

    printf("group id: %d\n", gr->gr_gid);   
    printf("group name: %s\n", gr->gr_name);   

    return 0;
}