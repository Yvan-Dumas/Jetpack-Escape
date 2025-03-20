/**
 *@file Partie.cpp
 *@brief Implémentation de la classe Partie
 */

#include <iostream>
#include "Partie.h"
#include <random>
#include <termios.h>

using namespace std;

Partie::Partie() {
    vitesseDefilement = 1;
    score = 0;
    distance = 0;
    nbVies = 3;
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

void Partie::generationObstacle(unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, HAUTEUR); // Plage de 0 à HAUTEUR
    int y = dist(gen); // Position y de l'Obstacle.
    unsigned int id = 0; // Identifiant du type de l'Obstacle.
    int x = LARGEUR;// Position x de l'Obstacle.
    unsigned int largeur = 3; // Largeur de l'Obstacle.
    unsigned int longueur = 1; // Longeur de l'Obstacle.
    Obstacle obstacle(id,x,y,largeur,longueur);
    tabObstacle.push_back(obstacle);

}

void Partie::generationObjet(unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, HAUTEUR); // Plage de 0 à 20
    int y = dist(gen); // Position y de l'Obstacle.
    unsigned int id= 1 ; // Identifiant du type de l'Obstacle.
    int x = LARGEUR; // Position x de l'Obstacle.
    unsigned int largeur = 1; // Largeur de l'objet.
    unsigned int longueur = 1; // Longeur de l'objet.
    Objet objet(id,x,y,largeur,longueur);
    tabObjets.push_back(objet);
}

unsigned int Partie::getHauteurPerso() const {
    return perso.getHauteur();
}

vector<Obstacle>& Partie::getObstacles() {
    return tabObstacle;
}

vector<Objet>& Partie::getObjets() {
    return tabObjets;
}

Personnage& Partie::getPerso() {
    return perso;
}

void Partie::actionsClavier(const char touche, unsigned int HAUTEUR) {
    switch (touche)
    {
    case 'z':
        if (perso.getHauteur()< HAUTEUR) {
        perso.monter(); }
        break;
    
    default:
        break;
    }
}

bool Partie::actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR) {
    // Réinitialisation des paramètres de la partie

    bool enMarche = true;
        // Génération aléatoire d'obstacles et d'objets à certains intervalles
        if (distance % 20 == 0) { // Tous les 20 mètres, on génère quelque chose
            generationObstacle(HAUTEUR, LARGEUR);
        }
        if (distance % 50 == 0) { // Tous les 50 mètres, on génère quelque chose
            generationObjet(HAUTEUR, LARGEUR);
        }
        // Vérification des collisions avec obstacles
        for (auto obstacle = tabObstacle.begin(); obstacle != tabObstacle.end();) {
            obstacle->mettreAJourPosition(vitesseDefilement);
            if (obstacle->getX() <= 0) {
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle s'il sort de l'écran
            } else if (obstacle->collisionObstacle(perso.getHauteur())) {
                nbVies--;
                if (nbVies <= 0) {
                    enMarche = false;
                    break;
                }
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
            } else {
                ++obstacle;
            }
        }

        // Vérification des objets ramassés
        for (auto it = tabObjets.begin(); it != tabObjets.end();) {
            it->mettreAJourPosition(vitesseDefilement);
            unsigned int identifiant = it->collecterObjet(perso.getHauteur());
            if (it->getX() <= 0) {
                it = tabObjets.erase(it); // Supprime l'objet s'il sort de l'écran
            } else if (identifiant !=100) {
                utiliserObjet(identifiant); 
                it = tabObjets.erase(it); // Supprime l'objet après collecte
            } else {
                ++it;
            }
        }

        perso.appliquerGravite();
        // Mise à jour de la distance
        ajouterDistance();
    return enMarche ;
}



