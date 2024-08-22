#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char *mapped_file;

    // 打开文件
    fd = open("example.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 获取文件大小
    off_t file_size = lseek(fd, 0, SEEK_END);

    // 映射文件到内存
    mapped_file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_file == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // 在内存中操作文件内容
    memcpy(mapped_file, "Hello", 6);
    printf("File contents: %s\n", mapped_file);

    // 解除内存映射
    if (munmap(mapped_file, file_size) == -1) {
        perror("munmap");
        exit(1);
    }

    // 关闭文件
    close(fd);

    return 0;
}