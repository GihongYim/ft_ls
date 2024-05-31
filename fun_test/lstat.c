#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <time.h> 
#define BUF_SIZE 1024;
void printType(const char *name, const struct stat *buf) {
       if(S_ISDIR(buf->st_mode))   
                printf("%s is DIR \n",name);  
        else if(S_ISREG(buf->st_mode))  
                printf("%s is FILE\n", name);  
        else if(S_ISSOCK(buf->st_mode))    
                printf("%s is SOCKET\n",name);   
        else if(S_ISCHR(buf->st_mode))   
                printf("%s is CHARACTER DEVICE\n",name);    
        else if(S_ISFIFO(buf->st_mode))    
                printf("%s is FIFO\n",name);     
        else if(S_ISBLK(buf->st_mode))   
                printf("%s is BLOCK DEVICE\n",name);   
        else if(S_ISLNK(buf->st_mode))   
                printf("%s is LINK\n",name); 
}

void printTime(struct stat *buf) {
    struct tm *mtime;
    mtime = localtime(&buf->st_mtime);
    printf("%04d-%02d-%02d %02d:%02d\n",
                        mtime->tm_year+1900, mtime->tm_mon+1,
                        mtime->tm_mday, mtime->tm_hour,  
                        mtime->tm_min);
}

void printFileSize(const char *name, struct stat *buf){      
        printf("%s size: %lld\n",name, buf->st_size); 
}  

int main() {
//     char filename_dir[128] = "dir";
    char filename_file[128] = "aaa";
//     struct stat dir;
    struct stat file;

//     lstat(filename_dir, &dir);   
    lstat(filename_file, &file);

//     printType(filename_dir, &dir);
//     printTime(&dir);
//     printFileSize(filename_dir, &dir);
//     printf("\n");

    printType(filename_file, &file);
    printTime(&file);
    printFileSize(filename_file, &file);
    printf("st_mode :%d\n", file.st_mode); 
    printf("\n");

}