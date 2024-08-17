
cmake_minimum_required(VERSION 3.10)
project(minishell_tests C)

# Ajouter tous les fichiers de test ici
file(GLOB_RECURSE TEST_SOURCES tests/*.c)

# Définir l'exécutable pour les tests
add_executable(run_tests ${TEST_SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(run_tests readline)
