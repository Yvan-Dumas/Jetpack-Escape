/**
 *@file AffichageGraphique.cpp
 *@brief Implémentation de la classe AffichageGraphique
 */

#include "AffichageGraphique.h"
#include <iostream>


using namespace std;

AffichageGraphique::AffichageGraphique() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur SDL: " << SDL_GetError() << endl;
    }


}
void AffichageGraphique::run(){
 // Création de la fenêtre
 SDL_Window* window = SDL_CreateWindow("Jetpack Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 243, SDL_WINDOW_SHOWN);
 if (!window) {
     cout << "Erreur de création de la fenêtre: " << SDL_GetError() << endl;
     SDL_Quit();
 }

 // Création du renderer
 SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
 if (!renderer) {
     cout << "Erreur de création renderer: " << SDL_GetError() << endl;
     SDL_DestroyWindow(window);
     SDL_Quit();
 }

 // Chargement de l'image
 SDL_Surface* image = SDL_LoadBMP("../data/met.bmp");
 if (!image) {
     cout << "Erreur chargement image: " << SDL_GetError() << endl;
     SDL_DestroyRenderer(renderer);  // Libérer le renderer
     SDL_DestroyWindow(window);  // Libérer la fenêtre
     SDL_Quit(); // Quitter si l'image ne se charge pas
 }

 // Création de la texture à partir de l'image
 SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer, image);
 SDL_FreeSurface(image);  // Libérer la surface, plus nécessaire après création de la texture

 if (!monImage) {
     cout << "Erreur de création de la texture: " << SDL_GetError() << endl;
     SDL_DestroyRenderer(renderer);  // Libérer le renderer
     SDL_DestroyWindow(window);  // Libérer la fenêtre
     SDL_Quit();  // Quitter si la texture ne se crée pas
 }

 // Affichage de la fenêtre et de l'image pendant 3 secondes
 SDL_RenderClear(renderer);  // Effacer l'écran
 SDL_RenderCopy(renderer, monImage, NULL, NULL);  // Copier l'image dans le renderer
 SDL_RenderPresent(renderer);  // Afficher l'image

 SDL_Delay(3000);  // Affiche la fenêtre pendant 3 secondes

 // Libération des ressources
 SDL_DestroyTexture(monImage);  // Libérer la texture
 SDL_DestroyRenderer(renderer);  // Libérer le renderer
 SDL_DestroyWindow(window);  // Libérer la fenêtre
 SDL_Quit();  // Quitter SDL

}