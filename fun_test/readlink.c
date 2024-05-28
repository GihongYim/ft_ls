#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    const char *linkPath = "./symlink";
    char buffer[1024];
    ssize_t len;

    len = readlink(linkPath, buffer, sizeof(buffer) - 1);
    if (len == -1) {
        
    }
}