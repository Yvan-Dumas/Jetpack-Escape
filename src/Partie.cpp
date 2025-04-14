/**
 *@file Partie.cpp
 *@brief Implémentation de la classe Partie
 */

#include "Partie.h"

using namespace std;

Partie::Partie() {
    perso1.setDistance(0);
    perso1.setNbPieces(0);
    perso1.setNbPieces(0);
    perso1.setNbVies(3);

    perso2.setDistance(0);
    perso2.setNbPieces(0);
    perso2.setNbPieces(0);
    perso2.setNbVies(3);

    record = chargerFichier();
}

void Partie::sauvegarderFichier(string contenu) {
    ofstream fichier("../data/sauvegarde.txt", ios::out | ios::trunc);
    if(fichier){
        fichier << contenu;
        fichier.close();
    }
    else cout << "impossible d'ouvrir le fichier !";
}

string Partie::chargerFichier() {
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
    if (perso.carburant < 3) {
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
        case 3: // Pour une vie, incrémente de 1
            if (perso.getNbVies()<4) {
                perso.setNbVies(perso.getNbVies()+1); 
            }
        default:
            break;
    }
}

bool Partie::bien_place(unsigned int x, unsigned int y, unsigned int largeur, unsigned int longueur) {
    auto superpose = [](int x1, int y1, int w1, int h1,
        int x2, int y2, int w2, int h2) {
    return !(x1 + w1 <= x2 || x2 + w2 <= x1 || y1 + h1 <= y2 || y2 + h2 <= y1);
    };
    
    for (const auto& obj : tabObjets) {
        if (superpose(x, y, largeur, longueur, obj.getX(), obj.getY(), 1, 1)) {
        return false;
    }}

    for (const auto& obs : tabObstacle) {
        if (superpose(x-1, y-1, largeur+2, longueur+2, 
                  obs.getX() - 1, obs.getY() - 1, 
                  obs.getLargeur() + 2, obs.getLongueur() + 2)) {
        return false;
    }}

    return true;
}

void Partie::generationObstacle(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, HAUTEUR - 1); // Plage de 0 à HAUTEUR - 1
    int y = dist(gen); // Position y de l'Obstacle.
    int x = LARGEUR;// Position x de l'Obstacle (à droite de l'écran pour l'initialisation)
    unsigned int largeur; 
    unsigned int longueur;
    switch (id) {
        case 1: // Création d'un obstacle
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
        default:
            largeur = 1; 
            longueur = 1;
            break;
    }
    if (y >= 0 && y + longueur <= HAUTEUR) { // L'obstacle est bien dans la grille        
    while (!bien_place(x, y, largeur, longueur))
    {
        x = x + 10;
    }
    Obstacle obstacle1(id, x, y, largeur, longueur);
    tabObstacle.push_back(obstacle1);}
}

void Partie::generationObjet(int id, unsigned int HAUTEUR, unsigned int LARGEUR) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, HAUTEUR - 1);
    int y = dist(gen); // Position y de l'objet.
    int x = LARGEUR; // Position x de l'objet (bord droit de l'écran).
    unsigned int largeur; 
    unsigned int longueur;

    while (!bien_place(x, y, largeur, longueur))
    {
        x = x + 1;
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

bool Partie::actionsAutomatiques(unsigned int HAUTEUR, unsigned int LARGEUR) {
        // Réinitialisation des paramètres de la partie
        bool enMarche = true;

        // Génération aléatoire d'obstacles et d'objets à certains intervalles
        if ((rand())%20==0){
        int id = 1;
        int poids[] = {20, 20, 10, 20, 10, 20, 7 ,10}; // Poids associés
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
            default:
                break;
        }
    }

    // Mise à jour de la distance
    perso1.setDistance(perso1.getDistance()+1);
    perso1.appliquerGravite();

        // Vérification des collisions avec obstacles
        for (auto obstacle = tabObstacle.begin(); obstacle != tabObstacle.end();) {
            obstacle->mettreAJourPosition();
            if (obstacle->getX()+obstacle->getLargeur() <= 0) {
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle s'il sort de l'écran
            } else if (obstacle->collisionObstacle(perso1.getHauteur())) {
                perso1.setNbVies(perso1.getNbVies()-1);
                if (perso1.getNbVies() <= 0) {
                    enMarche = false;
                    break;
                }
                obstacle = tabObstacle.erase(obstacle); // Supprime l'obstacle après collision
            } else {
                ++obstacle;
            }
        }

        // Vérification des objets ramassés
        for (auto it = tabObjets.begin(); it != tabObjets.end();) {
            it->mettreAJourPosition();
            unsigned int identifiant = it->collecterObjet(perso1.getHauteur());
            if (it->getX() <= 0) {
                it = tabObjets.erase(it); // Supprime l'objet s'il sort de l'écran
            } else if (identifiant !=100) {
                utiliserObjet(perso1, identifiant); 
                it = tabObjets.erase(it); // Supprime l'objet après collecte
            } else {
                ++it;
            }
        }
    return enMarche ;
}

