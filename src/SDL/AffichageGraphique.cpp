#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "AffichageGraphique.h"

using namespace std;

const int TAILLE_SPRITE = 64;
const int HAUTEUR = 10;
const int LARGEUR = 30;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS AffichageGraphique =============== //


string AffichageGraphique::getRecord(){
    return partie.record;
}


void AffichageGraphique::init() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        avecson = false;
    }
    else
        avecson = true;


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
    im_perso.loadFromFile("../data/images/perso32.png", renderer);
    im_perso2.loadFromFile("../data/images/perso32.png", renderer);

    im_toit.loadFromFile("../data/images/toit32.png", renderer);
    im_sol.loadFromFile("../data/images/sol32.png", renderer);
    im_bloc_sol.loadFromFile("../data/images/bloc_sol32.png", renderer);

    im_obstacle.loadFromFile("../data/images/obstacle32.png", renderer);

    im_piece.loadFromFile("../data/images/piece32.png", renderer);
    im_vie.loadFromFile("../data/images/coeur32.png", renderer);
    im_vies0.loadFromFile("../data/images/vies/vies032.png", renderer);
    im_vies1.loadFromFile("../data/images/vies/vies132.png", renderer);
    im_vies2.loadFromFile("../data/images/vies/vies232.png", renderer);
    im_vies3.loadFromFile("../data/images/vies/vies332.png", renderer);
    im_vies4.loadFromFile("../data/images/vies/vies432.png", renderer);

    im_carburant.loadFromFile("../data/images/carburant32.png", renderer);
    im_fond.loadFromFile("../data/images/background.png", renderer);

    // POLICE
    police1 = TTF_OpenFont("data/polices/policebase1.ttf", 50);
    if (police1 == nullptr)
        police1 = TTF_OpenFont("../data/polices/policebase1.ttf", 50);
    if (police1 == nullptr)
    {
        cout << "Failed to load policebase1.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    police2 = TTF_OpenFont("data/polices/policebase2.ttf", 50);
    if (police2 == nullptr)
        police2 = TTF_OpenFont("../data/polices/policebase2.ttf", 50);
    if (police2 == nullptr)
    {
        cout << "Failed to load policebase2.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    VT323 = TTF_OpenFont("data/polices/VT323.ttf", 50);
    if (VT323 == nullptr)
        VT323 = TTF_OpenFont("../data/polices/VT323.ttf", 50);
    if (VT323 == nullptr)

    PS2P = TTF_OpenFont("data/polices/PS2P.ttf", 50);
    if (PS2P == nullptr)
        PS2P = TTF_OpenFont("../data/polices/PS2P.ttf", 50);
    if (PS2P == nullptr)

    // SONS
        if (avecson)
        {
            son = Mix_LoadWAV("data/son.wav");
            if (son == nullptr)
                son = Mix_LoadWAV("../data/son.wav");
            if (son == nullptr)
            {
                cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl;
                avecson = false;
            }
        }
    }


void AffichageGraphique::renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

AffichageGraphique::~AffichageGraphique()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (avecson)
        Mix_Quit();
    SDL_Quit();
}

