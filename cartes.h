#ifndef CARTES_H
#define CARTES_H

typedef struct {
	int valeur;
	int type;
} Carte;

typedef struct {
	char nom[50];
	int score;
	int a_brule;
} Joueur;

// --- LES NOUVELLES FONCTIONS DU CROUPIER ---

// On utilise des pointeurs (*) pour que la fonction puisse modifier
// le paquet et sa taille directement dans la mémoire de l'ordinateur.
void initialiser_paquet(Carte *paquet, int *taille);
void melanger_paquet(Carte *paquet, int taille);
Carte piocher_carte(Carte *paquet, int *taille);

void afficher_carte(Carte c);

#endif