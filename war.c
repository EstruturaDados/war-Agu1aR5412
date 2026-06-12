#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

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

void exibirTerritorios(Territorio *mapa, int quantidade) {

    printf("\n===== MAPA =====\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtacante tirou: %d\n", dadoAtacante);
    printf("Defensor tirou: %d\n", dadoDefensor);

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

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    Territorio *mapa = calloc(quantidade, sizeof(Territorio));

    cadastrarTerritorios(mapa, quantidade);

    exibirTerritorios(mapa, quantidade);

    int atacante, defensor;

    printf("\nIndice do atacante: ");
    scanf("%d", &atacante);

    printf("Indice do defensor: ");
    scanf("%d", &defensor);

    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) != 0) {

        atacar(&mapa[atacante], &mapa[defensor]);

        exibirTerritorios(mapa, quantidade);

    } else {

        printf("\nNao e permitido atacar territorios da mesma cor.\n");
    }

    liberarMemoria(mapa);

    return 0;
}