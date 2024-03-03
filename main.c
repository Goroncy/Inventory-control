#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void validar_file(FILE *estoque);
int definir_operacao(FILE *estoque);
void imprimir_estoque(FILE *estoque);
void ajustar_estoque(FILE *estoque);
int retornar_quantidade_produto(FILE *estoque, char produto[100]);


int main(void){
    FILE *estoque;

    definir_operacao(estoque);

    return 0;
}

void validar_file(FILE *estoque){
    if (estoque == NULL)
    {
        printf("Não fo possível abrir o arquivo estoque.txt");
        exit(0);
    }
};

int definir_operacao(FILE *estoque){
    int escolha;

    printf("Escolha a operação a ser realizada:");
    printf("\n1 - Imprimir itens do estoque");
    printf("\n2 - Inserir item no estoque");
    printf("\n3 - Ajustar quantidade de um item");
    printf("\n4 - Remover item do estoque");
    printf("\nOperação a ser realizada -> ");
    
    scanf("%d",&escolha);

    switch (escolha)
    {
        case 1:
            printf("Não implementado.");
            break;
        case 2:
            printf("Não implementado.");
            break;
        case 3:
            ajustar_estoque(estoque);
            break;
        case 4:
            printf("Não implementado.");        
            break;
        default:
            break;
    };

    return escolha;
};

void imprimir_estoque(FILE *estoque){
    system("clear");
}

void ajustar_estoque(FILE *estoque){
    system("clear");
    FILE *tempEstoque;
    char linhas[100], produto[100], *produtoBusca;
    int quantidadeAntiga = -1, quantidadeNova, encontrado = 0 ;

    while(quantidadeAntiga == -1){
        printf("Informe o nome do produto que você deseja ajustar o estoque:\n");
        fgets(produto, sizeof(produto), stdin);
        fgets(produto, sizeof(produto), stdin);
        
        quantidadeAntiga = retornar_quantidade_produto(estoque,produto);

        if(quantidadeAntiga != -1){
            printf("O produto %s possui atualmente %d em estoque.\n", produto, quantidadeAntiga);
        }
        else{
            printf("Produto não encontrado, digite o nome novamente\n", produto, quantidadeAntiga);
        };
    }
    estoque = fopen("estoque.txt","r");
    validar_file(estoque);

    tempEstoque = fopen("estoqueTemporario.txt", "w");
    if (tempEstoque == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(estoque);
        exit(1);
    }

    printf("Informe a quantidade atual do produto:\n");
    scanf("%d", &quantidadeNova);

    while (fgets(linhas, 100, estoque) != NULL) {
        char linhaCopia[100];
        strcpy(linhaCopia, linhas);

        produtoBusca = strtok(linhaCopia, "|");
        if (produtoBusca != NULL) {
                if (strcmp(produtoBusca, produto) == 0) {
                    produtoBusca = strtok(NULL, "|"); // Avança para o próximo token que é a quantidade
                    quantidadeAntiga = atoi(produtoBusca); // Converte a quantidade antiga para inteiro
                    fprintf(tempEstoque, "%s|%d\n", produto, quantidadeNova);
                } else {
                    fprintf(tempEstoque, "%s", linhas);
                }
        }
    }
    fclose(estoque);
    fclose(tempEstoque);

    remove("estoque.txt");
    rename("estoqueTemporario.txt", "estoque.txt");
};

int retornar_quantidade_produto(FILE *estoque, char produto[100]){
    int encontrado = 0, quantidadeEstoque = 0;
    char linhas[100], *produtoBusca;
    estoque = fopen("estoque.txt","r");
    validar_file(estoque);
    
    while (fgets(linhas, 100, estoque) != NULL) {
        produto[strcspn(produto, "\n")] = '\0'; 
        produtoBusca = strtok(linhas, "|");
        if (strcmp(produto,produtoBusca) == 0) {
            encontrado = 1;
            produtoBusca = strtok(NULL, "|");
            quantidadeEstoque = atoi(produtoBusca);
            break;
        }
    }
    fclose(estoque);

    if (encontrado == 0) {
        return -1;
    } else {
        return quantidadeEstoque;
    }
}
