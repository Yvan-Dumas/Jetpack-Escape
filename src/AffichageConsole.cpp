#include "AffichageConsole.h"
#include <iostream>
#include <unistd.h>
using namespace std;

const int HAUTEUR = 20;
const int LARGEUR = 30;

AffichageConsole::AffichageConsole() {}

void AffichageConsole::afficher() {
    system("clear");

    char grille[LARGEUR][HAUTEUR] = {};

    for (int i = 0; i < HAUTEUR; i++)
        for (int j = 0; j < LARGEUR; j++)
            grille[i][j] = ' ';

    // Placer le personnage
    grille[partie.getHauteurPerso()][2] = '@';

    for(Obstacle& obs : partie.getObstacles()){
        if(obs.getX() < LARGEUR) {
            grille[obs.getY()][obs.getX()] = 'X';
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