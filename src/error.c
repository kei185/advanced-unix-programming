
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_err(const char* context)
{
    const int SIZE = 1024;
    char buf[SIZE];

    strerror_r(errno, buf, SIZE);
    fprintf(stderr, "[ERROR] %s :%s(%d)\n", context, buf,
            errno);
    exit(1);
}