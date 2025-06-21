#include "header/error.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#define READ_BUF 1024
#define WRITE_BUF 1050

size_t concat(char* dest, char* buf1, char* buf2);

void getln()
{
    char buf[READ_BUF];
    int nread = read(0, buf, READ_BUF - 1);
    if (nread == -1)
        handle_err("read stdin");

    buf[nread] = '\0';

    char msg[WRITE_BUF];
    size_t size = concat(msg, "received: ", buf);

    int nwrite = write(1, msg, size);
    if (nwrite != size)
        handle_err("stdout");
}

size_t concat(char* dest, char* buf1, char* buf2)
{
    size_t s = 0;

    for (; *buf1 != '\0'; ++buf1, ++s)
        *(dest++) = *buf1;
    for (; *buf2 != '\0'; ++buf2, ++s)
        *(dest++) = *buf2;

    *(dest) = '\0';
    ++s;

    return s;
}