void AffichageGraphique::affichage() {
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    // Scroll du fond
    int fondLargeur, fondHauteur;
    SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);

    for (int x = -fondLargeur + offset_x; x < 1920; x += fondLargeur) {
        for (int y = 0; y < 1080; y += fondHauteur) {
            im_fond.draw(renderer, x, y, fondLargeur, fondHauteur);
        }
    }

    // Affichage de la bordure supérieure (toit)
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_toit.draw(renderer, i*TAILLE_SPRITE , 0, TAILLE_SPRITE, TAILLE_SPRITE);
    }

    // Affichage de la bordure inférieure (sol)
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_sol.draw(renderer, i*TAILLE_SPRITE , 11*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    }
    for(unsigned int i = 0; i<LARGEUR; i++) {
        for (unsigned int j=12; j<17; j++) {
            im_bloc_sol.draw(renderer, i*TAILLE_SPRITE , j*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
        }
    }

    // Affichage du personnage
    const Personnage& perso1 = partie.getPerso1();
    im_perso.draw(renderer,   5*TAILLE_SPRITE, (HAUTEUR-perso1.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    
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
    // Couleur de survol de la souris
    SDL_Color color = {0, 0, 0, 0};

    // Afficher les textes
    string texte =  "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, color, VT323);

    texte = "Record: " + partie.record + "m";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 12.2*TAILLE_SPRITE, color, VT323);
    
    switch (perso1.getNbVies()) {
    case 1:
        im_vies1.draw(renderer, 0.5*TAILLE_SPRITE, 12.9*TAILLE_SPRITE, TAILLE_SPRITE*2, TAILLE_SPRITE/2);
        break;
    case 2:
        im_vies2.draw(renderer, 0.5*TAILLE_SPRITE, 12.9*TAILLE_SPRITE, TAILLE_SPRITE*2, TAILLE_SPRITE/2);
        break;
    case 3:
        im_vies3.draw(renderer, 0.5*TAILLE_SPRITE, 12.9*TAILLE_SPRITE, TAILLE_SPRITE*2, TAILLE_SPRITE/2);
        break;
    case 4:
        im_vies4.draw(renderer, 0.5*TAILLE_SPRITE, 12.9*TAILLE_SPRITE, TAILLE_SPRITE*2, TAILLE_SPRITE/2);
        break;
    default:
        im_vies0.draw(renderer, 0.5*TAILLE_SPRITE, 12.9*TAILLE_SPRITE, TAILLE_SPRITE*2, TAILLE_SPRITE/2);
        break;
    }
    
    texte = "Carburant : " + to_string(static_cast<int>(round(perso1.carburant * 1000))/ 1000.0) + "L";
    renderText(texte.c_str(), 120, 14*TAILLE_SPRITE, color, police2);
   
    texte = "Vous avez recolte " + to_string(perso1.getNbPieces()) + " pieces";
    renderText(texte.c_str(), 120, 18*TAILLE_SPRITE, color, police2);
}

void AffichageGraphique::afficherGameOver() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
    SDL_RenderClear(renderer);

    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    // Titre
    renderText("GAME OVER", 700, 200, rouge, police1);

    // Infos de fin de partie
    const Personnage& perso1 = partie.getPerso1();
    string texte;

    texte = "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 700, 300, blanc, police2);

    texte = "Pieces recoltees : " + to_string(perso1.getNbPieces());
    renderText(texte.c_str(), 700, 360, blanc, police2);

    texte = "Record actuel : " + partie.record + "m";
    renderText(texte.c_str(), 700, 420, blanc, police2);

    renderText("Appuyez sur ECHAP pour quitter", 700, 500, blanc, police2);

    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
        renderText("Vous avez realisee le record", 700, 600, blanc, police1);
    }

    SDL_RenderPresent(renderer);

    // Attente d'une touche pour quitter
    SDL_Event event;
    bool quitter = false;
    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quitter = true;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                quitter = true;
        }
        SDL_Delay(100);
    }
}

void AffichageGraphique::run() {
    init();
    SDL_Event events;
    bool ok = true;

    Uint32 startime = SDL_GetTicks(), nt;
    
    while (ok)
    {
        
        nt = SDL_GetTicks();
        if (nt - startime > 0)
        {
            ok = partie.actionsAutomatiques(HAUTEUR,LARGEUR);
            startime = nt;
        }

        while (SDL_PollEvent(&events))
        { 
            if (events.type == SDL_QUIT)
                ok = false; // Si l'utilisateur a cliqué sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN) { // Si une touche est enfoncee
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    partie.actionsClavier('z',HAUTEUR-1);
                    //if (avecson) {Mix_PlayChannel(-1, son, 0);}
                    break;
                case SDL_SCANCODE_ESCAPE:
                    ok = false;
                    break;
                case SDL_SCANCODE_A:
                    ok = false;
                    break;
                default:
                    break;
                }
            }
            
        }
        affichage();

        int fondLargeur, fondHauteur;
        SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
        offset_x = (offset_x - 6 + fondLargeur) % fondLargeur;
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    afficherGameOver();
}

