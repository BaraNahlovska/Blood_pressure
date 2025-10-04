#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

// PP
int pulse_pressure(int sys, int dias) {
    int pp = sys - dias;
    return pp < 0 ? 0 : pp;
}

// MAP
double mean_arterial_pressure(int sys, int dias) {
    return (sys + 2.0 * dias) / 3.0;
}

int main(void)
{
    int n;

    printf("How many measurements do you want to enter? ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid number (1..100).\n");
        return 1;
    }

    int sys[100];
    int dias[100];
    int hr[100] = {0};

    for (int i = 0; i < n; i++) {
        printf("Enter SYS/DIA (and optional HR) for day %d (e.g. 128/82 or 128/82 72): ", i+1);
        int s, d, h;
        int matched = scanf("%d/%d %d", &s, &d, &h);

        if (matched == 2) {
            sys[i] = s; dias[i] = d; hr[i] = 0;
        }
        else if (matched == 3) {
            sys[i] = s; dias[i] = d; hr[i] = h;
        }
        else {
            printf("Invalid input. Try again.\n");
            clear_stdin();
            i--;
            continue;
        }

        if (sys[i] < 50)  sys[i] = 50;
        if (dias[i] < 30) dias[i] = 30;
        if (hr[i] < 0) hr[i] = 0;
    }

    int count[5] = {0,0,0,0,0};

    printf("\n=== Results ===\n");
    for (int i = 0; i < n; i++) {

        int pp = pulse_pressure(sys[i], dias[i]);
        double map = mean_arterial_pressure(sys[i], dias[i]);

        printf("Day %02d: %3d/%d mmHg", i+1, sys[i], dias[i]);
        if (hr[i] > 0) printf(" (HR %d/min)", hr[i]);
        printf(" -> ");

        const char *category = NULL;


        if (sys[i] >= 180 || dias[i] >= 110) {
            category = "Stage III Hypertension";
            count[4]++;

        }
        else if ((sys[i] >= 160 && sys[i] <= 179) ||
                (dias[i] >= 100  && dias[i] <= 109)) {
            category = "Stage II Hypertension";
            count[3]++;

        }
        else if ((sys[i] >= 140 && sys[i] <= 159) ||
                (dias[i] >= 90 && dias[i] <= 99)) {
            category = "Stage I Hypertension";
            count[2]++;

        }
        else if ((sys[i] >= 130 && sys[i] <= 139) ||
                (dias[i] >= 85 && dias[i] <= 89)) {
            category = "High Normal Pressure";
            count[1]++;

        }
        else {
            category = "Normal Pressure";
            count[0]++;
        }
        printf("%s | PP=%d | MAP=%.1f\n", category, pp, map);
    }

    printf("\n === Summary of measurements === \n");
    printf("Normal Pressure: %d\n",        count[0]);
    printf("High Normal Pressure: %d\n",   count[1]);
    printf("Stage I Hypertension: %d\n",   count[2]);
    printf("Stage II Hypertension: %d\n",  count[3]);
    printf("Stage III Hypertension: %d\n", count[4]);

    // Saving results into a CSV file:
     FILE *f = fopen("readings.csv", "w");
     if (!f) {
        printf("\nCould not open readings.csv for writing. \n");
     }
     else {
        fprintf(f, "day,sys,dias,hr,pp,map,category\n");
        for(int i = 0; i < n; i++) {
            int pp = pulse_pressure(sys[i], dias[i]);
            double map = mean_arterial_pressure(sys[i], dias[i]);
            const char *cat;

            if (sys[i] >= 180 || dias[i] >= 110)  cat = "Stage III Hypertension";
            else if ((sys[i] >= 160 && sys[i] <= 179) ||
                    (dias[i] >= 100  && dias[i] <= 109)) cat = "Stage II Hypertension";

            else if ((sys[i] >= 140 && sys[i] <= 159) ||
                    (dias[i] >= 90 && dias[i] <= 99)) cat = "Stage I Hypertension";

            else if ((sys[i] >= 130 && sys[i] <= 139) ||
                    (dias[i] >= 85 && dias[i] <= 89))  cat = "High Normal Pressure";
           else                                        cat = "Normal Pressure";

           fprintf(f, "%d,%d,%d,%d,%d,%.1f,%s\n",
                    i+1, sys[i], dias[i], hr[i], pp, map, cat);
        }
        fclose(f);
        printf("\nCSV file saved as 'readings.csv'. \n");

     }

    return 0;
}
