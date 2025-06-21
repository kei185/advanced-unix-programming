
#include "header/error.h"
#include <dirent.h>   // dirent
#include <fcntl.h>    // open()
#include <inttypes.h> // uintmax_t
#include <stdio.h>    // printf()
#include <sys/dir.h>
#include <sys/mount.h>
#include <sys/stat.h>    // stat()
#include <sys/syscall.h> // syscall()
#include <unistd.h>      // close()

void _stat(const char* file)
{
    // int fd;
    // if ((fd = open(file, O_RDONLY | O_CLOEXEC)) == -1)
    //     handle_err("open file");

    struct stat s;

    if (stat(file, &s) == -1)
        handle_err("stat");

    printf("st_dev: %jd\n", (intmax_t)s.st_dev);
    printf("st_mode: %ju\n", (uintmax_t)s.st_mode);
    printf("st_nlink: %ju\n", (uintmax_t)s.st_nlink);
    printf("st_inode: %ju\n", (uintmax_t)s.st_ino);
    printf("st_uid: %ju\n", (uintmax_t)s.st_uid);
    printf("st_gid: %ju\n", (uintmax_t)s.st_gid);
    printf("st_rdev: %jd\n", (intmax_t)s.st_rdev);
    printf("st_size: %jd\n", (intmax_t)s.st_size);
    printf("st_blocks: %jd\n", (intmax_t)s.st_blocks);
    printf("st_blksize: %jd\n", (intmax_t)s.st_blksize);
    printf("st_flags: %ju\n", (uintmax_t)s.st_flags);
    printf("st_gen: %ju\n", (uintmax_t)s.st_gen);
    printf("st_lspare: %jd\n", (intmax_t)s.st_lspare);
    printf("st_qspare: %jd\n", (intmax_t)s.st_qspare);

    return;
}

// void statfs_(const char* path)
// {
//     struct statfs sfs;
//     if (statfs(path, &sfs) == -1)
//         handle_err("statfs");
//     {
//         printf("", (uint32_t)sfs.f_bsize);
//         printf("", (int32_t)sfs.f_iosize);
//         printf("", (uint64_t)sfs.f_blocks);
//         printf("", (uint64_t)sfs.f_bfree);
//         printf("", (uint64_t)sfs.f_bavail);
//         printf("", (uint64_t)sfs.f_files);
//         printf("", (uint64_t)sfs.f_ffree);
//         printf("", (fsid_t)sfs.f_fsid);
//         printf("", (uid_t)sfs.f_owner);
//         printf("", (uint32_t)sfs.f_type);
//         printf("", (uint32_t)sfs.f_flags);
//         printf("", (uint32_t)sfs.f_fssubtype);
//         printf("", (char)sfs.f_fstypename);
//         printf("", (char)sfs.f_mntonname);
//         printf("", (char)sfs.f_mntfromname);
//     }
// }

void dirstat(const char* dir)
{
    struct stat s;
    struct dirent* de;
    const int BUFSIZE = 4096;
    int fd, nread;
    char buf[BUFSIZE];
    long basep = 0;

    if ((fd = open(dir, O_RDONLY | O_DIRECTORY)) == -1)
        handle_err("open dir");

    if (stat(dir, &s) == -1)
        handle_err("stat");

    if (!S_ISDIR(s.st_mode))
        handle_err("not directory");

    if ((nread = syscall(SYS_getdirentries64, fd, buf, BUFSIZE, &basep)) == -1)
        handle_err("get directory entries");

    printf("basep: %ld\n", basep);
    printf("nread: %d\n", nread);

    off_t offset = 0;
    while (offset < nread) {

        de = (struct dirent*)(buf + offset);

        printf("d_ino: %ju\n", (uintmax_t)de->d_ino);
        printf("d_seekoff: %ju\n", (uintmax_t)de->d_seekoff);
        printf("d_reclen: %ju\n", (uintmax_t)de->d_reclen);
        printf("d_namlen: %ju\n", (uintmax_t)de->d_namlen);
        printf("d_type: %ju\n", (uintmax_t)de->d_type);
        printf("d_name: %s\n", de->d_name);
        printf("------------------------------------\n");

        offset += de->d_reclen;
    }

    printf("size of super block %lu\n", sizeof(statfs));

    close(fd);
}
