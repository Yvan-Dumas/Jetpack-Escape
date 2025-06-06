#include <iostream>
#include "AffichageConsole.h"

using namespace std;

int main() {
    AffichageConsole aff;
    string record = aff.getRecord();

    cout << "                   =========================================================" << endl;
    cout << "                   |                                                       |" << endl;
    cout << "                   |                     JETPACK ESCAPE                    |" << endl;
    cout << "                   |                                                       |" << endl;
    cout << "                   =========================================================" << endl << endl;

    char choix;
    cout << "                   Record: " << record << "m" << endl;
    cout << "                   Choisissez votre mode jeu : " << endl;
    cout << "                   1 - Mode 1 joueur" << endl;
    cout << "                   2 - Mode 2 joueur" << endl;
    cout << "                   0 - quitter" << endl << endl ;
    cout << "                   =========================================================" << endl;
    cout << "                   |    @ : Le joueur, c'est vous                          |" << endl;
    cout << "                   |    X : Un obstacle, à éviter !                        |" << endl;
    cout << "                   |    o : Une pièce                                      |" << endl;
    cout << "                   |    C : Du carburant                                   |" << endl;
    cout << "                   |    V : Une vie                                        |" << endl;
    cout << "                   =========================================================" << endl;
    cin >> choix;
    switch(choix) {
        case '1':
            aff.run();
            break;
        case '2':
            aff.run2Joueurs();
            break;
        default:
            break;
    }
    return 0;
}