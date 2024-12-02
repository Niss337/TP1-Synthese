# TP1-Synthese

Ce projet contient les fichiers principaux d'un shell simple en C, permettant d'exécuter des commandes d'un système d'exploitation. Les fichiers clés sont les suivants :

### 1. `main.c`

- **Fonctions Principales**: 
  - Gère le flux principal du shell, y compris l'affichage du prompt, la lecture des commandes de l'utilisateur et l'exécution de ces commandes.
  - Mesure le temps d'exécution des commandes à l'aide de `clock_gettime`.
- **Intérêt**: Ce fichier est le point d'entrée du programme. Il orchestre l'interaction utilisateur et le traitement des commandes, ce qui est essentiel pour le fonctionnement du shell.

### 2. `shell.c`

- **Fonctions Principales**:
  - Contient des fonctions pour afficher le prompt, lire les commandes de l'utilisateur, et exécuter les commandes via des processus enfants.
  - Gère l'exécution des commandes en utilisant `fork` et `execvp`.
- **Intérêt**: Ce fichier encapsule la logique d'exécution des commandes, permettant au shell de fonctionner de manière fluide et efficace. Il gère également les erreurs liées à l'exécution des commandes.

### 3. `shell.h`

- **Contenu**:
  - Définit les constantes, les prototypes de fonctions, et les structures nécessaires pour le fonctionnement du shell.
- **Intérêt**: Ce fichier d'en-tête facilite la modularité du code et permet de séparer les déclarations de fonctions des définitions, ce qui améliore la lisibilité et l'organisation du projet.

## Installation

Pour compiler le projet, utilisez la commande suivante :

```bash
gcc  main.c shell.c -o my_shell -lrt
./my_shell
