/** 2) Escreva um programa (na linguagem C) que leia um arquivo texto (entrada) e copie para um outro
arquivo (saída), ou seja, faz o que o comando cp faz no Linux.

O seu programa deve solicitar o nome do arquivo de entrada e de saída (por linha de comando),
uma vez obtido os dois nomes, o programa deve abrir o arquivo de entrada e criar o arquivo de saída.

Caso por alguma razão não possa abrir o arquivo de entrada seu programa deve imprimir uma mensagem de aviso
e finalizar, caso aconteça um erro de criação do arquivo saída o programa imprime uma mensagem e finaliza.

Caso o programa tenha sucesso na abertura e criação, o programa lê a partir do arquivo de entrada e
grava no arquivo de saída.

Finalmente, depois que o arquivo de entrada for inteiramente copiado o programa pode fechar os dois
arquivos.

Identifique no seu programa as linhas de comando onde ocorrem chamadas de sistemas ao SO.
Quantas chamadas de sistemas foram realizadas? **/

#include <stdio.h>
#include <stdlib.h>

#define FILE_READ_MODE "r"
#define FILE_WRITE_MODE "w"
#define MAX_SIZE 600

void copyFile(FILE *inputFilePath, FILE *outputFilePath) {
    char contentFile;
    while ((contentFile = getc(inputFilePath)) != EOF)         /** chamada no S.O. getc() **/
        putc(contentFile, outputFilePath);                    /** chamada no S.O. putc() **/
}

char manipulateFile(const char *inputFile, const char *outputFile) {
    FILE *fileOne, *fileTwo;

    fileOne = fopen(inputFile, FILE_READ_MODE);                /** chamada no S.O. fopen() **/
    if (fileOne == NULL) {
        printf("\nArquivo não encontrado!\n");                 /** chamada no S.O. printf() **/
        exit(EXIT_FAILURE);
    }

    fileTwo = fopen(outputFile, FILE_WRITE_MODE);              /** chamada no S.O. fopen() **/

    copyFile(fileOne, fileTwo);
    printf("\nArquivo copiado com sucesso!");                  /** chamada no S.O. printf() **/

    fclose(fileOne);                                           /** chamada no S.O. fclose() **/
    fclose(fileTwo);                                           /** chamada no S.O. fclose() **/
    return EXIT_SUCCESS;
}

int main() {                                                                     // criando espaço de memória dinâmica
    char *inputFilePath = malloc(MAX_SIZE * sizeof(char));                  /** chamada no S.O. malloc() **/
    char *outputFilePath = malloc(MAX_SIZE * sizeof(char));                 /** chamada no S.O. malloc() **/

    printf("\n**** Cópia do conteúdo de um arquivo ****\n");                      /** chamada no S.O. printf() **/

    printf("\n Digite o caminho do primeiro arquivo para obter a leitura: ");     /** chamada no S.O. printf() **/
    scanf("%s", inputFilePath);                                                   /** chamada no S.O. scanf() **/

    printf("\n Digite o caminho do segundo arquivo para obter a cópia: ");
    scanf("%s", outputFilePath);                                                 /** chamada no S.O. scanf() **/

    manipulateFile(inputFilePath, outputFilePath);
    // libera espaço de memória
    free(inputFilePath);                                                         /** chamada no S.O. free() **/
    free(outputFilePath);                                                        /** chamada no S.O. free() **/
    EXIT_SUCCESS;

    /** total de chamadas do sistema: 16 **/
}
