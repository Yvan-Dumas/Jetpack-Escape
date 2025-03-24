/**
 *@file Personnage.cpp
 *@brief Implémentation de la classe personnage
 */

#include <iostream>
#include "Personnage.h"
#include <cassert>

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
            velociteY = 1;
        } else {
            hauteur += velociteY;
        }

        carburant -= 0.05;  // Consommer du carburant
    }
}

void Personnage::appliquerGravite(unsigned int HAUTEUR) {
    if (hauteur > 0) {
        velociteY -= 0.5;  // Gravité
        {hauteur += velociteY;}  // Appliquer la vitesse verticale

        // Ne pas tomber sous le sol
        if (hauteur < 0) {
            hauteur = 0;
            velociteY = 0;
        }
    }
}


void Personnage::testPersonnage() {
    cout << "Début des test pour Personnage"<<endl ;
    // Test du constructeur
    Personnage p;
    // Vérification des valeurs initiales
    assert(p.getHauteur() == 0 && "Test échoué : La hauteur initiale n'est pas correcte");
    
    // Test de la méthode setHauteur
    p.setHauteur(10);
    assert(p.getHauteur() == 10 && "Test échoué : La hauteur n'a pas été mise à jour correctement");
    
    // Test de la méthode monter
    // On suppose que la hauteur initiale est 10 et que le carburant est suffisant
    p.monter(15);
    p.monter(15);
    assert(p.getHauteur() > 10 && "Test échoué : La montée n'a pas fonctionné correctement");

    // Test de la méthode appliquerGravite
    // On applique la gravité et on vérifie la diminution de la hauteur
    p.setHauteur(10);
    p.appliquerGravite(15); p.appliquerGravite(15); p.appliquerGravite(15);
    assert(p.getHauteur() < 10.0 && "Test échoué : La gravité n'a pas fonctionné correctement");
    
    // Test de la montée avec un manque de carburant
    p.setHauteur(0);  // Remise à 0 pour tester l'impact du carburant
    p.carburant = 0;
    p.monter(10); // Plus de carburant pour la deuxième montée
    assert(p.getHauteur() == 0 && "Test échoué : Le personnage n'aurait pas dû monter sans carburant");
    
    // Si tous les tests passent, on affiche un message de succès
    cout << "Tous les tests ont réussi !" <<endl;

}