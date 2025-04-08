 #include "Objet.h"
 #include <iostream>
 #include <cassert>

 
 using namespace std;


 Objet::Objet(unsigned int id, int x, int  y,unsigned int  largeur, unsigned int longueur )
    : idTypeObjet(id), x(x), y(y), largeur(largeur), longueur(longueur) {}
 
 unsigned int Objet::collecterObjet(int hauteur) const {
    bool abscisse = (x == 5 || x==4); // 5 correspond à la position x du personnage
    bool ordonnee;
    if (hauteur == 1 || hauteur == 9) { 
      ordonnee =  y == hauteur; }
      else {  
         ordonnee = y == hauteur ; }
    if (abscisse && ordonnee){
       return idTypeObjet;
    }
    return 100; // 100 indique que le perosnnage n'est pas en contact avec un objet
 }

void Objet::mettreAJourPosition() {
    x -= 0.5;
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
   cout<<"Début des test pour Objet"<<endl;
// Test du constructeur
Objet obj(1, 5, 10, 20, 30);
    
// Vérification de la position initiale et de l'ID
assert(obj.getX() == 5 && "Test échoué : La position X initiale n'est pas correcte");
assert(obj.getY() == 10 && "Test échoué : La position Y initiale n'est pas correcte");
assert(obj.getID() == 1 && "Test échoué : L'ID de l'objet n'est pas correct");

// Test de la méthode collecterObjet
// Le personnage est à la position x = 5 et y = 10, donc l'objet doit être collecté
assert(obj.collecterObjet(10) == 1 && "Test échoué : L'objet n'a pas été collecté alors qu'il aurait dû l'être");

// Test avec un personnage à une autre position (x=5 mais y=20)
assert(obj.collecterObjet(20) == 100 && "Test échoué : L'objet a été collecté alors qu'il ne l'aurait pas dû");

// Test de la méthode mettreAJourPosition
obj.mettreAJourPosition();
assert(obj.getX() == 0 && "Test échoué : La position X après mise à jour n'est pas correcte");

// Test avec une position hors de l'intervalle attendu pour collecter l'objet
obj.mettreAJourPosition(); // L'objet devrait se déplacer encore
assert(obj.getX() == -10 && "Test échoué : La position X après seconde mise à jour n'est pas correcte");

// Si tout passe, on affiche un message de succès
cout << "Tous les tests ont réussi !" <<endl;
}