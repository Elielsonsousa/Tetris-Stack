#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // Tamanho fixo da fila

// -------------------------
// Estrutura da peça
// -------------------------
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// -------------------------
// Estrutura da fila circular
// -------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// -------------------------
// Função para iniciar a fila
// -------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

// -------------------------
// Gera uma nova peça automática
// -------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = id;

    return nova;
}

// -------------------------
// Verifica se fila está cheia
// -------------------------
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// -------------------------
// Verifica se fila está vazia
// -------------------------
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// -------------------------
// Insere peça (enqueue)
// -------------------------
void inserirPeca(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nA fila está cheia! Não é possível inserir.\n");
        return;
    }

    f->fim = (f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = p;
    f->quantidade++;

    printf("\nPeça [%c %d] inserida com sucesso!\n", p.nome, p.id);
}

// -------------------------
// Remove peça (dequeue)
// -------------------------
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("\nA fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

// -------------------------
// Exibe fila
// -------------------------
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        Peca p = f->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// -------------------------
// Programa principal
// -------------------------
int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));

    // Inicializa com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila, gerarPeca(i));
    }

    int opcao;
    int contadorId = TAM_FILA;

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;

            case 2:
                if (!filaCheia(&fila)) {
                    inserirPeca(&fila, gerarPeca(contadorId++));
                } else {
                    printf("\nFila cheia! Não é possível inserir nova peça.\n");
                }
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
