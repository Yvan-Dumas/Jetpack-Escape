#include "AffichageGraphique.h"
using namespace std;

const int TAILLE_SPRITE = 32*2;
const int HAUTEUR = 10;
const int LARGEUR = 30;


// ============= CLASS AffichageGraphique =============== //

AffichageGraphique::AffichageGraphique() {
    windowMenu = nullptr;
    rendererMenu = nullptr;
    PS2Pmini = nullptr;
    
    window = nullptr;
    renderer = nullptr;
    VT323 = nullptr;
    PS2PGros = nullptr;
    PS2P = nullptr;
    curseurPerso = nullptr;

    offset_x = 0;
    debutMessage = 0;
}

AffichageGraphique::~AffichageGraphique() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (rendererMenu) {
        SDL_DestroyRenderer(rendererMenu);
        rendererMenu = nullptr;
    }
    if (windowMenu) {
        SDL_DestroyWindow(windowMenu);
        windowMenu = nullptr;
    }
    
    // Fermer les polices avec vérification
    if (PS2P) {
        TTF_CloseFont(PS2P);
        PS2P = nullptr;
    }
    if (PS2Pmini) {
        TTF_CloseFont(PS2Pmini);
        PS2Pmini = nullptr;
    }
    if (PS2PGros) {
        TTF_CloseFont(PS2PGros);
        PS2Pmini = nullptr;
    }
    if (VT323) {
        TTF_CloseFont(VT323);
        VT323 = nullptr;
    }
    
    // pour le curseur personnalisé
    if (curseurPerso) {
        SDL_FreeCursor(curseurPerso);
        curseurPerso = nullptr;
    }    

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

string AffichageGraphique::getRecord(){
    return partie.record;
}

void AffichageGraphique::initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() == -1) {
        std::cout << "Erreur TTF: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Curseur personnalisé
    SDL_Surface* curseurSurface = IMG_Load("../data/images/curseur.png");
    if (!curseurSurface) {
        std::cout << "Erreur chargement curseur: " << IMG_GetError() << std::endl;
    } else {
        curseurPerso = SDL_CreateColorCursor(curseurSurface, 0, 0); 
        SDL_SetCursor(curseurPerso);
        SDL_FreeSurface(curseurSurface);
    } 
}

