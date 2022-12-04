# ifndef VUE_MASTERMIND_H

	#define VUE_MASTERMIND_H

	#include <gtk/gtk.h>



/*__________________STRUCTURE DE LA VUE__________________*/

typedef struct s_vue_mastermind
{
	// LA FENETRE //
	GtkWindow* fenetre;

	// LES BOITES //
	GtkBox* boite_principale;                        /* Boite horizontale contenant tous les autres widgets, d'où le nom "boite_principale" */
	GtkBox* boite_secondaire;                        /* Boite verticale contenant :
	                                                    - les boutons "Nouvelle partie", "Effacer" et "Quitter"
                                                      - les libelles "libelle_secret" et "libelle_humour"
																							        - la grille "grille_secrete"  */

	// LES GRILLES //
	GtkGrid* grille_boutons_couleur;                 /* Grille contenant les 8 boutons de couleurs */
	GtkGrid* grille_boutons_menu;                    /* Grille contenant les boutons "Nouvelle partie", "Effacer" et "Quitter"  */
	GtkGrid* grille_de_jeu;                          /* Grille représentant la grille de jeu. Elle contient les 48 "images_grille_jeu" */
	GtkGrid* grille_de_verification;                 /* Grille représentant la grille de vérification. Elle contient les 48 "images_grille_verification" */
	GtkGrid* grille_secrete;                         /* Grille représentant la combinaison secrète. Elle contient les 4 "images_combinaison_secrete" */

	// LES LIBELLES //
	GtkLabel* libelle_secret;                        /* Libellé situé juste en dessous du bouton "Quitter" dans la vue. Il se change en :
	                                                    - "Configuration secrete..." si ETAT_MM_ENCOURS
																							        - "PERDUE !" si ETAT_MM_PERDU
																							        - "GAGNEE !" si ETAT_MM_GAGNE */

	GtkLabel* libelle_humour;                        /* Libellé "humoristique" qui change en fonction de l'essai en cours
	                                                    Par exemple, à l'essai n°2, on a "Brain is loading!" */

	// LES IMAGES //
	GtkImage* images_grille_jeu[48];                 /* Tableau de 48 images permettant de représenter les cercles qui constituent la grille de jeu */
	GtkImage* images_grille_verification[48];        /* Tableau de 48 images permettant de représenter les carrés qui constituent la grille de vérification */
	GtkImage* images_boutons_couleur[8];             /* Tableau de 8 images permettant de représenter les cercles de couleurs situés à droite des boutons de couleurs */
	GtkImage* images_combinaison_secrete[4];         /* Tableau de 4 images permettant de représenter les cercles qui constituent la combinaison secrète dans la vue */

	// LES BOUTONS //
	GtkButton* boutons_couleur[8];                   /* Tableau de 8 boutons, correspondant aux boutons de choix des couleurs */
	GtkButton* bouton_nouvelle_partie;               /* Bouton "Nouvelle partie" */
	GtkButton* bouton_quitter;                       /* Bouton "Quitter" */
	GtkButton* bouton_effacer;                       /* Bouton "Effacer" */
}vue_mastermind;



/*__________________DÉCLARATION DES FONCTIONS__________________*/


/* Cette fonction va permettre de créer tous les widgets de l'interface (boutons, grille, boite...) */
/* Pré-conditions :
	 - une_vue_mastermind contient bien l'adresse d'une variable de type vue_mastermind */
void vue_mastermind_creation_widgets(vue_mastermind* une_vue_mastermind);

/* Cette fonction va se charger d'attacher, aux différentes grilles de l'interface, des images ou des boutons */
/* Pré-conditions :
	 - une_vue_mastermind contient bien l'adresse d'une variable de type vue_mastermind */
void vue_mastermind_grid_attach(vue_mastermind* une_vue_mastermind);

/* Cette fonction va se charger de l'inclusion des widgets dans les différentes boites créees */
/* Pré-conditions :
	 - une_vue_mastermind contient bien l'adresse d'une variable de type vue_mastermind */
void vue_mastermind_inclusion_widgets(vue_mastermind* une_vue_mastermind);

/* Cette "petite" fonction (mais très importante!) permet simplement d'afficher la fenêtre et tous les widgets qu'elle contient (boutons, labels, etc...) */
/* Pré-conditions :
	 - une_vue_mastermind contient bien l'adresse d'une variable de type vue_mastermind */
void vue_mastermind_affichage_widgets(vue_mastermind* une_vue_mastermind);

/* Cette fonction permet à l'utilisateur de fermer la fenêtre de l'interface et d'arrêter la boucle de GTK */
/* Pré-conditions :
	 - une_vue_mastermind contient bien l'adresse d'une variable de type vue_mastermind */
void vue_mastermind_fermeture_interface(vue_mastermind* une_vue_mastermind);


#endif
