#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#define PAGE_SIZE (2048*1024) // 2MB
#define NUM_PAGES 1

int main() {
    void *ptr;

    // Allocate HugePages
    ptr = mmap(NULL, NUM_PAGES * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    strcpy(ptr, "Hello, HugePages!");

    printf("%s\n", (char *)ptr); 
    // Use the HugePages
    // ...

    // Free the HugePages
    if (munmap(ptr, NUM_PAGES * PAGE_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}