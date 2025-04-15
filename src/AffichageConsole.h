/**
 * @file AffichageConsole.h
 * @brief Définition de la classe AffichageConsole
 */

 #ifndef AFFICHAGE_CONSOLE_H
 #define AFFICHAGE_CONSOLE_H
  
 #include "Partie.h"
 #include "winTxt.h"
 #include <iostream>
 #include <unistd.h>
 #include <iomanip>
 
 /**
   * @class AffichageConsole
   * @brief Affiche l'ensemble du jeu dans la console, à l'aide de caractères ASCII et de la bibliothèque WinTxt.
   * @details Cette classe permet d'afficher tous les éléments du jeu dans un terminal, en mode 1 joueur ou 2 joueurs. 
   *          Elle récupère également les entrées clavier pour mettre à jour la partie.
   */


class AffichageConsole {

  private:
    Partie partie; ///<  Instance de la partie en cours

    /**
     * @brief Procédure pour l'affichage des éléments communs aux 2 modes de jeu.
     * @param win Référence vers la fenêtre WinTXT utilisée pour l'affichage.
     */
    void affichagesCommuns(WinTXT &win) const;

    /**
     * @brief Affiche les éléments du jeu (mode 1 joueur) dans la console.
     * @param win Référence vers la fenêtre WinTXT utilisée pour l'affichage.
     */
    void affichage1Joueur(WinTXT &win) const;

    /**
     * @brief Affiche les éléments du jeu (mode 2 joueurs) dans la console.
     * @param win Référence vers la fenêtre WinTXT utilisée pour l'affichage.
     */
    void affichage2Joueurs(WinTXT &win) const ;
  
  public:
    /**
     * @brief Boucle principale du jeu en mode 1 joueur.
     * @details Gère le rendu dans la console (appel à afficher() ) et la récupération des actions clavier.
     */
    void run();

    /**
     * @brief Boucle principale du jeu en mode 2 joueurs.
     * @details Gère le rendu dans la console (appel à afficher2Joueurs() ) 
     *          et la gestion des entrées clavier pour les deux joueurs.
     */
    void run2Joueurs();
 
    /**
     * @brief Récupère le record de distance réalisé.
     * @return string contenant la meilleure distance atteinte, enregistrée dans data/sauvegarde.txt.
     */
    string getRecord() const;
  };
  
#endif