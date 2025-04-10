#include "Obstacle.h"
#include <iostream>
#include <cassert>
using namespace std;


Obstacle::Obstacle(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur ) 
    : idTypeObstacle(id), x(x), y(y), largeur(largeur), longueur(longueur) {}
 
bool Obstacle::collisionObstacle(int hauteur) const {
        bool abscisse = (x <= 5) && (x + largeur >= 5); 
        bool ordonnee = (y <= hauteur) && (y + longueur > hauteur);
        return abscisse && ordonnee;
    }
    

void Obstacle::mettreAJourPosition() {
    x -= 1; ///< Déplacement de l'obstacle vers la gauche
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
    cout<<"Début des test pour Obstacle"<<endl;
 // Test du constructeur
 Obstacle obs(1, 5, 10, 20, 30);
    
 // Vérification de la position initiale et des dimensions
 assert(obs.getX() == 5 && "Test échoué : La position X initiale n'est pas correcte");
 assert(obs.getY() == 10 && "Test échoué : La position Y initiale n'est pas correcte");
 assert(obs.getLargeur() == 20 && "Test échoué : La largeur de l'obstacle n'est pas correcte");
 assert(obs.getLongueur() == 30 && "Test échoué : La longueur de l'obstacle n'est pas correcte");
 
 // Test de la méthode collisionObstacle
 // Test de collision lorsque l'obstacle est à la position x=5, y=10, et que le personnage est à x=5, y=10
 assert(obs.collisionObstacle(10) == true && "Test échoué : Collision attendue mais non détectée");
 
 // Test de non-collision lorsque le personnage est à y=20 (différent de la position y de l'obstacle)
 assert(obs.collisionObstacle(20) == false && "Test échoué : Aucune collision ne devrait être détectée à cette position");
 
 // Test de non-collision lorsque l'obstacle ne touche pas le personnage (par exemple x=6)
 Obstacle obs2(2, 6, 10, 20, 30);
 assert(obs2.collisionObstacle(10) == false && "Test échoué : Aucune collision ne devrait être détectée à cette position");

 // Test de la méthode mettreAJourPosition
 obs.mettreAJourPosition();
 assert(obs.getX() == -5 && "Test échoué : La position X après mise à jour n'est pas correcte");

 // Test avec une position hors de l'intervalle attendu pour collision
 obs.mettreAJourPosition(); // L'obstacle devrait se déplacer encore
 assert(obs.getX() == -25 && "Test échoué : La position X après seconde mise à jour n'est pas correcte");
 
 // Si tout passe, on affiche un message de succès
 cout << "Tous les tests ont réussi !" << endl;
}