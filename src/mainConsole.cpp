#include <iostream>
#include "AffichageConsole.h"

using namespace std;

int main() {

    AffichageConsole aff;

    cout << "======================================" << endl;
    cout << "|                                    |" << endl;
    cout << "|          JETPACK ESCAPE            |" << endl;
    cout << "|                                    |" << endl;
    cout << "======================================" << endl;

    char choix;
    cout << "Choisissez votre mode jeu : " << endl;
    cout << "1 - Mode 1 joueur" << endl;
    cout << "2 - Mode 2 joueur" << endl;
    cout << "0 - quitter" << endl;
    cin >> choix;

    switch(choix) {
        case '1':
            aff.run();
            break;
        case '2':
            // ajouter bool 2 players.
            aff.run();
            break;
        default:
            break;
    }
    return 0;
}