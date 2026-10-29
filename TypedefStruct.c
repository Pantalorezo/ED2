#include <stdbool.h>
#include <stdlib.h>

#define GRAU_MINIMO 2
#define MAX_CHAVES (2 * GRAU_MINIMO - 1)
#define MAX_FILHOS (2 * GRAU_MINIMO)

typedef struct NoArvoreB {
    int quantidade;
    bool folha;
    int chaves[MAX_CHAVES];
    struct NoArvoreB *filhos[MAX_FILHOS];
} NoArvoreB;

typedef struct ArvoreB {
    NoArvoreB *raiz;
} ArvoreB;

NoArvoreB *alocar_no(bool folha) {
    NoArvoreB *no = calloc(1, sizeof(*no));
    if (no != NULL)
        no->folha = folha;
    return no;
}

bool inicializar_arvore_b(ArvoreB *arvore) {
    if (arvore == NULL)
        return false;

    arvore->raiz = alocar_no(true);
    return arvore->raiz != NULL;
}

static NoArvoreB *buscar_no(NoArvoreB *no, int chave) {
    int i = 0;
    while (i < no->quantidade && chave > no->chaves[i])
        i++;

    if (i < no->quantidade && chave == no->chaves[i])
        return no;
    if (no->folha)
        return NULL;
    return buscar_no(no->filhos[i], chave);
}

bool buscar_arvore_b(const ArvoreB *arvore, int chave) {
    return arvore != NULL && arvore->raiz != NULL &&
           buscar_no(arvore->raiz, chave) != NULL;
}

