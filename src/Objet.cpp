 #include "Objet.h"
 #include <iostream>
 using namespace std;


 Objet::Objet(unsigned int id, int x, int  y,unsigned int  largeur, unsigned int longueur )
    : idTypeObjet(id), x(x), y(y), largeur(largeur), longueur(longueur) {}
 
 unsigned int Objet::collecterObjet(int hauteur) const {
    bool abscisse = x == 5; // 5 correspond à la position x du personnage
    bool ordonnee = y == hauteur;
    if (abscisse && ordonnee){
       return idTypeObjet;
    }
    return 100; // 100 indique que le perosnnage n'est pas en contact avec un objet
 }

void Objet::mettreAJourPosition(int vitesse) {
    x -= 0.5*vitesse;
 }

int Objet::getX() const {
    return x;
}

int Objet::getY() const {
    return y;
}
 