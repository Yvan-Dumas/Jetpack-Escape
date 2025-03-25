#include "AffichageConsole.h"
#include <iostream>
#include <unistd.h>
#include <iomanip>

using namespace std;

const int HAUTEUR = 5;
const int LARGEUR = 100;

AffichageConsole::AffichageConsole() {}

void AffichageConsole::afficher(WinTXT &win) {
    win.clear();

    // Remplissage de la gille avec des caractères vides
    for (unsigned int i = 0; i < LARGEUR; i++) {
        for (unsigned int j = 0; j < HAUTEUR; j++) {
            win.print(i, j+1, ' ');
        }
    }

    // Affichage de la bordure supérieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,0,'_');
    }
    
    // Placement du personnage
    int hauteurPerso = partie.getHauteurPerso();
    win.print(5, HAUTEUR - hauteurPerso, '@');

     //Placement des obstacles
     for (const Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();

        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    win.print(obsX + i, HAUTEUR - (obsY + j), 'X');
                }
            }
        }
    }

    //Placement des objets
    for (const Objet& obj : partie.getObjets()) {
        switch (obj.getID()){
        case 1:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'O');       
        break;
        case 2:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'C');
        break;
        case 3:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'V');
        default:
        break;
        } 

    }

    // Affichage de la bordure inférieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,6,'-');
    }

    win.draw();

    cout << "Vies : " << partie.nbVies << endl;
    cout << "Carburant : [";
    unsigned int longueurRemplie = ( partie.getCarburant() * 16) / 5;
    for (unsigned int i = 0; i < 16; i++) {
        if (i < longueurRemplie) {
            cout << "="; // Partie remplie
        } else {
            cout << " "; // Partie vide
        }
    }
    cout << "] " << std::fixed << std::setprecision(2) << partie.getCarburant() << "L" << "/" << 5 << "L" << endl;
    cout << "Distance parcourue : " << partie.distance << "m" << endl;
    cout << "Vous avez récolté " << partie.score << " pièces" <<endl;
}

void AffichageConsole::run() {
    termClear();
    WinTXT window(LARGEUR, HAUTEUR+3);
    int c;
    bool ok;
    window.clear();
    do 
    {       
        ok = partie.actionsAutomatiques(HAUTEUR, LARGEUR);

        c = window.getCh();

        switch (c)
        {
        case 'q':
            ok = false;
            break;

        case 'z':
            partie.actionsClavier('z', HAUTEUR-1);
            break;

        default:
            break;
        }

        afficher(window);

        usleep(100000); // Pause (100ms)
    } while (ok);
    window.clear();
    

    cout << "Game Over ! Distance parcourue : " << partie.distance << "m" << endl;
    cout << "Score : " << partie.score << endl;
}

