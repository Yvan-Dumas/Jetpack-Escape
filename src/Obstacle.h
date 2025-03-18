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
        unsigned int largeur; ///< Largeur de l'Obstacle.
        unsigned int longueur; ///< Longueur y de l'Obstacle.

    public:
        /**
         * @brief Constructeur par défaut de la classe Obstacle
         */
        Obstacle();
        
        /**
         * @brief Fonction booléene qui renvoie vrai si le personnage est en contact avec l'obstacle.
         * @param hauteur int Hauteur du personnage.
         */
        bool collisionObstacle(int hauteur) const;

        /**
         * @brief Procédure pour actualiser la position de l'obstacle.
         * @param vitesse int vitesse du jeu
         */
        void mettreAJourPosition(int vitesse);
  };

#endif