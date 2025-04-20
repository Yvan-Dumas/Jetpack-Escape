/**
 * @file SDLSprite.h
 * @brief Définition de la classe SDLSprite
 */

#ifndef _SDLSPRITE_H
#define _SDLSPRITE_H
 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstring>
 
 /**
  * @class SDLSprite
  * @brief Gère le chargement, la conversion, et l'affichage de sprites en SDL2.
  * Cette classe permet de charger une image à partir d'un fichier,
  * de la convertir en texture SDL, et de l'afficher à l'écran.
  * Cette classe est largement inspirée de l'exemple PAC-MAN du cours de LIFAPCD.
  */
 class SDLSprite
 {
 private:
     SDL_Surface* m_surface;     ///< Surface SDL
     SDL_Texture* m_texture;     ///< Texture SDL utilisée pour le rendu
     bool m_hasChanged;          ///< Indique si la surface a été modifiée depuis la dernière conversion en texture
 
 public:
     /**
      * @brief Constructeur par défaut.
      *
      * Initialisation des données membres. 
      */
     SDLSprite();
 
     /**
      * @brief Destructeur.
      *
      * Libère la surface et la texture associées au sprite.
      */
     ~SDLSprite();
 
     /**
      * @brief Charge une image depuis un fichier.
      * @param filename Chemin vers le fichier image.
      * @param renderer Le renderer SDL utilisé pour créer la texture.
      */
     void loadFromFile(const char *filename, SDL_Renderer *renderer);
 
     /**
      * @brief Crée une texture SDL à partir de la surface actuelle.
      * @param renderer Le renderer SDL utilisé pour créer la texture.
      */
     void loadFromCurrentSurface(SDL_Renderer *renderer);
 
     /**
      * @brief Dessine le sprite à l'écran.
      * @param renderer Le renderer SDL utilisé pour l'affichage.
      * @param x Position X du sprite.
      * @param y Position Y du sprite.
      * @param w Largeur du sprite (si -1, la largeur de la surface est utilisée).
      * @param h Hauteur du sprite (si -1, la hauteur de la surface est utilisée).
      */
     void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);
 
     /**
      * @brief Accède à la texture SDL du SDLSprite.
      * @return Un pointeur vers la texture SDL.
      */
     SDL_Texture* getTexture() const;
 
     /**
      * @brief Définit une nouvelle surface SDL pour le sprite.
      * @param surf Pointeur vers la surface SDL à utiliser.
      */
     void setSurface(SDL_Surface *surf);
 };
 
 #endif
 