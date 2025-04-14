# LIFAPCD - jetpack escape

-revoir proba apparition
-afficher mode 2 joueurs
-affichage adaptatif ?
-diagramme des classes (sdl sprite ?)
-cahier des charges ?
-mode 2joueurs clavier
-initialisation variables affGraph dans le constructeur ?
-Pièces récoltées game over ?
- mode 2 joueurs bug
-modifier run2Joueurs et actions automatiques2J
-valgrind version finale

- affichage console bug !!
car durée d'appel à la fonction de montée (récupération des touches) trop lent par rapport à actionsAutomatiques (-->gravité)
 

Questions au prof:
- affichage adaptatif ?
- faut il refaire le cahier des charges ?
- diagramme des classes (sdl sprite ?)



modifier: 

char WinTXT::getCh()
{ // lire un caractere si une touche a ete pressee
    char touche = 0;
#ifdef _WIN32
    if (kbhit())
    {
        DWORD mode;
        DWORD n;
        HANDLE consoleI = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(consoleI, &mode);
        SetConsoleMode(consoleI, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
        ReadConsole(consoleI, &touche, 1, &n, NULL);
    }
#else
    if (kbhit())
        touche = fgetc(stdin);
        viderBufferClavier();
#endif
    return touche;
}


DA:
1. Style graphique
Pixel art low-res 32x32
Palette : gris foncé, rouille, rouge métro, lumière fluorescente verte pâle
Typographie : Pixelated, façon LED d’affichage de stations

2. Menu principal
Fond : léger effet de flou de tunnel, ombrage de néons
Hover/selection : texte clignote comme un panneau LED défectueux

3. Transitions
Fondu “vers la gauche” comme un train qui passe
Sons : bruit de métro, bip d’ouverture de porte

4. Éléments bonus
Des graffitis pixelisés animés (tag style "PRESS START")
Petits rats courant dans le bas du menu en boucle
Affichage d'une station de métro fictive avec nom aléatoire

fonts : 
https://fonts.google.com/specimen/Press+Start+2P
https://fonts.google.com/specimen/VT323
https://fr.fonts2u.com/pixel-lcd-7.police?ptext=JETPACK+ESCAPE

https://craftpix.net/freebies/free-gui-for-cyberpunk-pixel-art/?srsltid=AfmBOorN88IlLcF5GHKjpGvR_oqWq6rgVs0UsseLV8I1AnVcNTF66zhI
https://closeluca.itch.io/heart?download
