#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "executor.h"

// Definição dos objetos
unsigned long ACC = 0; // Acumulador
unsigned long MQ = 0;  // Multiplicador/Quociente
unsigned long M[MEM_SIZE]; // Memória de 0x000 a 0x3FF

// Função para converter 20 bits em binário para um valor hexadecimal
unsigned long binaryToHex(char *binary) {
    unsigned long value = 0;
    for (int i = 0; i < 20; i++) {
        value <<= 1;
        if (binary[i] == '1') {
            value |= 1;
        }
    }
    return value;
}

// Função para processar uma instrução de 20 bits
void processar_instrucao(unsigned long opcode, unsigned long operando) {
    printf("Processando opcode: 0x%02lX, operando: 0x%03lX\n", opcode, operando); // Depuração

    switch (opcode) {
        case 0x0A: // 00001010 - LOAD MQ
            ACC = MQ;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x09: // 00001001 - LOAD MQ,M(X)
            MQ = M[operando];
            printf("Estado alterado: MQ = 0x%010lX\n", MQ);
            break;

        case 0x21: // 00100001 - STOR M(X)
            M[operando] = ACC;
            printf("Estado alterado: M[0x%03lX] = 0x%010lX\n", operando, M[operando]);
            break;

        case 0x01: // 00000001 - LOAD M(X)
            ACC = M[operando];
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x02: // 00000010 - LOAD -M(X)
            ACC = (-M[operando]) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x03: // 00000011 - LOAD |M(X)|
            ACC = (M[operando] < 0 ? -M[operando] : M[operando]) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x04: // 00000100 - LOAD -|M(X)|
            ACC = (-abs(M[operando])) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x0D: // 00001101 - JUMP M(X,0:19)
            // Neste exemplo, o salto não é implementado
            printf("JUMP M(X,0:19) nao implementado\n");
            break;

        case 0x0E: // 00001110 - JUMP M(X,20:39)
            // Neste exemplo, o salto não é implementado
            printf("JUMP M(X,20:39) nao implementado\n");
            break;

        case 0x0F: // 00001111 - JUMP +M(X,0:19)
            if (ACC >= 0) {
                // Salto condicional
                printf("JUMP +M(X,0:19) condicional nao implementado\n");
            }
            break;

        case 0x05: // 00000101 - ADD M(X)
            ACC = (ACC + M[operando]) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x07: // 00000111 - ADD |M(X)|
            ACC = (ACC + abs(M[operando])) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x26: // 00100110 - SUB M(X)
            ACC = (ACC - M[operando]) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x08: // 00001000 - SUB |M(X)|
            ACC = (ACC - abs(M[operando])) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x0B: // 00001011 - MUL M(X)
            {
                unsigned long long resultado = MQ * M[operando];
                ACC = (resultado >> 40) & BIT_MASK_40; // Bits mais significativos
                MQ = resultado & BIT_MASK_40; // Bits menos significativos
                printf("Estado alterado: ACC = 0x%010lX, MQ = 0x%010lX\n", ACC, MQ);
            }
            break;

        case 0x0C: // 00001100 - DIV M(X)
            if (M[operando] != 0) {
                MQ = ACC / M[operando];
                ACC = ACC % M[operando];
                printf("Estado alterado: ACC = 0x%010lX, MQ = 0x%010lX\n", ACC, MQ);
            } else {
                printf("Erro: Divisao por zero na instrucao DIV M(X)\n");
            }
            break;

        case 0x14: // 00010100 - LSH
            ACC = (ACC << 1) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x15: // 00010101 - RSH
            ACC = (ACC >> 1) & BIT_MASK_40;
            printf("Estado alterado: ACC = 0x%010lX\n", ACC);
            break;

        case 0x12: // 00010010 - STOR M(X,8:19)
            M[operando] = (ACC & 0xFFF); // Armazena os 12 bits mais à direita do ACC
            printf("Estado alterado: M[0x%03lX] = 0x%010lX\n", operando, M[operando]);
            break;

        default:
            printf("Opcode desconhecido: 0x%02lX\n", opcode);
            break;
    }
}

// Função para executar as instruções do arquivo binário
void executar_instrucoes(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", filePath);
        return;
    }

    char line[21]; // Linha de 20 bits
    while (fgets(line, sizeof(line), file)) {
        line[20] = '\0'; // Garante que a linha termina com um caractere nulo

        // Dividir a linha em opcode (8 bits) e operando (12 bits)
        unsigned long opcode = binaryToHex(line) >> 12;
        unsigned long operando = binaryToHex(line) & 0xFFF;

        // Processar a instrução
        processar_instrucao(opcode, operando);
    }

    fclose(file);

    // Escrever o resultado final em um arquivo
    char resultFilePath[512];
    snprintf(resultFilePath, sizeof(resultFilePath), "%s_resultado.txt", filePath);
    FILE *resultFile = fopen(resultFilePath, "w");
    if (resultFile == NULL) {
        printf("Erro ao criar o arquivo de resultado.\n");
        return;
    }

    fprintf(resultFile, "RESULTADO DO CODIGO:\n");
    fprintf(resultFile, "ACC = 0x%010lX\n", ACC);
    fprintf(resultFile, "MQ = 0x%010lX\n", MQ);

    for (int i = 0; i < MEM_SIZE; i++) {
        if (M[i] != 0) {
            fprintf(resultFile, "M[0x%03X] = 0x%010lX\n", i, M[i]);
        }
    }

    fclose(resultFile);
    printf("Execucao concluida. Resultado salvo no arquivo %s\n", resultFilePath);
}

// Função para inicializar a memória
void inicializar_memoria() {
    unsigned long endereco, valor;
    char continuar;

    do {
        printf("Entre com o endereco (em hexadecimal, maximo 0x3FF): ");
        scanf("%lx", &endereco);

        if (endereco >= MEM_SIZE) {
            printf("Endereco invalido. Tente novamente.\n");
            continue;
        }

        printf("Entre com o valor (em hexadecimal, maximo 0xFFFFFFFFFF): ");
        scanf("%lx", &valor);

        M[endereco] = valor;
        printf("Memoria M[0x%03lX] inicializada com 0x%010lX\n", endereco, valor);

        printf("Deseja continuar inicializando? (s/n): ");
        scanf(" %c", &continuar);

    } while (tolower(continuar) != 'n');
}
