#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>

#define PENSANDO 0
#define COM_FOME 1
#define COMENDO 2

int i, numeroFilosofos;

sem_t mutex;
sem_t semaforo[100];

int estado[200];

pthread_t *thread;

void devolveEstadoFilosofos();

_Noreturn void *gerenciaAcoesFilosofos(void *j);

void pegaGarfos(int i);

void soltaGarfos(int i);

void verificaAcoesFilosofos(int i);

void pensando();

void comendo();

void gerenciaThreads(int numeroFilosofos);

int calculaPosicaoFilosofoEsquerda(int meio, int total) {
    int esquerda;
    esquerda = (meio + total - 1) % total;
    return esquerda;
}

int calculaPosicaoFilosofoDireita(int meio, int total) {
    int direita;
    direita = (meio + 1) % total;
    return direita;
}

void devolveEstadoFilosofos() {
    for (i = 1; i <= numeroFilosofos; i++) {
        if (estado[i] == PENSANDO) { /** Mostra se o filósofo está pensando */
            printf("Filósofo %d esta pensando...\n", i);
        }
        if (estado[i] == COM_FOME) { /** Mostra se o filósofo está com fome */
            printf("Filósofo %d esta com fome...\n", i);
        }
        if (estado[i] == COMENDO) { /** Mostra se o filósofo está comendo */
            printf("Filósofo %d esta comendo!\n", i);
        }
    }
    printf("\n");
}

_Noreturn void *gerenciaAcoesFilosofos(void *j) {
    int i = *(int *) j;
    while (1) {
        pensando(i);
        pegaGarfos(i);
        comendo(i);
        soltaGarfos(i);
    }
}

void pegaGarfos(int i) {
    sem_wait(&mutex); /** Pega o semáforo */
    estado[i] = COM_FOME; /** Seta que está com fome */
    devolveEstadoFilosofos(); /** Mostra o estado dos filósofos */
    verificaAcoesFilosofos(i); /** Tenta pegar os garfos */
    sem_post(&mutex); /** Libera o semáforo */
    sem_wait(&semaforo[i]); /** Atualiza o seu próprio semáforo */
}

void soltaGarfos(int i) {
    int esquerda, direita;
    sem_wait(&mutex); /** Pega o semáforo */
    estado[i] = PENSANDO; /** Seta que está pensando */
    devolveEstadoFilosofos(); /** Mostra o estado dos filósofos */
    esquerda = calculaPosicaoFilosofoEsquerda(i, numeroFilosofos); /** Verifica se o filósofo a esquerda está comendo */
    direita = calculaPosicaoFilosofoDireita(i, numeroFilosofos); /** Verifica se o filósofo a direita está comendo */
    verificaAcoesFilosofos(esquerda);
    verificaAcoesFilosofos(direita);
    sem_post(&mutex);
}

// verifica quando o filósofo pode comer
void verificaAcoesFilosofos(int i) {
    int esquerda, direita;
    esquerda = calculaPosicaoFilosofoEsquerda(i, numeroFilosofos); /**Verifica se o filósofo a esquerda está comendo */
    direita = calculaPosicaoFilosofoDireita(i, numeroFilosofos); /**Verifica se o filósofo a direita está comendo */
    if (estado[i] == COM_FOME && estado[esquerda] != COMENDO && estado[direita] != COMENDO) {
        estado[i] = COMENDO;
        devolveEstadoFilosofos();
        sem_post(&semaforo[i]);
    }
}

void pensando() {
    sleep(2);
}

void comendo() {
    sleep(2);
}

void gerenciaThreads(int numeroFilosofos) {
    /** usa alocação dinâmica de memória para criar a quantidade de threads segundo o número de filósofos informados */
    thread = (pthread_t *) malloc(numeroFilosofos * sizeof(pthread_t));

    /** Inicializa o estado */
    for (i = 0; i < numeroFilosofos; i++) {
        estado[i] = 0;
    }
    devolveEstadoFilosofos();
    pthread_t thread[1000];

    sem_init(&mutex, 0, 1);    /** inicia semáforo mutex */

    for (i = 0; i < numeroFilosofos; i++) {
        sem_init(&semaforo[i], 0, 0);        /** inicia o semáforo dos filósofos */
    }

    for (i = 0; i < numeroFilosofos; i++) {    /** cria as threads para os filósofos */
        pthread_create(&thread[i], NULL, gerenciaAcoesFilosofos, &i);
    }

    for (i = 0; i < numeroFilosofos; i++) {
        pthread_join(thread[i], NULL);      /** faz um join - une as threads */
    }
}

int main() {

    printf("\n************ JANTAR DOS FILÓSOFOS ************\n");

    printf("\nDigite a quantidade de filósofos que participarão do jantar: ");

    scanf("%d", &numeroFilosofos);

    gerenciaThreads(numeroFilosofos);
}
