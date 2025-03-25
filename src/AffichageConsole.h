/**
 *@file AffichageConsole.h
 *@brief Définition de la classe AffichageConsole
 */

 #ifndef AFFICHAGE_CONSOLE_H
 #define AFFICHAGE_CONSOLE_H
 
 #include "Partie.h"
 #include "winTxt.h"

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
     void run(); ///< Procédure qui gère tout l'affichage et récupère les actions claviers
     /**
     * @brief Effectue une série de tests sur les méthodes de la classe AffichageConsole.
     * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
     */
     static void testRegression();
 };
 
 #endif