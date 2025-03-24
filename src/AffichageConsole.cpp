#include "AffichageConsole.h"
#include <iostream>
#include <unistd.h>

using namespace std;

const int HAUTEUR = 5;
const int LARGEUR = 100;

AffichageConsole::AffichageConsole() {}

void AffichageConsole::afficher(WinTXT &win) {

    win.clear();

    // Remplissage de la gille avec des caractères vides
    for (int i = 0; i < LARGEUR; i++) {
        for (int j = 0; j < HAUTEUR; j++) {
            win.print(i, j+1, ' ');
        }
    }

    // Affichage du toit
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,0,'_');
    }
    
    // Placement du personnage
    int hauteurPerso = partie.getHauteurPerso();
    win.print(5, HAUTEUR - hauteurPerso, '@');

    //Placement des obstacles
    for (Obstacle& obs : partie.getObstacles()) {
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
    for (Objet& obj : partie.getObjets()) {
        win.print(obj.getX(), HAUTEUR - obj.getY(), 'o');
    }

    // Affichage du sol
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,6,'-');
    }

    win.draw();
    cout << "Vies : ";
    cout << partie.nbVies << endl;
    cout << "Distance parcourue : " << partie.distance << "m" << endl;
    cout << "Vous avez récolté " << partie.score << " pièces" <<endl;
}


void AffichageConsole::run() {
    termClear();
    WinTXT win(LARGEUR, HAUTEUR+3);
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
            partie.actionsClavier('z', HAUTEUR-1);
            break;

        default:
            break;
        }

        afficher(win);

        usleep(100000); // Pause (100ms)
    } while (ok);
    

    cout << "Game Over ! Distance parcourue : " << partie.distance << "m" << endl;
    cout << "Score : " << partie.score << endl;
}