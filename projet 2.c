#include <stdio.h>
#include <stdlib.h>

int main()
{

    char motSecret[8] = "youcode";
    char motCache[8];
    char lettre;
    int i ;
    int correct = 0;
    int fini = 1;

    for (i = 0; i < 7; i++) {
        motCache[i] = '_';       // to initialise le motcache with ----
    }
    motCache[7] = '\0';  // \0 for the end chain

    printf("=== Jeu de devinette ===\n");

    while (1) {

        for (i = 0; i < 7; i++) {
            printf("%c ", motCache[i]);
        }
        printf("\n"); //to start

        printf("Saisir une lettre : ");
        scanf(" %c", &lettre);


                 // to check the letter
        for (i = 0; i < 7; i++) {
            if (motSecret[i] == lettre && motCache[i] == '_') {
                motCache[i] = lettre;
                correct = 1;
            }
        }

        if (correct == 0) {
            printf("Mauvaise réponse !\n");
        }
                // check if the whole word has been found
        for (i = 0; i < 7; i++) {
            if (motSecret[i] != motCache[i]) {
                fini = 0;
            }
        }

        if (fini == 1) {
            printf("\n Vous avez trouve le mot : %s\n", motSecret);
            break;
        }
    }
    return 0;
}
