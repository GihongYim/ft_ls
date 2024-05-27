#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) 
{

	struct stat sb;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <parameter>\n", argv[0]);
		return 1;
	}

	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return 1;
	}

	printf("File type: 			");

	 switch (sb.st_mode & __S_IFMT) {
        case __S_IFBLK:  printf("block device\n");            break;
        case __S_IFCHR:  printf("character device\n");        break;
        case __S_IFDIR:  printf("directory\n");               break;
        case __S_IFIFO:  printf("FIFO/pipe\n");               break;
        case __S_IFLNK:  printf("symlink\n");                 break;
        case __S_IFREG:  printf("regular file\n");            break;
        case __S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }

	printf("I-node number:				%ld\n", (long) sb.st_ino);
	printf("mode:						%lo (octal)\n", (unsigned long) sb.st_mode);
	printf("Link count:					%ld\n", (long) sb.st_nlink);
	printf("Ownership: 					UID=%ld  GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	printf("Preffered I/O block size:	%ld bytes\n", (long) sb.st_blksize);
	printf("File size:				:	%lld bytes\n", (long long) sb.st_size);
	printf("B;locks allocated:		:	%lld\n", (long long) sb.st_blocks);
	printf("Last status change:			%s", ctime(&sb.st_ctime));
    printf("Last file access:			%s", ctime(&sb.st_atime));
    printf("Last file modification:		%s", ctime(&sb.st_mtime));

	return 0;
}

