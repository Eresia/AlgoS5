#include "menu.h"

void loop(){
    ACTION a;
    char *string;
    Dictionary dico = createDictionary();

    do{
        do{
            print_menu();
            a = getAction();
            switch(a){
                case AJOUTER:
                    string = getString();
                    if(insideDictionary(dico, string)){
                        printf("Le mot est déjà dans le dictionnaire\n");
                    }
                    else{
                        dico = addWord(dico, string);
                        printf("Mot ajouté : %s\n", string);
                    }
                break;
                case SUPPRIMER:
                    string = getString();
                    if(!insideDictionary(dico, string)){
                        printf("Le mot n'est pas dans le dictionnaire\n");
                    }
                    else{
                        dico = deleteWord(dico, string);
                        printf("Mot supprimé\n");
                    }
                    break;
                case AFFICHER:
                    printf("%s", displayDictionary(dico));
                    break;
                case TESTER:
                    string = getString();
                    if(insideDictionary(dico, string)){
                        printf("Le mot est bien dans le dictionnaire\n");
                    }
                    else{
                        printf("Le mot n'est pas dans le dictionnaire\n");
                    }
                    break;
                case VIDER:
                    dico = freeDictionary(dico);
                    printf("Dictionnaire vidé\n");
                    break;
                case SAUVEGARDER:
                    string = getString();
                    saveDictionary(dico, string);
                    printf("Dictionnaire sauvé dans le fichier %s\n", string);
                    break;
                case CHARGER:
                    string = getString();
                    dico = loadDictionary(dico, string);
                    printf("Dictionnaire chargé depuis le fichier %s\n", string);
                    break;
                case QUITTER:
                    break;
                default:
                printf("Commande non connue\n");
                a = NOTHING;
            }
        }while(a == NOTHING);
    }while(a != QUITTER);
}


void print_menu(){
    printf("1) Ajouter un mot\n");
    printf("2) Supprimer un mot\n");
    printf("3) Afficher le contenu du dictionnaire\n");
    printf("4) Tester si un mot appartient au dictionnaire\n");
    printf("5) Vider le dictionnaire\n");
    printf("6) Sauvegarder le contenu du dictionnaire dans un fichier\n");
    printf("7) Charger un dictionnaire à partir d'un fichier\n");
    printf("8) Quitter\n");
}

void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
    *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

ACTION getAction(){
    return getInt(2);
}

int getInt(int size){
    char* string = calloc(size+1, sizeof(char));
    fgets(string, size+1, stdin);
    clean(string, stdin);
    return strtoul(string, NULL, 10);
}

char* getString(){
    char* string = calloc(100, sizeof(char));
    fgets(string, 100, stdin);
    clean(string, stdin);
    return string;
}
