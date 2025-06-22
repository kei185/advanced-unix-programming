#define BUFSIZE 1024
#include "header/error.h"
#include <curses.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void copy(char* from, char* to)
{
    int fromfd, tofd, nread, nwrite;
    char buf[BUFSIZE];

    if ((fromfd = open(from, O_RDONLY)) < 0)
        handle_err("open file");

    if ((tofd = creat(to, 0644)) < 0)
        handle_err("create file");

    while ((nread = read(fromfd, buf, BUFSIZE))) {
        if (nread == -1)
            handle_err("read file");

        nwrite = write(tofd, buf, nread);
        if (nwrite != nread)
            handle_err("write file");
    }

    if (close(fromfd) == -1 || close(tofd) == -1)
        handle_err("close file");

    return;
}
