#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{
	DIR	*dd = opendir(".");

	struct dirent *dp;

	for (dp == readdir(dd); dp != NULL; dp = readdir(dd)) {
		
	}

	return 0;
}