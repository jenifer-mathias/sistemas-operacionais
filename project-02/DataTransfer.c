#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t
    the_mutex; // variável utilizada para guardar a região crítica. Ao tentar
               // acessar a região crítica, as threads destravam o mutex e ao
               // estar fora da região crítica, o mutex fica travado
pthread_cond_t condc, condp; // variáveis de condição usadas para sinalização e
                             // para permitir que as threads sejam bloqueadas
                             // caso a condição estabelecida não seja atendida
int buffer = 0; // buffer (região de memória) usado para receber ou liberar
                // posições, mediante ao que é solicitado pelas threads
#define MAX 100
// limite de transferências simultâneas

struct Conta {
  int saldo; // cria struct com variável saldo
};

typedef struct Conta conta;
conta contaDe, contaPara; // cria as duas contas
int valor;                // cria variável valor

int transferencia() {

  while (contaDe.saldo != 0) {
    contaDe.saldo -= valor;
    contaPara.saldo += valor;
  }

  while (contaDe.saldo !=
         0) { /** caso a conta for igual a 0, a transferÃªncia Ã© paradda */
    contaDe.saldo -= valor; // subtrai valor da conta que está transferindo

    // contaDe.saldo -= valor; /** caso queira fazer mais de uma transaÃ§Ã£o
    // simultÃ¢nea */

    contaPara.saldo +=
        valor; // adiciona valor na conta que recebe a transferência
    // contaPara.saldo += valor; /** caso queira fazer mais de uma transaÃ§Ã£o
    // simultÃ¢nea */

    /** implementação da lógica  ao trocar as contas de ordem **/
    //    while (contaPara.saldo != 0) { /** caso a conta for igual a 0, a
    //    transferência é paradda */
    //        contaPara.saldo -= valor;
    //        contaDe.saldo += valor;
    //
    //        printf("\nTransferência concluída com sucesso!\n");
    //        printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
    //        printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);
    //    }

    printf("\nTransferÃªncia concluÃ­da com sucesso!\n");
    printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
    printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);
  }
  exit(0);
}

void *transfereParaOutraConta() { // transfere saldo para a outra conta
  valor = 10;                     // valor que será transferido
  for (int i = 0; i <= MAX; i++) {
    transferencia();                // realiza transferência
    pthread_mutex_lock(&the_mutex); // obtem acesso ao mutex no momento atual
    while (buffer != 0)
      pthread_cond_wait(&condp, &the_mutex);
    buffer = i;                       // adiciona item no buffer
    pthread_cond_signal(&condc);      // acorda recebeDaConta
    pthread_mutex_unlock(&the_mutex); // libera o mutex
  }
  pthread_exit(0);
}

void *recebeDaConta() { // recebe a transferência
  valor = 10;           // valor da transferência
  for (int i = 0; i <= MAX; i++) {
    transferencia();                // realiza transferência
    pthread_mutex_lock(&the_mutex); // obtem acesso ao mutex no momento atual
    while (buffer == 0)
      pthread_cond_wait(&condc, &the_mutex);
    buffer = 0;                       // retira itens do buffer
    pthread_cond_signal(&condp);      // acorda transfereParaOutraConta
    pthread_mutex_unlock(&the_mutex); // libera o mutex
  }
  pthread_exit(0);
}

void gerenciaThreads() {
  pthread_t pro, con; /** cria duas threads (uma para cada conta) **/
  pthread_mutex_init(&the_mutex, 0); // cria mutex

  pthread_cond_init(&condc, 0); // cria variáveis de condição
  pthread_cond_init(&condp, 0);

  pthread_create(&con, 0, transfereParaOutraConta(), 0);
  pthread_create(&con, 0, recebeDaConta(), 0);

  pthread_join(pro, 0); // aguarda término da thread pro
  pthread_join(con, 0); // aguarda término da thread con

  pthread_cond_destroy(&condc); // destroi variáveis de condição
  pthread_cond_destroy(&condp);

  pthread_mutex_destroy(&the_mutex); // destroi mutex
}

int main() {
  /**  Todas as contas comeÃ§am com saldo 100 */
  contaDe.saldo = 100;
  contaPara.saldo = 100;

  printf("\nSaldo das contas inicialmente: \n");
  printf("\nSaldo da conta de envio (C1): %d\n", contaDe.saldo);
  printf("\nSaldo da conta de destino (C2): %d\n", contaPara.saldo);

  gerenciaThreads();

  EXIT_SUCCESS;
}