bool Partie::actionsAutomatiques2Joueurs(unsigned int HAUTEUR, unsigned int LARGEUR) {
    // Réinitialisation des paramètres de la partie
    bool enMarche = true;
    // Génération aléatoire d'obstacles et d'objets à certains intervalles
    if ((rand())%20==0){
    int id = 1;
    int poids[] = {20, 20, 2, 20, 10, 5}; // Poids associés
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
    do  {
        i++ ;
        cumul = cumul + poids [i-1] ;
    }
    while(tirage > cumul);
    
    switch (i) {
        case 1: {// Création d'une obstacle de base
            generationObstacle(1,HAUTEUR, LARGEUR);
            break;}

        case 2: { // Création d'un échaffaudage
            generationObstacle(2,HAUTEUR, LARGEUR);
            break;
            }
        case 3: { // Création d'un métro
            generationObstacle(3,HAUTEUR, LARGEUR);
            break;
                }
        case 4: {// Création d'une pièce
            generationObjet(1,HAUTEUR, LARGEUR);
            break;}

        case 5: { // Création d'un carburant
            generationObjet(2,HAUTEUR, LARGEUR);
            break;
            }
        case 6: { // Création d'une vie
            generationObjet(3,HAUTEUR, LARGEUR);
            break;
                }
        default:
            break;
    }
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
return enMarche ;
}

const Personnage& Partie::getPerso1() const {
    return perso1;
}

const Personnage& Partie::getPerso2() const {
    return perso2;
}

bool Partie::acheterVieSiPossible() {
    if (perso1.getNbPieces() >= 10 && perso1.getNbVies() < 4) {
        perso1.setNbPieces(perso1.getNbPieces() - 10);
        perso1.setNbVies(perso1.getNbVies() + 1);
        return true;
    }
    if (perso2.getNbPieces() >= 10 && perso2.getNbVies() < 4) {
        perso2.setNbPieces(perso2.getNbPieces() - 10);
        perso2.setNbVies(perso2.getNbVies() + 1);
        return true;
    }
    return false;
}


void Partie::testPartie() {
    /*
    cout<<"Début des tests pour Partie"<<endl;
    // Initialisation de la partie
    Partie partie;
    
    // Vérification des paramètres initiaux
    assert(partie.getHauteurPerso(perso1) == 0 && "Test échoué : La hauteur initiale du personnage n'est pas correcte");
    assert(partie.getCarburant() == 5 && "Test échoué : Le carburant initial n'est pas correct");
    assert(partie.getObstacles().empty() && "Test échoué : Il ne devrait y avoir aucun obstacle au début");
    assert(partie.getObjets().empty() && "Test échoué : Il ne devrait y avoir aucun objet au début");

    // Test de l'ajout d'un carburant
    partie.ajouterCarburant();
    assert(partie.getCarburant() == 5 && "Test échoué : Le carburant ne doit pas dépasser 5");

    // Test de la mise à jour des obstacles et objets
    unsigned int initialObstacleSize = partie.getObstacles().size();
    unsigned int initialObjetSize = partie.getObjets().size();

    // Test de la fonction actionsAutomatiques
    bool enMarche = partie.actionsAutomatiques(100, 50);
    assert(enMarche && "Test échoué : La partie ne devrait pas être terminée après une action automatique");
    assert(partie.getObstacles().size() == initialObstacleSize && "Test échoué : Le nombre d'obstacles n'a pas été mis à jour correctement");
    assert(partie.getObjets().size() == initialObjetSize && "Test échoué : Le nombre d'objets n'a pas été mis à jour correctement");

    // Si tous les tests passent, on affiche un message de succès
    cout << "Tous les tests ont réussi !" << endl;
*/
}
