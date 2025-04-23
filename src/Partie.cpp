/**
 *@file Partie.cpp
 *@brief Implémentation de la classe Partie
 */
#include "Partie.h"

using namespace std;

Partie::Partie() {
    //Initalisation du personnage 1
    perso1.setDistance(0);
    perso1.setNbPieces(0);
    perso1.setNbVies(3);

    //Initialisation du personnage 2
    //Il est initialisé même en mode 1 joueur, mais on ne l'utilise par la suite qu'en mode 2 joueurs.
    perso2.setDistance(0);
    perso2.setNbPieces(0);
    perso2.setNbVies(3);

    piecesEnVie = false;

    record = chargerFichier();
}

void Partie::sauvegarderFichier(const string& contenu) const {
    ofstream fichier("../data/sauvegarde.txt", ios::out | ios::trunc);
    if(fichier){
        fichier << contenu;
        fichier.close();
    }
    else cout << "impossible d'ouvrir le fichier !";
}

string Partie::chargerFichier() const {
    fstream fichier("../data/sauvegarde.txt", ios::in);
    if(fichier){
        string contenu;
        getline(fichier, contenu);
        fichier.close();
        return contenu;
    }
    else return "impossible d'ouvrir le fichier !";
}

void Partie::ajouterCarburant(Personnage & perso){
    if (perso.carburant < 3) { // Si moins de 3L on ajoute 1L, sinon on mets au max=3L
        perso.carburant = perso.carburant + 1;
        if (perso.carburant > 3) perso.carburant = 3;
    }
}

void Partie::ajouterPiece(Personnage & perso) {
    perso.setNbPieces(perso.getNbPieces()+1);
}

void Partie::ajouterDistance(Personnage & perso) {
    perso.setDistance(perso.getDistance()+1);
}

void Partie::utiliserObjet(Personnage & perso,unsigned int id) {
    switch (id) {
        case 1: // pour une pièce
            ajouterPiece(perso);
            break;
        case 2: // Pour du carburant
            ajouterCarburant(perso);
            break;
        case 3: // Pour une vie, incrémente de 1 le nombres de vies du personnage.
            if (perso.getNbVies()<4) {
                perso.setNbVies(perso.getNbVies()+1); 
            }
            break;
        default:
            break;
    }
}

bool Partie::estBienPlace(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur) {  
    // Fonction interne a estBienPlace pour verifier la superposition
    auto superpose = [](int x1, int y1, int w1, int h1,
        int x2, int y2, int w2, int h2) {
    return !(x1 + w1 <= x2 || x2 + w2 <= x1 || y1 + h1 <= y2 || y2 + h2 <= y1);
    };
    // On vérifie avec l'ensemble des objets générés
    for (const auto& obj : tabObjets) {
        if (superpose(x, y, largeur, longueur, obj.getX(), obj.getY(), 1, 1)) {
        return false;
    }}
    // Et avec l'ensemble des obstacles générés
    for (const auto& obs : tabObstacle) {
        if (superpose(x-1, y-1, largeur+2, longueur+2, 
                  obs.getX() - 1, obs.getY() - 1, 
                  obs.getLargeur() + 2, obs.getLongueur() + 2)) {
        return false;
    }}
    return true;
}

void Partie::generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    int y = rand() % (HAUTEUR); // Plage de 0 à HAUTEUR - 1, position y de l'Obstacle.
    int x = LARGEUR;// Position x de l'obstacle (à droite de l'écran pour l'initialisation)
    unsigned int largeur; 
    unsigned int longueur;
    switch (id) {
        case 1: // Création d'un obstacle 3x1 horizontal
            largeur = 3; 
            longueur = 1;
            break;
        case 2: // Création d'un obstacle vertical (échaffaudage)
            largeur = 1; 
            longueur = 3;
            break; 
        case 3: // Création d'un métro (1ère variation)
            largeur = 16;
            longueur = 5;
            y = 0; // le métro est au sol
            break; 
        case 4: // Création d'un rat
            largeur = 1;
            longueur = 1;
            y = 0; // le rat est au sol
            break;
        case 5: // Création d'un métro (2ème variation)
            largeur = 16;
            longueur = 5;
            y = 0; // le métro est au sol
            break;
        case 6: // Création d'un panneau d'avertissement
            largeur = 1;
            longueur = 1;
            y = HAUTEUR - 1; // Le panneau est au plafond
            break;
        default:
            largeur = 1; 
            longueur = 1;
            break;
    }
    if (y >= 0 && y + longueur <= HAUTEUR) { // L'obstacle est bien dans la grille        
    
    while (!estBienPlace(x, y, largeur, longueur))
    {
        x = x + 10; // Tant que l'obstacle n'est pas bien placé, on le décale sur la droite jusqu'à qu'il y ait de la place.
    }
    Obstacle obstacle1(id, x, y, largeur, longueur);
    tabObstacle.push_back(obstacle1);}
}

