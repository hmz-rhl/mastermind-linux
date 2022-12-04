#include "vue_mastermind.h"
#include <gtk/gtk.h>


/*______________________________________DÉFINITION DES FONCTIONS______________________________________*/


/* Cette fonction va permettre de créer tous les widgets de l'interface (fenêtre, boutons, grille, boite...) */
void vue_mastermind_creation_widgets(vue_mastermind* une_vue_mastermind)
{
  int i = 0;    /*  Déclaration des variables techniques	*/

  /* CRÉATION DE LA FENÊTRE */
  une_vue_mastermind->fenetre = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(une_vue_mastermind->fenetre), "Maître d'esprit ©");      /* Titre de la fenêtre */
  gtk_window_set_default_size(GTK_WINDOW(une_vue_mastermind->fenetre), 500, 100);          /* Redimensionnement de la fenêtre */


  // CRÉATION DES GRILLES DU JEU //
  une_vue_mastermind->grille_de_jeu = (GtkGrid*)gtk_grid_new();
  une_vue_mastermind->grille_boutons_couleur = (GtkGrid*)gtk_grid_new();
  une_vue_mastermind->grille_boutons_menu = (GtkGrid*)gtk_grid_new();
  une_vue_mastermind->grille_de_verification = (GtkGrid*)gtk_grid_new();
  une_vue_mastermind->grille_secrete = (GtkGrid*)gtk_grid_new();


  // CRÉATION et INITIALISATION DES LIBELLES //
  une_vue_mastermind->libelle_secret = (GtkLabel*)gtk_label_new("Configuration secrète...");
  une_vue_mastermind->libelle_humour = (GtkLabel*)gtk_label_new("\n\n\n\n-------------------------------------\nPrêt ? C'est parti !\n\n-------------------------------------\nTu as 12 essais");


  // CRÉATION et INITIALISATION DES BOITES //
  une_vue_mastermind->boite_principale = (GtkBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  une_vue_mastermind->boite_secondaire = (GtkBox*)gtk_box_new(GTK_ORIENTATION_VERTICAL,10);


  // CRÉATION DES BOUTONS DE CHOIX DE COULEURS ET INITIALISATION DE LEURS LIBELLES //
  une_vue_mastermind->boutons_couleur[0] = (GtkButton*)gtk_button_new_with_label("Rouge");
  une_vue_mastermind->boutons_couleur[1] = (GtkButton*)gtk_button_new_with_label("Vert");
  une_vue_mastermind->boutons_couleur[2] = (GtkButton*)gtk_button_new_with_label("Bleu");
  une_vue_mastermind->boutons_couleur[3] = (GtkButton*)gtk_button_new_with_label("Mauve");
  une_vue_mastermind->boutons_couleur[4] = (GtkButton*)gtk_button_new_with_label("Orange");
  une_vue_mastermind->boutons_couleur[5] = (GtkButton*)gtk_button_new_with_label("Jaune");
  une_vue_mastermind->boutons_couleur[6] = (GtkButton*)gtk_button_new_with_label("Blanc");
  une_vue_mastermind->boutons_couleur[7] = (GtkButton*)gtk_button_new_with_label("Noir");


  // CRÉATION DES IMAGES REPRÉSENTANTS LES COULEURS ASSOCIÉES AUX BOUTONS (À DROITE DES BOUTONS DE CHOIX DE COULEURS) //
  une_vue_mastermind->images_boutons_couleur[0] = (GtkImage*)gtk_image_new_from_file("fichiers/images/rouge.png");
  une_vue_mastermind->images_boutons_couleur[1] = (GtkImage*)gtk_image_new_from_file("fichiers/images/vert.png");
  une_vue_mastermind->images_boutons_couleur[2] = (GtkImage*)gtk_image_new_from_file("fichiers/images/bleu.png");
  une_vue_mastermind->images_boutons_couleur[3] = (GtkImage*)gtk_image_new_from_file("fichiers/images/violet.png");
  une_vue_mastermind->images_boutons_couleur[4] = (GtkImage*)gtk_image_new_from_file("fichiers/images/orange.png");
  une_vue_mastermind->images_boutons_couleur[5] = (GtkImage*)gtk_image_new_from_file("fichiers/images/jaune.png");
  une_vue_mastermind->images_boutons_couleur[6] = (GtkImage*)gtk_image_new_from_file("fichiers/images/blanc.png");
  une_vue_mastermind->images_boutons_couleur[7] = (GtkImage*)gtk_image_new_from_file("fichiers/images/noir.png");


  // CRÉATION DES IMAGES REPRÉSENTANTS LES CERCLES DE LA GRILLE DE JEU ET INITIALISATION DE CES CERCLES À "VIDE"//
  for(i = 0 ; i < 48 ; ++i)
  {
    /* On affecte, à chaque élément du tableau "images_grille_jeu", une image (plus précisémént, ici il s'agit ici d'un cercle vide) */
    une_vue_mastermind->images_grille_jeu[i] = (GtkImage*)gtk_image_new_from_file("fichiers/images/vide.png");
  }


  // CRÉATION DES IMAGES REPRÉSENTANTS LES CARRÉS DE LA GRILLE DE VÉRIFICATION ET INITIALISATION DE CES CARRÉS À "VIDE" //
  for(i = 0 ; i < 48 ; ++i)
  {
    /* On affecte, à chaque élément du tableau "images_grille_verification", une image (plus précisémént, ici il s'agit ici d'un carré vide) */
    une_vue_mastermind->images_grille_verification[i] = (GtkImage*)gtk_image_new_from_file("fichiers/images/vide_verif.png");
  }


  // CRÉATION DES IMAGES REPRÉSENTANTS LES CERCLES DE LA GRILLE DE VÉRIFICATION ET INITIALISATION DE CES CERCLES À "POINT D'INTERROGATION" //
  for(i = 0 ; i < 4 ; ++i)
  {
    /* On affecte, à chaque élements du tableau "images_combinaison_secrete", une image (plus précisémént, il s'agit ici d'un cercle avec un point d'interrogation au centre) */
    une_vue_mastermind->images_combinaison_secrete[i] = (GtkImage*)gtk_image_new_from_file("fichiers/images/interrogation.png");
  }


  // CRÉATION DES BOUTONS "bouton_quitter", "bouton_effacer", "bouton_nouvelle_partie", ET AJOUT DE CES BOUTONS DANS "grille_boutons_menu" //
  une_vue_mastermind->bouton_quitter = (GtkButton*)gtk_button_new_with_mnemonic("_Quitter");
  une_vue_mastermind->bouton_effacer = (GtkButton*)gtk_button_new_with_mnemonic("_Effacer");
  une_vue_mastermind->bouton_nouvelle_partie = (GtkButton*)gtk_button_new_with_mnemonic("_Nouvelle partie");
}

