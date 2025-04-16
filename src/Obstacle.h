/**
 *@file Obstacle.h
 *@brief Définition de la classe Obstacle du jeu JetpackEscape
 */
#ifndef Obstacle_h
#define Obstacle_h

#include <iostream>
#include <cassert>

/**
  * @class Obstacle
  * @brief Classe définissant un Obstacle. Un obstacle est constitué d'un indentifiant qui caractérise son type,
  * d'une position (x,y), d'une largeur et d'une longueur. On gère dans cette classe l'initialisation, la collision
  * et le déplacement d'obstacles.
  */
class Obstacle {
  private: 
    unsigned int idTypeObstacle; ///< Identifiant du type de l'Obstacle.
    int x;  ///< Coordonnée horizontale (axe x) de l'obstacle.
    int y; ///< Coordonnée verticale (axe y) de l'obstacle
    unsigned int largeur; ///< Largeur de l'obstacle selon l'axe x.
    unsigned int longueur; ///< Longueur y de l'obstacle selon l'axe y.

  public:
    /**
     * @brief Constructeur par défaut de la classe Obstacle
     * @param id Identifiant du type d'obstacle.
     * @param x Coordonnée x initiale.
     * @param y Coordonnée y initiale.
     * @param largeur Largeur de l'obstacle (horizontale).
     * @param longueur Longueur de l'obstacle (verticale).
     */
    Obstacle(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur);
        
    /**
     * @brief Détecte une collision entre l'obstacle et le personnage.
     * @param hauteur Hauteur actuelle du personnage (position verticale). Cela suffit car la position verticale du personnage ne varie pas.
     * @return true s'il y a collision, false sinon.
     */
    bool collisionObstacle(int hauteur) const;

    /**
     * @brief Déplace l'obstacle vers la gauche (simulation d'un  mouvement du personnage vers la droite).
     * @details À appeler à chaque mise à jour du jeu pour faire défiler l'obstacle à l'écran.
     */
    void mettreAJourPosition();

    /**
     * @brief Accesseur de la coordonnée x.
     * @return La position horizontale actuelle de l'obstacle.
     */
    int getX() const;

    /**
     * @brief Accesseur de la coordonnée y.
     * @return La position verticale actuelle de l'obstacle.
     */
    int getY() const;

    /**
     * @brief Accesseur de la largeur de l'obstacle.
     * @return La largeur de l'obstacle.
     */
    int getLargeur() const;

    /**
     * @brief Accesseur de la longueur de l'obstacle.
     * @return La longueur de l'obstacle.
     */
    int getLongueur() const;

    /**
     * @brief Accesseur de l'identifiant de l'obstacle.
     * @return L'ID représentant le type de l'obstacle.
     */
    unsigned int getID() const;

    /**
     * @brief Effectue une série de tests sur la classe Obstacle.
     */
    static void testObstacle();
  };

#endif