void AffichageGraphique::affichage2Joueurs() {
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    // Scroll du fond
    int fondLargeur, fondHauteur;
    SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
    for (int x = -fondLargeur + offset_x; x < 1920; x += fondLargeur) {
        for (int y = 0; y < 1080; y += fondHauteur) {
            im_fond.draw(renderer, x, y, fondLargeur, fondHauteur);
        }
    }

    // Affichage de la bordure supérieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_toit.draw(renderer, i*TAILLE_SPRITE , 0, TAILLE_SPRITE, TAILLE_SPRITE);
    }

    // Affichage de la bordure inférieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        im_toit.draw(renderer, i*TAILLE_SPRITE , 11*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    }

    // Affichage des personnages
    const Personnage& perso1 = partie.getPerso1();
    const Personnage& perso2 = partie.getPerso2();
    im_perso.draw(renderer, 5*TAILLE_SPRITE, (HAUTEUR-perso1.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    im_perso2.draw(renderer, 5*TAILLE_SPRITE, (HAUTEUR-perso2.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

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
    // Couleur de survol de la souris
    SDL_Color color = {0, 0, 0, 0};

    // Afficher les textes
    string texte = "Vies : " + to_string(perso1.getNbVies());
    renderText(texte.c_str(), 120, 12*TAILLE_SPRITE, color, police2);
    texte = "Carburant : " + to_string(static_cast<int>(round(perso1.carburant * 1000))/ 1000.0) + "L";
    renderText(texte.c_str(), 120, 14*TAILLE_SPRITE, color, police2);
    texte =  "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 120, 16*TAILLE_SPRITE, color, police2);
    texte = "Vous avez recolte " + to_string(perso1.getNbPieces()) + " pieces";
    renderText(texte.c_str(), 120, 18*TAILLE_SPRITE, color, police2);
    texte = "Record: " + partie.record + "m";
    renderText(texte.c_str(), 120, 20*TAILLE_SPRITE, color, police2);
    

    //Textes de débugages
    const vector<Obstacle> tabobstacles = partie.getObstacles();
    if (!tabobstacles.empty()){
        const Obstacle& obs = tabobstacles.front();
        renderText((to_string(obs.getX())+","+to_string(obs.getY())).c_str(),0,14*TAILLE_SPRITE,color,police1);
    }

    const vector<Objet> tabobjet = partie.getObjets();
    if(!tabobjet.empty()){
        const Objet& obj = tabobjet.back();
        renderText((to_string(obj.getX())+","+to_string(obj.getY())).c_str(),0,16*TAILLE_SPRITE,color,police1);
    }
    
    renderText((to_string(perso1.getHauteur())).c_str(),0,12*TAILLE_SPRITE,color,police1);
}

void AffichageGraphique::run2Joueurs() {
    init();
    SDL_Event events;
    bool ok = true;
    Uint32 startime = SDL_GetTicks(), nt;
    while (ok){
        nt = SDL_GetTicks();
        if (nt - startime > 0)
        {
            ok = partie.actionsAutomatiques2Joueurs(HAUTEUR,LARGEUR);
            startime = nt;
        }

        while (SDL_PollEvent(&events)) { 
            if (events.type == SDL_QUIT)
                ok = false; // Si l'utilisateur a cliqué sur la croix de fermeture          else if (events.type == SDL_KEYDOWN) { // Si une touche est enfoncee
                switch (events.key.keysym.scancode) {
                /* case SDL_SCANCODE_W:
                    partie.actionsClavier2Joueurs('z', HAUTEUR-1);
                    break;
                case SDL_SCANCODE_L:
                    partie.actionsClavier2Joueurs('l', HAUTEUR-1);
                    break;
                */
                case SDL_SCANCODE_ESCAPE:
                    ok = false;
                    break;
                case SDL_SCANCODE_A:
                    ok = false;
                    break;
                default:
                    break;
                }
            
            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            if (keystates[SDL_SCANCODE_W]) {
                partie.actionsClavier2Joueurs('z', HAUTEUR - 1); // Joueur 1
            }
            if (keystates[SDL_SCANCODE_L]) {
                partie.actionsClavier2Joueurs('l', HAUTEUR - 1); // Joueur 2
            }
        
        }
        affichage2Joueurs();

        int fondLargeur, fondHauteur;
        SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
        offset_x = (offset_x - 6 + fondLargeur) % fondLargeur;
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    afficherGameOver();
}