#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    printf("Digite o nome do arquivo que deseja ler: ");
    char a[25];
    FILE *arq;
    scanf("%s", &a);
    arq = fopen(a, "r");
    while (true) {
        char x[25];
        int k = fscanf(arq, "%s", &x);
        printf(x);
        if (k != 1) break;
    }
    fclose(arq);
    return 0;
    
}
