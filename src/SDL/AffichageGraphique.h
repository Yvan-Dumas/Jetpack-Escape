/**
 *@file AffichageGraphique.h
 *@brief Définition de la classe AffichageGraphique
 */
#ifndef AFFICHAGEGRAPHIQUE_H
#define AFFICHAGEGRAPHIQUE_H
 
#include "SDLSprite.h"
#include "Partie.h"
#include <SDL2/SDL.h>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

 /**
  * @class AffichageGraphique
  * @brief Affiche l'ensemble du jeu à l'aide d'une bibliothèque graphique
  */
 class AffichageGraphique {
 private:
     Partie partie; ///<  La partie en cours

     SDL_Window *window;
     SDL_Renderer *renderer;

     SDLSprite im_perso;

    bool souris;
    bool touche;

 
 public:
     void init(); ///< Initialise l'affichageGraphique
     ~AffichageGraphique(); ///< Le destructeur de AffichageGraphique
     void run(); ///< La procédure qui gère tout le jeu
     void affichage(); ///< La procédure qui gère tout l'affichage
 };
 
 #endif