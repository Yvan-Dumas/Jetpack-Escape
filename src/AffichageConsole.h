/**
 *@file AffichageConsole.h
 *@brief Définition de la classe AffichageConsole
 */

 #ifndef AFFICHAGE_CONSOLE_H
 #define AFFICHAGE_CONSOLE_H
 
 #include "Partie.h"

 /**
  * @class AffichageConsole
  * @brief Affiche l'ensemble du jeu dans la console, à l'aide de caractères
*/
 class AffichageConsole {
 private:
     Partie partie; ///<  La partie en cours
 
 public:
     AffichageConsole(); ///< Le constructeur de AffichageConsole
     void afficher(); ///< procédure qui affiche les éléments
     void run(); ///< La procédure qui gère tout l'affichage
 };
 
 #endif