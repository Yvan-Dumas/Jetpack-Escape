/**
 *@file Objet.h
 *@brief Définition de la classe Objet
 */

#ifndef Objet_h
#define Objet_h

/**
  * @class Objet
  * @brief Classe définissant un objet en fonction de son identifiant et de sa position.
  */
class Objet {
  private: 
    unsigned int idTypeObjet; ///< Identifiant de l'objet.
    int x; ///< Position x de l'objet.
    int y; ///< Position y de l'objet.
    unsigned int largeur; ///< Largeur de l'objet.
    unsigned int longueur; ///< Hauteur y de l'objet.

  public:
    /**
     * @brief Constructeur par défaut de la classe Objet
     */
    Objet(unsigned int id, int x, int  y, unsigned int  largeur, unsigned int longueur);
        
    /**
     * @brief Fonction qui renvoie l'identifiant de l'objet si le personnage est en contact avec l'objet.
     * @param hauteur int Hauteur du personnage.
     */
    unsigned int collecterObjet(int hauteur) const;

    /**
     * @brief Procédure pour actualiser la position de l'objet.
     * @param vitesse int Vitesse de défilement du jeu
     */
    void mettreAJourPosition(int vitesse);

    /**
     * @brief renvoie la position x de l'objet
     */
    int getX() const;

    /**
     * @brief renvoie la position y de l'objet
     */
    int getY() const;
  };

#endif