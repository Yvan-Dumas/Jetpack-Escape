#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "AffichageGraphique.h"

using namespace std;

const int TAILLE_SPRITE = 32;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS AffichageGraphique =============== //

void AffichageGraphique::init() {
    Partie partie;
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int dimx, dimy;
    /*dimx = partie.getConstTerrain().getDimX();
    dimy = partie.getConstTerrain().getDimY();
    dimx = dimx * TAILLE_SPRITE;
    dimy = dimy * TAILLE_SPRITE;*/

    // Creation de la fenetre
    window = SDL_CreateWindow("JetpackEscape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_perso.loadFromFile("../data/perso32.png", renderer);


}

AffichageGraphique::~AffichageGraphique()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void AffichageGraphique::affichage()
{
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    int x, y;

    const Personnage& perso = partie.getPerso1();
    // Afficher les sprites des murs et des pastilles
    /*for (x = 0; x < ter.getDimX(); ++x)
        for (y = 0; y < ter.getDimY(); ++y)
            if (ter.getXY(x, y) == '#')
                im_mur.draw(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            else if (ter.getXY(x, y) == '.')
                im_pastille.draw(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);*/

    // Afficher le sprite de Pacman
    im_perso.draw(renderer,  5 * TAILLE_SPRITE, perso.getHauteur() * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

    /*
    // Afficher le sprite du Fantome
    //im_fantome.draw(renderer, fan.getX() * TAILLE_SPRITE, fan.getY() * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

    // Ecrire un titre par dessus
    SDL_Rect positionTitre;
    positionTitre.x = 270;
    positionTitre.y = 49;
    positionTitre.w = 100;
    positionTitre.h = 30;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTitre);*/
}

void AffichageGraphique::run()
{
    init();
    SDL_Event events;
    bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        nt = SDL_GetTicks();
        if (nt - t > 500)
        {
            partie.actionsAutomatiques(5,100);
            t = nt;
        }

        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            { // Si une touche est enfoncee
                bool mangePastille = false;
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_Z:
                    partie.actionsClavier('z',5);
                    break;
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

        // on affiche le partie sur le buffer caché
        affichage();

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}