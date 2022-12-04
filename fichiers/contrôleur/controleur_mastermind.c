#include "controleur_mastermind.h"
#include <gtk/gtk.h>


/*______________________________________DÉFINITION DES FONCTIONS______________________________________*/


/* Cette fonction permet de lier l'ensemble des boutons de la vue à leurs fonctions respectives */
/* Par exemple, lorsque l'utilisateur clique sur le bouton "Effacer", alors vue_mastermind_controler
   va faire un appel à la fonction "effacer" du contrôleur via un g_signal_connect */
void vue_mastermind_controler(ctrl_t *controleur)
{
	int i = 0;

	/* Boucle permettant de connecter les 8 boutons de choix de couleurs de la vue avec la fonction "jouer" du contrôleur */
	for(i = 0; i < 8; ++i)
	{

		g_signal_connect(G_OBJECT(controleur->vue->boutons_couleur[i]), "clicked", G_CALLBACK(jouer),controleur);
	}

  /* Permet de connecter le bouton "Effacer" de la vue avec la fonction "effacer" du contrôleur */
	g_signal_connect(G_OBJECT(controleur->vue->bouton_effacer), "clicked", G_CALLBACK(effacer),controleur);

  /* Permet de connecter le bouton "Nouvelle partie" de la vue avec la fonction "initialiser_partie" du contrôleur */
	g_signal_connect(G_OBJECT(controleur->vue->bouton_nouvelle_partie), "clicked", G_CALLBACK(initialiser_partie),controleur);

  /* Permet de connecter le bouton "Quitter" de la vue avec la fonction "gtk_main_quit" */
	g_signal_connect(G_OBJECT(controleur->vue->bouton_quitter), "clicked", G_CALLBACK(gtk_main_quit), NULL);

}



/* Cette fonction permet d'initialiser une partie de Mastermind : la grille de jeu est alors vide, idem pour la grille de vérification */
void initialiser_partie(GtkButton* b, ctrl_t* controleur)
{
	/* initialise une partie de Mastermind en affectant à chaque composante de la combinaison secrète une couleur tirée au hasard */
	mastermind_initialiser_avec_secret(controleur->mm);

	controleur->rg = 0;
	controleur->nb_case = 0;


  /* Saisie du texte des labels "libelle_secret" et "libelle_humour"  */
	gtk_label_set_label(controleur->vue->libelle_secret,"Configuration secrète...");
	gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nPrêt ? C'est parti !\n\n-------------------------------------\nTu as 12 essais");


  /* initialise la grille de jeu et la grille de vérification à vide (càd avec des images représentant des cercles vides pour la grille de jeu, et des
	   carrés vides pour la grille de vérification) */
	for (int i = 0; i < 48; ++i)
	{
		gtk_image_set_from_file(controleur->vue->images_grille_jeu[i],"fichiers/images/vide.png");
		gtk_image_set_from_file(controleur->vue->images_grille_verification[i],"fichiers/images/vide_verif.png");
	}


	/* initialise la représentation de la combinaison secrète dans la vue à vide (càd avec des images représentant des cercles vides avec
	   un point d'interrogation au centre) */
	for (int i = 0; i < 4; ++i)
	{
		gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i],"fichiers/images/interrogation.png");

	}
}



/* Cette fonction va se charger de placer, dans la grille de jeu, la couleur que l'utilisateur a choisi après avoir cliqué sur le bouton
   correspondant à cette couleur */
