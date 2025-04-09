#include <iostream>
#include "AffichageConsole.h"

using namespace std;

int main() {
    Personnage::testPersonnage();
    Objet::testObjet();
    Obstacle::testObstacle();
    Partie::testPartie();

    return 0;
}