#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static void sighandler(int sig) {
    if (sig == SIGINT) {
        char msg[50] = "program exited due to SIGINT\n";
        int file = open("msg.txt", O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 600);
        if (file == -1) {
            printf("Creating new file error: %s\n", strerror(errno));
        }
        int add = write(file, msg, sizeof(msg));
        if (add == -1) {
            printf("Writing to file error: %s\n", strerror(errno));
        }
        exit(0);
    }
    if (sig == SIGUSR1) {
        printf("ppid: %d\n", getppid());
    }
}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while (1) {
        printf("pid: %d\n", getpid());
        sleep(1);
    }
    return 0;
}