#include "AffichageGraphique.h"
using namespace std;

const int TAILLE_SPRITE = 32*2;
const int HAUTEUR = 10;
const int LARGEUR = 30;

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

    //Initialisation de TTF (utilisé pour le texte)
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

    // Creation de la fenetre
    window = SDL_CreateWindow("JetpackEscape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation images
    im_perso1.loadFromFile("../data/images/perso32.png", renderer);
    im_perso2.loadFromFile("../data/images/perso32.png", renderer);

    im_toit.loadFromFile("../data/images/toit32.png", renderer);
    im_sol.loadFromFile("../data/images/sol32.png", renderer);
    im_bloc_sol.loadFromFile("../data/images/bloc_sol32.png", renderer);

    im_obstacle.loadFromFile("../data/images/obstacles/obstacle32.png", renderer);
    im_rat.loadFromFile("../data/images/obstacles/rat32.png", renderer);

    im_piece.loadFromFile("../data/images/piece32.png", renderer);
    im_vie.loadFromFile("../data/images/coeur32.png", renderer);
    im_vies0.loadFromFile("../data/images/vies/vies032.png", renderer);
    im_vies1.loadFromFile("../data/images/vies/vies132.png", renderer);
    im_vies2.loadFromFile("../data/images/vies/vies232.png", renderer);
    im_vies3.loadFromFile("../data/images/vies/vies332.png", renderer);
    im_vies4.loadFromFile("../data/images/vies/vies432.png", renderer);

    im_carburant.loadFromFile("../data/images/carburant32.png", renderer);

    im_carburant0.loadFromFile("../data/images/carburant/carburant032.png", renderer);
    im_carburant1.loadFromFile("../data/images/carburant/carburant132.png", renderer);
    im_carburant2.loadFromFile("../data/images/carburant/carburant232.png", renderer);
    im_carburant3.loadFromFile("../data/images/carburant/carburant332.png", renderer);
    im_fond.loadFromFile("../data/images/background.png", renderer);

    // Initialisation des polices
    VT323 = TTF_OpenFont("../data/polices/VT323.ttf", 50);
    if (VT323 == nullptr)
    {
        cout << "Erreur de chargement VT323.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    PS2P = TTF_OpenFont("../data/polices/PS2P.ttf", 50);
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
        SDL_Quit();
        exit(1);
    } else {
    curseurPerso = SDL_CreateColorCursor(curseurSurface, 0, 0); 
    SDL_SetCursor(curseurPerso);
    SDL_FreeSurface(curseurSurface);
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

AffichageGraphique::~AffichageGraphique() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (VT323) TTF_CloseFont(VT323);
    if (PS2P) TTF_CloseFont(PS2P);
    if (curseurPerso) SDL_FreeCursor(curseurPerso);
    SDL_Quit();
}

void AffichageGraphique::affichage() {
    // couleurs
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};
    SDL_Color orange = {236, 88, 0, 255};


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
    im_perso1.draw(renderer,   5*TAILLE_SPRITE, (HAUTEUR-perso1.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
    
    //Placement des obstacles
    for (const Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();
        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    switch (obs.getID()) {
                        case 4: 
                            im_rat.draw(renderer, (obsX + i)*TAILLE_SPRITE, (HAUTEUR-(obsY + j))*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                        break;
                        default:
                            im_obstacle.draw(renderer, (obsX + i)*TAILLE_SPRITE, (HAUTEUR-(obsY + j))*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                        break;
                    }
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

    // Affichage du record de distance
    string texte = "Record: " + partie.record + "m";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 0*TAILLE_SPRITE, jaune, VT323);
    
    // Affichage de la distance parcourue
    texte =  "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);

    // Affichage du nb de vies
    switch (perso1.getNbVies()) {
    case 1:
        im_vies1.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 2:
        im_vies2.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 3:
        im_vies3.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 4:
        im_vies4.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    default:
        im_vies0.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    }

    // Affichage du carburant
    int niveau = (int)ceil(perso1.carburant);
    switch (niveau) {
    case 3:
        im_carburant3.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
    case 2:
        im_carburant2.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
    case 1:
        im_carburant1.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
    case 0:
        im_carburant0.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
    default:
        break;
    }
    // Affichage du carburant (texte)
    stringstream stringstream;
    stringstream << fixed << setprecision(2) << perso1.carburant;
    texte = stringstream.str() + "L/3L";
    renderText(texte.c_str(), 5*TAILLE_SPRITE,  11.5*TAILLE_SPRITE + 125, orange, VT323);

    //Affichage du nombre de pièces récoltées
    texte = to_string(perso1.getNbPieces());
    im_piece.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 180, TAILLE_SPRITE, TAILLE_SPRITE);
    renderText(texte.c_str(), 1.7*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 190, blanc, VT323);

    //Affichage d'un message en cas de conversion pièces en vie.
    if(piecesEnVie) {
        texte = "Vous avez obtenu une vie en echange de vos 5 pieces";
        renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 240, blanc, VT323);
    }
}

void AffichageGraphique::afficherGameOver() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
    SDL_RenderClear(renderer);

    // Couleurs
    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    // Affichage texte Game Over
    renderText("GAME OVER", 700, 200, rouge, PS2P);

    // Infos de fin de partie
    const Personnage& perso1 = partie.getPerso1();
    string texte;
    texte = "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 650, 300, blanc, VT323);
    texte = "Pieces recoltees : " + to_string(perso1.getNbPieces());
    renderText(texte.c_str(), 650, 360, blanc, VT323);
    texte = "Record actuel : " + partie.record + "m";
    renderText(texte.c_str(), 650, 420, blanc, VT323);
    renderText("Appuyez sur ECHAP pour quitter", 600, 800, blanc, VT323);
    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
        renderText("Vous avez realisé le record", 650, 600, blanc, PS2P);
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
    while (ok) {  
        ok = partie.actionsAutomatiques(HAUTEUR,LARGEUR);
        while (SDL_PollEvent(&events)) { 
            if (events.type == SDL_QUIT)
                ok = false; // Si l'utilisateur a cliqué sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN) { // Si une touche est enfoncée
                switch (events.key.keysym.scancode) {
                case SDL_SCANCODE_W: // Si la touche z est enfoncée (clavier azerty)
                    partie.actionsClavier('z',HAUTEUR-1);                 
                    break;
                case SDL_SCANCODE_ESCAPE: // Si la touche echap est enfoncée
                    ok = false;
                    break;
                case SDL_SCANCODE_A: // Si la touche q est enfoncée (clavier azerty)
                    ok = false;
                    break;
                default:
                    break;
                }
            }
            
        }
        affichage();

        // Défilement de l'arrière plan
        int fondLargeur, fondHauteur;
        SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
        offset_x = (offset_x - 50 + fondLargeur) % fondLargeur;
        
        // Timer pour l'affichage du message
        if (partie.acheterVieSiPossible()){
            piecesEnVie = true;
            debutMessage = SDL_GetTicks();
        }
        if (piecesEnVie && SDL_GetTicks()-debutMessage>5000) piecesEnVie = false ; 

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    afficherGameOver();
}

void AffichageGraphique::affichage2Joueurs() {
    // couleurs
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};
    SDL_Color orange = {236, 88, 0, 255};


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

    // Affichage des personnages
    const Personnage& perso1 = partie.getPerso1();
    const Personnage& perso2 = partie.getPerso2();
    im_perso1.draw(renderer, 5*TAILLE_SPRITE, (HAUTEUR-perso1.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
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
                   switch (obs.getID()) {
                       case 4: 
                           im_rat.draw(renderer, (obsX + i)*TAILLE_SPRITE, (HAUTEUR-(obsY + j))*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                       break;
                       default:
                           im_obstacle.draw(renderer, (obsX + i)*TAILLE_SPRITE, (HAUTEUR-(obsY + j))*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                       break;
                   }
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

    // Affichage du record de distance
    string texte = "Record: " + partie.record + "m";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 0*TAILLE_SPRITE, jaune, VT323);
   
    // Affichage de la distance parcourue
    texte =  "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(texte.c_str(), 11*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);

    //---- Affichage J1 ----
    texte =  "J1";
    renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);
    // Affichage du nb de vies J1
    switch (perso1.getNbVies()) {
    case 1:
        im_vies1.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 2:
        im_vies2.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 3:
        im_vies3.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 4:
        im_vies4.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    default:
        im_vies0.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    }
    // Affichage du carburant J1
    int niveau = (int)ceil(perso1.carburant);
    switch (niveau) {
   case 3:
       im_carburant3.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
       break;
   case 2:
       im_carburant2.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
       break;
   case 1:
       im_carburant1.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
       break;
   case 0:
       im_carburant0.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
   default:
       break;
   }
    // Affichage du carburant (texte) J1
    stringstream stringstreamJ1;
    stringstreamJ1 << fixed << setprecision(2) << perso1.carburant;
    texte = stringstreamJ1.str() + "L/3L";
    renderText(texte.c_str(), 5*TAILLE_SPRITE,  11.5*TAILLE_SPRITE + 125, orange, VT323);
    //Affichage du nombre de pièces récoltées J1
    texte = to_string(perso1.getNbPieces());
    im_piece.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 180, TAILLE_SPRITE, TAILLE_SPRITE);
    renderText(texte.c_str(), 1.7*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 190, blanc, VT323);

    // ---- Affichage J2 ----
    texte =  "J2";
    renderText(texte.c_str(), 29*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);
    // Affichage du nb de vies J1
    switch (perso2.getNbVies()) {
    case 1:
        im_vies1.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 2:
        im_vies2.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 3:
        im_vies3.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    case 4:
        im_vies4.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    default:
        im_vies0.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 50, TAILLE_SPRITE*4, TAILLE_SPRITE);
        break;
    }
    // Affichage du carburant J2
    int niveau2 = (int)ceil(perso2.carburant);
    switch (niveau2) {
        case 3:
            im_carburant3.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
        case 2:
            im_carburant2.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
        case 1:
            im_carburant1.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        break;
        case 0:
            im_carburant0.draw(renderer, 25.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 100, TAILLE_SPRITE*4, TAILLE_SPRITE*1.5);
        default:
        break;
    }
    // Affichage du carburant (texte) J2
    stringstream stringstreamJ2;
    stringstreamJ2 << fixed << setprecision(2) << perso2.carburant;
    texte = stringstreamJ2.str() + "L/3L";
    renderText(texte.c_str(), 22.5*TAILLE_SPRITE,  11.5*TAILLE_SPRITE + 125, orange, VT323);
    //Affichage du nombre de pièces récoltées J1
    texte = to_string(perso1.getNbPieces());
    im_piece.draw(renderer, 28.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 180, TAILLE_SPRITE, TAILLE_SPRITE);
    renderText(texte.c_str(), 28*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 190, blanc, VT323);


    //Affichage d'un message en cas de conversion pièces en vie. 
    if(piecesEnVie) {
        texte = "Vous avez obtenu une vie en echange de vos 5 pieces";
        renderText(texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 240, blanc, VT323);
    }
}

void AffichageGraphique::run2Joueurs() {
    init();
    SDL_Event events;
    bool ok = true;

    Uint32 startime = SDL_GetTicks(), nt;
    while (ok){
        ok = partie.actionsAutomatiques2Joueurs(HAUTEUR,LARGEUR);
        while (SDL_PollEvent(&events)) { 
            if (events.type == SDL_QUIT)
                ok = false;
                switch (events.key.keysym.scancode) {
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

    // Défilement de l'arrière plan
    int fondLargeur, fondHauteur;
    SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
    offset_x = (offset_x - 50 + fondLargeur) % fondLargeur;
 
    // Timer pour l'affichage du message
    if (partie.acheterVieSiPossible()){
        piecesEnVie = true;
        debutMessage = SDL_GetTicks();
    }
    if (piecesEnVie && SDL_GetTicks()-debutMessage>5000) piecesEnVie = false ; 

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
    }
    afficherGameOver();
}