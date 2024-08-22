#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* shm_name = "/my_shared_memory";
    const int shm_size = 4096;

    // Create a shared memory object
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, shm_size) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map the shared memory object into the process's address space
    void* shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Write data to the shared memory
    sprintf((char*)shm_ptr, "Hello, shared memory!");

    // Read data from the shared memory
    printf("Data read from shared memory: %s\n", (char*)shm_ptr);

    // Unmap the shared memory object
    if (munmap(shm_ptr, shm_size) == -1) {
        perror("munmap");
        exit(1);
    }

    // Close the shared memory object
    if (close(shm_fd) == -1) {
        perror("close");
        exit(1);
    }

    // Remove the shared memory object
    if (shm_unlink(shm_name) == -1) {
        perror("shm_unlink");
        exit(1);
    }

    return 0;
}