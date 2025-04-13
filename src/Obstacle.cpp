#include "Obstacle.h"
#include <iostream>
#include <cassert>
using namespace std;


Obstacle::Obstacle(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur ) 
    : idTypeObstacle(id), x(x), y(y), largeur(largeur), longueur(longueur) {}
 

bool Obstacle::collisionObstacle(int hauteur) const {
    bool abscisse = (x <= 5) && (x + largeur >= 5); // Collision horizontale (coordonnée x = 5 fixe du personnage)
    bool ordonnee = (y <= hauteur) && (y + longueur > hauteur); // Collision verticale en fonction du paramètre hauteur
    return abscisse && ordonnee;
    }
    

void Obstacle::mettreAJourPosition() {
    x -= 1; // L'obstacle se déplace d'une unité de jeu vers la gauche
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

unsigned int Obstacle::getID() const {
    return idTypeObstacle;
}

void Obstacle::testObstacle() {
    cout << "Début des tests pour la classe Obstacle" << endl;

    // Création d'un obstacle
    Obstacle obs(1, 5, 10, 2, 3);

    // Vérification des données membres
    assert(obs.getX() == 5 && "Test échoué : position X incorrecte");
    assert(obs.getY() == 10 && "Test échoué : position Y incorrecte");
    assert(obs.getLargeur() == 2 && "Test échoué : largeur incorrecte");
    assert(obs.getLongueur() == 3 && "Test échoué : longueur incorrecte");

    // Test de collision : le personnage est à la même position y et a la même hauteur
    assert(obs.collisionObstacle(10) && "Test échoué : on attendait une collision");

    // Pas de collision : personnage trop bas
    assert(!obs.collisionObstacle(20) && "Test échoué : on attendait pas de collision");

    // Pas de colision : position x décalée
    Obstacle obs2(2, 6, 10, 20, 30);
    assert(!obs2.collisionObstacle(10) && "Test échoué : on attendait pas de collision");

    // Test de mise à jour de la position
    obs2.mettreAJourPosition();
    assert(obs2.getX() == 5 && "Test échoué : mauvaise position");

    cout << "Tous les tests ont réussi !" << endl;
}