#include "menu.h"

void loop(){
	ACTION a;
	A_binomial* tas;
	int nbTas = 0;
	int param1, param2;

	tas = calloc(100, sizeof(A_binomial));
	do{
		print_menu();
		a = getAction();
		switch(a){
			case CREER_ARBRE:
			tas[nbTas] = creer_arbre_binomial();
			printf("Arbre créé - numéro %d\n", nbTas);
			nbTas++;
			break;
			case INSERER_CLE:
			printf("Dans quel arbre voulez vous ajouter une clé ?\n");
			param1 = getInt(3);
			printf("Quel clé voulez vous insérer ?\n");
			param2 = getInt(3);
			if((param1 < 0) || (param1 > 100) || (param1 >= nbTas)){
				printf("Arbre inconnu : %d\n", param1);
			}
			else{
				tas[param1] = ajouter_cle(tas[param1], param2);
				printf("Clé créée\n");
			}
			break;
			case LIER:
			printf("Donnez un premier arbre\n");
			param1 = getInt(3);
			printf("Donnez un deuxième arbre\n");
			param2 = getInt(3);
			tas[nbTas] = lier(tas[param1], tas[param2]);
			printf("Liaison créé - arbre numéro %d", nbTas);
			nbTas++;
			break;
			case CREER_TAS:
			break;
			case DETERMINER_PETITE_CLE:
			break;
			case EXTRAIRE_PETITE_CLE:
			break;
			case AFFICHER:
			break;
			case FUSIONER:
			break;
			case UNIONER:
			break;
			case INSERER_ARBRE:
			break;
			case DECREMENTER:
			break;
			case QUITTER:
			break;
			default:
			printf("Commande non connue\n");
			a = NOTHING;
		}
	}while(a != QUITTER);
}

void print_menu(){
	printf("1) Créer un arbre binomial\n");
	printf("2) Insérer une clé dans un arbre binomial\n");
	printf("3) Lier deux arbres binomiaux du même degrés\n");
	printf("4) Créer un Tas Binomial\n");
	printf("5) Déterminer la plus petite clé\n");
	printf("6) Extraire la plus petite clé\n");
	printf("7) Afficher le contenu d'un tas\n");
	printf("8) Fusionner deux tas binomiaux\n");
	printf("9) Faire l'union de deux tas binomiaux\n");
	printf("10) Ajouter un arbre binomial dans un tas\n");
	printf("11) Décrémenter la clé d'un tas binomial\n");
	printf("12) Quitter\n");
}

void clean(const char *buffer, FILE *fp)
{
	char *p = strchr(buffer,'\n');
	if (p != NULL){
		*p = 0;
	}
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
	char* string = calloc(3, sizeof(char));
	fgets(string, 3, stdin);
	clean(string, stdin);
	return string;
}
