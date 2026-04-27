#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartes.h"
#include <string.h> // Nécessaire pour donner un nom automatiquement à l'ordinateur

int main() {
    srand(time(NULL));
    printf("\033[1;33m=== BIENVENUE DANS FLIPTECH ===\033[0m\n\n");

    Carte le_paquet[150]; 
    int taille_du_paquet = 0;
    initialiser_paquet(le_paquet, &taille_du_paquet); 
    melanger_paquet(le_paquet, taille_du_paquet);
    printf("(Le croupier a melange un paquet de %d cartes)\n\n", taille_du_paquet);

    // --- NOUVEAU : LE MENU PRINCIPAL ---
    int mode_jeu = 0;
    while (mode_jeu != 1 && mode_jeu != 2) {
        printf("Choisissez votre mode de jeu :\n");
        printf("1. Joueur vs Ordinateur (IA)\n");
        printf("2. Multijoueur local (2 a 4 joueurs)\n");
        printf("Votre choix : ");
        scanf("%d", &mode_jeu);
    }

    Joueur liste_joueurs[4]; 
    int nb_joueurs = 0;
    int p;

    if (mode_jeu == 1) {
        nb_joueurs = 2; // Toi contre l'IA
        printf("\nTon prenom : ");
        scanf("%s", liste_joueurs[0].nom);
        liste_joueurs[0].score = 0;
        
        // On configure le joueur 2 comme étant l'ordinateur
        strcpy(liste_joueurs[1].nom, "L'Ordinateur (IA)");
        liste_joueurs[1].score = 0;
    } 
    else {
        while (nb_joueurs < 2 || nb_joueurs > 4) {
            printf("\nCombien de joueurs etes-vous ? (2 a 4) : ");
            scanf("%d", &nb_joueurs);
        }
        for (p = 0; p < nb_joueurs; p++) {
            printf("Prenom du joueur %d : ", p + 1);
            scanf("%s", liste_joueurs[p].nom); 
            liste_joueurs[p].score = 0;        
        }
    }

    printf("\n\033[1;36m>>> QUE LA PARTIE COMMENCE ! <<<\033[0m\n");

    for (p = 0; p < nb_joueurs; p++) {
        
        printf("\n------------------------------------------------\n");
        printf("\033[1;33mC'est a %s de jouer !\033[0m\n", liste_joueurs[p].nom);
        printf("------------------------------------------------\n");

        int choix = 1;
        int score_tour = 0;
        int cartes_en_main[15]; 
        int nb_cartes = 0;      
        int vies_en_plus = 0; 
        int tours_forces = 0; 

        // Variable pour savoir si le joueur actuel est l'IA
        int est_IA = 0;
        if (mode_jeu == 1 && p == 1) {
            est_IA = 1; 
        }

        while (choix == 1 && taille_du_paquet > 0) {
            
            Carte ma_carte = piocher_carte(le_paquet, &taille_du_paquet);
            
            printf("\n%s pioche :\n", liste_joueurs[p].nom);
            afficher_carte(ma_carte);

            if (ma_carte.type == 1) { 
                printf("\n\033[1;35m>>> CARTE STOP ! Fin du tour, mais les points sont conserves ! <<<\033[0m\n");
                choix = 0; 
                tours_forces = 0;
            }
            else if (ma_carte.type == 2) { 
                printf("\033[1;32mSUPER ! %s gagne une vie supplementaire !\033[0m\n", liste_joueurs[p].nom);
                vies_en_plus++;
            }
            else if (ma_carte.type == 3) { 
                printf("\033[1;33mAIE ! %s est oblige(e) de piocher 3 cartes de suite !\033[0m\n", liste_joueurs[p].nom);
                tours_forces = tours_forces + 3; 
            }
            else { 
                int a_perdu = 0; 
                int i;
                for (i = 0; i < nb_cartes; i++) {
                    if (cartes_en_main[i] == ma_carte.valeur) {
                        a_perdu = 1; 
                    }
                }

                if (a_perdu == 1) {
                    if (vies_en_plus > 0) {
                        printf("\033[1;32mOUF ! La 2nde chance sauve du %d !\033[0m\n", ma_carte.valeur);
                        vies_en_plus--;
                    } else {
                        printf("\033[1;31mOH NON ! Deja un %d. %s a brule !\033[0m\n", ma_carte.valeur, liste_joueurs[p].nom);
                        score_tour = 0; 
                        choix = 0;   
                        tours_forces = 0; 
                    }   
                } 
                else {
                    cartes_en_main[nb_cartes] = ma_carte.valeur;
                    nb_cartes++; 
                    score_tour += ma_carte.valeur;
                    printf("Score actuel de %s : %d\n", liste_joueurs[p].nom, score_tour);
                }
            }

            if (choix == 1) {
                if (tours_forces > 0) {
                    printf("\n(Tirage(s) force(s) restant(s) : %d...)\n", tours_forces);
                    tours_forces--; 
                } 
                else {
                    // --- NOUVEAU : C'EST L'IA QUI DÉCIDE TOUTE SEULE ---
                    if (est_IA == 1) {
                        // L'IA s'arrête si elle a 15 points ou plus
                        if (score_tour >= 15) {
                            printf("L'Ordinateur decide de S'ARRETER.\n");
                            choix = 0;
                        } else {
                            printf("L'Ordinateur decide de CONTINUER.\n");
                            choix = 1;
                        }
                    } 
                    // --- SINON C'EST UN HUMAIN QUI JOUE ---
                    else {
                        printf("Veux-tu piocher une autre carte ? (1 = OUI, 0 = NON) : ");
                        scanf("%d", &choix); 
                    }
                }
            }
        } 

        liste_joueurs[p].score = score_tour;
        printf("\nFin du tour de %s. Score final : %d points.\n", liste_joueurs[p].nom, liste_joueurs[p].score);
    } 

    printf("\n\n\033[1;33m======= FIN DE LA PARTIE =======\033[0m\n");
    int score_max = -1;
    char nom_gagnant[50];

    for (p = 0; p < nb_joueurs; p++) {
        printf("%s a fait %d points.\n", liste_joueurs[p].nom, liste_joueurs[p].score);
        if (liste_joueurs[p].score > score_max) {
            score_max = liste_joueurs[p].score;
            int i = 0;
            while(liste_joueurs[p].nom[i] != '\0') {
                nom_gagnant[i] = liste_joueurs[p].nom[i];
                i++;
            }
            nom_gagnant[i] = '\0';
        }
    }
    printf("\n\033[1;32mLE GAGNANT EST %s AVEC %d POINTS ! BRAVO !\033[0m\n", nom_gagnant, score_max);

    return 0;
}