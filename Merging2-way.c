#include <stdio.h>

void merging2Way(int l1[], int n1, int l2[], int n2, int saida[]) {
    int i = 0, j = 0, k = 0;

    // Intercala os elementos enquanto houver itens em ambos os vetores
    while (i < n1 && j < n2) {
        if (l1[i] <= l2[j]) {
            saida[k++] = l1[i++];
        } else {
            saida[k++] = l2[j++];
        }
    }

    // Copia os elementos restantes da Lista 1, se houver
    while (i < n1) {
        saida[k++] = l1[i++];
    }

    // Copia os elementos restantes da Lista 2, se houver
    while (j < n2) {
        saida[k++] = l2[j++];
    }
}

int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = {5, 20, 30, 40, 50, 70};
    int n1 = sizeof(l1) / sizeof(l1[0]);
    int n2 = sizeof(l2) / sizeof(l2[0]);
    int saida[n1 + n2];

    merging2Way(l1, n1, l2, n2, saida);

    printf("Resultado do Merging 2-way:\n");
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", saida[i]);
    }
    printf("\n");

    return 0;
}#include <stdio.h>

void merging2Way(int l1[], int n1, int l2[], int n2, int saida[]) {
    int i = 0, j = 0, k = 0;

    // Intercala os elementos enquanto houver itens em ambos os vetores
    while (i < n1 && j < n2) {
        if (l1[i] <= l2[j]) {
            saida[k++] = l1[i++];
        } else {
            saida[k++] = l2[j++];
        }
    }

    // Copia os elementos restantes da Lista 1, se houver
    while (i < n1) {
        saida[k++] = l1[i++];
    }

    // Copia os elementos restantes da Lista 2, se houver
    while (j < n2) {
        saida[k++] = l2[j++];
    }
}

int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = {5, 20, 30, 40, 50, 70};
    int n1 = sizeof(l1) / sizeof(l1[0]);
    int n2 = sizeof(l2) / sizeof(l2[0]);
    int saida[n1 + n2];

    merging2Way(l1, n1, l2, n2, saida);

    printf("Resultado do Merging 2-way:\n");
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", saida[i]);
    }
    printf("\n");

    return 0;
}#include <stdio.h>

void merging2Way(int l1[], int n1, int l2[], int n2, int saida[]) {
    int i = 0, j = 0, k = 0;

    // Intercala os elementos enquanto houver itens em ambos os vetores
    while (i < n1 && j < n2) {
        if (l1[i] <= l2[j]) {
            saida[k++] = l1[i++];
        } else {
            saida[k++] = l2[j++];
        }
    }

    // Copia os elementos restantes da Lista 1, se houver
    while (i < n1) {
        saida[k++] = l1[i++];
    }

    // Copia os elementos restantes da Lista 2, se houver
    while (j < n2) {
        saida[k++] = l2[j++];
    }
}

int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = {5, 20, 30, 40, 50, 70};
    int n1 = sizeof(l1) / sizeof(l1[0]);
    int n2 = sizeof(l2) / sizeof(l2[0]);
    int saida[n1 + n2];

    merging2Way(l1, n1, l2, n2, saida);

    printf("Resultado do Merging 2-way:\n");
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", saida[i]);
    }
    printf("\n");

    return 0;
}