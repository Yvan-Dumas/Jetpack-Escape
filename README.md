# LIFAPCD - JetpackEscape

## Description

**JetpackEscape** est un jeu développé en C++ utilisant **SDL2**. Il s'agit d'un jeu de type endless runner proposant un mode **1 joueur** et **2 joueurs** où les joueurs doivent éviter des obstacles et en gérant leur carburant pour aller le plus loin possible. Une version **graphique** avec SDL2 est proposée, ou bien une version **console**, utilisant WinTxt. Ce projet a été réalisé dans le cadre de l'UE LIFAPCD.

## Auteurs
Yvan Dumas et Hugo Marconnet, élèves en deuxième année de Peip à Polytech Lyon
numéros étudiants : p2302033 et p2308033
identifiant du projet sur la Forge - Univ Lyon 1 : 38536

## Compilation

Le projet utilise **CMake** pour la configuration et la génération des exécutables. Il nécessite les bibliothèques **SDL2**, **SDL2_ttf** et **SDL2_image**. Il est éxécutable uniquement sous Linux ou WSL.

### Prérequis

Assurez-vous d’avoir installé les éléments suivants :

- Un compilateur C++ compatible C++17
- CMake ≥ 3.10
- SDL2
- SDL2_ttf
- SDL2_image

Pour la version graphique, un écran 1920 * 1080 est nécéssaire.

Sous Linux, vous pouvez installer les dépendances avec :

```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

### Étapes de compilation

1. Téléchargez le projet:
Ouvrez un terminal la où vous souhaitez télécharger le projet, puis entrez la commande suivante:
```bash
git clone https://forge.univ-lyon1.fr/p2308033/lifapcd-jetpack-escape.git
```

2. Allez dans le dossier de build:
En vous plaçant à la racine du projet
```bash
cd bin
```

3. Générez les fichiers de build avec CMake :

```bash
cmake ..
```

4. Compilez le projet :

```bash
make
```

### Exécutables générés

Après compilation, vous obtiendrez trois exécutables dans le dossier `bin` :

- `JetpackEscapeConsole` — version console (la bibliothèque winTXT est utilisé, le code est intégré au `src` )
- `JetpackEscapeGraphique` — version graphique avec SDL2
- `JetpackEscapeReg` — éxécutable des tests de régression

Lancez-les avec, par exemple :

```bash
./JetpackEscapeConsole
./JetpackEscapeGraphique
./JetpackEscapeReg
```

---

## Contrôles

- **Z** : Activer le jetpack du premier joueur, en mode un et deux joueurs.
- **L** : Activer le jetpack du deuxième joueur, en mode deux joueurs.
- **Q**: Quitter le jeu en mode graphique ou console.
- **ECHAP**: Permet également de quitter le jeu en mode graphique.

---

## Documentation

La documentation du projet est générée automatiquement grâce à doxygen.

1. Assurez-vous d’avoir installé doxygen:
Sous Linux, vous pouvez installer doxygen avec :
```bash
sudo apt update
sudo apt install doxygen
```

2. Générez la documentation:
En vous plaçant à la racine du projet
```bash
doxygen doc/doxyfile
```

3. Accéder à la documenation
```bash
cd doc/html
xdg-open index.html
```

---

## Architecture du code:
Pour plus d'informations, se reporter à la documentation doxygen.

- **`src/`** : Contient le code source du projet.
  - **`src/Personnage.cpp`** : Gestion du personnage.
  - **`src/Obstacle.cpp`** : Gestion des obstacles dans le jeu.
  - **`src/Objet.cpp`** : Gestion des objets récupérables dans le jeu.
  - **`src/Partie.cpp`** : Gestion de la logique de la partie.
  - **`src/WinTxt.cpp`** : Bibliothèque utilisée pour la version console.
  - **`src/AffichageConsole.cpp`** : Gestion du rendu de la partie dans la version console.
  - **`src/mainConsole.cpp`** : Fonction principale pour la version console.  
  - **`src/mainRegression.cpp`** : Appelle les différents tests de régression.
  - **`src/SDL/`** : Contient les programmes utilisées pour la version graphique.
    - **`src/mainGraphique.cpp`** : Fonction principale pour la version graphique.
    - **`src/SDL/AffichageGraphique.cpp`** : Rendu graphique de la partie avec SDL.
    - **`src/SDL/SDLSprite.cpp`** : Gestion des sprites en SDL2.

- **`bin/`** : Dossier de compilation contenant les exécutables du jeu.

- **`data/`** : Dossier contenant différents fichiers nécessaires au bon fonctionnement du jeu.
  - **`data/images/`** : Contient les images utilisées dans la version graphique.
  - **`data/polices/`** : Contient les polices utilisées dans la version graphique.
  - **`data/sauvegarde.txt`** : Fichier où est sauvegardé le meilleur score du jeu.

- **`doc/`** : Dossier de documentation.
  - **`doc/doxyfile`** : Fichier de configuration de doxyfile.

- **`CMakeLists.txt`** : Fichier de configuration de CMake pour compiler le projet.
- **`README.md`** : Documentation du projet (ce fichier).

---

## Crédits:
polices : 
https://fonts.google.com/specimen/Press+Start+2P
https://fonts.google.com/specimen/VT323
https://fr.fonts2u.com/pixel-lcd-7.police?ptext=JETPACK+ESCAPE

Textures:
https://craftpix.net/freebies/free-gui-for-cyberpunk-pixel-art/?srsltid=AfmBOorN88IlLcF5GHKjpGvR_oqWq6rgVs0UsseLV8I1AnVcNTF66zhI
https://closeluca.itch.io/heart?download

---
