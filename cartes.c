#include <stdio.h>
#include <stdlib.h>
#include "cartes.h"

// 1. FABRIQUER LE PAQUET
void initialiser_paquet(Carte *paquet, int *taille) {
    *taille = 0; // On commence avec un paquet vide

    // On fabrique les cartes normales (1 fois le 1, 2 fois le 2, etc.)
    int valeur, i;
    for (valeur = 1; valeur <= 12; valeur++) {
        for (i = 0; i < valeur; i++) {
            paquet[*taille].valeur = valeur;
            paquet[*taille].type = 0;
            (*taille)++; // Le paquet grossit d'une carte
        }
    }

    // On fabrique les cartes spéciales (3 de chaque par exemple)
    for (i = 0; i < 3; i++) {
        paquet[*taille].valeur = 0; paquet[*taille].type = 1; (*taille)++; // STOP
        paquet[*taille].valeur = 0; paquet[*taille].type = 2; (*taille)++; // 2NDE CHANCE
        paquet[*taille].valeur = 0; paquet[*taille].type = 3; (*taille)++; // 3 A LA SUITE
    }
}

// 2. MÉLANGER LE PAQUET
void melanger_paquet(Carte *paquet, int taille) {
    int i;
    for (i = 0; i < taille; i++) {
        // On choisit une carte au hasard dans le paquet
        int hasard = rand() % taille;
        
        // On l'échange avec la carte actuelle (i)
        Carte carte_temporaire = paquet[i];
        paquet[i] = paquet[hasard];
        paquet[hasard] = carte_temporaire;
    }
}

// 3. PIOCHER LA CARTE DU DESSUS
Carte piocher_carte(Carte *paquet, int *taille) {
    // On diminue la taille du paquet de 1
    (*taille)--;
    // On donne la carte qui était tout en haut
    return paquet[*taille];
}

// 4. L'AFFICHAGE (Ne change pas)
void afficher_carte(Carte c) {
    if (c.type == 1) { 
        printf("\033[1;31m  .------.\n  | STOP |\n  '------'\n\033[0m"); 
    } 
    else if (c.type == 2) { 
        printf("\033[1;32m  .------.\n  | 2NDE |\n  |CHANCE|\n  '------'\n\033[0m"); 
    }
    else if (c.type == 3) { 
        printf("\033[1;33m  .------.\n  |3 A LA|\n  |SUITE!|\n  '------'\n\033[0m"); 
    }
    else { 
        printf("\033[1;36m  .------.\n  |  %2d  |\n  '------'\n\033[0m", c.valeur); 
    }
}