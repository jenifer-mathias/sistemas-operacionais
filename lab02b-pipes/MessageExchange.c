/** Considere o exemplo fornecido para troca de mensagens entre pai e filho.
Altere o programa a seguir de modo que a alteração da variável value se reflita no processo pai,
ou seja, o último print do programa deve apresentar o seguinte resultado:
PARENT: value = 20

int value = 5;

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {                                child process
        printf("Entrei no filho!\n");
        value += 15;
        printf ("CHILD: value = %d\n",value);      LINE A
        return 0;
    }
    else if (pid > 0) {                            parent process
        wait(NULL);
        printf ("PARENT: value = %d\n",value);      LINE A/
        return 0;
    }
}  **/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 5;

int main() {
    pid_t pid;

    pid = fork();

    value += 15;

    if (pid == 0) {                                   /** child process **/
        printf("\nEntrei no filho!\n");
        printf ("\nCHILD: value = %d\n",value);       /** LINE A **/
        return 0;
    }
    else if (pid > 0) {                               /** parent process **/
        wait(NULL);
        printf ("\nPARENT: value = %d\n",value);      /** LINE A **/
        return 0;
    }
}
