#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/time.h>
#include <utime.h>
#include <string.h>

extern void x_ls(char[]);
extern void x_stat(char *);
extern void x_show_file_info(char *, struct stat *);
extern void x_mode_to_letters(int, char []);
extern char *x_uid_to_name(uid_t);
extern char *x_gid_to_name(gid_t);

