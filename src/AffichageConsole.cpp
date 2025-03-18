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

    for (int i = 0; i < LARGEUR; i++)
        for (int j = 0; j < HAUTEUR; j++)
            grille[i][j] = ' ';

    // Placer le personnage
    grille[0][partie.getHauteurPerso()] = '@';

    for(const Obstacle& obs : partie.getObstacles()){
        if(obs.getX() < LARGEUR) {
            grille[obs.getX()][obs.getY()] = 'X'
        }
    }

    cout << "Vies : " << partie.nbVies << endl;
    cout << "Distance : " << partie.distance << "m" << endl;
    cout << "Score : " << partie.score  << endl;

    for (int i = 0; i < LARGEUR; i++) {
        for (int j = 0; j < HAUTEUR; j++)
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