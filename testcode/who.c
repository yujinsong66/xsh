#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST
#define UTMP_FILE "/var/run/utmpx"

void show_info(struct utmp *utbufp);
void showtime(long);

int main()
{
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }

    close(utmpfd);

    return 0;
}

void show_info(struct utmp *utbufp)
{

    printf("%- 8.8s", utbufp->ut_name);
    printf(" ");
    printf("%- 8.8s", utbufp->ut_line);
    printf(" ");
    printf("%10ld", utbufp->ut_time);
    printf(" ");
    showtime(utbufp->ut_time);
#ifdef SHHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}


void showtime(long timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf("%12.12s", cp + 4);
}
