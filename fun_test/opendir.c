#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


int dirSize(char *dir) {
	DIR *dd = opendir(dir);
	int len = 0;
	struct dirent *dp;

	while (1) {
		dp = readdir(dd);
		if (dp == NULL)	break;
		len++;
	}
	printf("%d\n", len);
	return len;
}

int main(void)
{
	DIR	*dd = opendir("..");

	if (dd == NULL) {
		perror("not directory");
		return 1;
	}

	// printf("__dd_buf: %s\n", dd->__dd_buf);
	// printf("__dd_len: %d\n", dd->__dd_len);
	// printf("__dd_loc: %ld\n", dd->__dd_loc);
	// printf("__dd_size: %ld\n", dd->__dd_size);
	int len = dirSize("..");
	// struct dirent *dp;

	// while (dp = readdir(dd)) {
	// 	printf("d_name: %s\n", dp->d_name);
	// 	printf("d_ino: %d\n", dp->d_ino);
	// 	// printf("d_off: %d\n", dp->d_off);
	// 	printf("d_reclen: %ud\n", dp->d_reclen);
	// 	printf("d_type: %uc\n", dp->d_type);
	// 	printf("sizeof(dp): %d\n", sizeof(dp));
	// 	putchar('\n');
	// }
	closedir(dd);

	return 0;
}