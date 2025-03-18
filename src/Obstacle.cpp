 #include "Obstacle.h"
 #include <iostream>
 using namespace std;


 Obstacle::Obstacle(unsigned int id, int x, int  y, unsigned int  larg, unsigned int longueur ) 
    : idTypeObstacle(id), x(x), y(y), largeur(larg), longueur(longueur) {}
 
 /*bool Obstacle::collisionObstacle(int hauteur) const {
     bool abscisse = (x-longueur<0) && (x + longueur >= 0) ; 
     bool ordonnee = (y + largeur > hauteur) && (y - largeur <= hauteur);
     return abscisse || ordonnee ;
 }*/
 bool Obstacle::collisionObstacle(int hauteur) const {
    // Le personnage commence à x = 5
    bool abscisse = x == 5; // Vérifie si le personnage, à x=5, entre dans la zone horizontale de l'obstacle
    bool ordonnee = y == hauteur; // Vérifie si l'obstacle se trouve dans la plage de la hauteur donnée
    return abscisse && ordonnee; // Si une collision est détectée dans l'une des deux directions
}

 void Obstacle::mettreAJourPosition(int vitesse) {
     x -= 1*vitesse; ///< Déplacement de l'obstacle vers la gauche (ajusté selon la vitesse du jeu)
 }

 int Obstacle::getX() {return x;}

 int Obstacle::getY() {return y;}
