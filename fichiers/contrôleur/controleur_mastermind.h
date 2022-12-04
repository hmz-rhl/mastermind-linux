#ifndef CONTROLER_H

#define CONTROLER_H

#include "../modèle/mastermind.h"
#include "../vue/vue_mastermind.h"
#include <gtk/gtk.h>


/*______________________________________STRUCTURE DU CONTROLEUR______________________________________*/

typedef struct ctrl_s
{

	vue_mastermind* vue;    /* Il s'agit ici de la vue */
	mastermind* mm;         /* Il s'agit ici du modèle */
	int rg;                 /* Variable à valeurs dans {0,...,4} représentant la position du joueur pour chaque essai
	                           (en réalité, 0 ne représente pas une position en tant que telle mais une position "transitoire") */
	int nb_case;            /* Variable à valeurs dans {0,...,48} représentant la position du joueur dans la grille de jeu dans son ensemble
	                           (en réalité, 0 ne représente pas une position en tant que telle mais une position "transitoire")*/

}ctrl_t;


/*______________________________________DÉCLARATION DES FONCTIONS______________________________________*/



/* Cette fonction permet de lier l'ensemble des boutons de la vue à leurs fonctions respectives */
/* Par exemple, lorsque l'utilisateur clique sur le bouton "Effacer", alors vue_mastermind_controler
   va faire un appel à la fonction "effacer" du contrôleur via un g_signal_connect */
/* Pré-conditions :
	 - controleur contient bien l'adresse d'une variable de type ctrl_t */
void vue_mastermind_controler(ctrl_t *controleur);


/* Cette fonction permet d'initialiser une partie de Mastermind : la grille de jeu est alors vide, idem pour la grille de vérification */
/* Pré-conditions :
	 - controleur contient bien l'adresse d'une variable de type ctrl_t
	 Post-conditions :
	 - l'état de la partie est ETAT_MM_ENCOURS
	 - le numéro d'essai en cours vaut 1, les composantes de cet essai valent toutes COULEUR_INDETERMINEE */
void initialiser_partie(GtkButton* b, ctrl_t *controleur);


/* Cette fonction va se charger de placer, dans la grille de jeu, la couleur que l'utilisateur a choisi après avoir cliqué sur le bouton
   correspondant à cette couleur */
/* De plus, cette fonction va gérer la grille de vérification du jeu (celle qui permet de savoir si une couleur est bien placée ou non). */
/* Ainsi, trois cas sont à distingués :
- si un ou des carrés rouge apparaîssent dans la grille de vérification, cela signifie qu'une ou des couleur(s) de la combinaison saisie sont bien placées.
- si un ou des carrés bleu apparaîssent dans la grille de vérification, cela signifie qu'une ou des couleur(s) de la combinaison sont correctes mais pas bien placées.
- si rien n'apparaît dans la grille de vérification, cela signifie qu'aucune des couleurs de la combinaison saisie est correcte. */
/* Pré-conditions :
	 - controleur contient bien l'adresse d'une variable de type ctrl_t */
void jouer(GtkButton* b, ctrl_t *controleur);


/* Cette fonction permet à l'utilisateur de pouvoir effacer une ou des couleurs de la combinaison qu'il est en train de saisir */
/* Pré-conditions :
	 - controleur contient bien l'adresse d'une variable de type ctrl_t */
void effacer(GtkButton* b, ctrl_t *controleur);


/* Cette fonction permet de dévoiler, en fin de partie, la combinaison secrète en cas de victoire ou défaite de l'utilisateur */
/* Pré-conditions :
	 - controleur contient bien l'adresse d'une variable de type ctrl_t
	 Post-condition :
	 - si l'état de la partie est ETAT_MM_PERDU ou 	ETAT_MM_GAGNE, la combinaison secrète est dévoilée */
void afficher_combinaison_secrete(ctrl_t *controleur);


#endif
