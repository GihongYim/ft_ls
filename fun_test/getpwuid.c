#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct  passwd *pwd;
    char    buf[1024];
    size_t  bufsize;
    int     ret;

    errno = 0;

    if ((pwd = getpwuid(getuid())) == NULL) {
        if (errno == 0 || errno == ENOENT || errno == ESRCH || errno == EBADF || errno == EPERM) {
            printf("미등록 된 사용자입니다.\n");
            return 1;
        } else {
            printf("errno: %s\n", strerror(errno));
            return 1;
        }
    }

    printf("User Id: %s\nHome Dir: %s\n", pwd->pw_name, pwd->pw_dir);
    
    return 0;
}