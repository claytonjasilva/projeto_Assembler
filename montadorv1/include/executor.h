#ifndef EXECUTOR_H
#define EXECUTOR_H

#define MEM_SIZE 0x400 // 0x000 to 0x3FF
#define BIT_MASK_40 0xFFFFFFFFFF // 40-bit mask

// Declaração dos objetos
extern unsigned long ACC;
extern unsigned long MQ;
extern unsigned long M[MEM_SIZE];

// Funções do executor
void inicializar_memoria(); // Inicializa a memória conforme entrada do usuário
void executar_instrucoes(const char *filePath); // Executa as instruções do arquivo binário

#endif
