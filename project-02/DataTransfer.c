#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
# define NUMBER_OF_THREADS 2 /** definição das threads */

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

struct Conta {
    int saldo;
};

typedef struct Conta conta;
conta contaDe, contaPara;
int valor;

int transferencia() {
    while (contaDe.saldo != 0) {
        contaDe.saldo -= valor;
        contaPara.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);
    }
    exit(0);
}

void *transferenciaEntreContas() {
    valor = 10;
    for (int i = 0; i <= valor; i++) {
        transferencia();
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
        buffer = 0;
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void gerenciaThreads() {
    pthread_t threads[NUMBER_OF_THREADS]; /** cria duas threads (uma para cada conta) **/
    pthread_mutex_init(&the_mutex, 0);

    pthread_cond_init(&condp, 0);

    pthread_create((pthread_t *) NUMBER_OF_THREADS, 0, transferenciaEntreContas(NULL), 0);

    pthread_mutex_destroy(&the_mutex);
}

int main() {
    /**  Todas as contas começam com saldo 100 */
    contaDe.saldo = 100;
    contaPara.saldo = 100;

    printf("\nSaldo das contas inicialmente: \n");
    printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
    printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);

    gerenciaThreads();

    EXIT_SUCCESS;
}