void AffichageGraphique::init() {
    // Creation de la fenetre de jeu
    window = SDL_CreateWindow("JetpackEscape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation images
    im_perso1.loadFromFile("../data/images/perso132.png", renderer);
    im_perso2.loadFromFile("../data/images/perso232.png", renderer);

    im_toit.loadFromFile("../data/images/toit32.png", renderer);
    im_sol.loadFromFile("../data/images/sol32.png", renderer);
    im_bloc_sol.loadFromFile("../data/images/bloc_sol32.png", renderer);

    im_obstacle.loadFromFile("../data/images/obstacles/obstacle32.png", renderer);
    im_obstacle3x1.loadFromFile("../data/images/obstacles/obstacle3x132.png", renderer);
    im_rat.loadFromFile("../data/images/obstacles/rat32.png", renderer);
    im_metro1.loadFromFile("../data/images/obstacles/metro132.png", renderer);
    im_metro2.loadFromFile("../data/images/obstacles/metro232.png", renderer);
    im_panneau_avertissement.loadFromFile("../data/images/obstacles/panneau_avertissement32.png", renderer);

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

    // Initialisation polices
    VT323 = TTF_OpenFont("../data/polices/VT323.ttf", 50);
    if (VT323 == nullptr)
    {
        cout << "Erreur de chargement VT323.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    PS2PGros = TTF_OpenFont("../data/polices/PS2P.ttf", 50);
    if (PS2PGros == nullptr)
    {
        cout << "Erreur de chargement PS2P.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

}

int AffichageGraphique::initMenu() { 
    // Creation de la fenetre
    windowMenu = SDL_CreateWindow("Menu SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!windowMenu) {
        printf("Erreur Window: %s\n", SDL_GetError());
        return 0;
    }

    rendererMenu = SDL_CreateRenderer(windowMenu, -1, SDL_RENDERER_ACCELERATED);
    if (!rendererMenu) {
        printf("Erreur Renderer: %s\n", SDL_GetError());
        return 0;
    }

    // Polices personnalisées
    PS2P = TTF_OpenFont("../data/polices/PS2P.ttf", 18);
    if (PS2P == nullptr)
    {
        cout << "Erreur de chargement PS2P.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    PS2Pmini = TTF_OpenFont("../data/polices/PS2P.ttf", 9);
    if (PS2Pmini == nullptr)
    {
        cout << "Erreur de chargement PS2P.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Initialisation images menu
    im_backgroundMenu.loadFromFile("../data/images/menu/menu_background.png", rendererMenu);
    im_boutonMenu.loadFromFile("../data/images/menu/bouton.png", rendererMenu);
    im_boutonHoverMenu.loadFromFile("../data/images/menu/bouton_hover.png", rendererMenu);

    return 1;
}

void AffichageGraphique::renderMenu(int selectedOption) {
    const char* menuOptions[] = {"1 joueur", "2 joueurs", "Comment jouer ?", "Quitter"};

    // Affichage de l'image de fond
    if (im_backgroundMenu.getTexture()) {
        im_backgroundMenu.draw(rendererMenu, 0, 0, 800, 600); 
    } else {
        SDL_SetRenderDrawColor(rendererMenu, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(rendererMenu);
    }

    // Couleur
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};

    string texte = "Record: " + getRecord() + "m";
    renderText(rendererMenu, texte.c_str(), 285, 125, jaune, PS2P);

    // Rendu du menu
    for (int i = 0; i < 4; i++) {
        SDL_Rect dstRect = { 260, 250 + i * 80, 280, 70};
    
        // Déterminer quelle texture utiliser pour le bouton
        SDLSprite* buttonSprite = (i == selectedOption) ? &im_boutonHoverMenu : &im_boutonMenu;
        if (buttonSprite->getTexture()) {
            buttonSprite->draw(rendererMenu, dstRect.x, dstRect.y, dstRect.w, dstRect.h);
        }
    
        // Affichage centré des textes sur les boutons
        int textLargeur, textHauteur;
        TTF_SizeText(PS2P, menuOptions[i], &textLargeur, &textHauteur);
        int textX = dstRect.x + (dstRect.w - textLargeur) / 2;
        int textY = dstRect.y + (dstRect.h - textHauteur) / 2;
        renderText(rendererMenu, menuOptions[i], textX, textY, blanc, PS2P);
    }
    SDL_RenderPresent(rendererMenu);
}

void AffichageGraphique::renderAide(){
    // Affichage de l'image de fond
    if (im_backgroundMenu.getTexture()) {
        im_backgroundMenu.draw(rendererMenu, 0, 0, 800, 600);
    } else {
        SDL_SetRenderDrawColor(rendererMenu, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(rendererMenu);
    }

    // Couleur
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};

    // Titre
    string titre = "Comment jouer ?";
    renderText(rendererMenu, titre.c_str(), 280, 125, jaune, PS2P);

    // Texte d’aide
    string texte =  "Le joueur 1 utilise Z pour voler";
    renderText(rendererMenu, texte.c_str(), 255, 260, blanc, PS2Pmini);
    texte = "Le joueur 2 utilise L pour voler";
    renderText(rendererMenu, texte.c_str(), 255, 280, blanc, PS2Pmini);
    texte = "Objectif: parcourir la plus grande ";
    renderText(rendererMenu, texte.c_str(), 250, 310, jaune, PS2Pmini);
    texte = "distance possible !";
    renderText(rendererMenu, texte.c_str(), 305, 320, jaune, PS2Pmini);
    texte = "Attention, des obstacles seront ";
    renderText(rendererMenu, texte.c_str(), 255, 360, blanc, PS2Pmini);
    texte = "presents tout au long de votre ";
    renderText(rendererMenu, texte.c_str(), 255, 370, blanc, PS2Pmini);
    texte = "parcours, evitez les tout en ";
    renderText(rendererMenu, texte.c_str(), 255, 380, blanc, PS2Pmini);
    texte = "gerant votre carburant.";
    renderText(rendererMenu, texte.c_str(), 255, 390, blanc, PS2Pmini);
    texte = "Differents objets sont ramassables ";
    renderText(rendererMenu, texte.c_str(), 250, 430, blanc, PS2Pmini);
    texte = "pour vous aider dans votre ";
    renderText(rendererMenu, texte.c_str(), 250, 440, blanc, PS2Pmini);
    texte = "aventure.";
    renderText(rendererMenu, texte.c_str(), 250, 450, blanc, PS2Pmini);
    texte = "Si vous ramassez 5 pieces, vous ";
    renderText(rendererMenu, texte.c_str(), 250, 470, blanc, PS2Pmini);
    texte = "obtiendrez 1 vie en echange.";
    renderText(rendererMenu, texte.c_str(), 250, 480, blanc, PS2Pmini);

    // Coordonnées du bouton
    SDL_Rect retourBtn = {260, 500, 280, 50};

    // Coordonnées souris
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Détection hover
    bool isHover = mouseX >= retourBtn.x && mouseX <= retourBtn.x + retourBtn.w &&
                   mouseY >= retourBtn.y && mouseY <= retourBtn.y + retourBtn.h;

    // Choix de la texture ou couleur en fonction du hover
    SDLSprite* buttonSprite = isHover ? &im_boutonHoverMenu : &im_boutonMenu;

    // Affichage du bouton Retour avec la texture choisie
    if (buttonSprite->getTexture()) {
        buttonSprite->draw(rendererMenu, retourBtn.x, retourBtn.y, retourBtn.w, retourBtn.h);
    }
    // Texte centré sur le bouton
    string retour = "Retour au menu";
    int textLargeur, textHauteur;
    TTF_SizeText(PS2P, retour.c_str(), &textLargeur, &textHauteur);
    int textX = retourBtn.x + (retourBtn.w - textLargeur) / 2;
    int textY = retourBtn.y + (retourBtn.h - textHauteur) / 2;
    renderText(rendererMenu, retour.c_str(), textX, textY, blanc, PS2P);

    SDL_RenderPresent(rendererMenu);
}

void AffichageGraphique::renderText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void AffichageGraphique::afficherObstacleGrandeImage(SDL_Renderer* renderer, const SDLSprite& im_metro, int obsX, int obsY, int obsLargeur, int obsLongueur) const {
    // Calcul des positions en pixels, en multipliant par la taille des sprites
    int pixelX = obsX * TAILLE_SPRITE;
    int pixelY = (HAUTEUR - obsY - obsLongueur + 1) * TAILLE_SPRITE; 
    int largeurTotale = TAILLE_SPRITE * obsLargeur; // taille en pixel de l'obstacle selon l'axe x (largeur)
    int longueurTotale = TAILLE_SPRITE * obsLongueur; // taille en pixel de l'obstacle selon l'axe y (longueur)

    // Définition des rectangles source et destination pour le rendu
    SDL_Rect srcRect = {0, 0, largeurTotale, longueurTotale};
    SDL_Rect dstRect = {pixelX, pixelY, largeurTotale, longueurTotale};

    // Si l'obstacle sort à gauche de l'écran (clipping)
    if (dstRect.x < 0) {
        srcRect.x = -dstRect.x; // Décaler la source pour enlever la portion qui dépasse à gauche
        srcRect.w -= srcRect.x;
        dstRect.w = srcRect.w;
        dstRect.x = 0; // Déplacement du rectangle de destination à 0 sur l'axe X (bord gauche de l'écran)
    }

    // On affiche seulement si une partie de l'image est visible
    if (srcRect.w > 0 && srcRect.h > 0) {
        SDL_RenderCopy(renderer, im_metro.getTexture(), &srcRect, &dstRect);
    }
}

void AffichageGraphique::affichagesCommuns() {
    // couleurs
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};
    SDL_Color orange = {236, 88, 0, 255};

    // Scroll de l'arrière-plan
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

    // Placement des obstacles
    for (const Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();
        switch (obs.getID()) {
            case 1: // Obstacle 3x1
                afficherObstacleGrandeImage(renderer, im_obstacle3x1, obsX, obsY, obsLargeur, obsLongueur);
                break;
            case 3: // Métro (1ère variation)
                afficherObstacleGrandeImage(renderer, im_metro1, obsX, obsY, obsLargeur, obsLongueur);
                break;
            case 4: // Rat (1 case)
                if (obsX >= 0 && obsX < LARGEUR && obsY >= 0 && obsY < HAUTEUR) {
                    im_rat.draw(renderer, obsX * TAILLE_SPRITE, (HAUTEUR - obsY) * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                    }
                break;
            case 5: // Métro (2ème variation)
                afficherObstacleGrandeImage(renderer, im_metro2, obsX, obsY, obsLargeur, obsLongueur);
                break;
            case 6: // Panneau d'avertissement
                if (obsX >= 0 && obsX < LARGEUR && obsY >= 0 && obsY < HAUTEUR) {
                    im_panneau_avertissement.draw(renderer, obsX * TAILLE_SPRITE, (HAUTEUR - obsY) * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                }
                break;
            default: // Autres obstacles
                for (int i = 0; i < obsLargeur; i++) {
                    for (int j = 0; j < obsLongueur; j++) {
                        int x = obsX + i;
                        int y = obsY + j;
                        if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
                            im_obstacle.draw(renderer, x * TAILLE_SPRITE, (HAUTEUR - y) * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
                    }
                }
            }
            break;
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
    renderText(renderer, texte.c_str(), 0.5*TAILLE_SPRITE, 0*TAILLE_SPRITE, jaune, VT323);

    // Affichage du personnage J1
    const Personnage& perso1 = partie.getPerso1();
    im_perso1.draw(renderer, 5*TAILLE_SPRITE, (HAUTEUR-perso1.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

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
    // Affichage du carburant (texte)
    stringstream stringstreamJ1;
    stringstreamJ1 << fixed << setprecision(2) << perso1.carburant;
    texte = stringstreamJ1.str() + "L/3L";
    renderText(renderer, texte.c_str(), 5*TAILLE_SPRITE,  11.5*TAILLE_SPRITE + 125, orange, VT323);

    //Affichage du nombre de pièces récoltées
    texte = to_string(perso1.getNbPieces());
    im_piece.draw(renderer, 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 180, TAILLE_SPRITE, TAILLE_SPRITE);
    renderText(renderer, texte.c_str(), 1.7*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 190, blanc, VT323);
}

void AffichageGraphique::affichage1Joueur() {
    // couleur
    SDL_Color blanc = {255, 255, 255, 255};

    affichagesCommuns();

    // Affichage de la distance parcourue
    const Personnage& perso1 = partie.getPerso1();
    string texte;
    texte =  "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(renderer, texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);
    
    //Affichage d'un message en cas de conversion pièces en vie.
    if(partie.piecesEnVie) {
        texte = "Vous avez obtenu une vie en echange de vos 5 pieces";
        renderText(renderer, texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 240, blanc, VT323);
    }
}

void AffichageGraphique::afficherGameOver1Joueur() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
    SDL_RenderClear(renderer);

    // Couleurs
    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    // Affichage texte Game Over
    renderText(renderer, "GAME OVER", 700, 200, rouge, PS2PGros);

    // Infos de fin de partie
    const Personnage& perso1 = partie.getPerso1();
    string texte;
    texte = "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(renderer, texte.c_str(), 650, 300, blanc, VT323);
    texte = "Nombre de pieces restantes: " + to_string(perso1.getNbPieces());
    renderText(renderer, texte.c_str(), 650, 360, blanc, VT323);
    texte = "Record actuel : " + partie.record + "m";
    renderText(renderer, texte.c_str(), 650, 420, blanc, VT323);
    renderText(renderer, "Appuyez sur ECHAP pour quitter", 630, 800, blanc, VT323);
    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
        renderText(renderer, "Vous avez realise le record", 650, 600, rouge, VT323);
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

void AffichageGraphique::afficherGameOver2Joueurs() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
    SDL_RenderClear(renderer);

    // Couleurs
    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    // Affichage texte Game Over
    renderText(renderer, "GAME OVER", 700, 200, rouge, PS2PGros);

    // Infos de fin de partie
    const Personnage& perso1 = partie.getPerso1();
    const Personnage& perso2 = partie.getPerso2();
    string texte;
    texte = "Distance parcourue : " + to_string(perso1.getDistance()) + "m";
    renderText(renderer, texte.c_str(), 650, 300, blanc, VT323);
    texte = "Nombre de pieces restantes J1 : " + to_string(perso1.getNbPieces());
    renderText(renderer, texte.c_str(), 650, 360, blanc, VT323);
    texte = "Nombre de pieces restantes J2 : " + to_string(perso2.getNbPieces());
    renderText(renderer, texte.c_str(), 650, 400, blanc, VT323);
    texte = "Record actuel : " + partie.record + "m";
    renderText(renderer, texte.c_str(), 650, 450, blanc, VT323);
    renderText(renderer, "Appuyez sur ECHAP pour quitter", 630, 800, blanc, VT323);
    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
        renderText(renderer, "Vous avez realise le record", 650, 600, rouge, VT323);
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
        affichage1Joueur();

        // Défilement de l'arrière plan
        int fondLargeur, fondHauteur;
        SDL_QueryTexture(im_fond.getTexture(), NULL, NULL, &fondLargeur, &fondHauteur);
        offset_x = (offset_x - 50 + fondLargeur) % fondLargeur;
        
        // Timer pour l'affichage du message
        if (partie.piecesEnVie){
            debutMessage = SDL_GetTicks();
        }
        if (partie.piecesEnVie && SDL_GetTicks()-debutMessage>5000) {

         partie.piecesEnVie = false ; }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    afficherGameOver1Joueur();
}

void AffichageGraphique::affichage2Joueurs() {
    // couleurs
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 255, 0, 255};
    SDL_Color orange = {236, 88, 0, 255};

    affichagesCommuns();

    // Affichage du 2eme joueur
    const Personnage& perso2 = partie.getPerso2();
    im_perso2.draw(renderer, 5*TAILLE_SPRITE, (HAUTEUR-perso2.getHauteur())*TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
   
    // Affichage de la distance parcourue
    string texte =  "Distance parcourue : " + to_string(perso2.getDistance()) + "m";
    renderText(renderer, texte.c_str(), 11*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);

    // affichage texte "J1"
    texte =  "J1";
    renderText(renderer, texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);

    // ---- Affichage J2 ----
    texte =  "J2";
    renderText(renderer, texte.c_str(), 29*TAILLE_SPRITE, 11.5*TAILLE_SPRITE, blanc, VT323);

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
    renderText(renderer, texte.c_str(), 22.5*TAILLE_SPRITE,  11.5*TAILLE_SPRITE + 125, orange, VT323);
    //Affichage du nombre de pièces récoltées J2
    texte = to_string(perso2.getNbPieces());
    im_piece.draw(renderer, 28.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 180, TAILLE_SPRITE, TAILLE_SPRITE);
    renderText(renderer, texte.c_str(), 28*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 190, blanc, VT323);

    //Affichage d'un message en cas de conversion pièces en vie. 
    if(partie.piecesEnVie) {
        texte = "Un des joueurs a obtenu une vie en echange de 5 pieces";
        renderText(renderer, texte.c_str(), 0.5*TAILLE_SPRITE, 11.5*TAILLE_SPRITE + 240, blanc, VT323);
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
    if (partie.piecesEnVie){
        debutMessage = SDL_GetTicks();
    }
    if (partie.piecesEnVie && SDL_GetTicks()-debutMessage>5000) {
        partie.piecesEnVie = false ; }

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
    }
    afficherGameOver2Joueurs();
}