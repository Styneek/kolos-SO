#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);

    mkfifo("fifo", 0666);

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Blad fifo");
        }
        if (pid == 0) {
            srand(getpid());
            int wylosowana = rand() % 100;
            int fd = open("fifo", O_WRONLY);
            if (fd != -1) {
                dprintf(fd, "%d %d\n", getpid(), wylosowana);
                close(fd);
            }
            exit(0);
        }
    }
    int fdCzytam = open("fifo", O_RDONLY);
    int suma = 0;
    int pidDziecka;
    int liczba;

    FILE *fifo = fdopen(fdCzytam, "r");
    for (int i = 0; i <= N; i++) {
        if (fscanf(fifo, "%d %d", &pidDziecka, &liczba) == 2) {
            printf("Odebrano od PID %d: %d\n", pidDziecka, liczba);
            suma += liczba;
        }
    }

    printf("suma %d\n", suma);

    close(fdCzytam);

    for (int i = 0; i <= N; i++) {
        wait(NULL);
    }
    unlink("fifo");
}