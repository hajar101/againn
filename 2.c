#include <stdio.h>

int main() {
    float C;
    float K;

    Printf("Entrez la temperature en Celsius : ");
    Scanf("%f", &C);

    K = C + 273.15;

    Printf("%.2f Celsius = %.2f Kelvin",C, K);

    return 0;
}

