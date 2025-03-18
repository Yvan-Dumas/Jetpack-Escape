 #include "Objet.h"
 #include <iostream>
 using namespace std;


 Objet::Objet(unsigned int id, int x, int  y,unsigned int  larg, unsigned int longueur )
    : idTypeObjet(id), x(x), y(y), largeur(larg), longueur(longueur) {}
 
 unsigned int Objet::collecterObjet(int hauteur) const {
     bool abscisse = (x-longueur<0) && (x + longueur >= 0) ; 
     bool ordonnee = (y + largeur > hauteur) && (y - largeur <= hauteur);
     if (abscisse && ordonnee){
        return idTypeObjet;
     }
     return 100;
 }

 void Objet::mettreAJourPosition(int vitesse) {
     x -= 0.5*vitesse; ///< Déplace l'objet vers la gauche en fonction de la vitesse du jeu
 }

 int Objet::getX() {return x;}
 int Objet::getY() {return y;}
 