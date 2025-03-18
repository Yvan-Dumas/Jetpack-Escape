# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(JetpackEscape)

# Définition du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajout des fichiers sources
set(SOURCES
    src/Personnage.cpp
    src/Obstacle.cpp
    src/Objet.cpp
    src/Partie.cpp
    src/AffichageConsole.cpp
    src/mainConsole.cpp
)

# Création de l'exécutable
add_executable(JetpackEscape ${SOURCES})

# Inclusion des fichiers d'en-tête
include_directories(src)