static bool dividir_filho(NoArvoreB *pai, int indice) {
    NoArvoreB *cheio = pai->filhos[indice];
    NoArvoreB *novo = alocar_no(cheio->folha);
    if (novo == NULL)
        return false;

    novo->quantidade = GRAU_MINIMO - 1;
    for (int j = 0; j < GRAU_MINIMO - 1; j++)
        novo->chaves[j] = cheio->chaves[j + GRAU_MINIMO];
    if (!cheio->folha) {
        for (int j = 0; j < GRAU_MINIMO; j++)
            novo->filhos[j] = cheio->filhos[j + GRAU_MINIMO];
    }

    cheio->quantidade = GRAU_MINIMO - 1;
    for (int j = pai->quantidade; j >= indice + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    pai->filhos[indice + 1] = novo;

    for (int j = pai->quantidade - 1; j >= indice; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    pai->chaves[indice] = cheio->chaves[GRAU_MINIMO - 1];
    pai->quantidade++;
    return true;
}

static bool inserir_em_no_nao_cheio(NoArvoreB *no, int chave) {
    int i = no->quantidade - 1;
    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->quantidade++;
        return true;
    }

    while (i >= 0 && chave < no->chaves[i])
        i--;
    i++;
    if (no->filhos[i]->quantidade == MAX_CHAVES) {
        if (!dividir_filho(no, i))
            return false;
        if (chave > no->chaves[i])
            i++;
    }
    return inserir_em_no_nao_cheio(no->filhos[i], chave);
}

/* Retorna 1 se inseriu, 0 se a chave já existia e -1 em caso de erro. */
int inserir_arvore_b(ArvoreB *arvore, int chave) {
    if (arvore == NULL)
        return -1;
    if (buscar_arvore_b(arvore, chave))
        return 0;

    if (arvore->raiz == NULL) {
        arvore->raiz = alocar_no(true);
        if (arvore->raiz == NULL)
            return -1;
    }

    NoArvoreB *raiz = arvore->raiz;
    if (raiz->quantidade == MAX_CHAVES) {
        NoArvoreB *nova_raiz = alocar_no(false);
        if (nova_raiz == NULL)
            return -1;
        nova_raiz->filhos[0] = raiz;
        if (!dividir_filho(nova_raiz, 0)) {
            free(nova_raiz);
            return -1;
        }
        arvore->raiz = nova_raiz;
        raiz = nova_raiz;
    }

    return inserir_em_no_nao_cheio(raiz, chave) ? 1 : -1;
}

static int indice_da_chave(const NoArvoreB *no, int chave) {
    int indice = 0;
    while (indice < no->quantidade && no->chaves[indice] < chave)
        indice++;
    return indice;
}

static int predecessor(NoArvoreB *no) {
    while (!no->folha)
        no = no->filhos[no->quantidade];
    return no->chaves[no->quantidade - 1];
}

static int sucessor(NoArvoreB *no) {
    while (!no->folha)
        no = no->filhos[0];
    return no->chaves[0];
}

static void emprestar_do_anterior(NoArvoreB *pai, int indice) {
    NoArvoreB *filho = pai->filhos[indice];
    NoArvoreB *irmao = pai->filhos[indice - 1];

    for (int i = filho->quantidade - 1; i >= 0; i--)
        filho->chaves[i + 1] = filho->chaves[i];
    if (!filho->folha) {
        for (int i = filho->quantidade; i >= 0; i--)
            filho->filhos[i + 1] = filho->filhos[i];
    }

    filho->chaves[0] = pai->chaves[indice - 1];
    if (!filho->folha)
        filho->filhos[0] = irmao->filhos[irmao->quantidade];
    pai->chaves[indice - 1] = irmao->chaves[irmao->quantidade - 1];
    filho->quantidade++;
    irmao->quantidade--;
}

static void emprestar_do_proximo(NoArvoreB *pai, int indice) {
    NoArvoreB *filho = pai->filhos[indice];
    NoArvoreB *irmao = pai->filhos[indice + 1];

    filho->chaves[filho->quantidade] = pai->chaves[indice];
    if (!filho->folha)
        filho->filhos[filho->quantidade + 1] = irmao->filhos[0];
    pai->chaves[indice] = irmao->chaves[0];

    for (int i = 1; i < irmao->quantidade; i++)
        irmao->chaves[i - 1] = irmao->chaves[i];
    if (!irmao->folha) {
        for (int i = 1; i <= irmao->quantidade; i++)
            irmao->filhos[i - 1] = irmao->filhos[i];
    }
    filho->quantidade++;
    irmao->quantidade--;
}

static void fundir_filhos(NoArvoreB *pai, int indice) {
    NoArvoreB *filho = pai->filhos[indice];
    NoArvoreB *irmao = pai->filhos[indice + 1];
    int quantidade_original = filho->quantidade;

    filho->chaves[quantidade_original] = pai->chaves[indice];
    for (int i = 0; i < irmao->quantidade; i++)
        filho->chaves[quantidade_original + 1 + i] = irmao->chaves[i];
    if (!filho->folha) {
        for (int i = 0; i <= irmao->quantidade; i++)
            filho->filhos[quantidade_original + 1 + i] = irmao->filhos[i];
    }
    filho->quantidade += irmao->quantidade + 1;

    for (int i = indice + 1; i < pai->quantidade; i++)
        pai->chaves[i - 1] = pai->chaves[i];
    for (int i = indice + 2; i <= pai->quantidade; i++)
        pai->filhos[i - 1] = pai->filhos[i];
    pai->quantidade--;
    free(irmao);
}

static void preparar_descida(NoArvoreB *no, int *indice) {
    if (*indice > 0 &&
        no->filhos[*indice - 1]->quantidade >= GRAU_MINIMO) {
        emprestar_do_anterior(no, *indice);
    } else if (*indice < no->quantidade &&
               no->filhos[*indice + 1]->quantidade >= GRAU_MINIMO) {
        emprestar_do_proximo(no, *indice);
    } else if (*indice < no->quantidade) {
        fundir_filhos(no, *indice);
    } else {
        fundir_filhos(no, *indice - 1);
        (*indice)--;
    }
}

static void remover_de_no(NoArvoreB *no, int chave) {
    int indice = indice_da_chave(no, chave);

    if (indice < no->quantidade && no->chaves[indice] == chave) {
        if (no->folha) {
            for (int i = indice + 1; i < no->quantidade; i++)
                no->chaves[i - 1] = no->chaves[i];
            no->quantidade--;
        } else if (no->filhos[indice]->quantidade >= GRAU_MINIMO) {
            int anterior = predecessor(no->filhos[indice]);
            no->chaves[indice] = anterior;
            remover_de_no(no->filhos[indice], anterior);
        } else if (no->filhos[indice + 1]->quantidade >= GRAU_MINIMO) {
            int proxima = sucessor(no->filhos[indice + 1]);
            no->chaves[indice] = proxima;
            remover_de_no(no->filhos[indice + 1], proxima);
        } else {
            fundir_filhos(no, indice);
            remover_de_no(no->filhos[indice], chave);
        }
        return;
    }

    if (no->folha)
        return;

    bool ultima_filha = indice == no->quantidade;
    if (no->filhos[indice]->quantidade < GRAU_MINIMO)
        preparar_descida(no, &indice);
    if (ultima_filha && indice > no->quantidade)
        remover_de_no(no->filhos[indice - 1], chave);
    else
        remover_de_no(no->filhos[indice], chave);
}

/* Retorna 1 se removeu e 0 se a chave não estava na árvore. */
int remover_arvore_b(ArvoreB *arvore, int chave) {
    if (arvore == NULL || !buscar_arvore_b(arvore, chave))
        return 0;

    remover_de_no(arvore->raiz, chave);
    if (arvore->raiz->quantidade == 0) {
        NoArvoreB *raiz_antiga = arvore->raiz;
        if (raiz_antiga->folha) {
            free(raiz_antiga);
            arvore->raiz = NULL;
        } else {
            arvore->raiz = raiz_antiga->filhos[0];
            free(raiz_antiga);
        }
    }
    return 1;
}

static void liberar_no(NoArvoreB *no) {
    if (no == NULL)
        return;
    if (!no->folha) {
        for (int i = 0; i <= no->quantidade; i++)
            liberar_no(no->filhos[i]);
    }
    free(no);
}

void liberar_arvore_b(ArvoreB *arvore) {
    if (arvore == NULL)
        return;
    liberar_no(arvore->raiz);
    arvore->raiz = NULL;
}