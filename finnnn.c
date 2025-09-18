#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXTE 2000
#define MAX_MOTS  500

// ----------- Structures -----------
typedef struct {
    char mot[50];
    int occurrences;
    int longueur;
    int positions[100];
    int nbPositions;
} WordInfo;

typedef struct {
    WordInfo mots[MAX_MOTS];
    int nbMots;
} Dictionnaire;

// ----------- Nettoyage Analyse -----------
void nettoyerMot(char *mot) {
    int i, j = 0;
    char temp[50];
    for(i = 0; mot[i] != '\0'; i++) {
        if(isalpha((unsigned char)mot[i])) {
            temp[j++] = tolower(mot[i]);
        }
    }
    temp[j] = '\0';
    strcpy(mot, temp);
}

void analyserTexte(char *texte, Dictionnaire *dico) {
    dico->nbMots = 0;
    char *token;
    int position = 1;

    token = strtok(texte, " \n\t");
    while(token != NULL) {
        nettoyerMot(token);
        if(strlen(token) > 0) {
            int found = 0;
            for(int i = 0; i < dico->nbMots; i++) {
                if(strcmp(dico->mots[i].mot, token) == 0) {
                    dico->mots[i].occurrences++;
                    dico->mots[i].positions[dico->mots[i].nbPositions++] = position;
                    found = 1;
                    break;
                }
            }
            if(!found && dico->nbMots < MAX_MOTS) {
                strcpy(dico->mots[dico->nbMots].mot, token);
                dico->mots[dico->nbMots].occurrences = 1;
                dico->mots[dico->nbMots].longueur = strlen(token);
                dico->mots[dico->nbMots].positions[0] = position;
                dico->mots[dico->nbMots].nbPositions = 1;
                dico->nbMots++;
            }
            position++;
        }
        token = strtok(NULL, " \n\t");
    }
}

// ----------- Affichage -----------
void afficherDictionnaire(Dictionnaire *dico) {
    printf("\n--- Dictionnaire ---\n");
    for(int i = 0; i < dico->nbMots; i++) {
        printf("Mot: %s | Occurrences: %d | Longueur: %d | Positions: ",
               dico->mots[i].mot, dico->mots[i].occurrences, dico->mots[i].longueur);
        for(int j = 0; j < dico->mots[i].nbPositions; j++) {
            printf("%d ", dico->mots[i].positions[j]);
        }
        printf("\n");
    }
}

// ----------- Recherche -----------
void rechercherMotExact(Dictionnaire *dico, char *mot) {
    for(int i = 0; i < dico->nbMots; i++) {
        if(strcmp(dico->mots[i].mot, mot) == 0) {
            printf("Trouvé: %s | Occurrences: %d\n", dico->mots[i].mot, dico->mots[i].occurrences);
            return;
        }
    }
    printf("Mot '%s' non trouvé.\n", mot);
}

void rechercherMotPartiel(Dictionnaire *dico, char *chaine) {
    int trouve = 0;
    for(int i = 0; i < dico->nbMots; i++) {
        if(strstr(dico->mots[i].mot, chaine) != NULL) {
            printf("Mot trouvé: %s\n", dico->mots[i].mot);
            trouve = 1;
        }
    }
    if(!trouve) printf("Aucun mot contenant '%s' trouvé.\n", chaine);
}

// ----------- Statistiques -----------
void statistiques(Dictionnaire *dico) {
    int totalMots = 0;
    int sommeLongueurs = 0;
    WordInfo *plusLong = &dico->mots[0];
    WordInfo *plusCourt = &dico->mots[0];
    WordInfo *plusFrequent = &dico->mots[0];

    for(int i = 0; i < dico->nbMots; i++) {
        totalMots += dico->mots[i].occurrences;
        sommeLongueurs += dico->mots[i].longueur * dico->mots[i].occurrences;

        if(dico->mots[i].longueur > plusLong->longueur)
            plusLong = &dico->mots[i];
        if(dico->mots[i].longueur < plusCourt->longueur)
            plusCourt = &dico->mots[i];
        if(dico->mots[i].occurrences > plusFrequent->occurrences)
            plusFrequent = &dico->mots[i];
    }

    printf("\n--- Statistiques ---\n");
    printf("Nombre total de mots: %d\n", totalMots);
    printf("Nombre de mots uniques: %d\n", dico->nbMots);
    printf("Longueur moyenne: %.2f\n", (float)sommeLongueurs / totalMots);
    printf("Mot le plus long: %s\n", plusLong->mot);
    printf("Mot le plus court: %s\n", plusCourt->mot);
    printf("Mot le plus fréquent: %s (%d fois)\n", plusFrequent->mot, plusFrequent->occurrences);
}

// ----------- Palindromes -----------
int estPalindrome(char *mot) {
    int i = 0, j = strlen(mot) - 1;
    while(i < j) {
        if(mot[i] != mot[j]) return 0;
        i++; j--;
    }
    return 1;
}

