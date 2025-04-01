/**
 *@file AffichageGraphique.h
 *@brief Définition de la classe AffichageGraphique
 */
#ifndef AFFICHAGEGRAPHIQUE_H
#define AFFICHAGEGRAPHIQUE_H
 
#include "ArrierePlan.h"
#include "Partie.h"
#include <SDL2/SDL.h>
#include <cassert>
#include <time.h>
#include <stdlib.h>

 /**
  * @class AffichageGraphique
  * @brief Affiche l'ensemble du jeu à l'aide d'une bibliothèque graphique
  */
 class AffichageGraphique {
 private:
     Partie partie; ///<  La partie en cours
 
 public:
     AffichageGraphique(); ///< Le constructeur de AffichageGraphique
     void run(); ///< La procédure qui gère tout le jeu
     void affichage(); ///< La procédure qui gère tout l'affichage
 };
 
 #endif