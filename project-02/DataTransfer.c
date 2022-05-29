#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

void *transfereParaOutraConta(pthread_t pro) {
    valor = 10;
    for (int i = 0; i <= valor; i++) {
        transferencia();
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}
