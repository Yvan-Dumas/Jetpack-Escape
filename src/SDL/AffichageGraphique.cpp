#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "AffichageGraphique.h"

using namespace std;

const int TAILLE_SPRITE = 32;
const int HAUTEUR = 10;
const int LARGEUR = 100;

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

    /*dimx = partie.getConstTerrain().getDimX();
    dimy = partie.getConstTerrain().getDimY();
    dimx = dimx * TAILLE_SPRITE;
    dimy = dimy * TAILLE_SPRITE;*/

    // Creation de la fenetre
    window = SDL_CreateWindow("JetpackEscape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_perso.loadFromFile("../data/perso32.png", renderer);
    im_toit.loadFromFile("../data/toit32.png", renderer);
    im_obstacle.loadFromFile("../data/obstacle32.png", renderer);
    im_piece.loadFromFile("../data/piece32.png", renderer);
    im_vie.loadFromFile("../data/coeur32.png", renderer);
    im_carburant.loadFromFile("../data/carburant32.png", renderer);

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

    // Affichage de la bordure supérieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_toit.draw(renderer, i*TAILLE_SPRITE , 0, TAILLE_SPRITE, TAILLE_SPRITE);
    }

    // Affichage de la bordure inférieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_toit.draw(renderer, i*TAILLE_SPRITE , 11*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    }

    // Affichage du personnage
    const Personnage& perso = partie.getPerso1();
    im_perso.draw(renderer,   5*TAILLE_SPRITE, (HAUTEUR-perso.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    
    //Placement des obstacles
    for (const Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();

        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    im_obstacle.draw(renderer, (obsX + i)*TAILLE_SPRITE, (HAUTEUR-(obsY + j))*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                }
            }
        }
    }

    //Placement des objets
    for (const Objet& obj : partie.getObjets()) {
        switch (obj.getID()){
            case 1:
                im_piece.draw(renderer, obj.getX()*TAILLE_SPRITE, (HAUTEUR - obj.getY())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            break;
            case 2:
                im_carburant.draw(renderer, obj.getX()*TAILLE_SPRITE, (HAUTEUR - obj.getY())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            break;
            case 3:
                im_vie.draw(renderer, obj.getX()*TAILLE_SPRITE, (HAUTEUR - obj.getY())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            default:
            break;
            } 
        }

    /*
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
    bool ok = true;

    Uint32 t = SDL_GetTicks(), nt;

    // tant que ce n'est pas la fin ...
    while (ok)
    {
        
        nt = SDL_GetTicks();
        if (nt - t > 500)
        {
            ok = partie.actionsAutomatiques(HAUTEUR,LARGEUR);
           //t = nt;
        }
        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        { 
            if (events.type == SDL_QUIT)
                ok = false; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            { // Si une touche est enfoncee
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    partie.actionsClavier('z',HAUTEUR-1);
                    break;
                case SDL_SCANCODE_ESCAPE:
                case SDLK_q:
                    ok = false;
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
        SDL_Delay(100);
    }
}