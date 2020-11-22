// declaracao das bibliotecas utilizadas
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// pega os registradores e os salva em ponteiros
int *getPointers(int *A, int *B, int *C, int *D)
{
    int i;
    int *pointers = (int *)malloc(4 * sizeof(int));
    for (i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            pointers[i] = *A;
        }
        else if (i == 1)
        {
            pointers[i] = *B;
        }
        else if (i == 2)
        {
            pointers[i] = *C;
        }
        else if (i == 3)
        {
            pointers[i] = *D;
        }
    }
    return pointers;
}

// funcao assembly MOV
void mov(char *destiny, char *data, int *dataMemory, int *A, int *B, int *C, int *D)
{
    int i;
    char *addr;
    int *cons;

    // faz o MOV de um endereco de memoria para um registrador
    if (data[0] == '[')
    {
        char regis = destiny[0];
        for (i = 0; i < strlen(data) - 2; i++)
        {
            addr[i] = data[i + 1];
        }
        int address = atoi(addr);
        switch (regis)
        {
        case 'A':
            *A = dataMemory[address];
            break;
        case 'B':
            *B = dataMemory[address];
            break;
        case 'C':
            *C = dataMemory[address];
            break;
        case 'D':
            *D = dataMemory[address];
            break;
        }
    }
    // faz o MOV de uma constante para um registrador
    else if ((destiny[0] == 'A') || (destiny[0] == 'B') || (destiny[0] == 'C') || (destiny[0] == 'D'))
    {
        char regis = destiny[0];
        for (i = 0; i < strlen(data); i++)
        {
            addr[i] = data[i];
        }
        int cons = atoi(addr);
        switch (regis)
        {
        case 'A':
            *A = cons;
            break;
        case 'B':
            *B = cons;
            break;
        case 'C':
            *C = cons;
            break;
        case 'D':
            *D = cons;
            break;
        }
    }

    // faz o MOV para um endereco de memoria
    if (destiny[0] == '[')
    {
        // com um registrador como o dado a ser movido
        if ((data[0] == 'A') || (data[0] == 'B') || (data[0] == 'C') || (data[0] == 'D'))
        {
            char regis = data[0];
            for (i = 0; i < strlen(destiny) - 2; i++)
            {
                addr[i] = destiny[i + 1];
                addr[i + 1] = '\0';
            }
            int address = atoi(addr);
            switch (regis)
            {
            case 'A':
                dataMemory[address] = *A;
                break;
            case 'B':
                dataMemory[address] = *B;
                break;
            case 'C':
                dataMemory[address] = *C;
                break;
            case 'D':
                dataMemory[address] = *D;
                break;
            }
        }
        // com uma constante como o dado a ser movido
        else
        {
            int cons = atoi(data);
            for (i = 0; i < strlen(destiny) - 2; i++)
            {
                addr[i] = destiny[i + 1];
                addr[i + 1] = '\0';
            }
            int address = atoi(addr);
            dataMemory[address] = cons;
        }
    }
}

// funcao assembly ADD
void add(char *destiny, char *data, int *dataMemory, int *A, int *B, int *C, int *D)
{
    int i, j;
    char *addr;
    int *cons;

    // faz o ADD de um registrador para um registrador
    if (((data[0] == 'A') || (data[0] == 'B') || (data[0] == 'C') || (data[0] == 'D')))
    {
        char regis = destiny[0];
        int *pointers = getPointers(A, B, C, D);
        int parcel;
        int count = 0;
        char k = 65;

        for (i = 65; i < 69; i++)
        {
            if (data[0] == i)
            {
                parcel = pointers[count];
            }
            count++;
            k++;
        }

        switch (regis)
        {
        case 'A':
            *A += parcel;
            break;

        case 'B':
            *B += parcel;
            break;
        case 'C':
            *C += parcel;
            break;
        case 'D':
            *D += parcel;
            break;
        }
    }
    // faz o ADD de uma constante para um registrador
    else if ((destiny[0] == 'A') || (destiny[0] == 'B') || (destiny[0] == 'C') || (destiny[0] == 'D'))
    {
        char regis = destiny[0];
        int dataInt = atoi(data);
        for (i = 0; i < strlen(data); i++)
        {
            addr[i] = data[i];
        }
        int cons = atoi(addr);
        switch (regis)
        {
        case 'A':
            *A += cons;
            break;
        case 'B':
            *B += cons;
            break;
        case 'C':
            *C += cons;
            break;
        case 'D':
            *D += cons;
            break;
        }
    }
}

