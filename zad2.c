#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Blad forka");
            return 1;
        }
        if (pid == 0) {
            printf("potomek: %d PID dziecka: %d PID rodzica: %d\n", i, getpid(), getppid());
            exit(i);
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        pid_t piddziecka = wait(&status);

        if (WIFEXITED(status)) {
            int statusOdebrany = WEXITSTATUS(status);
            printf("Potomek o PID %d, status %d\n", piddziecka, statusOdebrany);
        }
    }
}