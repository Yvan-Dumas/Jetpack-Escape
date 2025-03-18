/**
 *@file Partie.cpp
 *@brief Implémentation de la classe Partie
 */

#include <iostream>
#include "Partie.h"

using namespace std;

Partie::Partie() {
    vitesseDefilement = 1;
    score = 0;
    distance = 0;
    nbVies = 1;
}

void Partie::sauvegarder() {

}

void Partie::charger(){

}

void Partie::setNbVies(unsigned int nb) {
    nbVies = nb;
}

void Partie::ajouterPiece() {
    score++;
}

void Partie::ajouterDistance() {
    distance++;
}

void Partie::utiliserObjet(unsigned int id){
    switch (id)
    {
    case 1:
        ajouterPiece();
        break;
    
    default:
        
        break;
    }
}

void Partie::generationObstacle() {

}

void Partie::generationObjet() {

}

unsigned int Partie::getHauteurPerso() const {
    return perso.getHauteur();
}

const std::vector<Obstacle>& Partie::getObstacles() const {
    return tabObstacle;
}