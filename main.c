#include <stdio.h>
#include <string.h>

#define MIN 1000
#define MAX 200000      // diametru maxim permis
#define MAX_PLANETS 100 // numar maxim de planete stocate

typedef struct {
    char nume[100];
    float diametru;
    char tip; // 't' sau 'g'
} Planets;

void meniu() {
    printf("Meniu\n");
    printf("-------\n");
    printf("0. Iesire\n");
    printf("1. Adauga planeta\n");
    printf("2. Afiseaza toate planetele sortate crescator dupa diametrul lor\n");
    printf("3. Afiseaza planetele telurice cu diametrul mai mic decat o valoare introdusa de la tastatura\n");
    printf("4. Crearea unui vector cu numarul de vocale din numele fiecarei planete si afisarea vectorului\n");
    printf("-------\n");
}

void adauga_planeta(Planets *p) {
    printf("Nume: ");
    scanf("%99s", p->nume);

    do {
        printf("Diametru (intre %d si %d): ", MIN, MAX);
        scanf("%f", &p->diametru);
    } while (p->diametru < MIN || p->diametru > MAX);

    do {
        printf("Tip (t = telurica, g = gazoasa): ");
        scanf(" %c", &p->tip);
    } while (p->tip != 't' && p->tip != 'g');
}

void sortare_planeta(Planets v[], int n) {
    Planets temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i].diametru > v[j].diametru) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

void afiseaza_planete_sortata_diametrul(Planets v[], int n) {
    if (n == 0) {
        printf("Nu exista planete in catalog.\n\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Nume: %s | Diametru: %.2f | Tip: %c\n",
               v[i].nume, v[i].diametru, v[i].tip);
    }
    printf("\n");
}

void afiseaza_planete_telurice_sub_diametru(Planets v[], int n, float x) {
    if (n == 0) {
        printf("Nu exista planete in catalog.\n\n");
        return;
    }

    int gasit = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].tip == 't' && v[i].diametru < x) {
            printf("Nume: %s | Diametru: %.2f | Tip: %c\n",
                   v[i].nume, v[i].diametru, v[i].tip);
            gasit = 1;
        }
    }

    if (!gasit) {
        printf("Nu exista planete telurice cu diametrul mai mic decat %.2f.\n", x);
    }
    printf("\n");
}

int este_vocala(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void cautare_vocale(Planets v[], int n) {
    if (n == 0) {
        printf("Nu exista planete in catalog.\n\n");
        return;
    }

    int vocale[MAX_PLANETS];
    for (int i = 0; i < n; i++) {
        int counter = 0;
        for (int j = 0; v[i].nume[j] != '\0'; j++) {
            if (este_vocala(v[i].nume[j])) counter++;
        }
        vocale[i] = counter;
    }

    printf("Vector numar vocale (pe fiecare planeta):\n");
    for (int i = 0; i < n; i++) {
        printf("Planeta %d are %d vocale.\n", i, vocale[i]);
    }
    printf("\n\n");
}

int main(void) {
    int opt;
    int count = 0;
    Planets planet[MAX_PLANETS];

    do {
        meniu();
        printf("Optiune: ");
        scanf("%d", &opt);

        switch (opt) {
            case 0:
                printf("Iesire.\n");
                break;

            case 1:
                if (count >= MAX_PLANETS) {
                    printf("Catalog plin! (maxim %d planete)\n\n", MAX_PLANETS);
                } else {
                    printf("Adauga planeta.\n");
                    adauga_planeta(&planet[count]);
                    count++;
                    printf("\n");
                }
                break;

            case 2:
                sortare_planeta(planet, count);
                afiseaza_planete_sortata_diametrul(planet, count);
                break;

            case 3: {
                float diametrul;
                printf("Introdu diametrul: ");
                scanf("%f", &diametrul);
                afiseaza_planete_telurice_sub_diametru(planet, count, diametrul);
                break;
            }

            case 4:
                cautare_vocale(planet, count);
                break;

            default:
                printf("Optiune invalida.\n\n");
        }

    } while (opt != 0);

    return 0;
}
