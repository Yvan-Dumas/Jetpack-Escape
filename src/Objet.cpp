 #include "Objet.h"
 #include <iostream>
 #include <cassert>

 
 using namespace std;


 Objet::Objet(unsigned int id, int x, int  y)
   : idTypeObjet(id), x(x), y(y) {}
 
 unsigned int Objet::collecterObjet(int hauteur) const {
   bool abscisse = (x == 5 || x==4); // 5 correspond à la position x du personnage. On vérifie aussi en x = 4 pour plus de facilité
   bool ordonnee = y == hauteur ;    // Vérification de la correspondance entre la hauteur du personnage et celle de l'objet.
   if (abscisse && ordonnee){
      return idTypeObjet;
   }
   return 100; // 100 indique que le personnage n'est pas en contact avec un objet
 }

void Objet::mettreAJourPosition() {
    x -= 1; // L'objet se déplace vers la gauche
 }

int Objet::getX() const {
    return x;
}

int Objet::getY() const {
    return y;
}

int Objet::getID() const {
   return idTypeObjet;
}
void Objet::testObjet() {
   cout << "Début des tests pour Objet" << endl;

   // Test constructeur
   Objet obj(1, 5, 10);

   // Vérification des valeurs initiales après création de l'objet
   assert(obj.getX() == 5 && "Test échoué : La position X initiale n'est pas correcte");
   assert(obj.getY() == 10 && "Test échoué : La position Y initiale n'est pas correcte");
   assert(obj.getID() == 1 && "Test échoué : L'ID de l'objet n'est pas correct");

   // Test de la fonction collecterObjet

   // Le personnage est à la position x=5 et y=10, donc l'objet doit être collecté
   assert(obj.collecterObjet(10) == 1 && "Test échoué : L'objet n'a pas été collecté alors qu'il aurait dû l'être");

   // Test avec un personnage à une autre position (y=20), l'objet ne doit pas être collecté
   assert(obj.collecterObjet(20) == 100 && "Test échoué : L'objet a été collecté alors qu'il ne l'aurait pas dû");

   // Test de la procédure mettreAJourPosition
   obj.mettreAJourPosition();
   assert(obj.getX() == 4 && "Test échoué : La position X après mise à jour n'est pas correcte");

   cout << "Tous les tests ont réussi !" << endl;
}