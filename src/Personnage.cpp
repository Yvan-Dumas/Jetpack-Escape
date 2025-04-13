/**
 *@file Personnage.cpp
 *@brief Implémentation de la classe personnage
 */

#include "Personnage.h"
using namespace std;

Personnage::Personnage() {
    hauteur = 0;
    velociteY = 0;
    carburant = 3;
}

void Personnage::setHauteur(unsigned int y){
    hauteur = y;
}

unsigned int Personnage::getHauteur() const {
    return hauteur;
}

void Personnage::monter(unsigned int HAUTEUR) {
    if (carburant > 0) {  // Vérifier si le personnage a du carburant
         // Si la vitesse est négative (chute), on la mets en positive, pour pouvoir monter
        if (velociteY < 0) {
            velociteY = 0.5; 
        }
        // Si la vitesse verticale n'est pas à son maximum, on l'augmente.
        if (velociteY <= 0.5) {velociteY+= 0.5;} 
        // Si la montée dépasse la hauteur maximale passée en paramètre, on la limite; sinon, on monte
        if (hauteur + velociteY >= HAUTEUR) {
            hauteur = HAUTEUR;
            velociteY = 1;
        } else {
            hauteur += velociteY;
        }

        carburant -= 0.005;  // Consommer du carburant
    }
    else {
        carburant = 0; // Pour éviter une valeur négative de carburant.
    }
}

void Personnage::appliquerGravite() {
    if (hauteur > 0) {
        // Réduction de la vitesse verticale si elle n'est pas trop grande
        if (velociteY >= -0.5){
            velociteY -= 0.5; 
        }
        hauteur += velociteY;}  // Appliquer la vitesse verticale

    // Ne pas tomber sous le sol, y = 0
    if (hauteur <= 0) {
        hauteur = 0;
        velociteY = 0;
        }
    }

unsigned int Personnage::getNbPieces() const {
    return nbPièces;
}

void Personnage::setNbPieces(unsigned int nb) {
    nbPièces = nb;
}

unsigned int Personnage::getDistance() const {
    return distance;
}

void Personnage::setDistance(unsigned int nb) {
    distance = nb;
}

unsigned int Personnage::getNbVies() const {
    return nbVies;
}

void Personnage::setNbVies(unsigned int nb) {
    nbVies = nb;
}


void Personnage::testPersonnage() {
    cout << "Début des tests pour la classe Personnage" << endl;

    // Test du constructeur
    Personnage p;
    assert(p.getHauteur() == 0 && "Test échoué : hauteur initiale incorrecte");

    // Test setHauteur / getHauteur
    p.setHauteur(10);
    assert(p.getHauteur() == 10 && "Test échoué : setHauteur n'applique pas la bonne hauteur");

    // Test montée avec carburant
    p.carburant = 1;
    p.setHauteur(10);
    p.monter(15);
    p.monter(15);
    assert(p.getHauteur() > 10 && "Test échoué : la montée avec carburant n'a pas fonctionée");

    // Test appliquerGravite
    p.setHauteur(10);
    p.appliquerGravite();
    p.appliquerGravite();
    p.appliquerGravite();
    assert(p.getHauteur() < 10 && "Test échoué : la gravité ne s'est pas appliquée");

    // Test montée sans carburant
    p.setHauteur(0);
    p.carburant = 0;
    p.monter(10);
    assert(p.getHauteur() == 0 && "Test échoué : montée sans carburant possible");

    // Test get/set pièces
    p.setNbPieces(5);
    assert(p.getNbPieces() == 5 && "Test échoué : get/set NbPieces");

    // Test get/set distance
    p.setDistance(100);
    assert(p.getDistance() == 100 && "Test échoué : get/set Distance");

    // Test get/set vies
    p.setNbVies(2);
    assert(p.getNbVies() == 2 && "Test échoué : get/set NbVies");

    cout << "Tous les tests ont réussi" << endl;
}
