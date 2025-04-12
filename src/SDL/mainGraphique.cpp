#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "AffichageGraphique.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* PS2P = NULL;
SDL_Cursor* curseurPerso = nullptr;

SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* boutonTexture = nullptr;
SDL_Texture* boutonHoverTexture = nullptr;

int selectedOption = 0;

const char* menuOptions[] = {"1 joueur", "2 joueur","Comment jouer ?", "Quitter"};
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

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur SDL_image: %s\n", IMG_GetError());
        return 0;
    }    

    PS2P = TTF_OpenFont("../data/polices/PS2P.ttf", 18);
    if (PS2P == nullptr)
    {
        cout << "Erreur de chargement PS2P.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Curseur personnalisé
    SDL_Surface* curseurSurface = IMG_Load("../data/images/curseur.png");
    if (!curseurSurface) {
        cout << "Erreur chargement curseur: " << IMG_GetError() << endl;
    } else {
    curseurPerso = SDL_CreateColorCursor(curseurSurface, 0, 0); 
    SDL_SetCursor(curseurPerso);
    SDL_FreeSurface(curseurSurface);
    }

    SDL_Surface* surface = IMG_Load("../data/images/menu/menu_background.png");
    if (!surface) {
        cout << "Erreur chargement image menu: " << IMG_GetError() << endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    SDL_Surface* surfaceBtn = IMG_Load("../data/images/menu/bouton.png");
    boutonTexture = SDL_CreateTextureFromSurface(renderer, surfaceBtn);
    SDL_FreeSurface(surfaceBtn);
    if (!boutonTexture) {
        cout << "Erreur chargement bouton.png : " << SDL_GetError() << endl;
    }

    SDL_Surface* surfaceHover = IMG_Load("../data/images/menu/bouton_hover.png");
    boutonHoverTexture = SDL_CreateTextureFromSurface(renderer, surfaceHover);
    SDL_FreeSurface(surfaceHover);
    if (!boutonHoverTexture) {
        cout << "Erreur chargement bouton_hover.png : " << SDL_GetError() << endl;
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
    if (backgroundTexture) {
        SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(renderer);
    }

    // Couleur
    SDL_Color blanc = {255, 255, 255, 255};

    // Rendu du menu
    for (int i = 0; i < totalOptions; i++) {
        SDL_Rect dstRect = { 260, 250 + i * 80, 280, 70};
    
        SDL_Texture* textureToUse = (i == selectedOption) ? boutonHoverTexture : boutonTexture;
        SDL_RenderCopy(renderer, textureToUse, NULL, &dstRect);
    
        // Affichage des textes
        int textLargeur, textHauteur;
        TTF_SizeText(PS2P, menuOptions[i], &textLargeur, &textHauteur);
        int textX = dstRect.x + (dstRect.w - textLargeur) / 2;
        int textY = dstRect.y + (dstRect.h - textHauteur) / 2;
        renderText(menuOptions[i], textX, textY, blanc, PS2P);
    }
    SDL_RenderPresent(renderer);
}

void affichageAide(){
    
}

void cleanUp() {
    if (PS2P) TTF_CloseFont(PS2P);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (curseurPerso) SDL_FreeCursor(curseurPerso);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (boutonTexture) SDL_DestroyTexture(boutonTexture);
    if (boutonHoverTexture) SDL_DestroyTexture(boutonHoverTexture);
    IMG_Quit();
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
        }
        renderMenu();
        SDL_Delay(100);
    }

    if (selectedOption == 0) {
        AffichageGraphique aff; // Initialise affichage graphique
        aff.run();
    }
    if (selectedOption == 1) {
        AffichageGraphique aff; // Initialise affichage graphique
        aff.run2Joueurs();
    }
    if (selectedOption == 2) {
        //affichageAide(); 
    }
    cleanUp();
    return 0;
}