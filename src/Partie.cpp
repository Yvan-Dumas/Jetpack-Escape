/**
 *@file Partie.cpp
 *@brief Implémentation de la classe Partie
 */

#include <iostream>
#include "Partie.h"
#include <random>
#include <termios.h>
#include <cassert>

using namespace std;

Partie::Partie() {
    vitesseDefilement = 1;
    score = 0;
    distance = 0;
    nbVies = 3;
    record = chargerFichier();
}

void Partie::sauvegarderFichier(string contenu) {
    ofstream fichier("../data/sauvegarde.txt", ios::out | ios::trunc);
    if(fichier){
        fichier << contenu;
        fichier.close();
    }
    else cout << "impossible d'ouvrir le fichier !";
}

string Partie::chargerFichier() {
    fstream fichier("../data/sauvegarde.txt", ios::in);
    if(fichier){
        string contenu;
        getline(fichier, contenu);
        fichier.close();
        return contenu;
    }
    else return "impossible d'ouvrir le fichier !";
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
    if (perso.carburant < 4) {
    perso.carburant = perso.carburant + 1 ; }
    else {perso.carburant = 5;}
}

void Partie::utiliserObjet(unsigned int id) {
    switch (id) {
        case 1:
            ajouterPiece();
            break;
        case 2:
            ajouterCarburant();
            break;
        case 3:
            nbVies += 1 ;
        default:
            break;
    }
}

bool Partie::bien_place(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur) {
    if (tabObjets.empty() || tabObstacle.empty()) {
        return true; // Rien à tester, l'objet est bien placé
    }
    else {
    Objet obj = tabObjets.back();
    Obstacle obs = tabObstacle.back();

    // Fonction pour vérifier s'il y a une intersection entre deux rectangles
    auto superpose = [](unsigned int x1, unsigned int y1, unsigned int w1, unsigned int h1,
                         unsigned int x2, unsigned int y2, unsigned int w2, unsigned int h2) {
        return !(x1 + w1 <= x2 || x2 + w2 <= x1 || y1 + h1 <= y2 || y2 + h2 <= y1);
    };

    // Vérifie si l'objet à placer chevauche l'objet existant ou l'obstacle
    if (superpose(x, y, largeur, longueur, obj.getX(), obj.getY(), 1, 1) ||
        superpose(x, y, largeur, longueur, obs.getX(), obs.getY(), obs.getLargeur(), obs.getLongueur())) {
        return false; // Il y a une superposition
    }

    return true; // Aucun chevauchement, l'objet est bien placé
    }
}


void Partie::generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, HAUTEUR - 1); // Plage de 0 à HAUTEUR - 1
    int y = dist(gen); // Position y de l'Obstacle.
    int x = LARGEUR;// Position x de l'Obstacle.
    unsigned int largeur; 
    unsigned int longueur;

    switch (id) {
        case 1: {// Création d'un obstacle
            largeur = 3; 
            longueur = 1;
            Obstacle obstacle1(id, x, y, largeur, longueur);
            tabObstacle.push_back(obstacle1);
            break; }
        case 2: {// Création d'un obstacle vertical (échaffaudage)
            largeur = 1; // Largeur de l'objet.
            longueur = 3; // Longeur de l'objet.
            Obstacle obstacle2(id, x, y, largeur, longueur);
            tabObstacle.push_back(obstacle2);
            break; }
        case 3: {// Création d'un obstacle (métro)
            largeur = 6; // Largeur de l'objet.
            longueur = 3; // Longeur de l'objet.
            Obstacle obstacle2(id, x, 0, largeur, longueur);
            tabObstacle.push_back(obstacle2);
             break; }
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
    unsigned int largeur; 
    unsigned int longueur;
    switch (id) {
        case 1: {// Création d'une pièce
            largeur = 1; 
            longueur = 1; }

        case 2: { // Création d'un carburant
            largeur = 1; // Largeur de l'objet.
            longueur = 1; // Longeur de l'objet.
            }
        case 3: { // Création d'une vie
            largeur = 1; // Largeur de l'objet.
            longueur = 1; // Longeur de l'objet.
                }
        default:
            largeur = 1; 
            longueur = 1; // Ne rien faire si id est invalide
    }
    while (!bien_place(x, y, largeur, longueur))
    {
        x = x + 1;
    }
    
    Objet objet1(id, x, y, largeur, longueur);
            tabObjets.push_back(objet1);
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
        if (distance % 20 == 1) {
            generationObstacle(1,HAUTEUR, LARGEUR);
        }

        if (distance % 40 == 24) { 
            generationObstacle(2,HAUTEUR, LARGEUR);
        }
        if (distance % 40 == 24) { 
            generationObstacle(3,HAUTEUR, LARGEUR);
        }
        if (distance % 15 == 5) {
            generationObjet(1,HAUTEUR, LARGEUR);
        }

        if (distance % 30 == 16) { 
            generationObjet(2,HAUTEUR, LARGEUR);
        }

        if (distance % 100 == 50) { 
            generationObjet(3,HAUTEUR, LARGEUR);
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

float Partie::getCarburant() const {
    return perso.carburant;
}

void Partie::testPartie() {
    cout<<"Début des tests pour Partie"<<endl;
    // Initialisation de la partie
    Partie partie;
    
    // Vérification des paramètres initiaux
    assert(partie.getHauteurPerso() == 0 && "Test échoué : La hauteur initiale du personnage n'est pas correcte");
    assert(partie.getCarburant() == 5 && "Test échoué : Le carburant initial n'est pas correct");
    assert(partie.getObstacles().empty() && "Test échoué : Il ne devrait y avoir aucun obstacle au début");
    assert(partie.getObjets().empty() && "Test échoué : Il ne devrait y avoir aucun objet au début");

    // Test de l'ajout d'un carburant
    partie.ajouterCarburant();
    assert(partie.getCarburant() == 5 && "Test échoué : Le carburant ne doit pas dépasser 5");

    // Test de la mise à jour des obstacles et objets
    unsigned int initialObstacleSize = partie.getObstacles().size();
    unsigned int initialObjetSize = partie.getObjets().size();

    // Test de l'action automatique
    bool enMarche = partie.actionsAutomatiques(100, 50);
    assert(enMarche && "Test échoué : La partie ne devrait pas être terminée après une action automatique");
    assert(partie.getObstacles().size() == initialObstacleSize && "Test échoué : Le nombre d'obstacles n'a pas été mis à jour correctement");
    assert(partie.getObjets().size() == initialObjetSize && "Test échoué : Le nombre d'objets n'a pas été mis à jour correctement");

    // Si tous les tests passent, on affiche un message de succès
    cout << "Tous les tests ont réussi !" << endl;

}