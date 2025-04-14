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
TTF_Font* PS2Pmini = NULL;
SDL_Cursor* curseurPerso = nullptr;

SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* boutonTexture = nullptr;
SDL_Texture* boutonHoverTexture = nullptr;

const char* menuOptions[] = {"1 joueur", "2 joueurs", "Comment jouer ?", "Quitter"};
const int totalOptions = 4;
int selectedOption = 0;

// Fonction pour l'initialisation des ressources SDL
int initSDL() { 
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 0;
    }

    //Initialisation de TTF (utilisé pour le texte)
    if (TTF_Init() == -1) {
        printf("Erreur TTF: %s\n", TTF_GetError());
        return 0;
    }

    // Creation de la fenetre
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

    // Police personnalisée
    PS2P = TTF_OpenFont("../data/polices/PS2P.ttf", 18);
    if (PS2P == nullptr)
    {
        cout << "Erreur de chargement PS2P.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    PS2Pmini = TTF_OpenFont("../data/polices/PS2P.ttf", 8);
    if (PS2Pmini == nullptr)
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

    // Image de fond avec titre et design du menu
    SDL_Surface* surface = IMG_Load("../data/images/menu/menu_background.png");
    if (!surface) {
        cout << "Erreur chargement image menu: " << IMG_GetError() << endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    // Image bouton
    SDL_Surface* surfaceBtn = IMG_Load("../data/images/menu/bouton.png");
    boutonTexture = SDL_CreateTextureFromSurface(renderer, surfaceBtn);
    SDL_FreeSurface(surfaceBtn);
    if (!boutonTexture) {
        cout << "Erreur chargement bouton.png : " << SDL_GetError() << endl;
    }

    // Image bouton survolé
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

string getRecord(){
    fstream fichier("../data/sauvegarde.txt", ios::in);
    if(fichier){
        string contenu;
        getline(fichier, contenu);
        fichier.close();
        return contenu;
    }
    else return "erreur lors du chargement du fichier";
}

void renderMenu() {
    // Affichage de l'image de fond
    if (backgroundTexture) {
        SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(renderer);
    }

    // Couleur
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};

    string texte = "Record: " + getRecord() + "m";
    renderText(texte.c_str(), 280, 125, jaune, PS2P);

    // Rendu du menu
    for (int i = 0; i < totalOptions; i++) {
        SDL_Rect dstRect = { 260, 250 + i * 80, 280, 70};
    
        SDL_Texture* textureToUse = (i == selectedOption) ? boutonHoverTexture : boutonTexture;
        SDL_RenderCopy(renderer, textureToUse, NULL, &dstRect);
    
        // Affichage centré des textes sur les boutons
        int textLargeur, textHauteur;
        TTF_SizeText(PS2P, menuOptions[i], &textLargeur, &textHauteur);
        int textX = dstRect.x + (dstRect.w - textLargeur) / 2;
        int textY = dstRect.y + (dstRect.h - textHauteur) / 2;
        renderText(menuOptions[i], textX, textY, blanc, PS2P);
    }
    SDL_RenderPresent(renderer);
}

void renderAide() {

    // Affichage de l'image de fond
    if (backgroundTexture) {
        SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(renderer);
    }

    // Couleur
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};

    // Titre
    string titre = "Comment jouer ?";
    renderText(titre.c_str(), 280, 125, jaune, PS2P);

    // Texte d’aide
    string texte =  "Le joueur 1 utilise Z pour voler";
    string texte2 = "Le joueur 2 utilise L pour voler";
    string texte3 = "Vous devez eviter les obstacles,";
    string texte4 = "- le plus longtemps possible";
    string texte5 = "- sans tomber a cours de carburant,";
    string texte6 = "- et en ayant toujours une vie.";

    renderText(texte.c_str(), 245, 300, blanc, PS2Pmini);
    renderText(texte2.c_str(), 245, 350, blanc, PS2Pmini);
    renderText(texte3.c_str(), 245, 400, blanc, PS2Pmini);
    renderText(texte4.c_str(), 245, 425, blanc, PS2Pmini);
    renderText(texte5.c_str(), 245, 450, blanc, PS2Pmini);
    renderText(texte6.c_str(), 245, 475, blanc, PS2Pmini);



    // Coordonnées du bouton
    SDL_Rect retourBtn = {260, 500, 280, 50};

    // Coordonnées souris
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Détection hover
    bool isHover = mouseX >= retourBtn.x && mouseX <= retourBtn.x + retourBtn.w &&
                   mouseY >= retourBtn.y && mouseY <= retourBtn.y + retourBtn.h;

    // Choix de la texture ou couleur en fonction du hover
    if (isHover) {
        SDL_RenderCopy(renderer, boutonHoverTexture, NULL, &retourBtn); //texture hover
    } else {
        SDL_RenderCopy(renderer, boutonTexture, NULL, &retourBtn); // texture normale
    }

    // Texte centré sur le bouton
    string retour = "Retour au menu";
    int textLargeur, textHauteur;
    TTF_SizeText(PS2P, retour.c_str(), &textLargeur, &textHauteur);
    int textX = retourBtn.x + (retourBtn.w - textLargeur) / 2;
    int textY = retourBtn.y + (retourBtn.h - textHauteur) / 2;
    renderText(retour.c_str(), textX, textY, blanc, PS2P);

    SDL_RenderPresent(renderer);
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

    bool arret_brutal = false;
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
                    SDL_PollEvent(&event); //récupérer les événements à chaque tour
                    
                    if (event.type == SDL_QUIT) {
                        affichageAide = false;
                        running = false; // Pour quitter complètement si on ferme la fenêtre
                    }
            
                    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX2, mouseY2;
                        SDL_GetMouseState(&mouseX2, &mouseY2);
                        SDL_Rect retourBtn = { 260, 500, 280, 50 }; // même rectangle que dans renderAide
            
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
                    renderAide();
                    SDL_Delay(10);
                }
                selectedOption = 0;
                running = true;
            }
            
        }

        renderMenu();
        SDL_Delay(100);
    }
    if (!arret_brutal) {
        if (selectedOption == 0) {
            AffichageGraphique aff; // Initialise affichage graphique
            aff.run();
        }
        if (selectedOption == 1) {
            AffichageGraphique aff; // Initialise affichage graphique
            aff.run2Joueurs();
        } 
    }
    cleanUp();
    return 0;
}