/* Projet IAP Sprint 5
Marimouttou Rezouane, Carounagarane Moguech, Chathianathan Jeneifan
Date de cr�ation : 02/10/2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_champs 25 // Nombre maximum de champs d�une table
#define lgMot 30 // Longueur max d�une chaine de caract�res
#define lgMax 80 // Longueur maximale d�une ligne de commande
#define max_enregistrement 100 // Nombre maximum d'enregistrements dans une table

#pragma warning(disable:4996)


typedef struct {
	unsigned char  data[lgMot + 1]; // Type Data qui permet de stocker les donn�es dans chaques champs
}Data;

typedef struct {
	Data colonne[max_champs]; // Type Enregistrement qui permet de s�parer le tableau en colonnes
}Enregistrement;

typedef struct {          // Type Champs qui permet de donner le nom et le type d'un champs     
	char nom[lgMot + 1];  // Nom d'un champs
	char type[lgMot + 1]; // Type d'un champs
}Champ;

typedef struct {          // Type Table qui permet de s�parer les �l�ments de la Table
	char nom[lgMot + 1];  // Nom de la Table
	Champ  schema[max_champs]; // Les �l�ments de la table (les champs avec leurs noms et types)
	unsigned char nbChamps; // Nombres de champs dans la table
	Enregistrement enrg[max_enregistrement]; // Ligne d'une table
	unsigned int nb_enregistrement; //Nombres d'enregistrements ins�rer dans la table
}Table;



void create_table(Table *t); // Creer la table
							 // [in-out] Table*t

void afficher_schema(const Table *t); // Afficher les noms et types des champs
									  // [in-out] Table*t

void inserer_enregistrement(Table *t); // Inserer une ligne dans la table
									   // [in-out] Table*t

void afficher_enregistrements(const Table *t); // Afficher tout les enregistrements
											   // [in-out] Table*t

void afficher_enregistrement(const Table *t); // Afficher un enregistrement d'un rang donner
											  // [in-out] Table*t

void delete_enregistrement(Table *t); // Suprimmer un enregistrement
									  // [in-out] Table*t

void select_enregistrement(Table* t); // Afficher tout les enregistrements qui sont compris entre 2 crit�res
									  // [in-out] Table*t

int compare_enregistrement(Table* t, int nb_champ, unsigned int num_enregistrement, char crit1[lgMot + 1], char crit2[lgMot + 1]);
// Compare les enregistrement avec les crit�res pour la fonction select_enregistrement
// [in-out] Table*t, [in] nb_champ, [in] num_enregistrement, [in] crit1, [in] crit2

void delete_table(Table *t); // Suprimme tout les �l�ments d'une table
							 // [in-out] Table*t

unsigned int cmp_create = 0; // Compteur qui compte le nombre de fois que l'on rentre dans la fonction create_table 

int main() {
	char mot[lgMax + 1]; // varaible char o� l'on va rentrer le nom des commandes
	Table t;
	t.nb_enregistrement = 0; // initialisation des nombres d'enregistrements � 0
	while (1) { // boucle infinie sur les 7 commandes
		scanf("%s", mot); // le mot lu est une cha�ne de 30 caract.

		if (strcmp(mot, "Create_table") == 0) { // Si le mot entr� est "Create_table"
			create_table(&t); // alors appel de la fonction create_table avec param�tre effectif l'adresse de t
			++cmp_create;// incr�mentation du compteur cmp_create
		}


		if (strcmp(mot, "Insert_enregistrement") == 0) { // Si le mot entr� est "Insert_enregistrement"
			inserer_enregistrement(&t); // alors appel de la fonction inserer_enregistrement avec param�tre effectif l'adresse de t

		}
		if (strcmp(mot, "Afficher_schema") == 0) { // Si le mot entr� est "Afficher_schema"
			afficher_schema(&t); // alors appel de la fonction afficher_schema avec param�tre effectif l'adresse de t

		}
		if (strcmp(mot, "Afficher_enregistrements") == 0) { // Si le mot entr� est "Afficher_enregistrements"
			afficher_enregistrements(&t); // alors appel de la fonction afficher_enregistrements avec param�tre effectif l'adresse de t

		}
		if (strcmp(mot, "Afficher_enregistrement") == 0) { // Si le mot entr� est "Afficher_enregistrement"
			afficher_enregistrement(&t); // alors appel de la fonction afficher_enregistrement avec param�tre effectif l'adresse de t
		}
		if (strcmp(mot, "Delete_enregistrement") == 0) { // Si le mot entr� est "Delete_enregistrement"
			delete_enregistrement(&t); // alors appel de la fonction delete_enregistrement avec param�tre effectif l'adresse de t
		}
		if (strcmp(mot, "Delete_table") == 0) { // Si le mot entr� est "Delete_table"
			delete_table(&t); // alors appel de la fonction delete_table avec param�tre effectif l'adresse de t
		}
		if (strcmp(mot, "Select_enregistrement") == 0) { // Si le mot entr� est "Select_enregistrement"
			select_enregistrement(&t); // alors appel de la fonction select_enregistrement avec param�tre effectif l'adresse de t
		}

		if (strcmp(mot, "Exit") == 0) { // Si le mot entr� est "Exit"
			exit(0); // sortie du programme principal
		}

	}
	system("pause"); return 0;
}


void create_table(Table *t) { // Creer la table
							  // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	scanf("%s", temp); // Lecture de temp


	if (strcmp(t->nom, temp) == 0 && cmp_create != 0) { // Si temp est le nom de la table et cmp_create est diff�rent de 0
		printf("table existante\n"); // afficher "table existante"
	}
	else if (cmp_create == 0) { // sinon si cmp_create est �gal � 0 (donc premi�re fois que l'on rentre dans la fonction)
		scanf("%s", &t->nbChamps); // lecture du nombre de champs avec la notation fl�che
		strcpy(t->nom, temp); // copie de temp dans t->nom (le nom de la table)

		for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
			scanf("%s %s", &*t->schema[i].nom, &*t->schema[i].type); // lecture nom du champs et son type
		}

	}

}

void afficher_schema(const Table *t) { // Afficher les noms et types des champs
									   // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0 && cmp_create != 0) { // si temp est le nom de la table et cmp_table est diff�rent de 0
		printf("%s %s\n", &*t->nom, &t->nbChamps); // alors afficher le nom de la table et le nombre de champs

		for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
			printf("%s %s\n", &*t->schema[i].nom, &*t->schema[i].type); // afficher les noms des chants et leurs types
		}

	}
	else { // sinon
		printf("table inconnue\n"); // afficher "table inconnue"
	}
}



void inserer_enregistrement(Table *t) { // Inserer une ligne dans la table
										// [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0) { // si temp est le nom de la table
		++t->nb_enregistrement; // incr�mentation du nombre d'enregistrement � chaque fois que l'on inssere un enregistrement
		for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
			scanf("%s", &t->enrg[t->nb_enregistrement].colonne[i].data); // lecture des donn�es de la ligne t->nb_enregistrement et colonne i
		}
	}
	else { // sinon
		printf("table inconnue\n"); // afficher "table inconnue"
	}
}




void afficher_enregistrements(const Table *t) {// Afficher tout les enregistrements
											   // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0) { // si temp est le nom de la table
		for (unsigned int j = 1; j <= t->nb_enregistrement; ++j) { // pour j allant de 1 � t->nb_enregistrement
			printf("%d", j); // afficher le rang
			for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
				printf(" %s %s", t->schema[i].type, t->enrg[j].colonne[i].data); // afficher les le type du champ et son enregistrement
			}
			printf("\n"); // retour � la ligne quand une ligne est afficher compl�tement
		}
	}
	else { // sinon
		printf("table inconnue\n"); // afficher "table inconnue
	}
}

void afficher_enregistrement(const Table *t) { // Afficher un enregistrement d'un rang donner
											   // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	int num_enregistrement = 0; // initialisation d'une variable num_enregistrement � 0 qui est le rang que l'on veut afficher
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0) { // si temp est le nom de la table
		scanf("%d", &num_enregistrement); // lecture du rang de l'enregistrement que l'on veut afficher
		printf("%d", num_enregistrement); // afficher le rang de l'enregistrement
		for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
			printf(" %s %s", t->schema[i].type, t->enrg[num_enregistrement].colonne[i].data); // afficher les types de la colonne i et les enregistrement de ligne num_enregistrement et colonne i
		}
		printf("\n"); // retour � la ligne d�s que l'enregistrement est afficher
	}
	else { // sinon
		printf("table inconnue\n"); // afficher "table inconnue"
	}

}

void delete_enregistrement(Table *t) { // Suprimmer un enregistrement
									   // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	unsigned int num_enregistrement = 0; // initialisation d'une variable num_enregistrement � 0 qui est le rang que l'on veut supprimmer
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0) { // si temp est le nom de la table
		scanf("%d", &num_enregistrement); // lecture du rang de l'enregistrement que l'on veut supprimmer

		if (num_enregistrement == t->nb_enregistrement) { // si le rang est �gal au enregistrements max
			for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
				strcpy(t->enrg[num_enregistrement].colonne[i].data, ""); // mettre � vide les donn�es de la ligne d'enregistrement
			}
			--t->nb_enregistrement; // d�cr�mentation du nombre d'enregistrement
		}
		else if (num_enregistrement < t->nb_enregistrement) { // sinon si le rang est inf�rieur au nombre d'enregistrements max
			for (int i = 0; i < atoi(&t->nbChamps); i++) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
				strcpy(t->enrg[num_enregistrement].colonne[i].data, ""); // mettre � vide les donn�es de la ligne d'enregistrement
			}

			for (unsigned int j = num_enregistrement; j < t->nb_enregistrement; j++) { // pour j allant du rang de l'enregistrement suprimm� au nombre d'enregistrement max
				for (int k = 0; k < atoi(&t->nbChamps); k++) { // pour k allant de 0 au nombre de champs (convertit avec atoi)
					strcpy(t->enrg[j].colonne[k].data, t->enrg[j + 1].colonne[k].data); // on copie les donn�es de la ligne suivante dans la ligne j
				}
			}
			--t->nb_enregistrement; // d�cr�mentation du nombre d'enregistrement
		}
		else if (num_enregistrement > t->nb_enregistrement || num_enregistrement <= 0) { // sinon si num_enregistrement est hors des bornes des enregistrements
			printf("enregistrement inconnu\n"); // afficher "enregistrement inconnu"
		}

		else { // sinon
			printf("table inconnue\n"); // afficher "table inconnue"
		}
	}
}

void delete_table(Table *t) { // Suprimme tout les �l�ments d'une table
							  // [in-out] Table*t

	unsigned char temp[lgMot + 1]; // variable temporaire o� l'on va rentrer le nom de la table
	scanf("%s", temp); // Lecture de temp

	if (strcmp(t->nom, temp) == 0) { // si temp est le nom de la table

		for (unsigned int i = 1; i < t->nb_enregistrement; i++) { // pour i allant de 1 au nombre d'enregistrements max
			for (int j = 0; j < atoi(&t->nbChamps); j++) { // pour j allant de 0 au nombre de champs (convertit avec atoi)
				strcpy(t->enrg[i].colonne[j].data, ""); // mettre � vide la cha�ne de caract�re dans les donn�e de ligne 1 et colonnes j (tout les enregistrement)
			}
		}

		for (int k = 0; k < atoi(&t->nbChamps); k++) { // pour j allant de 0 au nombre de champs (convertit avec atoi)
			strcpy(t->schema[k].nom, ""); // mettre � vide les noms des champs
			strcpy(t->schema[k].type, "");  // mettre � vide les types des champs
		}
		strcpy(t->nom, ""); // mettre � vide le nom de la table
		strcpy(&t->nbChamps, ""); // mettre � vide le nombre de champs de la table
		t->nb_enregistrement = 0; // mettre � 0 le nombre d'enregistrements
		cmp_create = 0; // mettre � 0 cmp_create
	}
	else { // sinon
		printf("table inconnue\n"); // afficher "table inconnue"
	}
}


void select_enregistrement(Table* t) { // Afficher tout les enregistrements qui sont compris entre 2 crit�res
									   // [in-out] Table*t

	char temp1[lgMot + 1];  // variable temporaire 1 o� l'on va rentrer le nom de la table
	char temp2[lgMot + 1];  // variable temporaire 2 o� l'on va rentrer le nom du champ que l'on veut selectionner
	char min[lgMot + 1], max[lgMot + 1]; // variable min et max qui correspondent au crit�res de s�lection
	scanf("%s", temp1); // Lecture de temp1
	if (strcmp(t->nom, temp1) == 0) { // si temp1 est le nom de la table
		scanf("%s", temp2); // Lecture de temp2 (le nom du champs)
		scanf("%s %s", min, max); // lecture des bornes min et max
		for (int n = 0; n< atoi(&t->nbChamps); ++n) { // pour n allant de 0 au nombre de champs (convertit avec atoi)
			if (strcmp(t->schema[n].nom, temp2) == 0) { // si il existe un champ de nom temp 2
				for (unsigned int i = 1; i <= t->nb_enregistrement; ++i) { // alors pour i allant de 1 au nombres d'enregistrements max
					if (compare_enregistrement(t, n, i, min, max)) { // si la fonction compare_enregistrement renvoi 1
						printf("%u", i); // afficher le rang de l'enregistrement qui est compris entre les crit�res
						for (int j = 0; j < atoi(&t->nbChamps); ++j) { // pour i allant de 0 au nombre de champs (convertit avec atoi)
							printf(" %s %s", t->schema[j].type, t->enrg[i].colonne[j].data); // afficher les types des champs et leurs donn�es
						}
						printf("\n"); // retour � ligne d�s que l'enregistrement est afficher
					}
				}
			}
		}
	}
	else { // sinon 
		printf("table inconnue\n");  // afficher "table inconnue"
	}
}

int compare_enregistrement(Table* t, int nb_champ, unsigned int num_enregistrement, char crit1[lgMot + 1], char crit2[lgMot + 1]) {
	// Compare les enregistrement avec les crit�res pour la fonction select_enregistrement
	// [in-out] Table*t, [in] nb_champ, [in] num_enregistrement, [in] crit1, [in] crit2

	if (strcmp(t->schema[nb_champ].type, "INT") == 0) { // si le type du champ demand� est "INT"
		return (atoi(crit1) <= atoi(t->enrg[num_enregistrement].colonne[nb_champ].data) && // alors si il y a des enregistrement compris
			atoi(t->enrg[num_enregistrement].colonne[nb_champ].data) <= atoi(crit2)); // entre les bornes alors la fonction retourne 1
																					  // ici conversion avec atoi car c'est des INT
	}
	else if (strcmp(t->schema[nb_champ].type, "FLOAT") == 0) { // si le type du champ demand� est "FLOAT"
		return (atof(crit1) <= atof(t->enrg[num_enregistrement].colonne[nb_champ].data) && // alors si il y a des enregistrement compris
			atof(t->enrg[num_enregistrement].colonne[nb_champ].data) <= atof(crit2)); // entre les bornes alors la fonction retourne 1
																					  // ici conversion avec atof car c'est des FLOAT

	}
	else if (strcmp(t->schema[nb_champ].type, "TEXT") == 0) { // si le type du champ demand� est "TEXT"
		return((strcmp(crit1, t->enrg[num_enregistrement].colonne[nb_champ].data) <= 0) && // comparaison entre les crit�res et les cha�nes 
			(strcmp(crit2, t->enrg[num_enregistrement].colonne[nb_champ].data) >= 0)); // de caract�re si l'enreistrement est entre les bornes
																					   // alors la fonction retourne 1	

	}
	else if (strcmp(t->schema[nb_champ].type, "DATE") == 0) { // si le type du champ demand� est "DATE"
		char datemin[lgMot + 1], datemax[lgMot + 1], date_enrg[lgMot + 1]; // variabales afin de faire des comparaison de dates
		strncpy(&datemin[0], &crit1[6], 4); // on copie l'ann�e du crit�re 1 au d�but de datemin
		strncpy(&datemin[4], &crit1[3], 2); // on copie le mois � la suite
		strncpy(&datemin[6], &crit1[0], 2); // et on copie le jour � la suite
											// datemin est sous le format = aaaammjj

		strncpy(&datemax[0], &crit2[6], 4); // on copie l'ann�e du crit�re 2 au d�but de datemax
		strncpy(&datemax[4], &crit2[3], 2); // on copie le mois � la suite
		strncpy(&datemax[6], &crit2[0], 2); // et on copie le jour � la suite
											// datemax est sous le format = aaaammjj

		strncpy(&date_enrg[0], &t->enrg[num_enregistrement].colonne[nb_champ].data[6], 4); // on copie l'ann�e de l'enregistrement au d�but de date_enrg
		strncpy(&date_enrg[4], &t->enrg[num_enregistrement].colonne[nb_champ].data[3], 2); // on copie le mois � la suite
		strncpy(&date_enrg[6], &t->enrg[num_enregistrement].colonne[nb_champ].data[0], 2); // et on copie le jour � la suite
																						   // date_enrg est sous le format = aaaammjj

		return((atoi(datemin) <= atoi(date_enrg)) && (atoi(date_enrg) <= atoi(datemax))); // on convertit datemin datemax et date_enrg en int avec atoi
																						  // afn de les comparer entre elles et si la date de l'enregistrement
																						  // est dans l'intervalle [datemin; datemax] alors la fonction retourne 1
	}
	else { // sinon
		return 0; // la fonction retourne 0
	}
}