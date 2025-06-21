#include "header/error.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char* strcopy(char*, const char*);

void seek(const char* file)
{
    int fd = open(file, O_RDONLY | O_WRONLY | O_CLOEXEC);
    char buf[BUFSIZ];
    if (fd == -1)
        handle_err("file open");

    off_t offset = 10;
    if (lseek(fd, offset, SEEK_END) == -1)
        handle_err("seek");

    int nwrite;
    if (write(fd, strcopy(buf, "hoge"), BUFSIZ) == -1)
        handle_err("write file");

    if (close(fd) == -1)
        handle_err("file close");

    return;
}

char* strcopy(char* buf, const char* str)
{
    char* _start = buf;
    while ((*(buf++) = *(str++)))
        ;

    return _start;
}