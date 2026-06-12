#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Cadastro dos territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    for (int i = 0; i < quantidade; i++) {

        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibição do mapa
void exibirMapa(Territorio *mapa, int quantidade) {

    printf("\n===== MAPA =====\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Exibe a missão (passagem por valor)
void exibirMissao(char missao[]) {

    printf("\n===== SUA MISSAO =====\n");
    printf("%s\n", missao);
}

// Sorteia e copia uma missão
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {

    int sorteio = rand() % totalMissoes;

    strcpy(destino, missoes[sorteio]);
}

// Simulação de ataque
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtacante tirou %d", dadoAtacante);
    printf("\nDefensor tirou %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("Ataque venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1)
            tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {

        printf("Defensor venceu!\n");

        if (atacante->tropas > 1)
            atacante->tropas--;
    }
}

// Verificação simples da missão
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {

    int contador = 0;

    for (int i = 0; i < tamanho; i++) {

        if (strcmp(mapa[i].cor, "Azul") == 0) {
            contador++;
        }
    }

    if (contador >= 3) {
        return 1;
    }

    return 0;
}

// Libera memória
void liberarMemoria(Territorio *mapa, char *missaoJogador) {

    free(mapa);
    free(missaoJogador);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica do mapa
    Territorio *mapa = calloc(quantidade, sizeof(Territorio));

    cadastrarTerritorios(mapa, quantidade);

    // Vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios.",
        "Eliminar o exercito vermelho.",
        "Dominar metade do mapa.",
        "Conquistar territorios consecutivos.",
        "Expandir o imperio."
    };

    // Alocação dinâmica da missão do jogador
    char *missaoJogador = malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, 5);

    exibirMissao(missaoJogador);

    exibirMapa(mapa, quantidade);

    int atacante, defensor;

    printf("\nIndice do atacante: ");
    scanf("%d", &atacante);

    printf("Indice do defensor: ");
    scanf("%d", &defensor);

    // Impede ataque entre territórios da mesma cor
    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) != 0) {

        atacar(&mapa[atacante], &mapa[defensor]);

        exibirMapa(mapa, quantidade);

        // Verificação silenciosa da missão
        if (verificarMissao(missaoJogador, mapa, quantidade)) {

            printf("\nMISSAO CUMPRIDA!\n");
            printf("Voce venceu o jogo!\n");
        }

    } else {

        printf("\nNao e permitido atacar territorios da mesma cor.\n");
    }

    liberarMemoria(mapa, missaoJogador);

    return 0;
}