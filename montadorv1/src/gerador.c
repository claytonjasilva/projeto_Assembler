#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gerador.h"

// Função auxiliar para converter hexadecimal para binário
void hexToBinary(char *hex, char *binary) {
    int i;
    binary[0] = '\0';
    for (i = 2; i < 5; i++) {
        switch (toupper(hex[i])) {
            case '0': strcat(binary, "0000"); break;
            case '1': strcat(binary, "0001"); break;
            case '2': strcat(binary, "0010"); break;
            case '3': strcat(binary, "0011"); break;
            case '4': strcat(binary, "0100"); break;
            case '5': strcat(binary, "0101"); break;
            case '6': strcat(binary, "0110"); break;
            case '7': strcat(binary, "0111"); break;
            case '8': strcat(binary, "1000"); break;
            case '9': strcat(binary, "1001"); break;
            case 'A': strcat(binary, "1010"); break;
            case 'B': strcat(binary, "1011"); break;
            case 'C': strcat(binary, "1100"); break;
            case 'D': strcat(binary, "1101"); break;
            case 'E': strcat(binary, "1110"); break;
            case 'F': strcat(binary, "1111"); break;
            default: printf("Erro: Caractere hexadecimal invalido.\n"); exit(1);
        }
    }
}

void gerar_binario(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    char outputFilePath[256];
    strcpy(outputFilePath, filePath);
    strcat(outputFilePath, "_binario.txt");

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        fclose(file);
        return;
    }

    char line[100], instruction[20], operand[10];
    char binaryInstruction[9], binaryOperand[13];
    
    while (fgets(line, sizeof(line), file)) {
        // Remover o newline do final da linha
        line[strcspn(line, "\n")] = 0;

        // Dividir a linha em instrução e operando
        sscanf(line, "%s %s", instruction, operand);

        // Mapear a instrução para o seu código binário
        if (strcmp(instruction, "LOAD_MQ") == 0) {
            strcpy(binaryInstruction, "00001010");
        } else if (strcmp(instruction, "LOAD_MQ,M(X)") == 0) {
            strcpy(binaryInstruction, "00001001");
        } else if (strcmp(instruction, "STOR_M(X)") == 0) {
            strcpy(binaryInstruction, "00100001");
        } else if (strcmp(instruction, "LOAD_M(X)") == 0) {
            strcpy(binaryInstruction, "00000001");
        } else if (strcmp(instruction, "LOAD_-M(X)") == 0) {
            strcpy(binaryInstruction, "00000010");
        } else if (strcmp(instruction, "LOAD_ABS_M(X)") == 0) {
            strcpy(binaryInstruction, "00000011");
        } else if (strcmp(instruction, "LOAD_-ABS_M(X)") == 0) {
            strcpy(binaryInstruction, "00000100");
        } else if (strcmp(instruction, "JUMP_M(X,0:19)") == 0) {
            strcpy(binaryInstruction, "00001101");
        } else if (strcmp(instruction, "JUMP_M(X,20:39)") == 0) {
            strcpy(binaryInstruction, "00001110");
        } else if (strcmp(instruction, "JUMP+M(X,0:19)") == 0) {
            strcpy(binaryInstruction, "00001111");
        } else if (strcmp(instruction, "JUMP+M(X,20:39)") == 0) {
            strcpy(binaryInstruction, "00001110");
        } else if (strcmp(instruction, "ADD_M(X)") == 0) {
            strcpy(binaryInstruction, "00000101");
        } else if (strcmp(instruction, "ADD_ABS_M(X)") == 0) {
            strcpy(binaryInstruction, "00000111");
        } else if (strcmp(instruction, "SUB_M(X)") == 0) {
            strcpy(binaryInstruction, "00100110");
        } else if (strcmp(instruction, "SUB_ABS_M(X)") == 0) {
            strcpy(binaryInstruction, "00001000");
        } else if (strcmp(instruction, "MUL_M(X)") == 0) {
            strcpy(binaryInstruction, "00001011");
        } else if (strcmp(instruction, "DIV_M(X)") == 0) {
            strcpy(binaryInstruction, "00001100");
        } else if (strcmp(instruction, "LSH") == 0) {
            strcpy(binaryInstruction, "00010100");
        } else if (strcmp(instruction, "RSH") == 0) {
            strcpy(binaryInstruction, "00010101");
        } else if (strcmp(instruction, "STOR_M(X,8:19)") == 0) {
            strcpy(binaryInstruction, "00010010");
        } else if (strcmp(instruction, "JUMP_M(X,28:39)") == 0) {
            strcpy(binaryInstruction, "00001110");
        } else {
            printf("Erro: Instrução desconhecida '%s'.\n", instruction);
            fclose(file);
            fclose(outputFile);
            return;
        }

        // Converter o operando de hexadecimal para binário
        hexToBinary(operand, binaryOperand);

        // Escrever o código binário completo no arquivo de saída
        fprintf(outputFile, "%s%s\n", binaryInstruction, binaryOperand);
    }

    printf("Arquivo binario gerado com sucesso: %s\n", outputFilePath);

    fclose(file);
    fclose(outputFile);
}
