#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura básica do território do jogo
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrar(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        printf("Nome do território: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe os territórios cadastrados
void mostrarTerritorios(Territorio* mapa, int qtd) {
    printf("\n====== LISTA DE TERRITÓRIOS ======\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função do ataque entre dois territórios
void realizarAtaque(Territorio* atk, Territorio* def) {
    printf("\n=== ATAQUE EM ANDAMENTO ===\n");

    printf("%s (%s) atacando %s (%s)\n",
           atk->nome, atk->cor, def->nome, def->cor);

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtk);
    printf("Dado do defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\nO atacante venceu!\n");

        strcpy(def->cor, atk->cor);
        def->tropas = atk->tropas / 2;

        printf("O território %s agora pertence à cor %s.\n",
               def->nome, def->cor);
    } else {
        printf("\nO ataque falhou. O atacante perdeu 1 tropa.\n");
        atk->tropas--;

        if (atk->tropas < 0) atk->tropas = 0;
    }
}

// Libera a memória alocada
void liberar(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // alocação dinâmica
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrar(mapa, qtd);
    mostrarTerritorios(mapa, qtd);

    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("2 - Mostrar territórios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int at, df;

            mostrarTerritorios(mapa, qtd);

            printf("\nEscolha o número do território atacante: ");
            scanf("%d", &at);

            printf("Escolha o número do território defensor: ");
            scanf("%d", &df);

            at--;
            df--;

            if (at == df) {
                printf("\nUm território não pode atacar ele mesmo.\n");
            } else if (strcmp(mapa[at].cor, mapa[df].cor) == 0) {
                printf("\nNão é possível atacar territórios da mesma cor.\n");
            } else {
                realizarAtaque(&mapa[at], &mapa[df]);
            }
        }

    } while (opcao != 0);

    liberar(mapa);

    printf("\nPrograma encerrado.\n");

    return 0;
}