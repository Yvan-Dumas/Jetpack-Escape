#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "AffichageGraphique.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
TTF_Font* policetitre = NULL; 
int selectedOption = 0;

const char* menuOptions[] = {"Jouer au mode 1 joueur", "Jouer au mode 2 joueur","Comment jouer ?", "Quitter"};
const int totalOptions = 4;

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("Erreur TTF: %s\n", TTF_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Menu SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur Window: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur Renderer: %s\n", SDL_GetError());
        return 0;
    }

    font = TTF_OpenFont("data/polices/gooddog.ttf", 50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/polices/gooddog.ttf", 50);
    if (font == nullptr)
    {
        cout << "Failed to load gooddog.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    policetitre = TTF_OpenFont("data/polices/policetitre.ttf", 70);
    if (policetitre == nullptr)
        policetitre = TTF_OpenFont("../data/polices/policetitre.ttf", 70);
    if (policetitre == nullptr)
    {
        cout << "Failed to load policetitre.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    return 1;
}

void renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderMenu() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Couleur
    SDL_Color color = {255, 255, 255, 255};

    // Afficher le titre
    renderText("Jetpack Escape", 120, 50, color, policetitre);

    // Rendu du menu
    for (int i = 0; i < totalOptions; i++) {
        SDL_Rect rect = { 220, 200 + i * 50, 400, 40 };
        SDL_SetRenderDrawColor(renderer, (i == selectedOption) ? 0 : 100, (i == selectedOption) ? 255 : 100, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        // Affiche le texte des options
        renderText(menuOptions[i], 250, 210 + i * 50, color, font);
    }

    SDL_RenderPresent(renderer);
}

void cleanUp() {
    if (font) TTF_CloseFont(font);
    if (policetitre) TTF_CloseFont(policetitre);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main() {
    if (!initSDL()) {
        return -1;
    }

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
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
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                for (int i = 0; i < totalOptions; i++) {
                    SDL_Rect optionRect = { 220, 200 + i * 50, 400, 40 };
                    if (mouseX >= optionRect.x && mouseX <= optionRect.x + optionRect.w &&
                        mouseY >= optionRect.y && mouseY <= optionRect.y + optionRect.h) {
                        selectedOption = i;
                        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                            running = false;
                        }
                    }
                }
            }
        }
        renderMenu();
        SDL_Delay(100);
    }

    if (selectedOption == 0) {
        AffichageGraphique aff; // Initialise l'affichage graphique
        aff.run();
    }
    if (selectedOption == 1) {
        AffichageGraphique aff; // Initialise l'affichage graphique
        aff.run2Joueurs();
    }
    if (selectedOption == 2) {
        //affichageAide(); 
    }

    cleanUp();
    return 0;
}

void affichageAide(){
    

}