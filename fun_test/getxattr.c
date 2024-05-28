#include <sys/xattr.h>
#include <errno.h>
#include <stdio.h>

int main() {
    const char *filePath = "./listxattr.c";
    const char *attrName = "user.comment";
    char buffer[100];
    ssize_t result;

    result = getxattr(filePath, attrName, buffer, sizeof(buffer), 0, 0);
    if (result == -1) {
        perror("getxattr");
    } else {
        printf("Extended attribute value: %s\n", buffer);
    }

    return 0;
}
