#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define FIFO_A "fifo_A"
#define FIFO_B "fifo_B"

int main() {
    mkfifo(FIFO_A, 0666);
    mkfifo(FIFO_B, 0666);

    pid_t pid = fork();

    if (pid < 0) {
        perror("blad fifo");
        return 1;
    }
    else if (pid == 0) {
        char buffor[10];
        int fdA = open(FIFO_A, O_RDONLY);
        read(fdA, buffor, sizeof(buffor));
        printf("Dziecko odbiera: %s z %s\n", buffor, FIFO_A);
        close(fdA);

        int fdB = open(FIFO_B, O_WRONLY);
        write(fdB, "PONG", 5);
        close(fdB);

        exit(0);
    }
    else {
        char buffor[10];
        int fdA = open(FIFO_A, O_WRONLY);
        write(fdA, "PING", 5);
        close(fdA);

        int fdB = open(FIFO_B, O_RDONLY);
        read(fdB, buffor, sizeof(buffor));
        printf("Rodzic odbiera: %s z %s\n", buffor, FIFO_B);
        close(fdB);

        wait(NULL);
        unlink(FIFO_A);
        unlink(FIFO_B);
    }
}