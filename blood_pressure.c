#include <stdio.h>

void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int main(void)
{
    int n;

    printf("Kolik meření chceš zadat? ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Neplatný počet (1..100).\n");
        return 1;
    }

    int sys[100];
    int dias[100];

    for (int i = 0; i < n; i++) {
        printf("Zadej SYS a DIAS pro den %d (ve formátu: 128/82): ", i+1);
        if (scanf("%d/%d", &sys[i], &dias[i]) != 2) {
            printf("Neplatný vstup. Zkus to znovu.\n");
            clear_stdin();
            i--;
            continue;
        }

        if (sys[i] < 50)  sys[i] = 50;
        if (dias[i] < 30) dias[i] = 30;
    }

    int count[5] = {0,0,0,0,0};

    printf("\n=== Výsledky ===\n");
    for (int i = 0; i < n; i++) {
        printf("Den %02d: %3d/%d mmHg -> ", i+1, sys[i], dias[i]);


        if (sys[i] >= 180 || dias[i] >= 110) {
            printf("III. stupeň hypertenze\n");
            count[4]++;

        } else if ((sys[i] >= 160 && sys[i] <= 179) ||
                   (dias[i] >= 100  && dias[i] <= 109)) {
            printf("II.stupeň hypertenze\n");
            count[3]++;

        } else if ((sys[i] >= 140 && sys[i] <= 159) ||
                   (dias[i] >= 90 && sys[i] <= 99)) {
            printf("I.stupeň hypertenze\n");
            count[2]++;

        } else if ((sys[i] >= 130 && sys[i] <= 139) ||
                    (dias[i] >= 85 && sys[i] <= 89)) {
            printf("Vysoký normální tlak\n");
            count[1]++;

        } else {
            printf("Normalní tlak\n");
            count[0]++;
        }
    }

    printf("\n === Souhrn měření === \n");
    printf("Normální tlak: %d\n",          count[0]);
    printf("Vysoký normální tlak: %d\n",   count[1]);
    printf("I. stupeň hypertenze: %d\n",   count[2]);
    printf("II. stupeň hypertenze: %d\n",  count[3]);
    printf("III. stupeň hypertenze: %d\n", count[4]);

    return 0;
}
