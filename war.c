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

// Protótipos
void cadastrarTerritorios(
    Territorio *mapa,
    int quantidade);

void exibirTerritorios(
    Territorio *mapa,
    int quantidade);

void atacar(
    Territorio *atacante,
    Territorio *defensor);

void atribuirMissao(
    char *destino,
    char *missoes[],
    int totalMissoes);

void exibirMissao(
    char *missao);

int verificarMissao(
    char *missao,
    Territorio *mapa,
    int tamanho);

void liberarMemoria(
    Territorio *mapa,
    char *missaoJogador1,
    char *missaoJogador2);

int main()
{
    int quantidade;
    int indiceAtacante;
    int indiceDefensor;

    // inicializa a aleatoriedade
    srand(time(NULL));


    char *missoes[] =
    {
        "Conquistar 2 territorios",
        "Conquistar 3 territorios",
        "Possuir mais de 20 tropas",
        "Eliminar exercito vermelho",
        "Dominar todos os territorios"
    };

    int totalMissoes =
        sizeof(missoes) /
        sizeof(missoes[0]);

    printf("========================================\n");
    printf("      CADASTRO DE TERRITORIOS - WAR\n");
    printf("========================================\n\n");

    // quantidade de territórios
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

    // slocação das missões
    char *missaoJogador1 =
        malloc(100);

    char *missaoJogador2 =
        malloc(100);

    if (missaoJogador1 == NULL ||
        missaoJogador2 == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        free(territorios);
        return 1;
    }

    // sorteio das missões
    atribuirMissao(
        missaoJogador1,
        missoes,
        totalMissoes);

    atribuirMissao(
        missaoJogador2,
        missoes,
        totalMissoes);

    // cadastro
    cadastrarTerritorios(
        territorios,
        quantidade);

    // exibição inicial
    printf("\n");
    exibirTerritorios(
        territorios,
        quantidade);

    // exibição das missões
    printf("\n========================================\n");
    printf("MISSAO JOGADOR 1\n");
    printf("========================================\n");
    exibirMissao(
        missaoJogador1);

    printf("\n========================================\n");
    printf("MISSAO JOGADOR 2\n");
    printf("========================================\n");
    exibirMissao(
        missaoJogador2);

    // exibir mapa
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
        
                // Verificação das missões
        if (verificarMissao(
                missaoJogador1,
                territorios,
                quantidade))
        {
            printf(
                "\nJogador 1 cumpriu sua missao!\n");
        }

        if (verificarMissao(
                missaoJogador2,
                territorios,
                quantidade))
        {
            printf(
                "\nJogador 2 cumpriu sua missao!\n");
        }
    }

    // liberação da memória
    liberarMemoria(
        territorios,
        missaoJogador1, 
        missaoJogador2
    );

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

// sorteio da missão
void atribuirMissao(
    char *destino,
    char *missoes[],
    int totalMissoes)
{
    int indice =
        rand() % totalMissoes;

    strcpy(
        destino,
        missoes[indice]);
}

// exibir missão
void exibirMissao(
    char *missao)
{
    printf(
        "%s\n",
        missao);
}

// verificação simples
int verificarMissao(
    char *missao,
    Territorio *mapa,
    int tamanho)
{
    int totalTerritorios = tamanho;
    int totalTropas = 0;

    for (int i = 0; i < tamanho; i++)
    {
        totalTropas +=
            mapa[i].tropas;
    }

    if (strcmp(
            missao,
            "Conquistar 2 territorios") == 0)
    {
        return totalTerritorios >= 2;
    }

    if (strcmp(
            missao,
            "Conquistar 3 territorios") == 0)
    {
        return totalTerritorios >= 3;
    }

    if (strcmp(
            missao,
            "Possuir mais de 20 tropas") == 0)
    {
        return totalTropas > 20;
    }

    return 0;
}

// liberação
void liberarMemoria(
    Territorio *mapa,
    char *missaoJogador1,
    char *missaoJogador2)
{
    free(mapa);
    free(missaoJogador1);
    free(missaoJogador2);

    printf(
        "\nMemoria liberada com sucesso.\n");
}