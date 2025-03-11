/**
 *@file AffichageGraphique.h
 *@brief Définition de la classe AffichageGraphique
 */

 #ifndef AFFICHAGEGRAPHIQUE_H
 #define AFFICHAGEGRAPHIQUE_H
 
 #include "ArrierePlan.h"
 #include "Partie.h"

 /**
  * @class AffichageGraphique
  * @brief Affiche l'ensemble du jeu à l'aide d'une bibliothèque graphique
  */
 class AffichageGraphique {
 private:
    Partie p; ///<  La partie en cours
 
 public:
    AffichageGraphique(); ///< Le constructeur de AffichageGraphique
    void run(); ///< La fonction qui gère tout l'affichage
 };
 
 #endif