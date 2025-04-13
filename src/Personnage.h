/**
 *@file Personnage.h
 *@brief Définition de la classe Personnage du jeu JetpackEscape
 */

#ifndef Personnage_h
#define Personnage_h

#include <iostream>
#include <cassert>


/**
  * @class Personnage
  * @brief Classe représentant le personnage dans le jeu
  * Cette classe représente un personnage contrôlable par le joueur.
  * Elle gère les informations liées à sa position (plus exactement sa hauteur, car il n'y a pas de déplacement horizontal),
  * ses ressources (carburant, vies, pièces), et son déplacement (c'est dans cette classe que l'on a les fonctions monter,
  * et l'application de la gravité).
  */

class Personnage {
  private:
    unsigned int hauteur; ///< Position verticale (axe Y) du personnage. (valeur entière, on se situe sur une grille)
    unsigned int nbPièces;  ///< Nombre de pièces ramassées par ce personnage.
    unsigned int distance;  ///< Distance parcourue en unité de jeu (~m) depuis le début de la partie par ce personnage.
    unsigned int nbVies;    ///< Nombre de vies restantes de ce personnage.

  public:
    float carburant; ///< Quantité de carburant disponible pour le personnage.
    float velociteY;  ///< Vitesse verticale actuelle du personnage.

    /**
     * @brief Constructeur par défaut de la classe Personnage
     * Initialise la position Y (la position X est implicite car constante), le carburant, et la vitesse verticale.
     */
    Personnage();

    /**
     * @brief Mutateur pour la position y du personnage
     * @param y Hauteur (coordonnée Y) à affecter au personnage.
     */
    void setHauteur(unsigned int y);

    /**
     * @brief Accesseur pour la position y du personnage
     * @return La position verticale du personnage.
     */
    unsigned int getHauteur() const;

    /**
     * @brief Fonction pour le déplacement vertical du personnage.
     * @param HAUTEUR hauteur maximale (hauteur du toit).
     * On donne la hauteur maximale en paramètres car on peut avoir à envisager de la changer.
     */
    void monter(unsigned int HAUTEUR);

    /**
     * @brief Applique la gravité au personnage.
     * On applique une constante négative à la vélocité verticale du personnage en prennant
     * en compte sa position Y, que l'on modifie ensuite.
     */
    void appliquerGravite();

    /**
     * @brief Accesseur pour le nombre de pièces du personnage
     * @return Nombre de pièces du personnage.
     */
    unsigned int getNbPieces() const;

    /**
     * @brief Mutateur pour le nombre de pièces du personnage
     * @param nb Nombre de pièces à affecter.
     */
    void setNbPieces(unsigned int nb);

    /**
     * @brief Accesseur pour la distance parcourue par le personnage
     * @return Distance en unités de jeu.
     */
    unsigned int getDistance() const;

    /**
     * @brief Mutateur pour la distance parcourue par le personnage
     * @param nb Distance à affecter.
     */
    void setDistance(unsigned int nb);

    /**
     * @brief Accesseur pour le nombre de vies du personnage
     * @return Nombre de vies.
     */
    unsigned int getNbVies() const;

    /**
     * @brief Mutateur pour le nombre de vie du personnage
     * @param nb Nombre de vies à affecter.
     */
    void setNbVies(unsigned int nb);

    /**
     * @brief Effectue une série de tests sur la classe Personnage.
     */
    static void testPersonnage();
    };

#endif