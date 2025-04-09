/**
 *@file Personnage.h
 *@brief Définition de la classe Personnage
 */

#ifndef Personnage_h
#define Personnage_h

#include <iostream>
#include <cassert>


/**
  * @class Personnage
  * @brief Classe définissant le personnage.
  */

class Personnage {
  private:
    unsigned int hauteur; ///< Position y du personnnage (valeur entière).
    unsigned int nbPièces; ///< Le nombre de pièces ramassées par le personnage
    unsigned int distance; ///< La distance parcourue depuis le début de la partie par le personnage
    unsigned int nbVies; ///< Le nombre de vies restantes du personnage

  public:
    float carburant; ///< Quantité de carburant du joueur.
    float velociteY; ///< Vitesse du personnage selon l'axe y.

    /**
     * @brief Constructeur par défaut de la classe Personnage
     * Initialise la position du personnage et sa vitesse selon l'axe y à 0.
     */
    Personnage();

    /**
     * @brief Mutateur pour la position y du personnage
     * @param y entier non-signé 
     */
    void setHauteur(unsigned int y);

    /**
     * @brief Accesseur pour la position y du personnage
     * @return Retourne un entier non-signé
     */
    unsigned int getHauteur() const;

    /**
     * @brief Fonction pour le déplacement vertical du personnage.
     * @param HAUTEUR hauteur maximale (hauteur du toit)
     */
    void monter(unsigned int HAUTEUR);

    /**
     * @brief Fonction appliquant la gravité au personnage.
     */
    void appliquerGravite();

    /**
     * @brief Accesseur pour le nombre de pièces du personnage
     */
    unsigned int getNbPieces() const;

    /**
     * @brief Mutateur pour le nombre de pièces du personnage
     */
    void setNbPieces(unsigned int nb);

    /**
     * @brief Accesseur pour la distance parcourue par le personnage
     */
    unsigned int getDistance() const;

    /**
     * @brief Mutateur pour la distance parcourue par le personnage
     */
    void setDistance(unsigned int nb);

    /**
     * @brief Accesseur pour le nombre de vies du personnage
     */
    unsigned int getNbVies() const;

    /**
     * @brief Mutateur pour le nombre de vie du personnage
     */
    void setNbVies(unsigned int nb);

    /**
     * @brief Effectue une série de tests sur les méthodes de la classe Personnage.
     * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
     */
    static void testPersonnage();
    };

#endif