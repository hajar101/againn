#include <stdio.h>
#include <string.h>

int main() {
    char motSecret[] = "youcode";
    int taille = strlen(motSecret);
    char motCache[taille + 1];
    int i;

    for (i = 0; i < taille; i++) {
        motCache[i] = '_';
    }
    motCache[taille] = '\0';

    int tentativesMax = 5;
    int erreurs = 0;
    char lettre;
    int trouve;

    printf("Bienvenue dans le jeu du mot cache !\n");


    while (erreurs < tentativesMax) {
        printf("\nMot actuel : ");
        for (i = 0; i < taille; i++) {
            printf("%c ", motCache[i]);
        }
        printf("\nEntrez une lettre : ");
        scanf(" %c", &lettre);

        trouve = 0;
        for (i = 0; i < taille; i++) {
            if (motSecret[i] == lettre && motCache[i] == '_') {
                motCache[i] = lettre;
                trouve = 1;
            }
        }

        if (!trouve) {
            erreurs++;
            printf("Mauvaise lettre ! Tentatives restantes : %d\n", tentativesMax - erreurs);
        }


        if (strcmp(motSecret, motCache) == 0) {
            printf("\nFélicitations ! Vous avez deviné le mot : %s\n", motSecret);
            return 0;
        }
    }

    printf("\nGame Over ! Le mot était : %s\n", motSecret);
    return 0;
}
