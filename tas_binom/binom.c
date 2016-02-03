#include "binom.h"

A_binomial creer_arbre_binomial(){
	return NULL;
}

A_binomial allouer_arbre_binomial(){
	A_binomial arbre = malloc(sizeof(struct noeud));
	arbre->degre = 0;
	arbre->pere = NULL;
	arbre->pfg = NULL;
	arbre->pfd = NULL;
	#ifdef DEBUG
	printf("Arbre alloué\n");
	#endif
	return arbre;
}

A_binomial ajouter_cle(A_binomial arbre, int cle){
	return ajouter_cle_avec_pere(arbre, cle, NULL);
}

A_binomial ajouter_cle_avec_pere(A_binomial arbre, int cle, A_binomial pere){
	if(arbre == NULL){
		arbre = allouer_arbre_binomial();
		arbre->cle = cle;
		arbre->pere = pere;
		if(pere != NULL){
			pere->degre++;
		}
		#ifdef DEBUG
		printf("Clé insérée\n");
		#endif
		return arbre;
	}
	else{
		if(cle >= arbre->cle){
			#ifdef DEBUG
			printf("Insérer à gauche\n");
			#endif
			return ajouter_cle_avec_pere(arbre->pfg, cle, arbre);
		}
		else{
			if(pere == NULL){
				A_binomial new_arbre = allouer_arbre_binomial();
				new_arbre->cle = cle;
				new_arbre->pere = pere;
				new_arbre->pfg = arbre;
				new_arbre->pfd = arbre->pfd;
				new_arbre->degre = 1;
				arbre->pfd = NULL;
				#ifdef DEBUG
				printf("Noeud père changé\n");
				#endif
				return new_arbre;
			}
			else{
				#ifdef DEBUG
				printf("Inserer à droite\n");
				#endif
				return ajouter_cle_avec_pere(arbre->pfd, cle, pere);
			}
		}
	}
	return arbre;
}

A_binomial lier(A_binomial arbre, A_binomial arbre2){
	if(arbre == NULL){
		#ifdef DEBUG
		printf("arbre 1 null\n");
		#endif
		return arbre2;
	}
	if(arbre2 == NULL){
		#ifdef DEBUG
		printf("Arbre 2 null\n");
		#endif
		return arbre;
	}
	arbre2->pere = arbre;
	arbre2->pfd = arbre->pfg;
	arbre->pfg = arbre2;
	arbre->degre++;
	#ifdef DEBUG
	printf("Liaison\n");
	#endif
	return arbre;
}

/*A_binomial creer_tas_binomial(){
return allouer_tas_binomial();
}

A_binomial allouer_tas_binomial(){
Tas_binomial tas = malloc(sizeof(struct noeud));
tas = NULL;
tas->suivant = NULL;
return tas;
}*/

A_binomial inserer(A_binomial tas, A_binomial arbre){
	A_binomial result;
	arbre->pere = NULL;
	arbre->pfg = NULL;
	arbre->pfd = NULL;
	arbre->degre = 0;
	result = arbre;
	result = unir(result, tas);
	#ifdef DEBUG
	printf("Union\n");
	#endif
	return result;
}

A_binomial fusionner(A_binomial tas, A_binomial tas2){
	A_binomial result = allouer_arbre_binomial();
	while((tas != NULL) && (tas2 != NULL)){
		if(tas->degre == tas2->degre){
			result = inserer(result, tas);
			result = inserer(result, tas2);
			tas = tas->pfd;
			tas2 = tas2->pfd;
		}
		else if(tas->degre < tas2->degre){
			result = inserer(result, tas);
			tas = tas->pfd;
		}
		else{
			result = inserer(result, tas2);
			tas2 = tas2->pfd;
		}
	}

	while(tas != NULL){
		result = inserer(result, tas);
		tas = tas->pfd;
	}

	while(tas2 != NULL){
		result = inserer(result, tas2);
		tas2 = tas2->pfd;
	}

	#ifdef DEBUG
	printf("Fusion\n");
	#endif
	return result;
}

A_binomial unir(A_binomial tas, A_binomial tas2){
	A_binomial result = fusionner(tas, tas2);
	if(result == NULL){
		return result;
	}
	else{
		A_binomial pred = NULL;
		A_binomial x = result;
		A_binomial succ = x->pfd;
		while(succ != NULL){
			if(((x->degre != succ->degre) || (succ->pfd != NULL)) && (x->pfd->degre == x->degre)){
				pred = x;
				x = succ;
			}
			else if(x->cle <= succ->cle){
				x->pfd = succ->pfd;
				lier(succ, x);
			}
			else{
				if(pred == NULL){
					result = succ;
				}
				else{
					pred->pfd = succ;
				}
				lier(x, succ);
				x = succ;
			}
		}
	}
	#ifdef DEBUG
	printf("Union\n");
	#endif
	return result;
}

int extraire_min(A_binomial tas){
	if(tas->pfd == NULL){
		return tas->pfd->cle;
	}
	else{
		return extraire_min(tas);
	}
}

A_binomial supprimer_min(A_binomial tas){
	if(tas->pfd == NULL){
		tas = tas->pfg;
		A_binomial fils = tas;
		while(fils != NULL){
			fils->pere = NULL;
			fils = fils->pfd;
		}
	}
	else{
		if(tas->pfd->pfd != NULL){
			supprimer_min(tas->pfd);
		}
		else{
			A_binomial new_tas = tas->pfd->pfg;
			A_binomial fils = new_tas;
			tas->pfd = new_tas;
			while(fils != NULL){
				fils->pere = NULL;
				fils = fils->pfd;
			}
		}
	}
	return tas;
}

A_binomial decrementer_cle(A_binomial tas, A_binomial arbre){
	int k = arbre->degre - 1;
	A_binomial y;
	if(arbre->cle > k){
		return NULL;
	}
	else{
		y = arbre;
		arbre = y->pere;
		while((arbre != NULL) && (y->cle < arbre->cle)){
			int cleInt = arbre->cle;
			arbre->cle = y->cle;
			y->cle = cleInt;
			y = arbre;
			arbre = y->pere;
		}
	}
	return tas;
}

Boolean tas_binomial_vide(A_binomial tas){
	return (tas == NULL);
}

void afficher_tas(A_binomial tas){
	if(tas != NULL){
		printf("%d\n", tas->cle);
		afficher_tas(tas->pfg);
		afficher_tas(tas->pfd);
	}
}
