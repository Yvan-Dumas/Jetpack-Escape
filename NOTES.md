0# LIFAPCD - jetpack escape

@TODO: revoir proba apparition
--> trop de vies.0.

; 

-diagramme des classes
-diagramme de gant
- mode 2 joueurs bug
- qu'afficher en version 2 joueurs quand ils sont superposés ?

- bug menu aide


@TODO: MODE 2 JOUEUR A METTRE A JOUR
@TODO: MODE CONSOLE A METTRE A JOUR
--> ajouter appel à acheter_pieces

-valgrind version finale

 

Questions au prof:
- affichage adaptatif ? 
- faut il refaire le cahier des charges ?
- diagramme des classes (sdl sprite ?)
- ce n'est pas génant de ne pas faire de classe pour les menus
- test regression sur sdl ? et sur affichage console ?



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
