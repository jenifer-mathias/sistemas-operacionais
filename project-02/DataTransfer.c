#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;
#define MAX 100

struct Conta {
    int saldo;
};

typedef struct Conta conta;
conta contaDe, contaPara;
int valor;

int transferencia() {
    while (contaDe.saldo != 0) { /** caso a conta for igual a 0, a transferência é paradda */
        contaDe.saldo -= valor;

        // contaDe.saldo -= valor; /** caso queira fazer mais de uma transação simultânea */

        contaPara.saldo += valor;
        // contaPara.saldo += valor; /** caso queira fazer mais de uma transação simultânea */

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);
    }

    /** implementação da lógica  ao trocar as contas de ordem **/
//    while (contaPara.saldo != 0) { /** caso a conta for igual a 0, a transferência é paradda */
//        contaPara.saldo -= valor;
//        contaDe.saldo += valor;
//
//        printf("\nTransferência concluída com sucesso!\n");
//        printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
//        printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);
//    }

    exit(0);
}

void *transfereParaOutraConta() {
    valor = 10;
    for (int i = 0; i <= MAX; i++) {
        transferencia();
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) pthread_cond_wait(&condp, &the_mutex);
        buffer = i;
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *recebeDaConta() {
    valor = 10;
    for (int i = 0; i <= MAX; i++) {
        transferencia();
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void gerenciaThreads() {
    pthread_t pro, con; /** cria duas threads (uma para cada conta) **/
    pthread_mutex_init(&the_mutex, 0);

    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    pthread_create(&con, 0, transfereParaOutraConta(), 0);
    pthread_create(&con, 0, recebeDaConta(), 0);

    pthread_join(pro, 0);
    pthread_join(con, 0);

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);

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