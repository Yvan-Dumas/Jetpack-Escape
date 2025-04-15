#include "AffichageConsole.h"

using namespace std;

const int HAUTEUR = 10;
const int LARGEUR = 100;

string AffichageConsole::getRecord() const{
    return partie.record;
}

void AffichageConsole::affichagesCommuns(WinTXT &win) const {
    win.clear();

    // Remplissage de la gille avec des caractères vides
    for (unsigned int i = 0; i < LARGEUR; i++) {
        for (unsigned int j = 0; j < HAUTEUR; j++) {
            win.print(i, j+1, ' ');
        }
    }

    // Affichage de la bordure supérieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,0,'_');
    }

    //Placement des obstacles
    for (const Obstacle& obs : partie.getObstacles()) {
        int obsX = obs.getX();
        int obsY = obs.getY();
        int obsLargeur = obs.getLargeur();
        int obsLongueur = obs.getLongueur();
        for (int i = 0; i < obsLargeur; i++) {
            for (int j = 0; j < obsLongueur; j++) {
                if (obsX + i >= 0 && obsX + i < LARGEUR && obsY + j >= 0 && obsY + j < HAUTEUR) {
                    win.print(obsX + i, HAUTEUR - (obsY + j), 'X');
                }
            }
        }
    }

    //Placement des objets
    for (const Objet& obj : partie.getObjets()) {
        switch (obj.getID()){
        case 1:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'O');       
        break;
        case 2:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'C');
        break;
        case 3:
            win.print(obj.getX(), HAUTEUR - obj.getY(), 'V');
        default:
        break;
        } 
    }

    // Affichage de la bordure inférieure
    for(unsigned int i = 0; i<LARGEUR; i++) {
        win.print(i,11,'-');
    }
}

void AffichageConsole::affichage1Joueur(WinTXT &win) const{
    affichagesCommuns(win);
    
    // Placement du personnage
    const Personnage& perso1 = partie.getPerso1();
    int hauteurPerso = perso1.getHauteur();
    win.print(5, HAUTEUR - hauteurPerso, '@');

    win.draw();
    cout << "Vies : " << perso1.getNbVies() << endl;
    cout << "Carburant : [";
    unsigned int longueurRemplie = ( perso1.carburant * 16) / 3;
    for (unsigned int i = 0; i < 16; i++) {
        if (i < longueurRemplie) {
            cout << "="; // Partie remplie
        } else {
            cout << " "; // Partie vide
        }
    }
    cout << "] " << std::fixed << std::setprecision(2) << perso1.carburant << "L" << "/3L" << endl;
    cout << "Distance parcourue : " << perso1.getDistance() << "m" << endl;
    cout << "Nombre de pièces restantes : " << perso1.getNbPieces() << " pièces" <<endl;
    cout << "Record: " << partie.record << "m" << endl <<endl;
}

void AffichageConsole::run() {
    termClear();
    WinTXT window(LARGEUR, HAUTEUR+3);
    int c;
    bool ok;
    window.clear();
    int compteur = 0;
    do {       
        if (compteur % 3 == 0) {
            ok = partie.actionsAutomatiques(HAUTEUR, LARGEUR);
        }
        compteur++;

        c = window.getCh();
        switch (c)
        {
        case 'q':
            ok = false;
            break;
        case 'z':
            partie.actionsClavier('z', HAUTEUR-1);
            break;
        default:
            break;
        }

        affichage1Joueur(window);
        usleep(30000); // Pause
    } while (ok);
    window.clear();
    
    termClear();
    
    const Personnage& perso1 = partie.getPerso1();
    cout << "=====================================" << endl;
    cout << "              GAME OVER              " << endl;
    cout << "=====================================" << endl;
    cout << " Distance parcourue : " << perso1.getDistance() << "m"  << endl;
    cout << " Score final        : " << perso1.getNbPieces() << endl;
    if(perso1.getDistance() > stoi(getRecord())){
    cout << " VOUS AVEZ REALISE LE RECORD !" << endl;
    }
    cout << "====================================="  << endl;
    cout << "     Merci d'avoir joué !     "  << endl << endl;

    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
    }
}

