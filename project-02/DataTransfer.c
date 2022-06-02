#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
/** variável utilizada para guardar a região crítica. Ao tentar acessar a região crítica,
 * as threads destravam o mutex e ao estar fora da região crítica, o mutex fica travado */

pthread_cond_t condContaDestino, condContaEnvio;
/** variáveis de condição usadas para sinalização e para permitir que as threads sejam
 * bloqueadas caso a condição estabelecida não seja atendida */

int buffer = 0;
/** buffer (região de memória) usado para receber ou liberar informações, mediante ao que é solicitado pelas threads */

#define MAX 100
/** limite de transferências simultâneas */

struct Conta {
    int saldo; /** cria struct com variável saldo */
};

typedef struct Conta conta;
conta contaEnvio, contaDestino;  /** cria as duas contas */
int valor;                       /** cria variável valor */

int transferencia() {

    /** caso a conta for igual a 0, a transferência é parada */
//    while (contaEnvio.saldo != 0) {
//
//        contaEnvio.saldo -= valor;
//
//        /** caso queira fazer mais de uma transação simultânea */
//        // contaEnvio.saldo -= valor;
//
//        contaDestino.saldo += valor;
//
//        /** caso queira fazer mais de uma transação simultânea */
//        // contaDestino.saldo += valor;
//
//        printf("\nTransferência concluída com sucesso!\n");
//        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
//        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
//    }

    /** implementação da lógica  ao trocar as contas de ordem */
    while (contaDestino.saldo != 0) {
        contaDestino.saldo -= valor;
        contaEnvio.saldo += valor;

        printf("\nTransferência concluída com sucesso!\n");
        printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
        printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);
    }

    exit(0);
}

void *transfereParaOutraConta() {           /** transfere saldo para a outra conta */
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

void *recebeDaConta() {                     /** recebe a transferência */
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

void gerenciaThreads() {
    pthread_t pthread_conta_envio, pthread_conta_destino;        /** cria duas threads (uma para cada conta) */

    pthread_mutex_init(&mutex, 0);                               /** cria mutex */

    pthread_cond_init((pthread_cond_t *) &condContaDestino, 0);
    pthread_cond_init((pthread_cond_t *) &condContaEnvio, 0);             /** cria variáveis de condição */

    pthread_create(&pthread_conta_envio, 0, transfereParaOutraConta(), 0);    /** cria thread "produtora" */
    pthread_create(&pthread_conta_destino, 0, recebeDaConta(), 0);            /** cria thread "consumidora" */

    pthread_join(pthread_conta_envio, 0);                    /** aguarda término da thread pthread_conta_envio */
    pthread_join(pthread_conta_destino, 0);                  /** aguarda término da thread pthread_conta_destino */

    pthread_cond_destroy((pthread_cond_t *) &pthread_conta_destino);
    pthread_cond_destroy((pthread_cond_t *) &pthread_conta_envio);    /** destrói variáveis de condição */

    pthread_mutex_destroy(&mutex);         /** destrói mutex */
}

int main() {
    /**  Todas as contas começam com saldo 100 */
    contaEnvio.saldo = 100;
    contaDestino.saldo = 100;

    printf("\nSaldo das contas inicialmente: \n");
    printf("\nSaldo da conta de envio (C1): %d\n", contaEnvio.saldo);
    printf("\nSaldo da conta de destino (C2): %d\n", contaDestino.saldo);

    gerenciaThreads();

    EXIT_SUCCESS;
}
