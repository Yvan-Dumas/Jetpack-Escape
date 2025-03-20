/**
 *@file Partie.h
 *@brief Définition de la classe Partie
*/

#ifndef PARTIE_H
#define PARTIE_H
 
#include "Personnage.h"
#include "Obstacle.h"
#include "Objet.h"
#include <vector>

using namespace std;
 
/**
    *@class Partie
    *@brief Gère le fonctionnement du jeu
*/
class Partie {
    private:
        Personnage perso; ///< Le personnage contrôlé par le joueur
        std::vector<Obstacle> tabObstacle; ///< Tableau des obstacles présents
        std::vector<Objet> tabObjets; ///< Tableau des objets récupérables
        int vitesseDefilement; ///< Vitesse du jeu

        void generationObstacle(unsigned int HAUTEUR, unsigned int LARGEUR);///<Génère un obstacle et l'ajoute au tableau
        void generationObjet(unsigned int HAUTEUR, unsigned int LARGEUR);///<Génère un objet et l'ajoute au tableau
        void ajouterPiece(); ///<Augmente le score tant que enMarche est vrai
        void ajouterDistance(); ///<Augmente le score tant que enMarche est vrai
        void utiliserObjet(unsigned int id); ///<Utilise l'objet ramassé

    public:
        int score; ///<Le score de la partie en cours
        int distance; ///<La distance parcourue depuis le début de la partie
        int nbVies; ///<Le nombre de vies restantes du joueur

        Partie(); ///<Le constructeur de la classe
        void sauvegarder(); ///<Sauvegarde le score dans un fichier
        void charger(); ///<Charger depuis un fichier
        void setNbVies(unsigned int nb); ///<Défini le nombre de vies
        void actionsClavier(const char touche);
        bool actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonction nécéssaire a la partie
        unsigned int getHauteurPerso() const; ///< Retourne La hauteur du personnage
        vector<Obstacle>& getObstacles(); ///< Retourne le tableau d'obstacles
        vector<Objet>& getObjets(); ///< Retourne le tableau d'objets
        Personnage& getPerso();
 };
 
 #endif
 