/**
 *@file Personnage.h
 *@brief Définition de la classe Personnage
 */

#ifndef Personnage_h
#define Personnage_h


/**
  * @class Personnage
  * @brief Classe définissant le personnage.
  */

class Personnage {
    private:
        unsigned int hauteur; ///< Position y du personnnage (valeur entière).

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
         */
        void monter(unsigned int HAUTEUR);

        /**
         * @brief Fonction appliquant la gravité au personnage.
         */
        void appliquerGravite(unsigned int HAUTEUR);

        /**
        * @brief Effectue une série de tests sur les méthodes de la classe Personnage.
        * Vérifie le bon fonctionnement de toutes les méthodes et la cohérence des données membres.
        */
        static void testPersonnage();
    };

#endif