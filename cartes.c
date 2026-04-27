#include <stdio.h>
#include <stdlib.h> // OBLIGATOIRE pour malloc et free
#include "cartes.h"

// 1. FABRIQUER LE PAQUET (AVEC MALLOC)
Carte* initialiser_paquet(int *taille) {
    *taille = 0; 
    
    // Le vrai jeu Flip 7 a exactement 87 cartes.
    // On demande à l'ordinateur de réserver de la mémoire pour 87 "moules" de Cartes.
    Carte *paquet = malloc(87 * sizeof(Carte));
    
    // Sécurité obligatoire quand on utilise malloc : vérifier si ça a marché
    if (paquet == NULL) {
        printf("Erreur fatale : Plus de memoire disponible !\n");
        exit(1); // Arrête le programme
    }

    int valeur, i;
    for (valeur = 1; valeur <= 12; valeur++) {
        for (i = 0; i < valeur; i++) {
            paquet[*taille].valeur = valeur;
            paquet[*taille].type = 0;
            (*taille)++; 
        }
    }

    for (i = 0; i < 3; i++) {
        paquet[*taille].valeur = 0; paquet[*taille].type = 1; (*taille)++; // STOP
        paquet[*taille].valeur = 0; paquet[*taille].type = 2; (*taille)++; // 2NDE CHANCE
        paquet[*taille].valeur = 0; paquet[*taille].type = 3; (*taille)++; // 3 A LA SUITE
    }
    
    // On renvoie l'adresse du paquet fraîchement créé
    return paquet;
}

// 2. MÉLANGER LE PAQUET (Aucun changement)
void melanger_paquet(Carte *paquet, int taille) {
    int i;
    for (i = 0; i < taille; i++) {
        int hasard = rand() % taille;
        Carte carte_temporaire = paquet[i];
        paquet[i] = paquet[hasard];
        paquet[hasard] = carte_temporaire;
    }
}

// 3. PIOCHER (Aucun changement)
Carte piocher_carte(Carte *paquet, int *taille) {
    (*taille)--;
    return paquet[*taille];
}

// 4. L'AFFICHAGE (Couleurs retirées)
void afficher_carte(Carte c) {
    if (c.type == 1) { 
        printf("  .------.\n  | STOP |\n  '------'\n"); 
    } 
    else if (c.type == 2) { 
        printf("  .------.\n  | 2NDE |\n  |CHANCE|\n  '------'\n"); 
    }
    else if (c.type == 3) { 
        printf("  .------.\n  |3 A LA|\n  |SUITE!|\n  '------'\n"); 
    }
    else { 
        printf("  .------.\n  |  %2d  |\n  '------'\n", c.valeur); 
    }
}