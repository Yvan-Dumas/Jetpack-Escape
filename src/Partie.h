/**
 *@file Partie.h
 *@brief Définition de la classe Partie
 */
#ifndef PARTIE_H
#define PARTIE_H
 
#include <iostream>
#include "Personnage.h"
#include "Obstacle.h"
#include "Objet.h"
#include <vector>
#include <fstream>
#include <random>
#include <cassert>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
/**
    *@class Partie
    *@brief Gère le fonctionnement du jeu
*/
class Partie {
    private:
        int vitesseDefilement; ///< Vitesse du jeu
        Personnage perso1; ///< Le personnage contrôlé par le joueur
        Personnage perso2; ///< Le personnage contrôlé par le 2ème joueur si le jeu est en mode 2 joueurs

        vector<Obstacle> tabObstacle; ///< Tableau des obstacles présents
        vector<Objet> tabObjets; ///< Tableau des objets récupérables

        void generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR);///< Génère un obstacle et l'ajoute au tableau
        void generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR);///< Génère un objet et l'ajoute au tableau
        void ajouterPiece(Personnage & perso); ///< Incrémente le nombre de pièces du personnage
        void ajouterDistance(Personnage & perso); ///< Incrémente le score de distance parcourue du personnage
        void utiliserObjet(Personnage & perso, unsigned int id); ///< Utilise l'objet ramassé
        bool bien_place(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur); ///< Regarde si l'objet / obstacle n'empiete pas sur un autre

    public:
        string record; ///< Le record de distance parcourue

        Partie(); ///< Le constructeur de la classe

        void ajouterCarburant(Personnage & p); ///< Augmente le carburant du personnage

        void sauvegarderFichier(string contenu); ///< Sauvegarde dans un fichier
        string chargerFichier(); ///< Charger depuis un fichier

        void actionsClavier(const char touche, unsigned int HAUTEUR); ///< Effectue des actions en fonction des entrées claviers
        void actionsClavier2Joueurs(const char touche, unsigned int HAUTEUR); ///< Effectue des actions en fonction des entrées claviers en mode 2 joueurs

        bool actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonctions nécéssaire à la partie
        bool actionsAutomatiques2Joueurs(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonctions nécéssaire à la partie en mode 2 joueurs

        const vector<Obstacle>& getObstacles() const; ///< Retourne le tableau d'obstacles
        const vector<Objet>& getObjets() const; ///< Retourne le tableau d'objets

        const Personnage& getPerso1() const; ///< Accesseur pour le personnage 1
        const Personnage& getPerso2() const; ///< Accesseur pour le personnage 2

        /**
        * @brief Effectue une série de tests sur les méthodes de la classe Partie.
        * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
        */
       static void testPartie();
 };
 
 #endif