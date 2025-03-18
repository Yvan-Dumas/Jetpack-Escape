 #include "Obstacle.h"
 #include <iostream>
 using namespace std;


 Obstacle::Obstacle() {
    idTypeObstacle = 0 ;
}
 
 bool Obstacle::collisionObstacle(int hauteur) const {
     bool abscisse = (x-longueur<0) && (x + longueur >= 0) ; 
     bool ordonnee = (y + largeur > hauteur) && (y - largeur <= hauteur);
     return abscisse && ordonnee ;
 }
 void Obstacle::mettreAJourPosition(int vitesse) {
     x -= 1*vitesse; ///< Déplacement de l'obstacle vers la gauche (ajusté selon la vitesse du jeu)
 }

