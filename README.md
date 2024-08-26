
# Projeto Montador IAS

Este repositório contém o projeto de um Montador IAS, que inclui um analisador, gerador de binários e executor. O sistema é capaz de analisar código de montagem, gerar o código binário correspondente e executar as instruções, alterando o estado da memória e dos registradores.

## Estrutura do Projeto

O projeto é organizado nas seguintes pastas:

- `src/`: Contém o código-fonte principal (`analisador.c`, `gerador.c`, `executor.c`, `main.c`).
- `include/`: Contém os arquivos de cabeçalho (`analisador.h`, `gerador.h`, `executor.h`).
- `testes/`: Contém os arquivos de teste usados para validar o funcionamento do sistema.
- `bin/`: Diretório onde os binários gerados serão armazenados.
- `obj/`: Diretório para os arquivos objeto.

## Compilação

Para compilar o projeto, navegue até o diretório do projeto (`montadorv1`) no terminal e execute o seguinte comando:

```bash
gcc -Iinclude -o montadorv1_test src/main.c src/analisador.c src/gerador.c src/executor.c
```

Esse comando compilará o código-fonte e gerará um executável chamado `montadorv1_test`.

## Uso

Após compilar o projeto, você pode executar as três principais funcionalidades: analisar, gerar binário e executar as instruções. 

### Analisar Código Fonte

Para analisar o código fonte, use o comando:

```bash
./montadorv1_test a testes/seu_arquivo.txt
```

### Gerar Código Binário

Para gerar o código binário a partir de um código fonte analisado, use o comando:

```bash
./montadorv1_test g testes/seu_arquivo.txt
```

O binário gerado será salvo com o sufixo `_binario.txt`.

### Executar Código Binário

Para executar o código binário gerado, use o comando:

```bash
./montadorv1_test e testes/seu_arquivo_binario.txt
```

O resultado da execução será salvo em um arquivo com o sufixo `_resultado.txt`.

## Testes

Os arquivos de teste estão localizados na pasta `testes/`. Abaixo estão alguns exemplos de testes incluídos:

### Teste 1

Instruções corretas que passam pelo analisador sem erros.

```plaintext
LOAD_MQ
LOAD_MQ,M(X) 0x001
STOR_M(X) 0x002
LOAD_M(X) 0x003
ADD_M(X) 0x004
SUB_M(X) 0x005
MUL_M(X) 0x006
DIV_M(X) 0x007
LSH
RSH
```

### Teste 3

Contém um erro de sintaxe no operando.

```plaintext
LOAD_MQ
LOAD_MQ,M(X) 0x001
STOR_M(X) 0x002
LOAD_M(X) 0x003ZZ  // Operando inválido
ADD_M(X) 0x004
```

### Teste 5

Executa um conjunto de instruções que alteram o estado da memória e dos registradores, com ACC e MQ sendo diferentes de zero no estado final.

```plaintext
LOAD_MQ
LOAD_MQ,M(X) 0x001
STOR_M(X) 0x002
LOAD_M(X) 0x003
ADD_M(X) 0x001
MUL_M(X) 0x002
STOR_M(X) 0x003
DIV_M(X) 0x004
```

### Teste 6

Configura a memória para valores específicos e verifica que o ACC e MQ têm os valores esperados ao final da execução.

```plaintext
LOAD_M(X) 0x001
SUB_M(X) 0x002
ADD_M(X) 0x003
SUB_M(X) 0x004
ADD_M(X) 0x005
ADD_M(X) 0x006
STOR_M(X) 0x000
LOAD_MQ
ADD_M(X) 0x006
STOR_M(X) 0x000
DIV_M(X) 0x003
STOR_M(X) 0x000
```

## Contribuição

Se você deseja contribuir para este projeto, sinta-se à vontade para fazer um fork do repositório, realizar as mudanças desejadas e submeter um pull request.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
