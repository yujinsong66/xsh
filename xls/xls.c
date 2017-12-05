#include "xls.h"

void x_ls(char dirname[])
{
    DIR *dir;
    struct dirent *dp;
    if ((dir = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls: cannot open %s\n", dirname);
    } else {
        while ((dp = readdir(dir)) != NULL) {
            x_stat(dp->d_name);
        }
        closedir(dir);
    }
}

void x_stat(char *filename)
{
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename);
    } else {
        x_show_file_info(filename, &info);
    }
}

void x_show_file_info(char *filename, struct stat *info_p)
{
    char modestr[11];
    x_mode_to_letters(info_p->st_mode, modestr);
    printf("%s", modestr);

    printf("%4d ", (int) info_p->st_nlink);
    printf("%-8s ", x_uid_to_name(info_p->st_uid));
    printf("%-8s ", x_gid_to_name(info_p->st_gid));

    printf("%8ld ", (long)info_p->st_size);
    printf("%.12s ", 4 + ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}


void x_mode_to_letters(int mode, char str[])
{
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

char *x_uid_to_name(uid_t uid)
{
    struct passwd *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d ", uid);
        return numstr;
    }

    else {
        return pw_ptr->pw_name;
    }
}


char *x_gid_to_name(gid_t gid)
{
    struct group *grp_ptr;
    static char numstr[10];
    if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else {
        return grp_ptr->gr_name;
    }
}


int main(int argc, char *argv[])
{
    if(argc == 1) {
        x_ls(".");
    } else {
        while (--argc) {
            printf("%s:\n", * ++argv);
            x_ls(*argv);
        }
    }

}

