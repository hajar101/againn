#include <stdio.h>
#include <string.h>

#define TAILLE_MAX_ETUDIANTS 100
#define MAX_COURS 50

struct Etudiant {
    int id;
    char nom[50];
    char prenom[50];
    int age;
    float moyenne;
};

struct Cours {
    int code;
    char nom[50];
    int credits;
    float note;
};

struct Cours cours[MAX_COURS];
int nbCours = 0;

struct Etudiant etudiants[TAILLE_MAX_ETUDIANTS];
int nbEtudiants = 0;

void rechercherEtudiant() {
    int idRecherche;
    printf("\n--- Recherche d'un etudiant ---\n");
    printf("Entrez l'ID de l'etudiant a rechercher : ");
    scanf("%d", &idRecherche);

    int trouve = 0;
    for (int i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].id == idRecherche) {
            printf("Etudiant trouve !\n");
            printf("ID: %d | Nom: %s | Prenom: %s | Age: %d | Moyenne: %.2f\n",
                   etudiants[i].id, etudiants[i].nom, etudiants[i].prenom, etudiants[i].age, etudiants[i].moyenne);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun etudiant avec cet ID n'a ete trouve.\n");
    }
}

void afficherListeEtudiants() {
    printf("\n--- Liste des etudiants enregistres ---\n");
    if (nbEtudiants == 0) {
        printf("Aucun etudiant n'est enregistre pour le moment.\n");
        return;
    }
    for (int i = 0; i < nbEtudiants; i++) {
        printf("ID: %d | Nom: %s | Prenom: %s | Age: %d | Moyenne: %.2f\n",
               etudiants[i].id, etudiants[i].nom, etudiants[i].prenom, etudiants[i].age, etudiants[i].moyenne);
    }
}

void afficherListeCours() {
    printf("\n--- Liste des cours proposes ---\n");
    if (nbCours == 0) {
        printf("Aucun cours n'est enregistre pour le moment.\n");
        return;
    }
    for (int i = 0; i < nbCours; i++) {
        printf("Code: %d | Nom: %s | Credits: %d | Note: %.2f\n",
               cours[i].code, cours[i].nom, cours[i].credits, cours[i].note);
    }
}

void ajouterEtudiant() {
    if (nbEtudiants >= TAILLE_MAX_ETUDIANTS) {
        printf("Desole, la capacite maximale d'etudiants est atteinte.\n");
        return;
    }

    int idTemp;
    int dejaID = 0;

    printf("\n--- Ajout d'un etudiant ---\n");
    printf("Entrez l'ID de l'etudiant : ");
    scanf("%d", &idTemp);
    for (int i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].id == idTemp) {
            dejaID = 1;
            break;
        }
    }

    if (dejaID) {
        printf("Erreur : Un etudiant avec cet ID existe deja.\n");
        return;
    }

    etudiants[nbEtudiants].id = idTemp;
    getchar();
    printf("Entrez le nom : ");
    scanf("%49s", etudiants[nbEtudiants].nom);
    getchar();
    printf("Entrez le prenom : ");
    scanf("%49s", etudiants[nbEtudiants].prenom);
    getchar();
    printf("Entrez l'age : ");
    scanf("%d", &etudiants[nbEtudiants].age);
    getchar();
    printf("Entrez la moyenne : ");
    scanf("%f", &etudiants[nbEtudiants].moyenne);
    getchar();

    nbEtudiants++;
    printf("-> Etudiant ajoute avec succes !\n");
}
void modifierNoteCours() {
    if (nbCours == 0) {
        printf("Aucun cours n'est disponible pour modification.\n");
        return;
    }

    int codeRecherche;
    int trouve = 0;

    printf("\n--- Modification de la note d'un cours ---\n");
    printf("Entrez le code du cours a modifier : ");
    scanf("%d", &codeRecherche);

    for (int i = 0; i < nbCours; i++) {
        if (cours[i].code == codeRecherche) {
            trouve = 1;

            printf("Cours trouve : %s | Ancienne note : %.2f\n", cours[i].nom, cours[i].note);

            float nouvelleNote;
            printf("Entrez la nouvelle note : ");
            scanf("%f", &nouvelleNote);

            if (nouvelleNote < 0 || nouvelleNote > 20) {
                printf("Erreur : La note doit etre entre 0 et 20.\n");
                return;
            }

            cours[i].note = nouvelleNote;
            printf("-> Note mise a jour avec succes !\n");
            return;
        }
    }

    if (!trouve) {
        printf("Erreur : Aucun cours avec ce code n'a ete trouve.\n");
    }
}

void ajouterCours() {
    if (nbCours >= MAX_COURS) {
        printf("Erreur : Le nombre maximal de cours est atteint.\n");
        return;
    }

    printf("\n--- Ajout d'un cours ---\n");
    printf("Entrez le code du cours : ");
    scanf("%d", &cours[nbCours].code);
    printf("Entrez le nom du cours : ");
    scanf("%s", cours[nbCours].nom);
    printf("Entrez le nombre de credits : ");
    scanf("%d", &cours[nbCours].credits);
    printf("Entrez la note : ");
    scanf("%f", &cours[nbCours].note);

    nbCours++;
    printf("-> Cours ajoute avec succes !\n");
}

int main() {
    int choix;
    do {
        printf("\n      MENU DE GESTION UNIVERSITAIRE\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Ajouter un cours\n");
        printf("3. Afficher la liste des etudiants\n");
        printf("4. Afficher la liste des cours\n");
        printf("5. Rechercher un etudiant\n");
        printf("6. Modifier la note d'un cours\n");
        printf("0. Quitter\n");
        printf("--------------------------------------------\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                ajouterCours();
                break;
            case 3:
                afficherListeEtudiants();
                break;
            case 4:
                afficherListeCours();
                break;
            case 5:
                rechercherEtudiant();
                break;
            case 6:
                 modifierNoteCours();
                printf("Fonctionnalite de modification a venir.\n");
                break;
            case 0:
                printf("\nMerci d'avoir utilise le programme. Au revoir !\n");
                break;
            default:
                printf("-> Choix invalide. Veuillez reessayer.\n");
                break;
        }
    } while (choix != 0);

    return 0;
}
