#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define estoqueFIle "estoque.txt"
#define tempEstoqueFile "estoqueTemporario.txt"

void validar_file(FILE *estoque,char *file);
int definir_operacao(FILE *estoque);
void imprimir_estoque(FILE *estoque);
void inserir_estoque(FILE *estoque);
void ajustar_estoque(FILE *estoque);
int retornar_quantidade_produto(FILE *estoque, char produto[100]);


int main(void){
    FILE *estoque;

    while(definir_operacao(estoque) != 5){};

    return 0;
}

void validar_file(FILE *estoque,char *file){
    if (estoque == NULL)
    {
        printf("Não fo possível abrir o arquivo %s",file);
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
    printf("\n5 - Encerrar sistema");
    printf("\nOperação a ser realizada -> ");
    
    scanf("%d",&escolha);

    switch (escolha)
    {
        case 1:
            printf("Não implementado.");
            break;
        case 2:
            inserir_estoque(estoque);
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

void inserir_estoque(FILE *estoque){
    char produto[100];
    int quantidade;

    estoque = fopen(estoqueFIle,"w");
    validar_file(estoque,estoqueFIle);
    
    printf("Informe o nome do produto:\n");
    getchar();
    fgets(produto, sizeof(produto), stdin);
    printf("Informe a quantidade do produto:\n");
    scanf("%d", &quantidade);
    produto[strcspn(produto, "\n")] = '\0'; 
    fprintf(estoque,"%s|%d",produto,quantidade);

    fclose(estoque);
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

    remove(estoqueFIle);
    rename(tempEstoqueFile, estoqueFIle);
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
        }
    }
    fclose(estoque);

    if (encontrado == 0) {
        return -1;
    } else {
        return quantidadeEstoque;
    }
}
