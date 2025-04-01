/**
 *@file AffichageConsole.h
 *@brief Définition de la classe AffichageConsole
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
  * @brief Affiche l'ensemble du jeu dans la console, à l'aide de caractères
*/
class AffichageConsole {
  private:
    Partie partie; ///<  La partie en cours
 
  public:
    AffichageConsole(); ///< Le constructeur de AffichageConsole

    void afficher(WinTXT &win); ///< Procédure qui affiche les éléments
    void run(); ///< Procédure qui gère l'affichage et récupère les actions claviers

    void afficher2Joueurs(WinTXT &win); ///< Procédure qui affiche les éléments en mode 2 joueurs
    void run2Joueurs(); ///< Procédure qui gère l'affichage et récupère les actions claviers en mode 2 joueurs

    string getRecord(); //< Retourne le record de distance
 };
 
 #endif