void afficherPalindromes(Dictionnaire *dico) {
    printf("\n--- Palindromes ---\n");
    int trouve = 0;
    for(int i = 0; i < dico->nbMots; i++) {
        if(estPalindrome(dico->mots[i].mot) && strlen(dico->mots[i].mot) > 1) {
            printf("%s\n", dico->mots[i].mot);
            trouve = 1;
        }
    }
    if(!trouve) printf("Aucun palindrome trouvé.\n");
}

// ----------- Anagrammes -----------
void trierLettres(char *mot, char *result) {
    strcpy(result, mot);
    int n = strlen(result);
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(result[i] > result[j]) {
                char tmp = result[i];
                result[i] = result[j];
                result[j] = tmp;
            }
        }
    }
}

void afficherAnagrammes(Dictionnaire *dico) {
    printf("\n--- Anagrammes ---\n");
    int trouve = 0;
    for(int i = 0; i < dico->nbMots; i++) {
        for(int j = i+1; j < dico->nbMots; j++) {
            char tri1[50], tri2[50];
            trierLettres(dico->mots[i].mot, tri1);
            trierLettres(dico->mots[j].mot, tri2);
            if(strcmp(tri1, tri2) == 0) {
                printf("%s <--> %s\n", dico->mots[i].mot, dico->mots[j].mot);
                trouve = 1;
            }
        }
    }
    if(!trouve) printf("Aucun anagramme trouvé.\n");
}

// ----------- Nuage de mots -----------
void afficherNuage(Dictionnaire *dico) {
    printf("\n--- Nuage de mots ---\n");
    for(int i = 0; i < dico->nbMots; i++) {
        printf("%s : ", dico->mots[i].mot);
        for(int j = 0; j < dico->mots[i].occurrences; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// ----------- Tri -----------
void trierAlphabet(Dictionnaire *dico) {
    for(int i = 0; i < dico->nbMots - 1; i++) {
        for(int j = i + 1; j < dico->nbMots; j++) {
            if(strcmp(dico->mots[i].mot, dico->mots[j].mot) > 0) {
                WordInfo tmp = dico->mots[i];
                dico->mots[i] = dico->mots[j];
                dico->mots[j] = tmp;
            }
        }
    }
    afficherDictionnaire(dico);
}

void trierFrequence(Dictionnaire *dico) {
    for(int i = 0; i < dico->nbMots - 1; i++) {
        for(int j = i + 1; j < dico->nbMots; j++) {
            if(dico->mots[i].occurrences < dico->mots[j].occurrences) {
                WordInfo tmp = dico->mots[i];
                dico->mots[i] = dico->mots[j];
                dico->mots[j] = tmp;
            }
        }
    }
    afficherDictionnaire(dico);
}

void trierLongueur(Dictionnaire *dico) {
    for(int i = 0; i < dico->nbMots - 1; i++) {
        for(int j = i + 1; j < dico->nbMots; j++) {
            if(dico->mots[i].longueur > dico->mots[j].longueur) {
                WordInfo tmp = dico->mots[i];
                dico->mots[i] = dico->mots[j];
                dico->mots[j] = tmp;
            }
        }
    }
    afficherDictionnaire(dico);
}

// ----------- Menu principal -----------
int main() {
    Dictionnaire dico;
    char texte[MAX_TEXTE];
    int choix, sousChoix;
    char mot[50];

    do {
        printf("\n--- Menu ---\n");
        printf("1. Saisir un texte et analyser\n");
        printf("2. Afficher tous les mots\n");
        printf("3. Rechercher un mot exact\n");
        printf("4. Rechercher un mot partiel\n");
        printf("5. Statistiques globales\n");
        printf("6. Palindromes\n");
        printf("7. Anagrammes\n");
        printf("8. Nuage de mots\n");
        printf("9. Trier les mots\n");
        printf("10. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1:
                printf("Entrez votre texte:\n");
                fgets(texte, MAX_TEXTE, stdin);
                analyserTexte(texte, &dico);
                break;
            case 2:
                afficherDictionnaire(&dico);
                break;
            case 3:
                printf("Mot à rechercher: ");
                scanf("%s", mot);
                rechercherMotExact(&dico, mot);
                break;
            case 4:
                printf("Sous-chaîne à rechercher: ");
                scanf("%s", mot);
                rechercherMotPartiel(&dico, mot);
                break;
            case 5:
                statistiques(&dico);
                break;
            case 6:
                afficherPalindromes(&dico);
                break;
            case 7:
                afficherAnagrammes(&dico);
                break;
            case 8:
                afficherNuage(&dico);
                break;
            case 9:
                printf("\n--- Choisir type de tri ---\n");
                printf("1. Alphabétique\n");
                printf("2. Fréquence décroissante\n");
                printf("3. Longueur croissante\n");
                scanf("%d", &sousChoix);
                switch(sousChoix) {
                    case 1: trierAlphabet(&dico); break;
                    case 2: trierFrequence(&dico); break;
                    case 3: trierLongueur(&dico); break;
                    default: printf("Choix invalide.\n");
                }
                break;
            case 10:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while(choix != 10);

    return 0;
}