/* Cette fonction va se charger d'attacher, aux différentes grilles de l'interface, des images ou des boutons */
void vue_mastermind_grid_attach(vue_mastermind* une_vue_mastermind)
{
  int i = 0;    /*  Déclaration des variables techniques	*/

  // REMPLISSAGE DE "grille_de_jeu" AVEC LES "images_grille_jeu" //
  for(i = 0 ; i < 48 ; ++i)
  {

    /* Ajout de chaque éléments de "images_grille_jeu" dans "grille_de_jeu" */
    gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_de_jeu), GTK_WIDGET(une_vue_mastermind->images_grille_jeu[i]), i%4, (int)(i/4),1,1);

  }


  // REMPLISSAGE DE "grille_de_verification" AVEC LES "images_grille_verification" //
  for(i = 0 ; i < 48 ; ++i)
  {

    /* Ajout de chaque éléments de "images_grille_verification" dans "grille_de_verification" */
    gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_de_verification), GTK_WIDGET(une_vue_mastermind->images_grille_verification[i]), i%2,(int)i/2 ,1,1);
  }


  /* Ajouts de tous les "boutons_couleur" et "images_boutons_couleur" dans "grille_boutons_couleur" */
  for (i = 0 ; i < 8 ; i++)
  {

    gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_boutons_couleur),GTK_WIDGET((une_vue_mastermind->boutons_couleur)[i]),0,i,1,1);
    gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_boutons_couleur),GTK_WIDGET((une_vue_mastermind->images_boutons_couleur)[i]),1,i,1,1);

  }

  // REMPLISSAGE DE "grille_secrete" AVEC LES "images_combinaison_secrete" //
  for(i = 0 ; i < 4 ; ++i)
  {
    /* Ajout des images à la grille */
    gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_secrete), GTK_WIDGET(une_vue_mastermind->images_combinaison_secrete[i]), i,0,1,1);
  }


  // REMPLISSAGE DE "grille_boutons_menu" AVEC LES "bouton_quitter", "bouton_effacer" et "bouton_nouvelle_partie" //
  gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_boutons_menu),GTK_WIDGET(une_vue_mastermind->bouton_quitter),0,2,1,1);
  gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_boutons_menu),GTK_WIDGET(une_vue_mastermind->bouton_effacer),0,0,1,1);
  gtk_grid_attach(GTK_GRID(une_vue_mastermind->grille_boutons_menu),GTK_WIDGET(une_vue_mastermind->bouton_nouvelle_partie),0,1,1,1);

}

