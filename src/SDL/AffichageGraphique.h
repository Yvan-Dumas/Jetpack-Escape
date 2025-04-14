/**
 * @file AffichageGraphique.h
 * @brief Définition de la classe AffichageGraphique
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
 
using namespace std;

 /**
  * @class AffichageGraphique
  * @brief Gère l'affichage graphique du jeu à l'aide de SDL2.
  * Cette classe encapsule tous les éléments liés à l'affichage graphique :
  * fenêtre, textures, textes, sprites, et logique de rendu en jeu.
  */
 class AffichageGraphique {
 private:
     Partie partie; ///< Partie en cours
 
     SDL_Window *window;          ///< Fenêtre principale SDL
     SDL_Renderer *renderer;      ///< Renderer SDL pour l'affichage
     TTF_Font *VT323;             ///< Police VT323, police principale du jeu
     TTF_Font *PS2P;              ///< Police PS2 Pixel, police des menus.
     SDL_Cursor* curseurPerso;    ///< Curseur personnalisé
 
     // Sprites des personnages
     SDLSprite im_perso1;         ///< Sprite du personnage 1
     SDLSprite im_perso2;         ///< Sprite du personnage 2
 
     // Sprites du décor
     SDLSprite im_toit;           ///< Sprite du toit
     SDLSprite im_sol;            ///< Sprite du sol
     SDLSprite im_bloc_sol;       ///< Sprite des blocs de sol
 
     // Sprites des obstacles
     SDLSprite im_obstacle;       ///< Sprite des obstacles de base
     SDLSprite im_rat;            ///< Sprite du rat
     SDLSprite im_metro1;         ///< Sprite du métro 1
     SDLSprite im_metro2;         ///< Sprite du métro 2
 
     // Sprites des objets et UI
     SDLSprite im_piece;          ///< Sprite de l'item pièce
     SDLSprite im_vie;            ///< Sprite de l'item vie
     SDLSprite im_vies0;          ///< Sprite pour 0 vies
     SDLSprite im_vies1;          ///< Sprite pour 1 vie
     SDLSprite im_vies2;          ///< Sprite pour 2 vies
     SDLSprite im_vies3;          ///< Sprite pour 3 vies
     SDLSprite im_vies4;          ///< Sprite pour 4 vies
 
     SDLSprite im_carburant;      ///< Sprite de l'item carburant
     SDLSprite im_carburant0;     ///< Sprite jauge vide
     SDLSprite im_carburant1;     ///< Sprite jauge 1/3
     SDLSprite im_carburant2;     ///< Sprite jauge 2/3
     SDLSprite im_carburant3;     ///< Sprite jauge pleine
 
     SDLSprite im_fond;           ///< Sprite de fond
 
     int offset_x = 0;            ///< Décalage horizontal pour effet de scrolling
     int debutMessage;            ///< Timestamp du début d'affichage d’un message
 
 public:
     /**
      * @brief Initialise l'affichage graphique, les polices, la fenêtre et les sprites.
      */
     void init();
 
     /**
      * @brief Destructeur : libère les ressources SDL.
      */
     ~AffichageGraphique();
 
     /**
      * @brief Gère tout l'affichage pour le mode solo.
      */
     void affichage();
    /**
    * @brief Affiche un grand obstacle à l'écran en utilisant une image.
    * 
    * Cette fonction affiche un obstacle graphique à l'aide d'un sprite SDL. 
    * L'obstacle est dessiné avec la largeur et la longueur spécifiées, 
    * à la position (obsX, obsY). La fonction est utilisé pour l'affichage des métros.
    * 
    * @param renderer Le renderer SDL utilisé pour l'affichage.
    * @param im_metro Le sprite SDL représentant l'image de l'obstacle.
    * @param obsX La position horizontale (x) de l'obstacle.
    * @param obsY La position verticale (y) de l'obstacle.
    * @param obsLargeur La largeur de l'obstacle à afficher.
    * @param obsLongueur La longueur (hauteur) de l'obstacle à afficher.
    */
     void afficherObstacleGrandeImage(SDL_Renderer* renderer, const SDLSprite& im_metro, int obsX, int obsY, int obsLargeur, int obsLongueur);
 
     /**
      * @brief Affiche un écran de fin de partie.
      */
     void afficherGameOver();
 
     /**
      * @brief Boucle principale du jeu en mode solo (affichage + interactions).
      */
     void run();
 
     /**
      * @brief Affiche un texte à une position donnée.
      * 
      * @param text Le texte à afficher.
      * @param x Position X du texte.
      * @param y Position Y du texte.
      * @param color Couleur du texte (SDL_Color).
      * @param font Police TTF à utiliser.
      */
     void renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font);
 
     /**
      * @brief Gère l'affichage complet en mode deux joueurs.
      */
     void affichage2Joueurs();
 
     /**
      * @brief Boucle principale du jeu en mode deux joueurs (affichage + interactions).
      */
     void run2Joueurs();
 
     /**
      * @brief Retourne le record de distance réalisé dans le jeu.
      * @return Record sous forme de chaîne de caractères.
      */
     string getRecord();
 };
 
#endif
 