void Partie::generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    int y = rand() % (HAUTEUR); // Plage de 0 à HAUTEUR - 1, position y de l'Obstacle.
    int x = LARGEUR; // Position x de l'objet (bord droit de l'écran).
    unsigned int largeur = 1; 
    unsigned int longueur = 1;

    while (!estBienPlace(x, y, largeur, longueur))
    {
        x = x + 1; // Tant que l'objet n'est pas bien placé, on le décale sur la droite jusqu'à qu'il y ait de la place.
    }
    
    Objet objet1(id, x, y);
    tabObjets.push_back(objet1);
}

const vector<Obstacle>& Partie::getObstacles() const {
    return tabObstacle;
}

const vector<Objet>& Partie::getObjets() const{
    return tabObjets;
}

const Personnage& Partie::getPerso1() const {
    return perso1;
}

const Personnage& Partie::getPerso2() const {
    return perso2;
}

bool Partie::acheterVieSiPossible() {
    if (perso1.getNbPieces() >= 5 && perso1.getNbVies() < 4) {
        perso1.setNbPieces(perso1.getNbPieces() - 5);
        perso1.setNbVies(perso1.getNbVies() + 1);
        return true;
    }
    if (perso2.getNbPieces() >= 5 && perso2.getNbVies() < 4) {
        perso2.setNbPieces(perso2.getNbPieces() - 5);
        perso2.setNbVies(perso2.getNbVies() + 1);
        return true;
    }
    return false;
}

void Partie::actionsClavier(const char touche, unsigned int HAUTEUR) {
    switch (touche)
    {
    case 'z':
        perso1.monter(HAUTEUR);
        break;
    default:
        break;
    }
}

void Partie::actionsClavier2Joueurs(const char touche, unsigned int HAUTEUR) {
    switch (touche)
    {
    case 'z':
        perso1.monter(HAUTEUR);
        break;
    case 'l':
        perso2.monter(HAUTEUR);
        break;
    default:
        break;
    }
}

void Partie::tirageEtGenerationObstaclesObjets(int HAUTEUR, int LARGEUR) {
    int id = 1;
    int poids[] = {20, 20, 8, 25, 15, 7, 10, 8, 12}; // Poids associés
    int taille = sizeof(poids) / sizeof(poids[0]);
    // Calcul de la somme des poids
    int sommePoids = 0;
    for (int i = 0; i < taille; i++) {
        sommePoids += poids[i];
    }
    // Tirage aléatoire d'un nombre entre 1 et sommePoids
    int tirage = (rand() % sommePoids) + 1;
    int i = 0;
    int cumul = 0;
    do {
        i++ ;
        cumul = cumul + poids [i-1] ;
    } while(tirage > cumul);
    switch (i) {
        case 1: // Création d'une obstacle de base
            generationObstacle(1,HAUTEUR, LARGEUR);
            break;
        case 2:  // Création d'un échaffaudage
            generationObstacle(2,HAUTEUR, LARGEUR);
            break;
        case 3: // Création d'un métro (1ère variation)
            generationObstacle(3,HAUTEUR, LARGEUR);
            break;
        case 4: // Création d'une pièce
            generationObjet(1,HAUTEUR, LARGEUR);
            break;
        case 5: // Création d'un carburant
            generationObjet(2,HAUTEUR, LARGEUR);
            break;
        case 6: // Création d'une vie
            generationObjet(3,HAUTEUR, LARGEUR);
            break;
        case 7: // Création d'un rat 
            generationObstacle(4, HAUTEUR, LARGEUR);
            break;
        case 8: // Création d'un métro (2ème variation)
            generationObstacle(5, HAUTEUR, LARGEUR);
            break;
        case 9: // Création d'un panneau d'avertissement
            generationObstacle(6, HAUTEUR, LARGEUR);
            break;
        default:
            break;
    }
}

