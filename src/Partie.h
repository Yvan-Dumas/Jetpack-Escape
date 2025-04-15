/**
 *@file Partie.h
 *@brief Définition de la classe Partie
 */
#ifndef PARTIE_H
#define PARTIE_H
 
#include "Personnage.h"
#include "Obstacle.h"
#include "Objet.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cassert>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
/**
 * @class Partie
 * @brief Classe responsable de la gestion complète d'une partie du jeu, notamment des obstacles, des objets et du/des personnage(s)
 */

class Partie {

    private:
        Personnage perso1; ///< Le personnage contrôlé par le joueur 1
        Personnage perso2; ///< Le personnage contrôlé par le joueur 2 (mode 2 joueurs).

        vector<Obstacle> tabObstacle; ///< Tableau des obstacles présents
        vector<Objet> tabObjets; ///< Tableau des objets récupérables

        /**
        * @brief Génère un obstacle et l’ajoute au tableau d’obstacles.
        * @param id L’identifiant du type d’obstacle.
        * @param HAUTEUR La hauteur de la grille de jeu.
        * @param LARGEUR La largeur de la grille de jeu. Ainsi on sait où placer l'objet (y<=hauteur et x = largeur)
        */
        void generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR);

        /**
        * @brief Génère un objet et l’ajoute au tableau d’objets.
        * @param id L’identifiant du type d’objet.
        * @param HAUTEUR La hauteur de la grille de jeu.
        * @param LARGEUR La largeur de la grille de jeu. Ainsi on sait où placer l'objet (y<=hauteur et x = largeur)
        */
        void generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR);
        
        /**
        * @brief Incrémente le nombre de pièces du personnage.
        * @param perso Référence au personnage auquel on souhaite ajouter une pièce.
        */
        void ajouterPiece(Personnage & perso); 
        
        /**
        * @brief Incrémente la distance parcourue du personnage d'une unité de jeu.
        * @param perso Référence au personnage auquel on souhaite augmenter la distance.
        */
        void ajouterDistance(Personnage & perso);
        
        /**
        * @brief Applique les effets d’un objet ramassé par le personnage.
        * @param perso Référence au personnage qui va utiliser l'objet.
        * @param id Identifiant du type d’objet ramassé.
        */
        void utiliserObjet(Personnage & perso, unsigned int id);
        
        /**
        * @brief Vérifie si une position est valide pour placer un objet ou un obstacle.
        * @param x Position en x.
        * @param y Position en y.
        * @param largeur Largeur de l'objet à placer.
        * @param longueur Longueur de l'objet à placer.
        * @return true si la position est libre, false sinon.
        * @details Une position est valide si l'objet / obstacle est à plus de 1 unité de distance de tout autre obstacle / objet
        */
        bool estBienPlace(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur); ///< Regarde si l'objet / obstacle n'empiete pas sur un autre

        /**
         * @brief Procédure pour le tirage aléatoire d'un identifiant et la génération d'un obstacle ou d'un objet associé à cette identifiant.
         * @param HAUTEUR La hauteur de la grille de jeu.
         * @param LARGEUR La largeur de la grille de jeu.
         */
        void tirageEtGenerationObstaclesObjets(int HAUTEUR, int LARGEUR);
    public:

        string record; ///< Le record de distance parcourue atteint dans le jeu. Récupéré dans le fichier data/sauvegarde.txt lors de l'initialisation.
        bool piecesEnVie = false;    ///< Indique si des pièces ont été échangées en vies, pour pouvoir afficher un message.

        /**
        * @brief Constructeur de la classe Partie.
        * @details Initialise les structures du jeu.
        */
        Partie();

        /**
        * @brief Mutateur : augmente le carburant du personnage de 1 litres.
        * @param p Référence au personnage auquel on souhaite augmenter le carburant.
        */
        void ajouterCarburant(Personnage & p);

        /**
        * @brief Sauvegarde le record de la partie dans data/sauvegarde.txt
        * @param contenu Chaîne représentant les données à sauvegarder.
        */
        void sauvegarderFichier(const string& contenu) const;
        
        /**
        * @brief Charge les données depuis data/sauvegarde.txt
        * @return Une chaîne contenant les données chargées.
        */
        string chargerFichier() const ;

        /**
        * @brief Effectue les actions liées aux touches clavier (mode 1 joueur).
        * @param touche Touche pressée par l'utilisateur.
        * @param HAUTEUR Hauteur de la grille de jeu.
        * @details Fait monter le personnage si la touche est 'Z'
        */
        void actionsClavier(const char touche, unsigned int HAUTEUR);
        
        /**
        * @brief Effectue les actions liées aux touches clavier (mode 2 joueurs).
        * @param touche Touche pressée par un des joueurs.
        * @param HAUTEUR Hauteur de la grille de jeu.
        * @details Fait monter le personnage 1 si la touche est 'Z' et le personnage 2 si la touche est 'L'
        */
        void actionsClavier2Joueurs(const char touche, unsigned int HAUTEUR);

        /**
        * @brief Exécute les actions automatiques du jeu à chaque tour (mode 1 joueur).
        * @param HAUTEUR Hauteur de la grille.
        * @param LARGEUR Largeur de la grille.
        * @return true si la partie continue, false si elle est terminée.
        * @details Les actions éffectuées sont la génération d'obstacles, l'augmentation de la distance parcourue du personnage,
        * l'application de la gravité et les test des collisions avec objets / obstacles. La partie est finie quand un joueur n'a plus de vies.
        */
        bool actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonctions nécéssaire à la partie
        
        /**
        * @brief Exécute les actions automatiques du jeu à chaque tour (mode 2 joueurs).
        * @param HAUTEUR Hauteur de la grille.
        * @param LARGEUR Largeur de la grille.
        * @return true si la partie continue, false si elle est terminée.
        * @details Les actions éffectuées sont la génération d'obstacles, l'augmentation de la distance parcourue du personnage,
        * l'application de la gravité et les test des collisions avec objets / obstacles. La partie est finie quand un joueur n'a plus de vies.
        */
        bool actionsAutomatiques2Joueurs(unsigned int HAUTEUR, unsigned int LARGEUR); ///< Appele les différentes fonctions nécéssaire à la partie en mode 2 joueurs

        /**
        * @brief Accesseur : retourne le tableau des obstacles présents dans la partie.
        * @return Une référence constante vers le vecteur d’obstacles.
        */
        const vector<Obstacle>& getObstacles() const;
        
        /**
        * @brief Accesseur : retourne le tableau des objets présents dans la partie.
        * @return Une référence constante vers le vecteur d’objets.
        */
        const vector<Objet>& getObjets() const;

        /**
        * @brief Accesseur : retourne le personnage 1.
        * @return Une référence constante vers le personnage 1.
        */
        const Personnage& getPerso1() const;
        
        /**
        * @brief Accesseur : retourne le personnage 2.
        * @return Une référence constante vers le personnage 2.
        */
        const Personnage& getPerso2() const;

        /**
        * @brief Achète une vie si le personnage a suffisamment de pièces (plus de 10 pièces et moins de 4 vie).
        * @return true si une vie a été achetée, false sinon.
        */
        bool acheterVieSiPossible();

        /**
        * @brief Effectue une série de tests sur la classe Partie.
        */
       static void testPartie();
 };
 
 #endif