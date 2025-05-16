#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINHAS 10
#define COLUNAS 12
#define TAM_PLATEIA (LINHAS * COLUNAS)
#define ARQUIVO_PLATEIA "plateia.txt" 

//**plateia é o ponteiro duplo para a matriz original da plateia 
//**p é o ponteiro duplo para a matriz a qual recebe as manipulações (cópia de **plateia)

//PROTOTIPOS DAS FUNÇÕES
int menu (); 
void sair (); 
int escolheropcao (char **plateia); 
int InputInt (const char *prompt, int min, int max); //função para validar a entrada do usuario
char **alocMemPlateia(); //aloca memoria para a matriz da plateia
void criarCarregarPlateia(); //carrega a plateia do arquivo ou cria um novo arquivo caso não exista
void liberarPlateia(char **p); //libera a memoria alocada para a matriz
void salvarPlateia(char *nomeArquivo, char **p); //salva a plateia no arquivo
void mostrarplateia(char **plateia); //mostra a plateia
void mostrarocupacao(char **plateia); //mostra a ocupação da plateia + o numero de poltronas meias e inteiras vendidas
void venderingresso(char **plateia); //vende ingressos
void cancelaringresso(char **plateia);

int main() {
  char **plateia = alocMemPlateia();

  criarCarregarPlateia(ARQUIVO_PLATEIA, plateia);
  escolheropcao(plateia);

  liberarPlateia(plateia);
  return 0;
}

int menu (){ 
  printf ("-------------------------------\n \t      MENU\n-------------------------------\n0-Sair do programa \n1-Mostrar plateia \n2-Mostrar ocupacao \n3-Vender ingresso \n4-Cancelar ingresso (devolucao) \n-------------------------------\n");
  return 0;
}

void sair() {
    printf("\nSaindo do programa...\n");
    fflush(stdout); 
    exit(0);        
}

int escolheropcao (char **plateia){
  int opcao;

  while (1){
    menu(); 
    opcao = InputInt("Digite a opcao desejada: ", 0, 4);

    switch (opcao){
      case 0:
        sair();
        break;
      case 1:
        mostrarplateia(plateia);
        break;
      case 2:
        mostrarocupacao(plateia);
        break;
      case 3:
        venderingresso(plateia);
        break;
      case 4:
        cancelaringresso(plateia);
        break;
      default:
        printf("Erro inesperado: opcao invalida.\n");
        break;
    }
  }
}

int InputInt (const char *prompt, int min, int max){
  char input [100];
  int i, numero;
  int valido;

  while (1){
    printf ("%s", prompt);
    scanf ("%99s", input);
    fflush(stdin);

    i = 0;
    valido = 1;
    //verifica se a entrada começa com um sinal de menos
    if (input[0] == '-'){
        if (input[1] == '\0'){
            valido = 0;
        }
      i = 1;
    }
    //verifica se a entrada e um numero inteiro
    while (valido && input [i] != '\0'){
      if (input [i] < '0' || input [i] > '9'){
        valido = 0;
      }
      i++;
    }
    if (!valido){
      printf ("Erro: Entrada invalida. Por favor, digite um numero inteiro.\n");
      continue;
    }
    
    numero = atoi (input); //converte a string para um numero inteiro
    
    if (numero < min || numero > max){ //se a entrada for um numero inteiro, verifica se esta dentro do intervalo valido
      printf ("Erro: Entrada invalida. Por favor, digite um numero inteiro entre %d e %d.\n", min, max);
      continue;
    }
    return numero;
  }
}

char **alocMemPlateia(){
  char **p = malloc(LINHAS*sizeof(char*)); //aloca memoria para o vetor de ponteiros
  if (p == NULL){
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }
  for (int i = 0; i < LINHAS; i++){
    p[i] = malloc(COLUNAS*sizeof(char)); //aloca memoria para cada linha da matriz
    if (p[i] == NULL){
      printf("Erro ao alocar memoria.\n");
      exit(1);
    }
  }
  return p; //retorna o endereço da matriz 
}

void criarCarregarPlateia(char *nomeArquivo, char **p){
  FILE *arquivo = fopen(nomeArquivo, "r"); //abre o arquivo para leitura

  //se o arquivo nao existir, cria um novo arquivo com a plateia vazia
  if (arquivo == NULL){
      arquivo = fopen(nomeArquivo, "w"); //abre o arquivo para escrita
    if (arquivo == NULL){
      printf("Erro ao criar o arquivo da plateia.\n");
      exit (1);
    }
    for (int i = 0; i < LINHAS; i++){
      for (int j = 0; j < COLUNAS; j++){
        fputc('-', arquivo); //escreve um '-' para cada assento
      }
      fputc('\n', arquivo); 
    }
    fclose(arquivo);
    arquivo = fopen(nomeArquivo, "r"); //abre o arquivo para leitura novamente
  }  
  for(int i = 0; i < LINHAS; i++){
    for(int j = 0; j < COLUNAS; j++){
      fscanf(arquivo, "%c", &p[i][j]); //armazena o conteudo do arquivo na matriz p
    }
    fgetc(arquivo); //consome o '\n'
  }  
  fclose(arquivo);
}

void liberarPlateia(char **p){
  for (int i = 0; i < LINHAS; i++){
    free(p[i]); //libera a memoria alocada para cada linha da matriz
  }
  free(p);
}

void salvarPlateia(char *nomeArquivo, char **p){ 
  FILE *arquivo = fopen(nomeArquivo, "w"); //abre o arquivo para escrita
  if (arquivo == NULL){
    printf("Erro ao abrir o arquivo da plateia.\n");
    exit (1);
  }
  for (int i = 0; i < LINHAS; i++){
    for (int j = 0; j < COLUNAS; j++){
      fputc(p[i][j], arquivo); //escreve o conteudo da matriz no arquivo
    }
    fputc('\n', arquivo);
  }
  fclose(arquivo);
}

