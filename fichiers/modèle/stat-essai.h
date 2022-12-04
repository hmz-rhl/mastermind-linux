#ifndef STAT_ESSAI_H

#define STAT_ESSAI_H


struct s_stat_essai {
	int ordo;		/* nombre de couleurs bien placées d'un essai */
	int non_ordo;	/* nombre de couleurs correctes d'un essai */
};

typedef struct s_stat_essai stat_essai;

/* ____ Valeur par défaut : -1 (pour distinguer une statistique non renseignée d'une statistique renseignée, à valeur alors >= 0)
*/
#define STAT_VAL_DEF -1

/*	______________________________________
	Accesseurs en lecture / écriture		*/

/* Cette fonction attribue une valeur à la propriété ordo d'une variable de type stat_essai
	Pré-condition : stat contient bien l'adresse d'une variable de type stat_essai
	Post-condition : la propriété ordo de la variable *stat est mise à jour à val
*/
void stat_essai_set_nb_couleurs_placees(stat_essai* stat, int val);

/* Cette fonction renvoie la valeur de la propriété ordo d'une variable de type stat_essai
	Pré-condition : stat contient bien l'adresse d'une variable de type stat_essai
	Valeur retournée : la valeur de la propriété ordo de la variable *stat
*/
int stat_essai_get_nb_couleurs_placees(stat_essai* stat);

/* Cette fonction attribue une valeur à la propriété non_ordo d'une variable de type stat_essai
	Pré-condition : stat contient bien l'adresse d'une variable de type stat_essai
	Post-condition : la propriété non_ordo de la variable *stat est mise à jour à val
*/
void stat_essai_set_nb_couleurs_correctes(stat_essai* stat, int val);

/* Cette fonction renvoie la valeur de la propriété non_ordo d'une variable de type stat_essai
	Pré-condition : stat contient bien l'adresse d'une variable de type stat_essai
	Valeur retournée : la valeur de la propriété non_ordo de la variable *stat
*/
int stat_essai_get_nb_couleurs_correctes(stat_essai* stat);

#endif
