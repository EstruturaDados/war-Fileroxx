// Removi todos os comentários pois estava atrapalhando a interpretação do código

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// estrutura Território
typedef struct
{
    char nome[30]; // nome do território
    char cor[10];  // cor do exército dominante
    int tropas;    // quantidade de tropas no território
} Territorio;

void cadastrarTerritorios(Territorio *mapa, int quantidade);
void exibirTerritorios(Territorio *mapa, int quantidade);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

int main()
{
    int quantidade;
    int indiceAtacante;
    int indiceDefensor;

    // inicializa a aleatoriedade
    srand(time(NULL));

    printf("========================================\n");
    printf("      CADASTRO DE TERRITORIOS - WAR\n");
    printf("========================================\n\n");

    // Quantidade de territórios
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);
    getchar();

    // alocação dinâmica
    Territorio *territorios =
        (Territorio *)malloc(
            quantidade * sizeof(Territorio));

    if (territorios == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // cadastro
    cadastrarTerritorios(
        territorios,
        quantidade);

    // exibição inicial
    printf("\n");
    exibirTerritorios(
        territorios,
        quantidade);

    // escolha do atacante
    printf("\n========================================\n");
    printf("ESCOLHA O TERRITORIO ATACANTE\n");
    printf("========================================\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf(
            "%d - %s (%s)\n",
            i,
            territorios[i].nome,
            territorios[i].cor);
    }

    printf("\nIndice do atacante: ");
    scanf("%d", &indiceAtacante);

    // escolha do defensor
    printf("\nIndice do defensor: ");
    scanf("%d", &indiceDefensor);

    // validação
    if (indiceAtacante < 0 ||
        indiceAtacante >= quantidade ||
        indiceDefensor < 0 ||
        indiceDefensor >= quantidade)
    {

        printf("\nIndice invalido.\n");
    }
    else if (indiceAtacante == indiceDefensor)
    {
        printf("\nUm territorio nao pode atacar a si mesmo.\n");
    }
    else if (
        strcmp(
            territorios[indiceAtacante].cor,
            territorios[indiceDefensor].cor) == 0)
    {
        printf(
            "\nNao e permitido atacar um territorio aliado.\n");
    }
    else
    {
        atacar(
            &territorios[indiceAtacante],
            &territorios[indiceDefensor]);

        printf("\n");
        exibirTerritorios(
            territorios,
            quantidade);
    }

    // liberação da memória
    liberarMemoria(territorios);

    return 0;
}

// função para cadastrar territórios
void cadastrarTerritorios(
    Territorio *mapa,
    int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {

        printf("\nTerritorio %d\n", i + 1);
        printf("-------------------------\n");

        printf("Nome do territorio: ");
        fgets(
            mapa[i].nome,
            sizeof(mapa[i].nome),
            stdin);

        mapa[i].nome[strcspn(
            mapa[i].nome,
            "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(
            mapa[i].cor,
            sizeof(mapa[i].cor),
            stdin);

        mapa[i].cor[strcspn(
            mapa[i].cor,
            "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        getchar();
    }
}

// função para exibir territórios
void exibirTerritorios(
    Territorio *mapa,
    int quantidade)
{
    printf("========================================\n");
    printf("          MAPA DO JOGO\n");
    printf("========================================\n");

    for (int i = 0; i < quantidade; i++)
    {

        printf("\nTerritorio %d\n", i);
        printf(
            "Nome.....: %s\n",
            mapa[i].nome);

        printf(
            "Exercito.: %s\n",
            mapa[i].cor);

        printf(
            "Tropas...: %d\n",
            mapa[i].tropas);
    }
}

// função de ataque
void atacar(
    Territorio *atacante,
    Territorio *defensor)
{
    int dadoAtacante =
        rand() % 6 + 1;

    int dadoDefensor =
        rand() % 6 + 1;

    printf("\n========================================\n");
    printf("            BATALHA\n");
    printf("========================================\n");

    printf(
        "%s atacou %s\n",
        atacante->nome,
        defensor->nome);

    printf(
        "Dado atacante: %d\n",
        dadoAtacante);

    printf(
        "Dado defensor: %d\n",
        dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {

        printf(
            "\nO atacante venceu!\n");

        strcpy(
            defensor->cor,
            atacante->cor);

        defensor->tropas =
            atacante->tropas / 2;

        if (defensor->tropas < 1)
            defensor->tropas = 1;
    }
    else
    {

        printf(
            "\nO defensor venceu!\n");

        if (atacante->tropas > 1)
            atacante->tropas--;
    }
}

// função para liberar memória
void liberarMemoria(
    Territorio *mapa)
{
    free(mapa);

    printf(
        "\nMemoria liberada com sucesso.\n");
}