// imprimir o estado dos Registradores e da Memoria de Dados
void print(int A, int B, int C, int D, int *dataMemory)
{
    int i;
    printf("Banco de registradores: A:%i B:%i C:%i D:%i\n", A, B, C, D);
    printf("Memoria de dados:");

    for (i = 0; i < 50; i++)
    {
        printf(" %d", dataMemory[i]);
    }
    printf("\n");
}

// descubrindo a posicao da virgula
int getCommaPosition(char *instruction)
{
    int posComma = -1, i;
    for (i = 0; instruction[i] != '\0'; i++)
    {
        if (instruction[i] == ',')
        {
            posComma = i;
        }
    }
    return posComma;
}

// saparando os parametros da instrucao
char *getParam1(char *instruction, int posComma)
{
    int i, j = 0;
    char *param1 = (char *)malloc(sizeof(char) * 5);

    // pegando o parametro 1
    for (i = 4; i < posComma; i++)
    {
        param1[j] = toupper(instruction[i]); // passando o parametro com letras maiusculas para evitar erros de case sensitive
        j++;
    }
    return param1;
}
char *getParam2(char *instruction, int posComma)
{
    int i, j = 0;
    char *param2 = (char *)malloc(sizeof(char) * 5);

    // pegando o parametro 2
    for (i = posComma + 1; i < strlen(instruction); i++)
    {
        param2[j] = toupper(instruction[i]);
        j++;
    }

    return param2;
}

int main()
{
    // declarando variaveis e valores iniciais
    bool stop = true;
    int A = 0, B = 0, C = 0, D = 0, i = 0, j = 0, posComma = -1;
    int *dataMemory = (int *)malloc(sizeof(int) * 50);
    char *instruction = (char *)malloc(sizeof(char) * 5);
    char *function = (char *)malloc(sizeof(char) * 5);
    char *param1 = (char *)malloc(sizeof(char) * 5);
    char *param2 = (char *)malloc(sizeof(char) * 5);

    for (i = 0; i < 50; i++)
    {
        dataMemory[i] = 0;
    }

    printf("** Bem vindo ao Simulador Assembly em Linguagem C **\n");
    while (stop)
    {
        print(A, B, C, D, dataMemory); // chama a funcao print que exibe os valores dos registradores e da memoria de dados

        fgets(instruction, 20, stdin); // pegando a instrucao com o usuario
        // separando a funcao da instrucao
        for (i = 0; i < 3; i++)
        {
            function[i] = toupper(instruction[i]); // salva a instrucao como palavra maiuscula para evitar erros de case sensitive
        }

        posComma = getCommaPosition(instruction); // pegando a posicao da virgula
        // pegando os parametros 1 e 2
        param1 = getParam1(instruction, posComma);
        param2 = getParam2(instruction, posComma);

        if (strncmp(function, "MOV", 3) == 0)
        {
            mov(param1, param2, dataMemory, &A, &B, &C, &D); // se a function for igual a MOV ele chama a funcao mov
        }
        else if (strncmp(function, "ADD", 3) == 0)
        {
            add(param1, param2, dataMemory, &A, &B, &C, &D); // se a function for igual a ADD ele chama a funcao add
        }
        else if (strncmp(function, "HLT", 3) == 0)
        {
            stop = false; // se a function for igual a HLT entao o codigo e encerrado
        }
    }

    return 0;
}
