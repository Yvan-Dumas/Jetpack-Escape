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
    carburant = 50000000000000;
}

void Personnage::setHauteur(unsigned int y){
    hauteur = y;
}

unsigned int Personnage::getHauteur() const {
    return hauteur;
}
/*
void Personnage::monter() {
    if (velociteY < 0) {
        velociteY = 0;
    }
    if (velociteY == 0) {
        velociteY = 0.5;
    }
    //if (carburant != 0) {
        hauteur = hauteur + 1*velociteY;
        velociteY = velociteY + velociteY;
        carburant -= 0.2;
    //}
}

void Personnage::appliquerGravite(){
    if (hauteur > 0) {
        velociteY = velociteY - 0.5*abs(velociteY);
        if (velociteY < 0) {hauteur = hauteur + velociteY; }
    }
}*/
void Personnage::monter(unsigned int HAUTEUR) {
    if (carburant > 0) {  // Vérifier si on a du carburant
        if (velociteY < 0) {
            velociteY = 0;  // On empêche une descente immédiate
        }
        if (velociteY <= 0.5) {velociteY+= 0.5;}  // Augmentation plus progressive de la poussée
        // Appliquer la poussée mais ne pas dépasser HAUTEUR
        if (hauteur + velociteY >= HAUTEUR) {
            hauteur = HAUTEUR;
            velociteY = 1;
        } else {
            hauteur += velociteY;
        }

        carburant -= 0.2;  // Consommer du carburant
    }
}

void Personnage::appliquerGravite(unsigned int HAUTEUR) {
    if (hauteur > 0) {
        velociteY -= 0.5;  // Gravité
        /*if (hauteur + velociteY < HAUTEUR)*/ {hauteur += velociteY;}  // Appliquer la vitesse verticale

        // Ne pas tomber sous le sol
        if (hauteur < 0) {
            hauteur = 0;
            velociteY = 0;
        }
    }
}