void AffichageConsole::affichage2Joueurs(WinTXT &win) const{
    affichagesCommuns(win);
    const Personnage& perso1 = partie.getPerso1();
    const Personnage& perso2 = partie.getPerso2();

    // Placement des personnages
    int hauteurPerso1 = perso1.getHauteur();
    int hauteurPerso2 = perso2.getHauteur();
    if(hauteurPerso2 == hauteurPerso1) {
        win.print(5, HAUTEUR - hauteurPerso1, '@');
    }
    else{
        win.print(5, HAUTEUR - hauteurPerso1, 'Z');
        win.print(5, HAUTEUR - hauteurPerso2, 'L');
    }

    win.draw();

    cout << "Record: " << partie.record << "m" << endl;
    cout << "Distance parcourue : " << perso1.getDistance() << "m" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Vies J1: " << perso1.getNbVies() << endl;
    cout << "Carburant J1 : [";
    unsigned int longueurRemplieJ1 = ( perso1.carburant * 16) / 5;
    for (unsigned int i = 0; i < 16; i++) {
        if (i < longueurRemplieJ1) {
            cout << "="; // Partie remplie
        } else {
            cout << " "; // Partie vide
        }
    }
    cout << "] " << std::fixed << std::setprecision(2) << perso1.carburant << "L" << "/" << 5 << "L" << endl;
    cout << "Nombre de pièces J1: " << perso1.getNbPieces() << " pièces" <<endl;
    cout << "-----------------------------------------------------------" << endl;

    cout << "Vies J2: " << perso2.getNbVies() << endl;
    cout << "Carburant J2 : [";
    unsigned int longueurRemplieJ2 = ( perso2.carburant * 16) / 5;
    for (unsigned int i = 0; i < 16; i++) {
        if (i < longueurRemplieJ2) {
            cout << "="; // Partie remplie
        } else {
            cout << " "; // Partie vide
        }
    }
    cout << "] " << std::fixed << std::setprecision(2) << perso2.carburant << "L" << "/" << 5 << "L" << endl;
    cout << "Nombre de pièces J2: " << perso2.getNbPieces() << " pièces" <<endl;

}

void AffichageConsole::run2Joueurs() {
    termClear();
    WinTXT window(LARGEUR, HAUTEUR+3);
    int c;
    bool ok;
    window.clear();
    int compteur = 0 ;
    do 
    {   
        if (compteur % 3 == 0) {
            ok = partie.actionsAutomatiques2Joueurs(HAUTEUR, LARGEUR);
        }

        compteur++;       

        c = window.getCh();

        switch (c)
        {
        case 'q':
            ok = false;
            break;

        case 'z':
            partie.actionsClavier2Joueurs('z', HAUTEUR-1);
        break;
        
        case 'l':
            partie.actionsClavier2Joueurs('l', HAUTEUR-1);
        break;

        default:
            break;
        }

        affichage2Joueurs(window);

        usleep(30000); // Pause
    } while (ok);
    window.clear();
    
    termClear();
    const Personnage& perso1 = partie.getPerso1();
    const Personnage& perso2 = partie.getPerso2();

    cout << "=====================================" << endl;
    cout << "              GAME OVER              " << endl;
    cout << "=====================================" << endl;
    cout << " Distance parcourue : " << perso1.getDistance() << "m"  << endl;
    cout << " Nombre de pièces restantes J1 : " << perso1.getNbPieces() << endl;
    cout << " Nombre de pièces restantes J2 : " << perso2.getNbPieces() << endl;
    if(perso1.getDistance() > stoi(getRecord())){
    cout << " VOUS AVEZ REALISE LE RECORD !" << endl;
    }
    cout << "====================================="  << endl;
    cout << "     Merci d'avoir joué !     "  << endl << endl;

    if (perso1.getDistance() > stoi(getRecord())) {
        partie.sauvegarderFichier(to_string(perso1.getDistance()));
    }
}
