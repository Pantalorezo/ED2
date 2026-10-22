#include <stdio.h>

void matching3Way(int l1[], int n1, int l2[], int n2, int l3[], int n3) {
    int i = 0, j = 0, k = 0;

    printf("Resultado do Matching Multi-way (interseccao):\n");

    while (i < n1 && j < n2 && k < n3) {
        // Se o elemento for igual nas três listas, encontramos uma correspondência
        if (l1[i] == l2[j] && l2[j] == l3[k]) {
            printf("%d ", l1[i]);
            i++;
            j++;
            k++;
        }
        // Caso contrário, avança o ponteiro da lista que tiver o menor elemento
        else if (l1[i] < l2[j]) {
            i++;
        } else if (l2[j] < l3[k]) {
            j++;
        } else {
            k++;
        }
    }
    printf("\n");
}

int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = {10, 25, 30, 40, 50, 70};
    int l3[] = {1, 8, 10, 18, 25};

    int n1 = sizeof(l1) / sizeof(l1[0]);
    int n2 = sizeof(l2) / sizeof(l2[0]);
    int n3 = sizeof(l3) / sizeof(l3[0]);

    matching3Way(l1, n1, l2, n2, l3, n3);

    return 0;
}