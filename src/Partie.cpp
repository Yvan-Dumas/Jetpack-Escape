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

void Partie::charger() {

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

void Partie::ajouterCarburant(){
    perso.carburant = perso.carburant + 1 ;
}

void Partie::utiliserObjet(unsigned int id) {
    switch (id) {
        case 1:
            ajouterPiece();
            break;
        case 2:
            ajouterCarburant();
            break;
        default:
            break;
    }
}

void Partie::generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, HAUTEUR - 1); // Plage de 0 à HAUTEUR - 1
    int y = dist(gen); // Position y de l'Obstacle.
    int x = LARGEUR;// Position x de l'Obstacle.
    switch (id) {
        case 1: // Création d'un obstacle
            unsigned int largeur = 3; 
            unsigned int longueur = 1;
            Obstacle obstacle(id, x, y, largeur, longueur);
            tabObstacle.push_back(obstacle);
            break;
        case 2: // Création d'un carburant
            unsigned int largeur = 1; // Largeur de l'objet.
            unsigned int longueur = 3; // Longeur de l'objet.
            Obstacle obstacle(id, x, y, largeur, longueur);
            tabObstacle.push_back(obstacle);
            break;
        default:
            return; // Ne rien faire si id est invalide
    }

}

void Partie::generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, HAUTEUR - 1);
    int y = dist(gen); // Position y de l'objet.
    int x = LARGEUR; // Position x de l'objet (bord droit de l'écran).
    
    switch (id) {
        case 1: // Création d'une pièce
            unsigned int largeur = 1; 
            unsigned int longueur = 1;
            Objet objet(id, x, y, largeur, longueur);
            tabObjets.push_back(objet);
            break;
        case 2: // Création d'un carburant
            unsigned int largeur = 1; // Largeur de l'objet.
            unsigned int longueur = 1; // Longeur de l'objet.
            Objet objet(id, x, y, largeur, longueur);
            tabObjets.push_back(objet);
            break;
        default:
            return; // Ne rien faire si id est invalide
    }
}

unsigned int Partie::getHauteurPerso() const {
    return perso.getHauteur();
}

const vector<Obstacle>& Partie::getObstacles() const {
    return tabObstacle;
}

const vector<Objet>& Partie::getObjets() const{
    return tabObjets;
}

void Partie::actionsClavier(const char touche, unsigned int HAUTEUR) {
    switch (touche)
    {
    case 'z':
        perso.monter(HAUTEUR);
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
            generationObstacle(1,HAUTEUR, LARGEUR);
        }

        if (distance % 20 == 0) { // Tous les 20 mètres, on génère quelque chose
            generationObstacle(2,HAUTEUR, LARGEUR);
        }

        if (distance % 50 == 0) { // Tous les 50 mètres, on génère quelque chose
            generationObjet(1,HAUTEUR, LARGEUR);
        }
        if (distance % 30 == 0) { // Tous les 50 mètres, on génère quelque chose
            generationObjet(2,HAUTEUR, LARGEUR);
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

        // Mise à jour de la distance
        ajouterDistance();

        perso.appliquerGravite(HAUTEUR);
    return enMarche ;
}