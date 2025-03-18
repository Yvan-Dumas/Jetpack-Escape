 #include "Objet.h"
 #include <iostream>
 using namespace std;


 Objet::Objet() {
    idTypeObjet = 0;
 }
 
 unsigned int Objet::collecterObjet(int hauteur) const {
     bool abscisse = (x-longueur<0) && (x + longueur >= 0) ; 
     bool ordonnee = (y + largeur > hauteur) && (y - largeur <= hauteur);
     if (abscisse && ordonnee){
        return idTypeObjet;
     }
     return 0;
 }

 void Objet::mettreAJourPosition(int vitesse) {
     x -= 0.5*vitesse; ///< Déplace l'objet vers la gauche en fonction de la vitesse du jeu
 }
 