/* De plus, cette fonction va gérer la grille de vérification du jeu (celle qui permet de savoir si une couleur est bien placée ou non). */
/* Ainsi, trois cas sont à distingués :
- si un ou des carrés rouge apparaîssent dans la grille de vérification, cela signifie qu'une ou des couleur(s) de la combinaison saisie sont bien placées.
- si un ou des carrés bleu apparaîssent dans la grille de vérification, cela signifie qu'une ou des couleur(s) de la combinaison sont correctes mais pas bien placées.
- si rien n'apparaît dans la grille de vérification, cela signifie qu'aucune des couleurs de la combinaison saisie est correcte. */
void jouer(GtkButton* b, ctrl_t *controleur)
{
	int verif_bienplacees = 0;  /* variable qui compte le nombre de couleurs bien placées */
	int verif_correctes = 0;    /* variable qui compte le nombre de couleurs correctes mais pas à la bonne place */
	int boutons_couleurs;       /* variable temp */

  /* On rentre dans ce "if" uniquement si la partie est en cours et donc s'il nous reste encore des essais */
	if(mastermind_get_num_dernier_essai(controleur->mm)<12 && controleur->mm->etat == ETAT_MM_ENCOURS)
	{

		++controleur->rg;
		++controleur->nb_case;

		/* Cette boucle permet de recupérer la couleur que l'utilisateur a choisi, pour ensuite la transmettre à la fonction "mastermind_set_essai_encours" */
		for(int i = 1; i <= 8 ; ++i)
		{
			if(b == controleur->vue->boutons_couleur[i-1])
			{
				boutons_couleurs = i;
				mastermind_set_essai_encours(controleur->mm,controleur->rg,boutons_couleurs);
			}
		}

		/* Evolution du texte du label "libelle_humour" en fonction des différents essais */
		if(mastermind_get_num_dernier_essai(controleur->mm) == 1)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nBrain is loading...\n\n-------------------------------------\n\nTu as 11 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 2)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nBrain still loading...\n\n-------------------------------------\n\nTu as 10 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 3)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nÇa m'en bouche un coin!\n\n-------------------------------------\n\nTu as 9 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 4)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\n4 couleurs à trouver,\nc'est pas si difficile!\n-------------------------------------\n\nTu as 8 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 5)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nRoooh je te sur-estimais!\n\n-------------------------------------\n\nTu as 7 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 6)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nLa prochaine fois,je te \nlaisse choisir la combi!\n-------------------------------------\n\nTu as 6 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 7)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nBon j'arrive, \nje vais me chercher un café!\n-------------------------------------\n\nTu as 5 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 8)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\n*...parti chercher son café...*\n\n-------------------------------------\n\nTu as 4 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 9)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nRe, toujours pas ?!\n\n-------------------------------------\n\nTu as 3 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 10)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\nJe t'aide ?\n\n-------------------------------------\n\nTu as 2 essais restants");
		}

		if(mastermind_get_num_dernier_essai(controleur->mm) == 11)
		{
			gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n\n-------------------------------------\n Je pense que ce jeu, \n n'est pas fait pour toi :(\n-------------------------------------\n\nTu as 1 essais restants");

		}


    /* On rentre dans ce "if" uniquement lorsque l'utilisateur a choisi la 4ème et dernière couleur de sa combinaison pour chacun de ses essais */
		if((controleur->rg)%4 == 0)
		{

      /* Ainsi, on peut désormais valider l'essai en cours */
			mastermind_valider_essai_encours(controleur->mm);

			/* Si l'utilisateur a trouvé la bonne combinaison en 12 essais ou moins, alors :
			   - on affiche la combinaison secrète (à la place des cercles vides avec un point d'interrogation au centre)
				 - on change le texte du "libelle_secret" en "GAGNÉE !"
				 - on change le texte du "libelle_humour" en "Coup de poker! ..." */
			if(controleur->mm->etat == ETAT_MM_GAGNE)
			{
				afficher_combinaison_secrete(controleur);
				gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n-------------------------------------\nCoup de poker !\n Mais fait moins \nque ça la prochaine fois!\n-------------------------------------");
				gtk_label_set_label (controleur->vue->libelle_secret,"GAGNÉE !");
			}

			/* Si l'utilisateur n'a pas trouvé la bonne combinaison même après 12 essais, alors :
			   - on affiche la combinaison secrète (à la place des cercles vides avec un point d'interrogation au centre)
				 - on change le texte du "libelle_secret" en "PERDUE !"
				 - on change le texte du "libelle_humour" en "Non..." */
			if(controleur->mm->etat == ETAT_MM_PERDU)
			{
				afficher_combinaison_secrete(controleur);
				gtk_label_set_label(controleur->vue->libelle_humour,"\n\n\n-------------------------------------\nBon on va dire que tu n'étais \npas échauffé aujourd'hui...\n-------------------------------------");
				gtk_label_set_label (controleur->vue->libelle_secret,"PERDUE !");
			}

      /* On réintialise le rang à 0 car on passe à l'essai suivant */
			controleur->rg = 0;

      /* Permet de récupérer le nombre de couleurs bien placées et le nombre de couleurs correctes de l'essai en cours */
			verif_correctes = mastermind_get_nb_couleurs_correctes(controleur->mm , mastermind_get_num_dernier_essai(controleur->mm));
			verif_bienplacees = mastermind_get_nb_couleurs_placees(controleur->mm,mastermind_get_num_dernier_essai(controleur->mm));

      /* Permet de remplacer les carrés vides de la grille de vérification par des carrés bleu (le nombre de carrés bleus représente alors le nombre de couleurs
			   correctes mais pas à la bonne place) */
			if(verif_correctes - verif_bienplacees > 0 )
			{
				for(int i = 0; i < verif_correctes - verif_bienplacees; ++i)
				{

					gtk_image_set_from_file(controleur->vue->images_grille_verification[controleur->nb_case - 4 + i],"fichiers/images/bleu_verif.png");
				}
			}

			/* Permet de remplacer les carrés vides de la grille de vérification par des carrés rouge (le nombre de carrés rouge représente alors le nombre de couleurs
				 bien placées) */
			if(verif_bienplacees > 0 )
			{

				for(int i = 0; i < verif_bienplacees; ++i)
				{

					gtk_image_set_from_file(controleur->vue->images_grille_verification[controleur->nb_case - 4 + verif_correctes - verif_bienplacees + i],"fichiers/images/rouge_verif.png");
				}
			}

		}

    /* Permet de remplacer les cercles vides de l'essai en cours par des cercles de la couleur choisie */
		if(boutons_couleurs == 1)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/rouge.png");
		}
		if(boutons_couleurs == 2)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/vert.png");
		}
		if(boutons_couleurs == 3)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/bleu.png");
		}
		if(boutons_couleurs == 4)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/violet.png");
		}
		if(boutons_couleurs == 5)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/orange.png");
		}
		if(boutons_couleurs == 6)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/jaune.png");
		}
		if(boutons_couleurs == 7)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/blanc.png");
		}
		if(boutons_couleurs == 8)
		{
			gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case-1],"fichiers/images/noir.png");
		}
	}
}



