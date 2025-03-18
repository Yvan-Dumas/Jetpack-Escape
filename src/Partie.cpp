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
    Personnage perso;
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

void Partie::generationObstacle() {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 20); // Plage de 0 à 20
    int y = dist(gen); // Position y de l'Obstacle.
    unsigned int id = 0; // Identifiant du type de l'Obstacle.
    int x = 100; // Position x de l'Obstacle.
    unsigned int largeur = 5; // Largeur de l'Obstacle.
    unsigned int longueur = 5; // Longeur de l'Obstacle.
    Obstacle obstacle(id,x,y,largeur,longueur);
    tabObstacle.push_back(obstacle);

}

void Partie::generationObjet() {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 20); // Plage de 0 à 20
    int y = dist(gen); // Position y de l'Obstacle.
    unsigned int id; // Identifiant du type de l'Obstacle.
    int x = 100; // Position x de l'Obstacle.
    unsigned int largeur = 2; // Largeur de l'Obstacle.
    unsigned int longueur = 2; // Longeur de l'Obstacle.
    Objet objet(id,x,y,largeur,longueur);
    tabObjets.push_back(objet);
}

unsigned int Partie::getHauteurPerso() const {
    return perso.getHauteur();
}

vector<Obstacle>& Partie::getObstacles() {
    return tabObstacle;
}

bool Partie::lancerPartie() {
    // Vérification de l'appui sur la touche Z
    /*char touche = getch(); // Récupère immédiatement la touche
        if (touche == 'z' || touche == 'Z') {
            perso.monter();  // Appel de la méthode monter() du personnage
        }*/
    // Réinitialisation des paramètres de la partie
    bool enMarche = true;
        // Génération aléatoire d'obstacles et d'objets à certains intervalles
        if (distance % 2 == 0) { // Tous les 20 mètres, on génère quelque chose
            generationObstacle();
            generationObjet();
        }
        // Vérification des collisions avec obstacles
        for (auto obstacle = tabObstacle.begin(); obstacle != tabObstacle.end();) {
            obstacle->mettreAJourPosition(vitesseDefilement);
            if (obstacle->getX() <= 0) {
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle s'il sort de l'écran
            } else if (obstacle->collisionObstacle(perso.getHauteur())) {
                setNbVies(nbVies-1);
                if (nbVies <= 0) {
                    enMarche = false;
                    break;
                }
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
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



    return enMarche ;
}



