#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    FILE *plik = fopen("plik.txt", "w");

    if (plik == NULL) {
        perror("blad otwarcia pliku");
        return 1;
    }

    fprintf(plik, "Rodzic inicjalizacja\n");
    fclose(plik);

    pid_t pid = fork();

    if (pid < 0) {
        perror("blad forka");
        return 1;
    }

    if (pid == 0) {
        FILE *plik = fopen("plik.txt", "a");

        fprintf(plik, "dziecko przetwarza dane\n");
        fclose(plik);
        exit(0);
    } 
    else {
        wait(NULL);
        FILE *plik = fopen("plik.txt", "a");

        fprintf(plik, "rodzic konczy\n");
        fclose(plik);

        char zawartoscPliku[256];
        plik = fopen("plik.txt", "r");

        while (fgets(zawartoscPliku, sizeof(zawartoscPliku), plik)) {
            printf("%s", zawartoscPliku);
        }
        fclose(plik);
    }
}