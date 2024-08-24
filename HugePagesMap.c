#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define HUGEPAGE_SIZE (2 * 1024 * 1024)  // 2MB HugePage size

int main() {
    int fd;
    void *addr;
    size_t length = HUGEPAGE_SIZE;

    // Open the file descriptor for hugepage memory
    fd = open("/dev/hugepages/my_hugepage", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Allocate hugepage memory using mmap
    addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }


    // Write to the memory
    snprintf((char *)addr, length, "This is a huge page memory allocation example.");

    // Read from the memory
    printf("Read from huge page memory: %s\n", (char *)addr);

    // Clean up
    if (munmap(addr, length) == -1) {
        perror("munmap");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}
