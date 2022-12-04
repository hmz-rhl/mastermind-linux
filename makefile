# ______________ parametres de compilation
CFLAGS= -Wall --pedantic

VERSION= gtk+-3.0
CGTK= `pkg-config $(VERSION) --cflags`
LGTK= `pkg-config $(VERSION) --libs`

# ______________ excecutables
all: mastermind.exe

# mastermind.exe
mastermind.exe: main.o vue_mastermind.o controleur_mastermind.o combinaison.o stat-essai.o mastermind.o
	gcc $^ -o $@ $(LGTK)

main.o: fichiers/main.c fichiers/contrôleur/controleur_mastermind.h fichiers/vue/vue_mastermind.h
	gcc -c $< -o $@ $(CFLAGS) $(CGTK)

# ______________ objets bibliothèque

# vue
vue_mastermind.o: fichiers/vue/vue_mastermind.c fichiers/vue/vue_mastermind.h
	gcc -c $< -o $@ $(CFLAGS) $(CGTK)

# controleur
controleur_mastermind.o: fichiers/contrôleur/controleur_mastermind.c fichiers/contrôleur/controleur_mastermind.h fichiers/modèle/mastermind.h fichiers/vue/vue_mastermind.h
	gcc -c $< -o $@ $(CFLAGS) $(CGTK)

# mastermind
mastermind.o: fichiers/modèle/mastermind.c fichiers/modèle/mastermind.h fichiers/modèle/combinaison.h fichiers/modèle/stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)

# combinaison
combinaison.o: fichiers/modèle/combinaison.c fichiers/modèle/combinaison.h
	gcc -c $< -o $@ $(CFLAGS)

# stat-essai
stat-essai.o: fichiers/modèle/stat-essai.c fichiers/modèle/stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)


# ______________ nettoyage
clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf *.exe

