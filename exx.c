#include <stdio.h>
int main() {
float n1,n2,n3,n4,n5;
float total,moy,max,min;
char mension[50];

printf("entrer la note 1:");scanf("%f",&n1);
printf("entrer la note 2:");scanf("%f",&n2);
printf("entrer la note 3:");scanf("%f",&n3);
printf("entrer la note 4:");scanf("%f",&n4);
printf("entrer la note 5:");scanf("%f",&n5);

total=n1+n2+n3+n4+n5;
moy=total/5;

printf("Total:%.2f", total);
printf("Moyenne:%.2f", moy);


if(moy<= 90)
 printf("Mention Excellent");
    else if (moy >= 80)
        printf("Mention Très bien");
    else if(moy >= 70)
    printf("Mention Bien");
    else if(moy>= 60)
     printf("Mention Passable");
    else
     printf("Mention echec");

  if(moy >= 50)
    printf("Réussi");
    else
    printf("Échoué");



return 0;
}



