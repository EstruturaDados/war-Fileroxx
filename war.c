// Removi todos os comentários pois estava atrapalhando a interpretação do código

#include <stdio.h>
#include <string.h>

// Estrutura Território
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército dominante
    int tropas;      // Quantidade de tropas no território
} Territorio;

int main() {

    // vetor que armazena 5 território
    Territorio territorios[5];

    char buffer[20];

    printf("========================================\n");
    printf("      CADASTRO DE TERRITORIOS - WAR\n");
    printf("========================================\n\n");

    // estruturando os dados
    for(int i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("--------------------------\n");


        // nome do território
        printf("Nome do territorio: ");
        
        fgets(territorios[i].nome,
              sizeof(territorios[i].nome),
              stdin);
        
        territorios[i].nome[
            strcspn(territorios[i].nome, "\n")
        ] = '\0';

        // cor do exército
        printf("Cor do exercito: ");
        fgets(territorios[i].cor,
              sizeof(territorios[i].cor),
              stdin);

        territorios[i].cor[
            strcspn(territorios[i].cor, "\n")
        ] = '\0';


        // quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar();
        printf("\n");

    }

    // exibição dos dados

    printf("\n========================================\n");
    printf("          MAPA ATUAL DO JOGO\n");
    printf("========================================\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome........: %s\n", territorios[i].nome);
        printf("Exercito....: %s\n", territorios[i].cor);
        printf("Tropas......: %d\n", territorios[i].tropas);
    }

    printf("\n========================================\n");
    printf("Cadastro finalizado com sucesso.\n");
    printf("========================================\n");

    return 0;
}