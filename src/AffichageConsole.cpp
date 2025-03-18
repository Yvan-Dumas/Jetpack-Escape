#include "AffichageConsole.h"
#include <iostream>
#include <unistd.h>
using namespace std;

const int HAUTEUR = 5;
const int LARGEUR = 100;

AffichageConsole::AffichageConsole() {}

void AffichageConsole::afficher() {
    system("clear");

    // Initialisation de la grille (origine en haut à gauche)
    char grille[HAUTEUR][LARGEUR] = {};

    for (int i = 0; i < HAUTEUR; i++)
        for (int j = 0; j < LARGEUR; j++)
            grille[i][j] = ' ';

    // Placer le personnage
    int hauteurPerso = partie.getHauteurPerso();
    if (hauteurPerso >= 0 && hauteurPerso < HAUTEUR) {
        grille[HAUTEUR - 1 - hauteurPerso][5] = '@';
    }

    for (Obstacle& obs : partie.getObstacles()) {
        if (obs.getX() >= 0 && obs.getX() < LARGEUR && obs.getY() >= 0 && obs.getY() < HAUTEUR) {
            grille[HAUTEUR - 1 - obs.getY()][obs.getX()] = 'X';
        }
    }

    cout << "Vies : " << partie.nbVies << endl;
    cout << "Distance : " << partie.distance << "m" << endl;
    cout << "Score : " << partie.score  << endl;

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++)
            cout << grille[i][j];
        cout << endl;
    }
}


void AffichageConsole::run() {
    while (partie.lancerPartie() == true)
    {
        afficher();
        usleep(100000); // Pause (100ms)
    }

    cout << "Game Over ! Distance parcourue : " << partie.distance << endl;
    cout << "Score : " << partie.score;
}