/* Cette fonction va se charger de l'inclusion des widgets dans les différentes boites créees */
void vue_mastermind_inclusion_widgets(vue_mastermind* une_vue_mastermind)
{
  // INCLUSION DE "boite_principale" DANS LA FENETRE //
  gtk_container_add(GTK_CONTAINER(une_vue_mastermind->fenetre), GTK_WIDGET(une_vue_mastermind->boite_principale));


  // INCLUSION DE "grille_de_jeu" DANS "boite_principale" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_principale), GTK_WIDGET(une_vue_mastermind->grille_de_jeu), TRUE, TRUE, 2);


  // INCLUSION DE "grille_de_verification" DANS "boite_principale" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_principale), GTK_WIDGET(une_vue_mastermind->grille_de_verification), TRUE, TRUE, 2);


  // INCLUSION DE "grille_boutons_couleur" DANS "boite_principale" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_principale), GTK_WIDGET(une_vue_mastermind->grille_boutons_couleur), TRUE, TRUE, 2);


  // INCLUSION DE "grille_boutons_menu" DANS "boite_secondaire" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_secondaire), GTK_WIDGET(une_vue_mastermind->grille_boutons_menu), FALSE, FALSE, 2);


  // INCLUSION DE "libelle_secret" DANS "boite_secondaire" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_secondaire), GTK_WIDGET(une_vue_mastermind->libelle_secret), FALSE, FALSE, 2);


  // INCLUSION DE "grille_secrete" DANS "boite_secondaire" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_secondaire), GTK_WIDGET(une_vue_mastermind->grille_secrete), FALSE, FALSE, 2);


  // INCLUSION DE "libelle_humour" DANS "boite_secondaire"//
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_secondaire), GTK_WIDGET(une_vue_mastermind->libelle_humour), FALSE, FALSE, 2);


  // INCLUSION DE "boite_secondaire" DANS "boite_principale" //
  gtk_box_pack_start(GTK_BOX(une_vue_mastermind->boite_principale), GTK_WIDGET(une_vue_mastermind->boite_secondaire), FALSE, FALSE, 2);

}

/* Cette "petite" fonction (mais très importante!) permet simplement d'afficher la fenêtre et tous les widgets qu'elle contient (boutons, labels, etc...) */
void vue_mastermind_affichage_widgets(vue_mastermind* une_vue_mastermind)
{
  // AFFICHAGE DE TOUS LES WIDGETS DANS L'INTERFACE //
  gtk_widget_show_all(GTK_WIDGET(une_vue_mastermind->fenetre));

}

/* Cette fonction permet à l'utilisateur de fermer la fenêtre de l'interface et d'arrêter la boucle de GTK */
void vue_mastermind_fermeture_interface(vue_mastermind* une_vue_mastermind)
{

  g_signal_connect(G_OBJECT(une_vue_mastermind->fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

}
