#include <stdio.h>
int main() {
float n1,n2,n3,n4,n5;
float total,moy,max,min;
char *mention;

printf("entrer la note 1:");scanf("%f",&n1);
printf("entrer la note 2:");scanf("%f",&n2);
printf("entrer la note 3:");scanf("%f",&n3);
printf("entrer la note 4:");scanf("%f",&n4);
printf("entrer la note 5:");scanf("%f",&n5);

total=n1+n2+n3+n4+n5;
moy=total/5;

 max = n1;
    if(n2 > max) max = n2;
    if(n3 > max) max = n3;
    if(n4 > max) max = n4;
    if(n5 > max) max = n5;
min = n1;
    if(n2 < min) min = n2;
    if(n3 < min) min = n3;
    if(n4 < min) min = n4;
    if(n5 < min) min = n5;

if(moy >= 90)
    mention="Excellent";
 else if (moy >= 80)
     mention="Très bien";
else if(moy >= 70)
     mention="Bien";
else if(moy>= 60)
 mention="Passable";
else
     mention="echec";

printf("\n .....Rapport Final .....\n");
    printf("Total des notes   : %.2f\n", total);
    printf("Moyenne           : %.2f\n", moy);
    printf("Note la plus haute: %.2f\n", max);
    printf("Note la plus basse: %.2f\n", min);
    printf("Mention           : %c\n", mention);
printf("Total:%.2f", total);
printf("Moyenne:%.2f", moy);

if(moy >= 50)
    printf("Réussi");
    else
    printf("Échoué");



return 0;
}



