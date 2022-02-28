#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x;
    fork();
    x = 1;
    printf("\n I am process %ld and my x is %d\n", (long) getpid(), x);
    return 0;
}
