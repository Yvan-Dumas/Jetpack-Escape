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
        vector<Obstacle> tabObstacle; ///< Tableau des obstacles présents
        vector<Objet> tabObjets; ///< Tableau des objets récupérables
        int vitesseDefilement; ///< Vitesse du jeu

        void generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR);///< Génère un obstacle et l'ajoute au tableau
        void generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR);///< Génère un objet et l'ajoute au tableau
        void ajouterPiece(); ///< Incrémente le score des pièces
        void ajouterDistance(); ///< Incrémente le score de distance parcourue
        void utiliserObjet(unsigned int id); ///< Utilise l'objet ramassé
        bool bien_place(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur); ///< Regarde si l'objet / obstacle n'empiete pas sur un autre

    public:
        int score; ///< Le score de la partie en cours
        int distance; ///< La distance parcourue depuis le début de la partie
        int nbVies; ///< Le nombre de vies restantes du joueur

        Partie(); ///< Le constructeur de la classe
        void ajouterCarburant(); ///< Augmente le carburant
        void sauvegarder(); ///< Sauvegarde dans un fichier
        void charger(); ///< Charger depuis un fichier
        void setNbVies(unsigned int nb); ///< Défini le nombre de vies
        void actionsClavier(const char touche, unsigned int HAUTEUR); ///< Effectue des actions en fonction des entrées claviers
        bool actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonctions nécéssaire à la partie
        unsigned int getHauteurPerso() const; ///< Retourne la hauteur du personnage
        const vector<Obstacle>& getObstacles() const; ///< Retourne le tableau d'obstacles
        const vector<Objet>& getObjets() const; ///< Retourne le tableau d'objets
        float getCarburant() const;
        /**
        * @brief Effectue une série de tests sur les méthodes de la classe Partie.
        * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
        */
       static void testPartie();
 };
 
 #endif