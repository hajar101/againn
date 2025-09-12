#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INPUT 200
#define MAX_HISTORY 100


char *positif[] = {"happy", "content", "bon", "great", "thanks", "bien", "lol"};
char *negatif[] = {"sad", "triste", "mauvais", "terrible"};
char *neutral[] = {"ok", "fine", "quoi de neuf", "iwa", "walo"};
char *salutavv<wtion[] = {"bonjour", "hello", "salam", "salut", "slt", "hi"};


char *rep_positif[] = {"Glad to hear that!", "Bon courage!", "Nhark mbrok!"};
char *rep_negatif[] = {"Sorry to hear that! ╯︿╰", "Keep going!", "Tell me more ＞﹏＜"};
char *rep_neutral[] = {"Keep in touch.", "You finished the project?"};
char *rep_salutation[] = {"Bonjour!", "Labas 3lik?", "Chkat3awd?", "Wassup!"};


char history[MAX_HISTORY][MAX_INPUT];
int history_count = 0;

int checkkw(char *input, char *keywords[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strstr(input, keywords[i]) != NULL)
        {
            return i;
        }
    }
    return -1;
}


char *random_response(char *responses[], int size)
{
    return responses[rand() % size];
}

int main()
{
    char input[MAX_INPUT];
    srand(time(NULL));

    printf("🤖 Bienvenue dans YouChat ! Tape 'exit' pour quitter.\n");

    while (1)
    {
        printf("\n🗣️ User: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            printf("👋 See you later!\n");
            break;
        }

        if (strcmp(input, "history") == 0)
        {
            printf("\n📜 Historique:\n");
            for (int i = 0; i < history_count; i++)
            {
                printf("%s\n", history[i]);
            }
            continue;
        }

        snprintf(history[history_count++], MAX_INPUT, "User: %s", input);

        int sal = checkkw(input, salutation, sizeof(salutation) / sizeof(salutation[0]));
        int pos = checkkw(input, positif, sizeof(positif) / sizeof(positif[0]));
        int neg = checkkw(input, negatif, sizeof(negatif) / sizeof(negatif[0]));
        int neut = checkkw(input, neutral, sizeof(neutral) / sizeof(neutral[0]));

        printf("🤖 Bot: ");
        if (sal != -1)
        {
            char *response = random_response(rep_salutation, sizeof(rep_salutation) / sizeof(rep_salutation[0]));
            printf("%s\n", response);
            snprintf(history[history_count++], MAX_INPUT, "Bot: %s", response);
        }
        else if (pos != -1)
        {
            char *response = random_response(rep_positif, sizeof(rep_positif) / sizeof(rep_positif[0]));
            printf("%s\n", response);
            snprintf(history[history_count++], MAX_INPUT, "Bot: %s", response);
        }
        else if (neg != -1)
        {
            char *response = random_response(rep_negatif, sizeof(rep_negatif) / sizeof(rep_negatif[0]));
            printf("%s\n", response);
            snprintf(history[history_count++], MAX_INPUT, "Bot: %s", response);
        }
        else if (neut != -1)
        {
            char *response = random_response(rep_neutral, sizeof(rep_neutral) / sizeof(rep_neutral[0]));
            printf("%s\n", response);
            snprintf(history[history_count++], MAX_INPUT, "Bot: %s", response);
        }
        else
        {
            printf("I didn't catch that... try again!\n");
            snprintf(history[history_count++], MAX_INPUT, "Bot: I didn't catch that... try again!");
        }
    }

    return 0;
}
