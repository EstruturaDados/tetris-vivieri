#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

//struct
typedef struct{
    char tipo;
    int id;
} Peca;

// variáveis globais
Peca fila [TAM_FILA];
int inicio = 0, fim = 0, qtd = 0;
int idAtual = 1;

// funções da fila
void inicializarFila() {
    inicio = fim = qtd = 0;
}

int filaVazia() {
    return qtd == 0;
}

int filaCheia() {
    return qtd == TAM_FILA;
}

Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L', 'S'};
    nova.tipo = tipos[rand() % 5];
    nova.id = idAtual++;
    return nova;
}

void enqueue(Peca p) {
    if (filaCheia()) {
        printf("Fila cheia!\n");
        return;
    }
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    qtd++;
}

Peca dequeue() {
    Peca removida = {' ', -1};
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return removida;
    }
    removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    qtd--;
    return removida;
}

void mostrarFila() {
    printf("\n--- FILA DE PEÇAS ---\n");
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return;
    }
    int i, idx;
    for (i = 0; i < qtd; i++) {
        idx = (inicio + i) % TAM_FILA;
        printf("Posição %d -> Tipo: %c | ID: %d\n", i + 1, fila[idx].tipo, fila[idx].id);
    }
    printf("----------------------\n");
}

// função principal
int main() {
    srand(time(NULL));
    inicializarFila();

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;
    do {
        mostrarFila();
        printf("\nMenu:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue();
                if (jogada.id != -1) {
                    printf("\nPeça jogada -> Tipo: %c | ID: %d\n", jogada.tipo, jogada.id);
                    // Sempre gera uma nova peça para manter 5 na fila
                    enqueue(gerarPeca());
                }
                break;
            }
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}