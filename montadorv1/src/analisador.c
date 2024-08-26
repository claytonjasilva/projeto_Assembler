#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "analisador.h"

#define MAX_LINE_LENGTH 100

// Função auxiliar para verificar se o operando é um hexadecimal válido (0xXXX)
int isValidHex(char *operand) {
    if (strlen(operand) != 5 || operand[0] != '0' || operand[1] != 'x')
        return 0;
    
    for (int i = 2; i < 5; i++) {
        if (!isxdigit(operand[i])) 
            return 0;
    }

    return 1;
}

// Função auxiliar para verificar se a instrução é válida
int isValidInstruction(char *instruction) {
    char *validInstructions[] = {
        // Instruções de transferência de dados
        "LOAD_MQ",
        "LOAD_MQ,M(X)",
        "STOR_M(X)",
        "LOAD_M(X)",
        "LOAD_-M(X)",
        "LOAD_ABS_M(X)",
        "LOAD_-ABS_M(X)",
        
        // Instruções de desvio incondicional
        "JUMP_M(X,0:19)",
        "JUMP_M(X,20:39)",

        // Instruções de desvio condicional
        "JUMP+M(X,0:19)",
        "JUMP+M(X,20:39)",

        // Instruções aritméticas
        "ADD_M(X)",
        "ADD_ABS_M(X)",
        "SUB_M(X)",
        "SUB_ABS_M(X)",
        "MUL_M(X)",
        "DIV_M(X)",
        "LSH",
        "RSH",

        // Instruções de alteração de endereço
        "STOR_M(X,8:19)",
        "JUMP_M(X,28:39)"
    };

    int instructionValid = 0;
    for (int i = 0; i < sizeof(validInstructions) / sizeof(validInstructions[0]); i++) {
        if (strcmp(instruction, validInstructions[i]) == 0) {
            instructionValid = 1;
            break;
        }
    }

    return instructionValid;
}

int analisar_arquivo(const char *filePath) {
    int erro = 0; // Identifica erro no código

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNumber++;

        // Remover o newline do final da linha
        line[strcspn(line, "\n")] = 0;

        char instruction[20], operand[10];

        // Dividir a linha em instrução e operando
        if (sscanf(line, "%s %s", instruction, operand) != 2) {
            printf("Erro na linha %d: Sintaxe incorreta.\n", lineNumber);
            erro = 1;
            continue; // Avança para a próxima linha se houver erro de sintaxe
        }

        if (!isValidInstruction(instruction)) {
            printf("Erro na linha %d: Sintaxe incorreta '%s'.\n", lineNumber, instruction);
            erro = 1;
            continue; // Avança para a próxima linha se a instrução for inválida
        }

        if (!isValidHex(operand)) {
            printf("Erro na linha %d: Sintaxe incorreta '%s'.\n", lineNumber, operand);
            erro = 1;
            continue; // Avança para a próxima linha se o operando for inválido
        }
    }

    fclose(file);
    return erro ? 1 : 0; // Retorna 1 se houve erro, caso contrário 0
}
