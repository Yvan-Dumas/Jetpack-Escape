/**
 *@file AffichageGraphique.h
 *@brief Définition de la classe AffichageGraphique
 */
#ifndef AFFICHAGEGRAPHIQUE_H
#define AFFICHAGEGRAPHIQUE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <cassert>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "SDLSprite.h"
#include "Partie.h"


/**
  * @class AffichageGraphique
  * @brief Affiche l'ensemble du jeu à l'aide de la bibliothèque graphique SDL2 
  */
class AffichageGraphique {
  private:
    Partie partie; ///<  La partie en cours

    SDL_Window *window;
    SDL_Renderer *renderer;
      TTF_Font *police1;
      TTF_Font *police2;
      TTF_Font *VT323;
      TTF_Font *PS2P;
      SDL_Cursor* curseurPerso;

      SDLSprite im_perso1;
      SDLSprite im_perso2;

      SDLSprite im_toit;
      SDLSprite im_sol;
      SDLSprite im_bloc_sol;

      SDLSprite im_obstacle;
      SDLSprite im_rat;

      SDLSprite im_piece;
      SDLSprite im_vie;
      SDLSprite im_vies0;
      SDLSprite im_vies1;
      SDLSprite im_vies2;
      SDLSprite im_vies3;
      SDLSprite im_vies4;

      SDLSprite im_carburant;
      SDLSprite im_carburant0;
      SDLSprite im_carburant1;
      SDLSprite im_carburant2;
      SDLSprite im_carburant3;
      SDLSprite im_fond;

      int offset_x = 0;
      bool piecesEnVie = false;
      int debutMessage;
 
    public:
    void init(); ///< Initialise l'affichageGraphique
    ~AffichageGraphique(); ///< Le destructeur de AffichageGraphique

    void affichage(); ///< La procédure qui gère tout l'affichage
    void afficherGameOver(); ///<La procédure qui affiche un message en fin de partie
    void run(); ///< La procédure qui gère tout le jeu
    void renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font); ///< Procédure pour afficher du texte

    void affichage2Joueurs(); ///< La procédure qui gère tout l'affichage en mode 2 joueurs
    void run2Joueurs(); ///< La procédure qui gère tout le jeu en mode 2 joueurs

    string getRecord(); ///< Renvoie le record
 };
#endif