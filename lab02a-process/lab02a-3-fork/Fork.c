#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t childPid;
    childPid = fork();
    if (childPid == -1) {
        perror("Failed to fork");
        return 1;
    }
    if (childPid == 0)                                         /** child code */
        printf("\n I am child %ld\n", (long)getpid());
    else                                                      /** parent code */
        printf("\n I am parent %ld\n", (long)getpid());
    return 0;
}