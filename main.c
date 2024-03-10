#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define estoqueFIle "estoque.txt"
#define tempEstoqueFile "estoqueTemporario.txt"

void validar_file(FILE *estoque,char *file);
int definir_operacao(FILE *estoque);
void imprimir_estoque(FILE *estoque);
void inserir_estoque(FILE *estoque);
void ajustar_estoque(FILE *estoque);
int retornar_quantidade_produto(FILE *estoque, char produto[100]);
void remover_estoque(FILE *estoque);


int main(void){
    FILE *estoque;
    
    setlocale(LC_ALL, "");
    while(definir_operacao(estoque) != 5){};
    return 0;
}

void validar_file(FILE *estoque,char *file){
    if (estoque == NULL)
    {
        printf("Não fo possível abrir o arquivo %s!\nVerifique se o arquivo estoque.txt se encontra na pasta e reinicie o programa.",file);
        getchar();
        getchar();
        exit(0);
    }
};

int definir_operacao(FILE *estoque){
    int escolha;
    system("clear");
    printf("Escolha a operação a ser realizada:");
    printf("\n1 - Imprimir itens do estoque");
    printf("\n2 - Inserir item no estoque");
    printf("\n3 - Ajustar quantidade de um item");
    printf("\n4 - Remover item do estoque");
    printf("\n5 - Encerrar sistema");
    printf("\nOperação a ser realizada -> ");
    
    scanf("%d",&escolha);

    switch (escolha)
    {
        case 1:
            imprimir_estoque(estoque);
            break;
        case 2:
            inserir_estoque(estoque);
            break;
        case 3:
            ajustar_estoque(estoque);
            break;
        case 4:
            remover_estoque(estoque);
            break;
        default:
            break;
    };

    return escolha;
};

void imprimir_estoque(FILE *estoque){
    system("clear");
    char *linha, *linhaCopia, *produto;
    int quantidade;

    linha = malloc(150 * sizeof(char));
    linhaCopia = malloc(150 * sizeof(char));

    estoque = fopen(estoqueFIle,"r");
    validar_file(estoque,estoqueFIle);    

    while(fgets(linha,150,estoque) != NULL){        
        strcpy(linhaCopia, linha);

        produto = strtok(linhaCopia, "|");
        quantidade = atoi(strtok(NULL, "|"));

        printf("Produto %s -> %d\n",produto,quantidade);
    }
    fclose(estoque);

    printf("\nAperte qualquer tecla para retornar a tela inicial.");
    getchar();
    getchar();
}

void inserir_estoque(FILE *estoque){
    char produto[100];
    int quantidade;

    system("clear");
    estoque = fopen(estoqueFIle,"a");
    validar_file(estoque,estoqueFIle);
    
    printf("Informe o nome do produto:\n");
    getchar();
    fgets(produto, sizeof(produto), stdin);
    printf("Informe a quantidade do produto:\n");
    scanf("%d", &quantidade);
    produto[strcspn(produto, "\n")] = '\0'; 
    fprintf(estoque,"%s|%d\n",produto,quantidade);
    fclose(estoque);
    printf("Aperte qualquer tecla para retornar a tela de opções.");
    getchar();
    getchar();
    system("clear");
};

void ajustar_estoque(FILE *estoque){
    system("clear");
    FILE *tempEstoque;
    char linhas[100], produto[100], *produtoBusca;
    int quantidadeAntiga = -1, quantidadeNova, encontrado = 0 ;

    while(quantidadeAntiga == -1){
        printf("Informe o nome do produto que você deseja ajustar o estoque:\n");
        getchar();
        fgets(produto, sizeof(produto), stdin);
        
        quantidadeAntiga = retornar_quantidade_produto(estoque,produto);

        if(quantidadeAntiga != -1){
            printf("O produto %s possui atualmente %d em estoque.\n", produto, quantidadeAntiga);
        }
        else{
            printf("Produto não encontrado, digite o nome novamente\n", produto, quantidadeAntiga);
        };
    };

    estoque = fopen(estoqueFIle,"r");
    validar_file(estoque,estoqueFIle);

    tempEstoque = fopen(tempEstoqueFile, "w");
    validar_file(tempEstoque,tempEstoqueFile);

    printf("Informe a quantidade atual do produto:\n");
    scanf("%d", &quantidadeNova);

    while (fgets(linhas, 100, estoque) != NULL) {
        char linhaCopia[100];
        strcpy(linhaCopia, linhas);

        produtoBusca = strtok(linhaCopia, "|");
        if (produtoBusca != NULL) {
                if (strcmp(produtoBusca, produto) == 0) {
                    produtoBusca = strtok(NULL, "|"); 
                    quantidadeAntiga = atoi(produtoBusca);
                    fprintf(tempEstoque, "%s|%d\n", produto, quantidadeNova);
                } else {
                    fprintf(tempEstoque, "%s", linhas);
                };
        };
    };

    fclose(estoque);
    fclose(tempEstoque);

    remove(estoqueFIle);
    rename(tempEstoqueFile, estoqueFIle);

    printf("Produto ajustado, aperte qualquer tecla para retornar a tela inicial.");
    getchar();
    getchar();
    system("clear");
};

int retornar_quantidade_produto(FILE *estoque, char produto[100]){
    int encontrado = 0, quantidadeEstoque = 0;
    char linhas[100], *produtoBusca;
    estoque = fopen(estoqueFIle,"r");
    validar_file(estoque,estoqueFIle);
    
    while (fgets(linhas, 100, estoque) != NULL) {
        produto[strcspn(produto, "\n")] = '\0'; 
        produtoBusca = strtok(linhas, "|");
        if (strcmp(produto,produtoBusca) == 0) {
            encontrado = 1;
            produtoBusca = strtok(NULL, "|");
            quantidadeEstoque = atoi(produtoBusca);
            break;
        };
    };
    
    fclose(estoque);

    if (encontrado == 0) {
        return -1;
    } else {
        return quantidadeEstoque;
    };
}

void remover_estoque(FILE *estoque){
    system("clear");
    FILE *tempEstoque;
    char linhas[100], produto[100], *produtoBusca;

    printf("Informe o nome do produto que você deseja remover do estoque:\n");
    getchar();
    fgets(produto, sizeof(produto), stdin);

    estoque = fopen(estoqueFIle,"r");
    validar_file(estoque,estoqueFIle);

    tempEstoque = fopen(tempEstoqueFile, "w");
    validar_file(tempEstoque,tempEstoqueFile);

    while (fgets(linhas, 100, estoque) != NULL) {
        char linhaCopia[100];
        strcpy(linhaCopia, linhas);
        produto[strcspn(produto, "\n")] = '\0'; 
        produtoBusca = strtok(linhaCopia, "|");
        if (produtoBusca != NULL) {
                if (strcmp(produtoBusca, produto) != 0) {
                    fprintf(tempEstoque, "%s", linhas);
                };
        };
    };

    fclose(estoque);
    fclose(tempEstoque);

    remove(estoqueFIle);
    rename(tempEstoqueFile, estoqueFIle);
    
    printf("Produto removido do estoque, aperte qualquer tecla para retornar a tela inicial.");
    getchar();
    system("clear");
}