void mostrarplateia(char **plateia){
    int numero = 1;
    printf("\nPlateia\n");
    printf("-------------------------------\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (plateia[i][j] == '-') {
                printf("%4d", numero); // numeros alinhados em 4 dígitos
            } else {
                printf("    "); // espacos para assentos ocupados
            }
            numero++;
        }
        printf("\n");
    }
    printf("-------------------------------\nFIM PLATEIA\n\n");
}

void mostrarocupacao(char **plateia){
  int meia = 0, inteira = 0;

  printf("\nOcupacao\n");
  printf("\n-------------------------------\n");

  for(int i = 0; i < LINHAS; i++){
    for(int j = 0; j < COLUNAS; j++){
      char assento = plateia [i][j]; 

      // contador de poltronas meias ou inteiras vendidas 
      if (assento == 'm' || assento == 'M')
        meia++;
      if (assento == 'i' || assento == 'I')
        inteira++;
      printf(" %c ", assento); 
    }
    printf("\n");
  }
  printf("\n-------------------------------\n");
  printf("Poltronas meias vendidas: %d\n", meia);
  printf("Poltronas inteiras vendidas: %d\n", inteira);
  printf("\n-------------------------------\nFim Ocupacao\n");
}


void venderingresso(char **plateia){
  int continuar = 1;

  while (continuar){
    mostrarplateia(plateia);

    int poltrona = 0;

    do{
      poltrona = InputInt("Digite o numero da poltrona <1..120> (zero encerra): ", 0, TAM_PLATEIA); //valida a entrada do usuario
      if (poltrona == 0) return;
      if (poltrona < 1 || poltrona > TAM_PLATEIA){
        printf("Poltrona invalida. Tente novamente.\n");
      }
    } while (poltrona < 1 || poltrona > TAM_PLATEIA); //realiza o loop enquanto o numero da poltrona for invalido

    //calcula a linha e a coluna da poltrona escolhida
    int linha = (poltrona - 1) / COLUNAS;
    int coluna = (poltrona - 1) % COLUNAS;

    //verifica se a poltrona esta ocupada
    if (plateia[linha][coluna] != '-'){
      printf("Poltrona ocupada. Tente novamente.\n");
      continue;
    }

    char tipo;
    do{
      printf("Digite se a entrada é (m)eia ou (i)nteira: ");
      scanf(" %c", &tipo);
      tipo = toupper(tipo); //converte o caractere para maiusculo para facilitar a comparacao
      fflush(stdin);
      if (tipo != 'M' && tipo != 'I') {
        printf("Entrada inválida! Digite apenas M ou I.\n"); //notifica o usuario sobre o erro
      }
    } while (tipo != 'M' && tipo != 'I'); //realiza o loop enquanto o tipo de ingresso for invalido

    plateia[linha][coluna] = tipo; //atualiza a matriz da plateia com o tipo de ingresso vendido

    salvarPlateia(ARQUIVO_PLATEIA, plateia); //salva a plateia no arquivo

    printf("Poltrona vendida: %d (%s). \n", poltrona, tipo == 'M' ? "meia" : "inteira"); //verifica o tipo do ingresso e imprime a string correspondente
    printf("(Fileira %d, coluna %d). \n", linha + 1, coluna + 1);

    int opcao; 
    do{
      opcao = InputInt("Deseja vender mais um ingresso? (1) Sim (0) Nao: ", 0, 1);
    } while (opcao != 0 && opcao != 1); //realiza o loop enquanto a opção for invalida

    if (opcao == 0) continuar = 0; 
  }

  printf("-------------------------------\nFIM VENDA DE INGRESSOS\n\n");
  
}
void cancelaringresso(char **plateia){

  int continuar = 1;

  printf("\nCancelamento de Ingressos\n-------------------------------\n");

  while (continuar){
  
    int poltrona;
  
    do{
      poltrona = InputInt("Digite o numero da poltrona a cancelar <1..120> (zero encerra): ", 0, TAM_PLATEIA);
    } while (poltrona < 1 || poltrona > TAM_PLATEIA);
  
    //calcula a linha e a coluna da poltrona escolhida
    int linha = (poltrona - 1) / COLUNAS;
    int coluna = (poltrona - 1) % COLUNAS;
  
    //verifica se a poltrona esta ocupada, caso esteja, desocupa a mesma
    if (plateia [linha][coluna] == 'I' || plateia [linha][coluna] == 'M'){
      plateia [linha][coluna] = '-';
      printf("Poltrona %d cancelada.\n", poltrona);
  
      //salva a plateia no arquivo
      FILE *fp = fopen(ARQUIVO_PLATEIA, "w");
      if (fp == NULL){
        printf("Erro ao abrir o arquivo da plateia.\n");
        exit (1);
      }
      for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
          fputc(plateia[i][j], fp);
        }
        fputc('\n', fp);
      } 
      fclose (fp);
    } else {
      printf("\nPoltrona %d nao vendida. Nada foi cancelado. \n", poltrona); //se a poltrona nao estiver vendida exibe uma mensagem de poltrona livre 
      }
    int opcao; 
    do{
      opcao = InputInt("\nDeseja cancelar mais um ingresso? (1) Sim (0) Nao: ", 0, 1);
    } while (opcao != 0 && opcao != 1); //realiza o loop enquanto a opção for invalida

    if (opcao == 0) continuar = 0; 
  }
  
  printf("-------------------------------\nFIM CANCELAMENTO DE INGRESSOS\n\n");

}

  
  