#ifndef BINOM
#define BINOM

#include <stdlib.h>
#include <stdio.h>

#define Boolean int

typedef struct noeud *A_binomial;
struct noeud{
	int degre;
	int cle;
	struct noeud *pere, *pfg, *pfd;
};

/*typedef struct cellule *Tas_binomial;
struct cellule{
A_binomial a;
struct cellule *suivant;
};*/

A_binomial creer_arbre_binomial();
A_binomial allouer_arbre_binomial();
A_binomial ajouter_cle(A_binomial, int);
A_binomial ajouter_cle_avec_pere(A_binomial, int, A_binomial);
A_binomial lier(A_binomial, A_binomial);

//A_binomial creer_tas_binomial();
//A_binomial allouer_tas_binomial();
A_binomial inserer(A_binomial, A_binomial);
int extraire_min(A_binomial);
A_binomial supprimer_min(A_binomial);
A_binomial fusionner(A_binomial, A_binomial);
A_binomial unir(A_binomial, A_binomial);
A_binomial supprimer_min(A_binomial);
A_binomial decrementer_cle(A_binomial, A_binomial);
Boolean tas_binomial_vide(A_binomial);

void afficher_tas(A_binomial);

#endif
