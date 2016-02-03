#ifndef MENU
#define MENU

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dico.h"

typedef enum ACTION ACTION;
enum ACTION{
    NOTHING=0, AJOUTER=1, SUPPRIMER=2, AFFICHER=3, TESTER=4, VIDER=5, SAUVEGARDER=6,
    CHARGER=7, QUITTER=8
};

void loop();
void print_menu();
void clean(const char*, FILE*);
ACTION getAction();
int getInt(int);
char* getString();

#endif
