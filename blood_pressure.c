#include <stdio.h>

void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int main(void)
{
    int n;

    printf("Kolik mereni chces zadat? ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Neplatny pocet (1..100).\n");
        return 1;
    }

    int sys[100];
    int dias[100];

    for (int i = 0; i < n; i++) {
        printf("Zadej SYS a DIAS pro den %d (napr. 128 82): ", i+1);
        if (scanf("%d %d", &sys[i], &dias[i]) != 2) {
            printf("Neplatny vstup. Zkus to znovu.\n");
            clear_stdin();
            i--; 
            continue;
        }

        if (sys[i] < 50)  sys[i] = 50;
        if (dias[i] < 30) dias[i] = 30;
    }

    printf("\n=== Vysledky ===\n");
    for (int i = 0; i < n; i++) {
        printf("Den %02d: %3d/%3d mmHg -> ", i+1, sys[i], dias[i]);


        if (sys[i] >= 140 || dias[i] >= 90) {
            printf("Hypertension\n");
        } else if ((sys[i] >= 130 && sys[i] <= 139) ||
                   (dias[i] >= 85  && dias[i] <= 89)) {
            printf("High-normal\n");
        } else {
            printf("Normal\n");
        }
    }

    return 0;
}
