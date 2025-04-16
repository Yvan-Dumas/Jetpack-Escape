#include <iostream>
#include "AffichageGraphique.h"

using namespace std;

// Fonction pour vérifier si la souris est dans un rectangle
bool estDansRectangle(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w &&
           y >= rect.y && y <= rect.y + rect.h;
}

// Procédure pour l'affichage de l’aide
void afficherAide(AffichageGraphique& affichage) {
    bool aideActive = true;
    SDL_Event event;

    while (aideActive) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                aideActive = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                aideActive = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Rect retourRect = {260, 500, 280, 50};
                if (estDansRectangle(mouseX, mouseY, retourRect)) {
                    aideActive = false;
                }
            }
        }

        affichage.renderAide();
        SDL_Delay(10);
    }
}

int main() {
    const int totalOptions = 4;
    int selectedOption = 0;

    AffichageGraphique affichage;

    // Initialisation SDL
    affichage.initSDL();

    if (!affichage.initMenu()) {
        return -1;
    }

    bool arretBrutal = false;
    bool menuActif = true;
    SDL_Event event;
    while (menuActif) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                arretBrutal = true;
                menuActif = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % totalOptions;
                        break;
                    case SDLK_RETURN:
                        menuActif = false;
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                for (int i = 0; i < totalOptions; ++i) {
                    SDL_Rect optionRect = {260, 250 + i * 80, 280, 70};
                    if (estDansRectangle(mouseX, mouseY, optionRect)) {
                        selectedOption = i;
                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                            menuActif = false;
                        }
                    }
                }
            }
        }

        // Afficher l'aide
        if (selectedOption == 2 && !arretBrutal && !menuActif) {
            afficherAide(affichage);
            selectedOption = 0;
            menuActif = true;
        }

        affichage.renderMenu(selectedOption);
        SDL_Delay(100);
    }

    if (!arretBrutal) {
        if (selectedOption == 0) {
            affichage.run();
        } else if (selectedOption == 1) {
            affichage.run2Joueurs();
        }
    }

    return 0;
}