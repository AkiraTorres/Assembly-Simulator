#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

//* funcao mov
int movR(char *destiny, char *data, int *dataMemory) {
    int i;
    char *addr;

    if (data[0] == '[') {
        for (i = 0; i < strlen(data) - 2; i++) {
            addr[i] = data[i + 1];
        }
        int address = atoi(addr);
        return dataMemory[address];
    } else {
        return atoi(data);
    }
}

//* imprimir o estado dos Registradores e da Memoria de Dados
void print(int A, int B, int C, int D, int *dataMemory) {
    int i;
    printf("Banco de registradores: A:%i B:%i C:%i D:%i\n", A, B, C, D);
    printf("Memoria de dados:");

    for (i = 0; i < 50; i++) {
        printf(" %d", dataMemory[i]);
    }
    printf("\n");
}

//* descubrindo a posicao da virgula
int getCommaPosition(char *instruction) {
    int posComma = -1, i;
    for (i = 0; instruction[i] != '\0'; i++) {
        if (instruction[i] == ',') {
            posComma = i;
        }
    }
    return posComma;
}

//* saparando os parametros da instrucao
char *getParam1(char *instruction, int posComma) {
    int i, j = 0;
    char *param1 = (char *)malloc(sizeof(char) * 5);

    //* pegando o parametro 1
    for (i = 4; i < posComma; i++) {
        param1[j] = instruction[i];
        j++;
    }
    return param1;
}
char *getParam2(char *instruction, int posComma) {
    int i, j = 0;
    char *param2 = (char *)malloc(sizeof(char) * 5);

    //* pegando o parametro 2
    for (i = posComma + 1; i < strlen(instruction); i++) {
        param2[j] = instruction[i];
        j++;
    }

    return param2;
}

int main() {
    //* declarando variaveis e valores iniciais
    bool stop = true;
    int A = 0, B = 0, C = 0, D = 0, i = 0, j = 0, posComma = -1;
    int *dataMemory = (int *)malloc(sizeof(int) * 50);
    char *instruction = (char *)malloc(sizeof(char) * 5);
    char *function = (char *)malloc(sizeof(char) * 5);
    char *param1 = (char *)malloc(sizeof(char) * 5);
    char *param2 = (char *)malloc(sizeof(char) * 5);

    printf("** Bem vindo ao Simulador Assembly em Linguagem C **\n");
    while (stop) {
        print(A, B, C, D, dataMemory);

        fgets(instruction, 20, stdin);  //* pegando a instrucao com o usuario
        //* separando a funcao da instrucao
        for (i = 0; i < 3; i++) {
            function[i] = toupper(instruction[i]);
        }

        //* se a function for igual a HLT entao o codigo e encerrado
        if (strncmp(function, "HLT", 3) == 0) {
            stop = false;
        }

        posComma = getCommaPosition(instruction);  //* pegando a posicao da virgula
        //* pegando os parametros 1 e 2
        param1 = getParam1(instruction, posComma);
        param2 = getParam2(instruction, posComma);

        if (strncmp(function, "MOV", 3) == 0) {
            if (strncmp(param1, "A", 1) == 0) {
                A = movR(param1, param2, dataMemory);
            } else if (strncmp(param1, "B", 1) == 0) {
                B = movR(param1, param2, dataMemory);
            } else if (strncmp(param1, "C", 1) == 0) {
                C = movR(param1, param2, dataMemory);
            } else if (strncmp(param1, "D", 1) == 0) {
                D = movR(param1, param2, dataMemory);
            }
        } else if (strncmp(function, "ADD", 3) == 0) {
            printf("add");
        }
    }

    return 0;
}
