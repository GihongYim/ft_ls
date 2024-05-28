#include <sys/xattr.h>
#include <errno.h>
#include <stdio.h>

int main() {
    const char *filePath = "./listxattr.c";
    const char *attrName = "user.comment";
    const char *attrValue = "This is a test comment";
    size_t valueSize = sizeof(attrValue);

    int result = setxattr(filePath, attrName, attrValue, valueSize, 0, 0);

    if (result == -1) {
        perror("setxattr");
    } else {
        printf("Excented attribute set successfully\n");
    }
    return 0;
}