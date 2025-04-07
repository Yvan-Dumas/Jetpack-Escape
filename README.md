# LIFAPCD - jetpack escape

-modifier cmakelist pour installer les bibliothèques toutes seules 
-pb menu --> fait
-affichager mode 2 joueurs
-son
-pb colissions -- > fait
si les trucs se superposent en réalité ils ne sont pas superposé c'est juste l'affichage qui a du retard
-textes --> fait version pas beau
-titre pendant 5 secondes au début? --> il faudrait passer le tempsinit dans affichage

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