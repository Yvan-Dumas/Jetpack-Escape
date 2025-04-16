#include <iostream>
#include "AffichageGraphique.h"

using namespace std;

int main() { 
    const int totalOptions = 4;
    int selectedOption = 0;

    AffichageGraphique affichage;
    affichage.initSDL();
    
    if (!affichage.initMenu()) {
        return -1;
    }

    bool arret_brutal = false; //arret brutal permet de bien fermer l'entiereté du jeu si on appuie sur la croix.
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                arret_brutal = true;
            }
            // Sélection des boutons au clavier 
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % totalOptions;
                        break;
                    case SDLK_RETURN:
                        running = false;
                        break;
                }
            }
            // Sélection des boutons à la souris  
            else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                for (int i = 0; i < totalOptions; i++) {
                    SDL_Rect optionRect = {  260, 250 + i * 80, 280, 70 };
                    if (mouseX >= optionRect.x && mouseX <= optionRect.x + optionRect.w &&
                        mouseY >= optionRect.y && mouseY <= optionRect.y + optionRect.h) {
                        selectedOption = i;
                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                            running = false;
                        }
                    }
                }
            }
            if (selectedOption == 2 && running == false) {
                bool affichageAide = true;
            
                while (affichageAide) {
                    SDL_PollEvent(&event);
                    
                    if (event.type == SDL_QUIT) {
                        affichageAide = false;
                        running = false;
                    }
            
                    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX2, mouseY2;
                        SDL_GetMouseState(&mouseX2, &mouseY2);
                        SDL_Rect retourBtn = { 260, 500, 280, 50 };
            
                        if (mouseX2 >= retourBtn.x && mouseX2 <= retourBtn.x + retourBtn.w &&
                            mouseY2 >= retourBtn.y && mouseY2 <= retourBtn.y + retourBtn.h) {
                            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                                affichageAide = false;
                            }
                        }
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_ESCAPE) {
                                affichageAide = false;
                            }
                        }
                    }
                    affichage.renderAide();
                    SDL_Delay(10);
                }
                selectedOption = 0;
                running = true;
            }
        }

        affichage.renderMenu(selectedOption);
        SDL_Delay(100);
    }
    if (!arret_brutal) {
        if (selectedOption == 0) {
            affichage.run();
        }
        if (selectedOption == 1) {
            affichage.run2Joueurs();
        } 
    }
    
    return 0;
}