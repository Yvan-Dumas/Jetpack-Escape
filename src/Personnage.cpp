/**
 *@file Personnage.cpp
 *@brief Implémentation de la classe personnage
 */

#include <iostream>
#include "Personnage.h"

using namespace std;

Personnage::Personnage() {
    hauteur = 0;
    velociteY = 0;
    carburant = 5;
}

void Personnage::setHauteur(unsigned int y){
    hauteur = y;
}

unsigned int Personnage::getHauteur() const {
    return hauteur;
}

void Personnage::monter(unsigned int HAUTEUR) {
    if (carburant > 0) {  // Vérifier si on a du carburant
        if (velociteY < 0) {
            velociteY = 0;  // On empêche une descente immédiate
        }
        if (velociteY <= 0.5) {velociteY+= 0.5;}  // Augmentation plus progressive de la poussée
        // Appliquer la poussée mais ne pas dépasser HAUTEUR
        if (hauteur + velociteY >= HAUTEUR) {
            hauteur = HAUTEUR;
            //velociteY = 0;
        } else {
            hauteur += velociteY;
        }

        carburant -= 0.1;  // Consommer du carburant
    }
}

void Personnage::appliquerGravite(unsigned int HAUTEUR) {
    if (hauteur > 0) {
        velociteY -= 0.5;  // Gravité légèrement plus forte pour équilibrer
        if (hauteur + velociteY < HAUTEUR) {hauteur += velociteY;}  // Appliquer la vitesse verticale

        // Ne pas tomber sous le sol
        if (hauteur < 0) {
            hauteur = 0;
            velociteY = 0;
        }
    }
}
