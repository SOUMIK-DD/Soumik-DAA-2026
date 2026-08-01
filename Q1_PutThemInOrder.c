#include <stdio.h>

int main() {
    char *functions[] = {
        "1/n",
        "log2(n)",
        "12*sqrt(n)",
        "50*n^0.5",
        "n^0.51",
        "2^32 * n",
        "n*log2(n)",
        "n^2 - 324",
        "100*n^2 + 6*n",
        "2*n^3",
        "n^(log2(n))",
        "3^n"
    };

    int n = sizeof(functions) / sizeof(functions[0]);

    printf("Functions in increasing order of growth:\n\n");

    for (int i = 0; i < n; i++) {
        printf("%2d. %s\n", i + 1, functions[i]);
    }

    return 0;
}