#ifndef MENU
#define MENU

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binom.h"

typedef enum ACTION ACTION;
enum ACTION{
	NOTHING=0, CREER_ARBRE=1, INSERER_CLE=2, LIER=3, CREER_TAS=4, DETERMINER_PETITE_CLE=5,
	EXTRAIRE_PETITE_CLE=6, AFFICHER=7, FUSIONER=8, UNIONER=9, INSERER_ARBRE=10,
	DECREMENTER=11, QUITTER=12
};

void loop();
void print_menu();
void clean(const char*, FILE*);
ACTION getAction();
int getInt(int);
char* getString();

#endif
