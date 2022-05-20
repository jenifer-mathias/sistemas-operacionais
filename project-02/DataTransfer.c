#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

# define NUMBER_OF_THREADS 2 /** definição das threads */

struct Conta {
    int saldo;
};

typedef struct Conta conta;
conta contaDe, contaPara;
int valor;

int transferencia() {
    if (contaDe.saldo >= valor) {
        contaDe.saldo -= valor;
        contaPara.saldo += valor;
    }

    printf("\nTransferência concluída com sucesso!\n");
    printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
    printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);

    pthread_exit(NULL);
}

void tranferenciaEntreContas(pthread_t threads[NUMBER_OF_THREADS]) {
    valor = 10;

    /** Todas as contas começam com saldo 100 */

    contaDe.saldo = 100;
    contaPara.saldo = 100;
    printf("\nSaldo das contas inicialmente: \n");
    printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
    printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);


    for (int i = 0; i < valor; i++) {
        printf( "\nTransferindo 10 para a conta conta de destino:\n" );
        pthread_create(&threads[i], NULL, transferencia, i);
        contaDe.saldo;
        contaPara.saldo;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS]; /** cria duas threads (uma para cada conta) **/
    tranferenciaEntreContas(threads);
    EXIT_SUCCESS;
}