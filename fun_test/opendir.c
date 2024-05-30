#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{
	DIR	*dd = opendir("..");

	if (dd == NULL) {
		perror("not directory");
		return 1;
	}

	struct dirent *dp;

	while (dp = readdir(dd)) {
		printf("d_name: %s\n", dp->d_name);
		printf("d_ino: %d\n", dp->d_ino);
		// printf("d_off: %d\n", dp->d_off);
		printf("d_reclen: %ud\n", dp->d_reclen);
		printf("d_type: %uc\n", dp->d_type);
		printf("sizeof(dp): %d\n", sizeof(dp));
		putchar('\n');
	}

	return 0;
}