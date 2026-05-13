#include <stdio.h>
#include <stdlib.h>
#include "cartes.h"

// Generation dynamique des 85 cartes du jeu de base (avec malloc)
Carte* initialiser_paquet(int *taille) {
    *taille = 0; 
    Carte *paquet = malloc(85 * sizeof(Carte));
    
    if (paquet == NULL) {
        printf("Erreur d'allocation memoire pour le paquet.\n");
        exit(1);
    }

    int i, j;
    
    // 1. Les 79 cartes numeros
    for (i = 0; i <= 1; i++) {
        paquet[*taille].valeur = i; 
        paquet[*taille].type = 0; 
        (*taille)++;
    }
    for (i = 2; i <= 12; i++) {
        for (j = 0; j < i; j++) {
            paquet[*taille].valeur = i; 
            paquet[*taille].type = 0; 
            (*taille)++;
        }
    }

    // 2. Les 6 cartes bonus
    paquet[*taille].valeur = 2; 
    paquet[*taille].type = 2; 
    (*taille)++; // x2
    
    int bonus_plus_vals[5] = {2, 4, 6, 8, 10};
    for (i = 0; i < 5; i++) {
        paquet[*taille].valeur = bonus_plus_vals[i]; 
        paquet[*taille].type = 1; 
        (*taille)++;
    }
    
    return paquet;
}

// Melange du paquet
void melanger_paquet(Carte *paquet, int taille) {
    int i;
    for (i = taille - 1; i > 0; i--) {
        int hasard = rand() % (i + 1);
        Carte temp = paquet[i];
        paquet[i] = paquet[hasard];
        paquet[hasard] = temp;
    }
}

// Piocher (on reduit simplement la taille avec le pointeur)
Carte piocher_carte(Carte *paquet, int *taille) {
    (*taille)--;
    return paquet[*taille];
}

// Affichage 
void afficher_carte(Carte c) {
    if (c.type == 0) {
        printf("  .------.\n  |  %2d  |\n  '------'\n", c.valeur); 
    } else if (c.type == 1) {
        printf("  .------.\n  |  +%2d |\n  '------'\n", c.valeur); 
    } else if (c.type == 2) {
        printf("  .------.\n  |  x2  |\n  '------'\n"); 
    }
}

// Statistiques demandees
void afficher_statistiques(int *stats) {
    printf("\n--- STATISTIQUES DES CARTES TIREES ---\n");
    int i;
    for (i = 0; i <= 12; i++) {
        int max_cartes = (i <= 1) ? 1 : i; 
        printf("Carte %2d : %d / %d tirees\n", i, stats[i], max_cartes);
    }
    printf("--------------------------------------\n");
}