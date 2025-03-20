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

void Personnage::monter() {
    if (carburant !=0) {
        velociteY = velociteY + 1;
        hauteur = hauteur + 1*velociteY;
        carburant -= 0.2;
    }
}

void Personnage::appliquerGravite(){
    /*if (hauteur > 0) {
        velociteY = velociteY + 0.5;
        hauteur = hauteur - 1*velociteY;
    }*/
}