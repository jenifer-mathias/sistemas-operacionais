# Project-02 

# Implementação

O exemplo a seguir, implementado na linguagem C1, apresenta uma operação de transferência de fundos entre duas contas:

```
#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
// 64kB stack
#define FIBER_STACK 1024*64


struct c {
 int saldo;
};
typedef struct c conta;
conta from, to;
int valor;
// The child thread will execute this function
int transferencia( void *arg)
{
 if (from.saldo >= valor){ // 2
  from.saldo -= valor;
  to.saldo += valor;
 }
 printf("Transferência concluída com sucesso!\n");
 printf("Saldo de c1: %d\n", from.saldo);
 printf("Saldo de c2: %d\n", to.saldo);
 return 0;
}
int main()
{
 void* stack;
 pid_t pid;
 int i;
 // Allocate the stack
 stack = malloc( FIBER_STACK );
 if ( stack == 0 )
  {
  perror("malloc: could not allocate stack");
  exit(1);
 }
 // Todas as contas começam com saldo 100
from.saldo = 100;
 to.saldo = 100;
 printf( "Transferindo 10 para a conta c2\n" );
 valor = 10;
 for (i = 0; i < 10; i++) {
  // Call the clone system call to create the child thread
  pid = clone( &transferencia, (char*) stack + FIBER_STACK,
  SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
 if ( pid == -1 )
  {
  perror( "clone" );
  exit(2);
 }
 }
 // Free the stack
 free( stack );
 printf("Transferências concluídas e memória liberada.\n");
 return 0;
} 
``` 

O trecho de código tem como objetivo zerar o saldo de uma conta (from) através de várias transferências para a outra (to). Contudo, acontece uma falha em sua execução causada por um dos problemas relativos à concorrência apresentados em sala. Para que o código seja executado com sucesso, é necessário identificar o problema e apresentar uma solução, com base nas observações relativas aos problemas e suas soluções discutidos em sala.

Considere os seguintes requisitos para o problema acima:

1. A conta to pode receber mais de uma transferência simultânea;
2. A conta from pode enviar mais de uma transferência simultânea;
3. A conta from não pode enviar dinheiro se não tiver mais saldo;
4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
   receber e a conta que recebia pode enviar;
5. Poderão ser realizadas até 100 transações simultâneas de transferência.

PROJETO: Utilizando o exemplo e os conceitos apresentados em sala, implemente uma solução
para a condição de corrida apresentada no problema.

#Detalhes da resolução

O problema de transferência de contas foi resolvido utilizando os fundamentos do problema do produtor-consumidor,onde o produtor insere informações no buffer e o consumidor retira, ou seja, ao realizar uma transferência foi debitada o valor de uma conta e foi recebida este mesmo valor na conta de destino. Para isso, usamos threads e para sincronizar as threads, utilizamos a biblioteca pthreads, juntamente com mutex para travar ou destravar as threads que querem entrar em uma região crítica.

1. A conta to pode receber mais de uma transferência simultânea;
```
while (contaEnvio.saldo != 0) {

        contaEnvio.saldo -= valor;

        /** caso queira fazer mais de uma transação simultânea */
        contaEnvio.saldo -= valor;

        contaDestino.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
    }
```
2. A conta from pode enviar mais de uma transferência simultânea;
```
   while (contaEnvio.saldo != 0) {

        contaEnvio.saldo -= valor;

        contaDestino.saldo += valor;

        /** caso queira fazer mais de uma transação simultânea */
        // contaDestino.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
   }
```
3. A conta from não pode enviar dinheiro se não tiver mais saldo;
Com o while (contaDe.saldo != 0) nos certificamos que a conta só vai enviar dinheiro se o saldo não for 0

```
/** caso a conta for igual a 0, a transferência é parada */
    while (contaEnvio.saldo != 0) {

        contaEnvio.saldo -= valor;
        contaDestino.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
    }
```

4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;

```
 /** implementação da lógica  ao trocar as contas de ordem */
    while (contaDestino.saldo != 0) {
        contaDestino.saldo -= valor;
        contaEnvio.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
    }
```

5. Poderão ser realizadas até 100 transações simultâneas de transferência.

```
#define MAX 100
/** limite de transferências simultâneas */

void transfereParaOutraConta() {           /* transfere saldo para a outra conta */
    valor = 10;                             /** valor que será transferido */
    for (int i = 0; i <= MAX; i++) {
        transferencia();                    /** realiza transferência */
        pthread_mutex_lock(&mutex);         /** obtém acesso ao mutex no momento atual */
        while (buffer != 0)
            pthread_cond_wait(&condContaEnvio, &mutex);
        buffer = i;                              /** adiciona item no buffer */
        pthread_cond_signal(&condContaDestino);  /** acorda recebeDaConta */
        pthread_mutex_unlock(&mutex);            /** libera o mutex */
    }
    pthread_exit(0);
}

void recebeDaConta() {                     /* recebe a transferência */
    valor = 10;                             /** valor da transferência */
    for (int i = 0; i <= MAX; i++) {
        transferencia();                    /** realiza transferência */
        pthread_mutex_lock(&mutex);         /** obtém acesso ao mutex no momento atual */
        while (buffer == 0)
            pthread_cond_wait(&condContaDestino, &mutex);
        buffer = 0;                            /** retira itens do buffer */
        pthread_cond_signal(&condContaEnvio);  /** acorda transfereParaOutraConta */
        pthread_mutex_unlock(&mutex);          /** libera o mutex */
    }
    pthread_exit(0);
}
```



Foi usado como referência as páginas 88, 91, 92, 93, 94 e 95 do livro de Tanenbaum, Andrew. Sistemas Operacionais 
Modernos. 4ª edição.
