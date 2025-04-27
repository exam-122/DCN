#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>  

#define FIFO_NAME "/tmp/crc_fifo"
#define MAX_SIZE 32  

// Function to check if divisor is valid
int is_valid_divisor(const char *divisor) {
    int len = strlen(divisor);


    if (len < 2 || divisor[0] != '1' || divisor[len - 1] != '1') {
        return 0;  
    }
    return 1;  
}

int main() {
    int fd;
    char divisor[MAX_SIZE];
    pid_t pid;


    mkfifo(FIFO_NAME, 0666);


    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

  
    if (pid == 0) {
        sleep(1);  
        printf("\n[Receiver] Waiting for divisor...\n");

     
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("Error opening FIFO for reading");
            exit(1);
        }

 
        read(fd, divisor, MAX_SIZE);
        close(fd);

        printf("[Receiver] Received divisor: %s\n", divisor);

 
        if (is_valid_divisor(divisor)) {
            printf("[Receiver]  Valid CRC divisor.\n");
        } else {
            printf("[Receiver]  Invalid CRC divisor. (Must start and end with 1 and be at least 2 bits long)\n");
        }

     
        unlink(FIFO_NAME);

    } 
   
    else {
        printf("[Sender] Enter CRC Divisor in binary format: ");
        scanf("%s", divisor);

      
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("Error opening FIFO for writing");
            exit(1);
        }

        
        write(fd, divisor, strlen(divisor) + 1);
        close(fd);

        printf("[Sender] Divisor sent to receiver.\n");

        wait(NULL);  
    }

    return 0;
}