/* Cette fonction permet à l'utilisateur de pouvoir effacer une ou des couleurs de la combinaison qu'il est en train de saisir */
void effacer(GtkButton* b, ctrl_t* controleur)
{

	if(controleur->rg <= 4 && controleur->rg > 0)
	{
		/* pour effacer une couleur, il suffit seulement de superposer, par dessus, une image représentant un cercle vide */
		gtk_image_set_from_file(controleur->vue->images_grille_jeu[controleur->nb_case - 1],"fichiers/images/vide.png");

		--controleur->rg;
		--controleur->nb_case;

	}
}



/* Cette fonction permet de dévoiler, en fin de partie, la combinaison secrète en cas de victoire ou défaite de l'utilisateur */
void afficher_combinaison_secrete(ctrl_t *controleur)
{

	for(int i = 1; i < 5; ++i)
	{
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_NOIR)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/noir.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_BLEU)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/bleu.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_MAUVE)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/violet.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_ORANGE)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/orange.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_JAUNE)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/jaune.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_BLANC)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/blanc.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_VERT)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/vert.png");
		}
		if(mastermind_get_secret(controleur->mm,i) == COULEUR_ROUGE)
		{
			gtk_image_set_from_file(controleur->vue->images_combinaison_secrete[i - 1],"fichiers/images/rouge.png");
		}

	}
}
