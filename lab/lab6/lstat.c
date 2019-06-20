/*
 * Illustrating various stuff about calling lstat().
 * Note that if you change lstat() to stat() below, it will _never_ say that
 * the target is a symlink -- it follows the symlink.  The purpose of lstat()
 * is to suppress this normal following of the symlink.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char **argv)
{
    int i, status = 0;
    struct stat statbuf;

    if (argc == 1) {
	fprintf(stderr, "usage: %s file ...\n", argv[0]);
	return(1);
    }

    for (i = 1; i < argc; i++) {
	if (lstat(argv[i], &statbuf)) {
	    perror(argv[i]);
	    status = 1;
	} else {
	    /*
	     * Here we show various attributes of the file that we can find
	     * in the "stat" struct
	     */

	    if (S_ISDIR(statbuf.st_mode))
		printf("%s is a directory\n", argv[i]);
	    if (S_ISREG(statbuf.st_mode))
		printf("%s is a plain file\n", argv[i]);
	    if (S_ISLNK(statbuf.st_mode))
		printf("%s is a symlink\n", argv[i]);

	    printf("%s has owner (uid) %d and group %d\n", argv[i],
		    statbuf.st_uid, statbuf.st_gid);

	    printf("%s has link count %d\n", argv[i], (int)statbuf.st_nlink);

	    printf("%s has mode %o", argv[i], statbuf.st_mode);
	    printf(" (%o is the permissions part)\n", statbuf.st_mode & 0777);
	    if (statbuf.st_mode & 0200)
		printf("%s is owner-writable\n", argv[i]);
	    if (statbuf.st_mode & 020)
		printf("%s is group-writable\n", argv[i]);
	    if (statbuf.st_mode & 2)
		printf("%s is writable by other\n", argv[i]);

	    /* ctime()'s return value includes a \n, which is silly but true */
	    /* see time.c for more example time stuff */
	    printf("%s was last modified %s", argv[i], ctime(&statbuf.st_mtime));
	    printf("%s was last accessed %s", argv[i], ctime(&statbuf.st_atime));
	    printf("%s's ctime is %s", argv[i], ctime(&statbuf.st_ctime));

	}
    }

    return(status);
}
