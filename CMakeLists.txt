# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(JetpackEscape)

# Définition du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Rechercher SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)  # Recherche de SDL2_ttf
find_package(SDL2_image REQUIRED) # Recherche de SDL2_image
find_package(SDL2_mixer REQUIRED) # Recherche de SDL2_mixer

# Inclusion des fichiers d'en-tête
include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# Ajout des fichiers sources
set(SOURCESCONSOLE
    src/Personnage.cpp
    src/Obstacle.cpp
    src/Objet.cpp
    src/Partie.cpp
    src/AffichageConsole.cpp
    src/mainConsole.cpp
    src/winTxt.cpp
)

set(SOURCESGRAPHIQUE
    src/Personnage.cpp
    src/Obstacle.cpp
    src/Objet.cpp
    src/Partie.cpp
    src/SDL/mainGraphique.cpp
    src/SDL/AffichageGraphique.cpp
    src/SDL/SDLSprite.cpp
)

set(SOURCESREGRESSION
    src/Personnage.cpp
    src/Obstacle.cpp
    src/Objet.cpp
    src/Partie.cpp
    src/mainRegression.cpp
)

# Création de l'exécutable
add_executable(JetpackEscapeConsole ${SOURCESCONSOLE})
add_executable(JetpackEscapeGraphique ${SOURCESGRAPHIQUE})
add_executable(JetpackEscapeReg ${SOURCESREGRESSION})

# Inclusion des fichiers d'en-tête
include_directories(src)

# Lier les bibliothèques SDL2, SDL2_ttf, SDL2_image et SDL2_mixer pour graphique
target_link_libraries(JetpackEscapeGraphique SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer)