bool Partie::actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR) {
    bool enMarche = true; 
    // Génération pseudo-aléatoire d'obstacles et d'objets à certains intervalles
    if ((rand())%20==0){
        tirageEtGenerationObstaclesObjets(HAUTEUR, LARGEUR);
    }

    // Mise à jour de la distance
    perso1.setDistance(perso1.getDistance()+1);
    perso1.appliquerGravite();

    // Vérification des collisions avec obstacles
    for (auto obstacle = tabObstacle.begin(); obstacle != tabObstacle.end();) {
        obstacle->mettreAJourPosition();
        if (obstacle->getX()+obstacle->getLargeur() <= 0) {
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle s'il sort de l'écran
            } 
        else if (obstacle->collisionObstacle(perso1.getHauteur())) {
            perso1.setNbVies(perso1.getNbVies()-1);
            if (perso1.getNbVies() <= 0) {
                enMarche = false;
                break;
            }
            obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
            } 
            else {
                ++obstacle;
            }
        }

    // Vérification des objets ramassés
    for (auto it = tabObjets.begin(); it != tabObjets.end();) {
        it->mettreAJourPosition();
        unsigned int identifiant = it->collecterObjet(perso1.getHauteur());
        if (it->getX() <= 0) {
            it = tabObjets.erase(it); // Supprime l'objet s'il sort de l'écran
            } 
        else if (identifiant !=100) {
            utiliserObjet(perso1, identifiant); 
            it = tabObjets.erase(it); // Supprime l'objet après collecte
            } 
        else {
            ++it;
            }
        }

    if (acheterVieSiPossible()){
        piecesEnVie = true;
    }
    return enMarche ;
}

bool Partie::actionsAutomatiques2Joueurs(unsigned int HAUTEUR, unsigned int LARGEUR) {
    // Réinitialisation des paramètres de la partie
    bool enMarche = true;
    // Génération aléatoire d'obstacles et d'objets à certains intervalles
    if ((rand())%20==0){
        tirageEtGenerationObstaclesObjets(HAUTEUR, LARGEUR);
    }

    // Vérification des collisions avec obstacles
    for (auto obstacle = tabObstacle.begin(); obstacle != tabObstacle.end();) {
        obstacle->mettreAJourPosition();
        if (obstacle->getX()+obstacle->getLargeur() <= 0) {
            obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle s'il sort de l'écran
        }
        // Si les 2 joueurs sont en contact avec l'obstacle
        else if (obstacle->collisionObstacle(perso1.getHauteur()) && obstacle->collisionObstacle(perso2.getHauteur())) {
            perso1.setNbVies(perso1.getNbVies()-1);;
            if (perso1.getNbVies() <= 0) {
                enMarche = false;
                break;
            }
            perso2.setNbVies(perso2.getNbVies()-1);;
            if (perso2.getNbVies() <= 0) {
                enMarche = false;
                break;
            }
            obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
        }
        // Si seulement le joueur 1 est en contact avec l'obstacle
        else if (obstacle->collisionObstacle(perso1.getHauteur())) {
            perso1.setNbVies(perso1.getNbVies()-1);;
            if (perso1.getNbVies() <= 0) {
                enMarche = false;
                break;
            }
            obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
        }
        // Si seulement le joueur 2 est en contact avec l'obstacle
        else if (obstacle->collisionObstacle(perso2.getHauteur())) {
            perso2.setNbVies(perso2.getNbVies()-1);;
            if (perso2.getNbVies() <= 0) {
                enMarche = false;
                break;
            }
            obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
        }
        else {
            ++obstacle;
        }
    }

    // Vérification des objets ramassés
    for (auto it = tabObjets.begin(); it != tabObjets.end();) {
        it->mettreAJourPosition();
        unsigned int identifiant1 = it->collecterObjet(perso1.getHauteur());
        unsigned int identifiant2 = it->collecterObjet(perso2.getHauteur());
        if (it->getX() <= 0) {
            it = tabObjets.erase(it); // Supprime l'objet s'il sort de l'écran
        }
        // Si les 2 joueurs sont en contact avec l'objet
        else if (identifiant1 !=100 && identifiant2 !=100) {
            utiliserObjet(perso1, identifiant1);
            utiliserObjet(perso2, identifiant1);
            it = tabObjets.erase(it); // Supprime l'objet après collecte
        }
        // Si seulement le joueur 1 est en contact avec l'objet
        else if (identifiant1 !=100) {
            utiliserObjet(perso1, identifiant1); 
            it = tabObjets.erase(it); // Supprime l'objet après collecte
        }
        // Si seulement le joueur 2 est en contact avec l'objet
        else if (identifiant2 !=100) {
            utiliserObjet(perso2, identifiant2); 
            it = tabObjets.erase(it); // Supprime l'objet après collecte
        }
        else {
            ++it;
        }
    }

    // Mise à jour de la distance
    perso1.setDistance(perso1.getDistance()+1);
    perso2.setDistance(perso2.getDistance()+1);
    perso1.appliquerGravite();
    perso2.appliquerGravite();

    if (acheterVieSiPossible()){
        piecesEnVie = true;
    }

    return enMarche ;
}

