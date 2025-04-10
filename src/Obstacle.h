/**
 *@file Obstacle.h
 *@brief Définition de la classe Obstacle
 */

#ifndef Obstacle_h
#define Obstacle_h

/**
  * @class Obstacle
  * @brief Classe définissant un Obstacle en fonction de son identifiant et de sa position.
  */
class Obstacle {
  private: 
    unsigned int idTypeObstacle; ///< Identifiant du type de l'Obstacle.
    int x; ///< Position x de l'Obstacle.
    int y; ///< Position y de l'Obstacle.
    unsigned int largeur; ///< Largeur de l'Obstacle selon l'axe x.
    unsigned int longueur; ///< Longueur y de l'Obstacle selon l'axe y.

  public:
    /**
     * @brief Constructeur par défaut de la classe Obstacle
     */
    Obstacle(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur);
        
    /**
     * @brief Fonction booléene qui renvoie vrai si le personnage est en contact avec l'obstacle.
     * @param hauteur int Hauteur du personnage.
     */
    bool collisionObstacle(int hauteur) const;

    /**
     * @brief Procédure pour actualiser la position de l'obstacle.
     */
    void mettreAJourPosition();

    /**
     * @brief renvoie la position x de l'obstacle
     */
    int getX() const;

    /**
     * @brief renvoie la position y de l'obstacle
     */
    int getY() const;

    /**
     * @brief renvoie la largeur de l'obstacle
     */
    int getLargeur() const;

    /**
     * @brief renvoie la longueur y de l'obstacle
     */
    int getLongueur() const;

    /**
     * @brief renvoie l'ID de l'obstacle
     */
    unsigned int getID() const;

    /**
     * @brief Effectue une série de tests sur les méthodes de la classe Obstacle.
     * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
    */
    static void testObstacle();
  };

#endif