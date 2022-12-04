#include <stdlib.h>  /* fonction srand() */
#include <time.h>    /* fonction srand() */
#include "vue/vue_mastermind.h"
#include "contrôleur/controleur_mastermind.h"



int main()
{
	srand(time(NULL));    /* Permet de générer des combinaisons aléatoires à chaque nouvelle partie de Mastermind */

/* Déclaration des variable du jeu */

	/* La vue */
	vue_mastermind vue;

	/* Le modèle */
	mastermind mm;

	/* Le contrôleur */
	ctrl_t controleur;
	controleur.vue = &vue;
	controleur.mm = &mm;
	controleur.rg = 0;
	controleur.nb_case = 0;


	/* initialisation de l'environnnement gtk */
	gtk_init(NULL,NULL);

	/* construction de la vue */
	vue_mastermind_creation_widgets(&vue);      /* création des différents widgets */
	vue_mastermind_grid_attach(&vue);           /* on attache ici les boutons et les images sur les grilles qui leur correspondent */
	vue_mastermind_inclusion_widgets(&vue);     /* on inclut les widgets dans les boites */
	vue_mastermind_affichage_widgets(&vue);     /* on affiche tous les widgets */
	vue_mastermind_fermeture_interface(&vue);   /* on peut arrêter l'interface à tout moment ! */

	/* initialisation du jeu */
	mastermind_initialiser_avec_secret(&mm);    /* initialisation de la partie de Mastermind avec une combinaison générée aléatoirement */

	/* contrôle du modele et de la vue */
	vue_mastermind_controler(&controleur);      /* appel au contrôleur */


	/* lancement du programme */
	gtk_main();

	return EXIT_SUCCESS;
}
