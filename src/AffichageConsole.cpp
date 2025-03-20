#include "AffichageConsole.h"
#include <iostream>
#include <unistd.h>

using namespace std;

const int HAUTEUR = 5;
const int LARGEUR = 100;

AffichageConsole::AffichageConsole() {}

void AffichageConsole::afficher(WinTXT &win) {
    /*
    system("clear");

    // Initialisation de la grille (origine en haut à gauche)
    char grille[HAUTEUR][LARGEUR] = {};

    // Remplissage de la gille avec des caractères vides
    for (int i = 0; i < HAUTEUR; i++)
        for (int j = 0; j < LARGEUR; j++)
            grille[i][j] = ' ';

    // Placement le personnage
    int hauteurPerso = partie.getHauteurPerso();
    if (hauteurPerso >= 0 && hauteurPerso < HAUTEUR) {
        grille[HAUTEUR - 1 - hauteurPerso][5] = '@';
    }

    //Placement des obstacles
    for (Obstacle& obs : partie.getObstacles()) {
        if (obs.getX() >= 0 && obs.getX() < LARGEUR && obs.getY() >= 0 && obs.getY() < HAUTEUR) {
            grille[HAUTEUR - 1 - obs.getY()][obs.getX()] = 'X';
        }
    }

    
    for (Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();  // Largeur de l'obstacle
        int obsLongueur = obs.getLongueur(); // Longueur de l'obstacle

        // Vérification que l'obstacle ne sort pas de la grille
        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                // Vérification si la position (obsX + i, obsY + j) est dans les limites de la grille
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    grille[HAUTEUR - 1 - (obsY + j)][obsX + i] = 'X';  // Placer l'obstacle sur la grille
                }
            }
        }
    }

    //Placement des objets
    for (Objet& obj : partie.getObjets()) {
        if (obj.getX() >= 0 && obj.getX() < LARGEUR && obj.getY() >= 0 && obj.getY() < HAUTEUR) {
            grille[HAUTEUR - 1 - obj.getY()][obj.getX()] = 'o';
        }
    }

    cout << "Vies : " << partie.nbVies << endl;
    cout << "Distance : " << partie.distance << "m" << endl;
    cout << "Score : " << partie.score  << endl;

    // Affichage de la grille
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++)
            cout << grille[i][j];
        cout << endl;
    }

    */

    win.clear();

    // Remplissage de la gille avec des caractères vides
    for (int i = 0; i < LARGEUR; i++)
        for (int j = 0; j < HAUTEUR; j++)
            win.print(i, j, '-');

    // Placement du personnage
    int hauteurPerso = partie.getHauteurPerso();
    win.print(3, HAUTEUR - 1 - hauteurPerso, '@');

     //Placement des obstacles
     for (Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();

        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    win.print(obsX + i, HAUTEUR - 1 - (obsY + j), 'X');
                }
            }
        }
    }

    //Placement des objets
    for (Objet& obj : partie.getObjets()) {
        win.print(obj.getX(), HAUTEUR - 1 - obj.getY(), 'o');
    }

    char texte[] = "Vies : ";
    win.print(0, 0, texte);
    win.print(1, 0, partie.nbVies);

    win.draw();
}


void AffichageConsole::run() {
    termClear();
    WinTXT win(LARGEUR, HAUTEUR);
    int c;
    bool ok;
    win.clear();
    do 
    {       
        ok = partie.actionsAutomatiques(HAUTEUR, LARGEUR);

        c = win.getCh();
        switch (c)
        {
        case 'q':
            ok = false;
            break;

        case 'z':
            partie.actionClavier(z);
            break;

        default:
            break;
        }

        afficher(win);

        usleep(100000); // Pause (100ms)
    } while (ok);
    win.clear();
    

    cout << "Game Over ! Distance parcourue : " << partie.distance << endl;
    cout << "Score : " << partie.score;
}