 #include "Obstacle.h"
 #include <iostream>
 using namespace std;


 Obstacle::Obstacle(unsigned int id, int x, int  y, unsigned int  larg, unsigned int longueur ) 
    : idTypeObstacle(id), x(x), y(y), largeur(larg), longueur(longueur) {}
 
 bool Obstacle::collisionObstacle(int hauteur) const {
     bool abscisse = (x-longueur<0) && (x + longueur >= 0) ; 
     bool ordonnee = (y + largeur > hauteur) && (y - largeur <= hauteur);
     return abscisse && ordonnee ;
 }
 void Obstacle::mettreAJourPosition(int vitesse) {
     x -= 1*vitesse; ///< Déplacement de l'obstacle vers la gauche (ajusté selon la vitesse du jeu)
 }

 int Obstacle::getX() {return x;}

 int Obstacle::getY() {return y;}

 int Obstacle::getLargeur() {return largeur;}
 int Obstacle::getLongueur() {return longueur;}
