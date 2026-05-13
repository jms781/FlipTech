typedef struct {
    int valeur; 
    int type;   // 0 = Nombre, 1 = Bonus Addition (+), 2 = Bonus Multiplicateur (x2)
} Carte;

typedef struct {
    char nom[50];
    int score_total;
    int score_manche;
    int en_jeu;             // 1 = joue encore la manche, 0 = a arrete ou a brule
    int cartes_main[15];    // Historique des cartes pour verifier les doublons
    int nb_cartes;          // Nombre de cartes nombres en main (pour le Flip 7)
    int bonus_plus;         
    int a_bonus_x2;         // 1 = oui, 0 = non
} Joueur;

// Prototypes avec pointeurs (comme vu dans le chapitre sur les pointeurs et tableaux dynamiques)
Carte* initialiser_paquet(int *taille);
void melanger_paquet(Carte *paquet, int taille);
Carte piocher_carte(Carte *paquet, int *taille);
void afficher_carte(Carte c);
void afficher_statistiques(int *stats);