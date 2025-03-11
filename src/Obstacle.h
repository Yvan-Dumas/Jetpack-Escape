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
        unsigned int idTypeObstacle; ///< Identifiant de l'Obstacle.
        unsigned int x; ///< Position x de l'Obstacle.
        unsigned int y; ///< Position y de l'Obstacle.
        unsigned int largeur; ///< Largeur de l'Obstacle.
        unsigned int hauteur; ///< Hauteur y de l'Obstacle.

    public:
        /**
         * @brief Constructeur par défaut de la classe Obstacle
         */
        Obstacle();
        
        /**
         * @brief Fonction booléene qui renvoie vrai si le personnage est en contact avec l'obstacle.
         * @param unsignedint Hauteur du personnage.
         */
        bool collisionObstacle(unsigned int y);

        /**
         * @brief Procédure pour actualiser la position de l'obstacle.
         */
        void mettreAJourPosition();
  };

#endif