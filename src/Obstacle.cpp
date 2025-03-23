#include "Obstacle.h"
#include <iostream>
using namespace std;


Obstacle::Obstacle(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur ) 
    : idTypeObstacle(id), x(x), y(y), largeur(largeur), longueur(longueur) {}
 
bool Obstacle::collisionObstacle(int hauteur) const {
    bool abscisse = (x < 5 + 1) && (x + largeur > 5); 
    bool ordonnee = (y == hauteur);
    return abscisse && ordonnee;
}

void Obstacle::mettreAJourPosition(int vitesse) {
    x -= 1*vitesse; ///< Déplacement de l'obstacle vers la gauche (ajusté selon la vitesse du jeu)
}

int Obstacle::getX() const {
    return x;
}

int Obstacle::getY() const {
    return y;
}

int Obstacle::getLargeur() const {
    return largeur;
}

int Obstacle::getLongueur() const {
    return longueur;
}
