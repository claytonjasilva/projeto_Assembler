#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analisador.h"
#include "gerador.h"
#include "executor.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <opcao> <caminho_do_arquivo.txt>\n", argv[0]);
        printf("Opcao:\n");
        printf("  a - Analisador: Analisa o codigo fonte\n");
        printf("  g - Gerador: Gera o codigo binario a partir do fonte\n");
        printf("  e - Executor: Executa o codigo binario\n");
        return 1;
    }

    char opcao = argv[1][0];
    char *filePath = argv[2];

    switch (opcao) {
        case 'a':
            printf("Analisando o codigo fonte...\n");
            if (analisar_arquivo(filePath) == 0) {
                printf("Analise concluida. Nenhum erro encontrado.\n");
            } else {
                printf("Erro(s) encontrado(s) na analise.\n");
            }
            break;

        case 'g':
            printf("Gerando codigo binario...\n");
            gerar_binario(filePath);
            printf("Codigo binario gerado com sucesso.\n");
            break;

        case 'e':
            printf("Executando o codigo binario...\n");
            inicializar_memoria();
            executar_instrucoes(filePath);
            break;

        default:
            printf("Opcao invalida. Use 'a', 'g' ou 'e'.\n");
            return 1;
    }

    return 0;
}