void Partie::testPartie() {
    cout << "Début des tests pour Partie" << endl;
    Partie partie;

    // Test valeurs initiales des personnages
    assert(partie.getPerso1().getNbVies() == 3 && "Erreur : perso1 doit commencer avec 3 vies.");
    assert(partie.getPerso1().getNbPieces() == 0 && "Erreur : perso1 doit commencer avec 0 pièce.");
    assert(partie.getPerso1().getDistance() == 0 && "Erreur : perso1 doit commencer avec 0 de distance.");
    assert(partie.getPerso2().getNbVies() == 3 && "Erreur : perso2 doit commencer avec 3 vies.");
    assert(partie.getPerso2().getNbPieces() == 0 && "Erreur : perso2 doit commencer avec 0 pièce.");
    assert(partie.getPerso2().getDistance() == 0 && "Erreur : perso2 doit commencer avec 0 de distance.");

    // Test ajout de pièce
    partie.ajouterPiece(partie.perso1);
    assert(partie.getPerso1().getNbPieces() == 1 && "Erreur : perso1 doit avoir 1 pièce après ajout.");

    // Test ajout de distance
    partie.ajouterDistance(partie.perso1);
    assert(partie.getPerso1().getDistance() == 1 && "Erreur : perso1 doit avoir 1 de distance après ajout.");

    // Test ajout de carburant
    partie.perso1.carburant = 1;
    partie.ajouterCarburant(partie.perso1); // -> 2
    assert(partie.perso1.carburant == 2 && "Erreur : le carburant devrait être 2.");
    partie.ajouterCarburant(partie.perso1); // -> 3
    assert(partie.perso1.carburant == 3 && "Erreur : le carburant devrait être 3.");
    partie.ajouterCarburant(partie.perso1); // reste à 3
    assert(partie.perso1.carburant == 3 && "Erreur : le carburant ne doit pas dépasser 3.");

    // Test utilisation d’un objet (type 1 = pièce)
    unsigned int nbPiecesAvant = partie.getPerso1().getNbPieces();
    partie.utiliserObjet(partie.perso1, 1);
    assert(partie.getPerso1().getNbPieces() == nbPiecesAvant + 1 && "Erreur : utiliser un objet de type 1 devrait ajouter une pièce.");

    // Test achat de vie
    partie.perso1.setNbPieces(5);
    partie.perso1.setNbVies(3);
    bool achete = partie.acheterVieSiPossible();
    assert(achete && "Erreur : l'achat de vie aurait dû être possible avec 5 pièces.");
    assert(partie.getPerso1().getNbVies() == 4 && "Erreur : perso1 devrait avoir 4 vies après l'achat.");
    assert(partie.getPerso1().getNbPieces() == 0 && "Erreur : perso1 devrait avoir 0 pièce après l'achat.");

    cout << "Tous les tests ont réussi" << endl;
}