#ifndef Personnage_h
#define Personnage_h


/**
  * @class Personnage
  * @brief Classe définissant le personnage.
  */

class Personnage {
    private:
        unsigned int hauteur; ///< Position y du personnnage (valeur entière).
        float velociteY; ///< Vitesse du personnage selon l'axe y.

    public:
        float carburant; ///< Quantité de carburant du joueur.

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
         */
        unsigned int getHauteur();

        /**
         * @brief Fonction pour le déplacement vertical du personnage.
         */
        void monter();

        /**
         * @brief Fonction appliquant la gravité au personnage.
         */
        void appliquerGravite();
    };

#endif