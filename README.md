# Projet d'Analyse de Complexité Algorithmique

Ce projet implémente et analyse trois stratégies différentes pour identifier les marqueurs négatifs dans un ensemble de données, en comptant le nombre d'opérations de comparaison nécessaires pour chaque stratégie.

## Description

Ce projet est une implémentation en C d'un exercice d'analyse de complexité algorithmique. Il travaille avec le concept d'expériences contenant des marqueurs, certains étant identifiés comme "positifs". Le but est de trouver efficacement tous les marqueurs "négatifs" (non-positifs) en utilisant différentes stratégies et d'analyser leur complexité.

Les trois stratégies implémentées sont :
1. **Stratégie 1** : Approche par force brute - vérifie chaque marqueur contre tous les marqueurs positifs
2. **Stratégie 2** : Utilisation de la recherche dichotomique après tri préalable
3. **Stratégie 3** : Approche optimisée utilisant un parcours linéaire après tri

## Structure du Projet

- `main.c` : Contient l'implémentation de toutes les stratégies et le code de test
- `CMakeLists.txt` : Configuration pour la compilation avec CMake
- `run.sh` : Script pour exécuter le programme et sauvegarder les résultats
- `res-*.dat` : Fichiers de données contenant les résultats d'exécution pour différentes tailles d'ensembles

## Fonctionnalités

- Création et manipulation d'expériences avec marqueurs positifs et négatifs
- Implémentation de trois stratégies différentes pour trouver les marqueurs négatifs
- Comptage du nombre d'opérations pour chaque stratégie
- Comparaison et analyse des performances des stratégies
- Génération de résultats pour différentes tailles d'ensembles de données

## Comment utiliser

### Prérequis
- Compilateur C (GCC recommandé)
- CMake (optionnel)

### Compilation
```bash
# Avec CMake
cmake .
make

# Ou directement avec gcc
gcc -o main main.c
```

### Exécution
```bash
./main
```
Le programme vous demandera :
1. Le nombre de marqueurs positifs
2. Le nombre total de marqueurs

### Générer des résultats
Utilisez le script `run.sh` pour exécuter le programme et sauvegarder les résultats :
```bash
chmod +x run.sh
./run.sh
```

## Analyse de la complexité

- **Stratégie 1** : Complexité O(m×p), où m est le nombre total de marqueurs et p le nombre de marqueurs positifs
- **Stratégie 2** : Complexité O(m log p), grâce à l'utilisation de la recherche dichotomique
- **Stratégie 3** : Complexité O(m), approche optimisée avec parcours linéaire

Les fichiers `res-*.dat` contiennent les résultats expérimentaux qui confirment ces analyses théoriques. 