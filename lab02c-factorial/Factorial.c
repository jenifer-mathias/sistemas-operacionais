/** Considere o trecho de código em anexo para resolver o seguinte item:
1) Transforme o código em um exemplo multiprocessado

# include <stdio.h>

int main() {
    int i, num, j;
    printf ("Enter the number: ");
    scanf ("%d", &num );

	j = 1;
	for (i = 1; i<=num; i++) {
        j=j*i;
	}

    printf("The factorial of %d is %d\n",num,j);
}
 **/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
int num;

int main() {
  printf("\nInsira um número: ");
  scanf("%i", &num);

  int fd[2];
  pid_t pid;
  pipe(fd);
  pid = fork();

  if (pid > 0) {
    int n;
    int n2 = 1;
    for (int i = num / 2 + 1; i <= num; i++) {
      n2 *= i;
    }
    close(fd[WRITE]);
    read(fd[READ], &n, sizeof(n));
    close(fd[READ]);
    int fatorial = n * n2;
    printf("\nO fatorial de %i é %i\n", num, fatorial);
    _exit(0);
  }
  if (pid == 0) {
    int n = 1;
    for (int i = 1; i <= num / 2; i++) {
      n *= i;
    }

    close(fd[READ]);
    write(fd[WRITE], &n, sizeof(n));
    close(fd[WRITE]);
    pause();
  }
}
