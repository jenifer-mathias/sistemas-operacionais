/** 1) O comando cat é usado no sistema operacional Linux para exibir o conteúdo de um arquivo na tela do
computador. Escreva um programa (na linguagem C) faça exatamente o que o cat faz, o programa
deverá ler um arquivo texto (entrada) informado por linha de comando no interpretador de comando
(Como se faz isso?) e depois imprimir o conteúdo do arquivo na tela. Faça todos os testes necessários
para abertura, leitura e ao final não se esqueça de fechar o arquivo.

Identifique no seu programa as linhas de comando onde ocorrem chamadas de sistemas ao SO.
Quantas chamadas de sistemas foram realizadas?

Dica de arquivos em C: https://www.ime.usp.br/~pf/algoritmos/aulas/io.html **/

#include <stdio.h>
#include <stdlib.h>

#define FILE_MODE "r"

char readFile(char filePath[]) {
    FILE *file;
    char fileContent;

    file = fopen(filePath, FILE_MODE);           // abertura do arquivo
    if (file == NULL) {
        printf("\nArquivo não encontrado!\n");    // caso em que o path passado está incorreto ou não existem arquivos
        exit(EXIT_FAILURE);
    } else {
        while((fileContent = fgetc(file)) != EOF) {               // EOF representa o fim do arquivo
            putchar(fileContent);
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int main() {
    printf("\n**** Exibição do conteúdo de um arquivo ****\n");

    printf("\n Digite o caminho do arquivo para obter a impressão do texto: ");
    char filePath;
    scanf("%s",&filePath);
    readFile(&filePath);
}

