#include <fcntl.h>
#include <unistd.h>

int mproc()
{
    // execl("/bin/ls", "ls", "-l", ".", NULL);
    // execl("omain", "statdir", ".", NULL);

    write(1, "hello", 5);

    return 0;
}
