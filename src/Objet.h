/**
 *@file Objet.h
 *@brief Définition de la classe Objet du jeu JetpackEscape
 */

#ifndef Objet_h
#define Objet_h

/**
  * @class Objet
  * @brief Classe définissant un objet collectable dans le jeu. Un objet est constitué d'un type, et d'un couple de coordonnées.
  * On gère ici son initialisation, son déplacement, et les collisions avec le personnage.
  */
class Objet {
  private: 
    unsigned int idTypeObjet; ///< Identifiant du type de l'objet.
    int x; ///< Position x de l'objet.
    int y; ///< Position y de l'objet.

  public:
    /**
     * @brief Constructeur par défaut de la classe Objet
     * @param id Identifiant du type d'objet.
     * @param x Position horizontale de l'objet.
     * @param y Position verticale de l'objet
     */
    Objet(unsigned int id, int x, int  y);
        
    /**
     * @brief Détermine si le personnage entre en collision avec l'objet, et quel est son type
     * @param hauteur Hauteur actuelle du personnage.
     * @return L'identifiant de l'objet s'il est en collision avec le personnage, sinon 100.
     */
    unsigned int collecterObjet(int hauteur) const;

    /**
     * @brief Procédure pour actualiser la position de l'objet. L'objet est déplacé vers la gauche d'une unité de jeu.
     */
    void mettreAJourPosition();

    /**
     * @brief Accesseur pour obtenir la position horizontale de l'objet.
     * @return La position x de l'objet.
     */
    int getX() const;

    /**
     * @brief Accesseur pour obtenir la position verticale de l'objet.
     * @return La position y de l'objet.
     */
    int getY() const;

    /**
     * @brief Accesseur pour obtenir l'identifiant du type d'objet.
     * @return L'identifiant de l'objet.
     */
    int getID() const;
    
    /**
     * @brief Effectue une série de tests sur la classe Objet.
    */
    static void testObjet();
    
  };

#endif