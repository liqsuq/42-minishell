[English](./README_en.md) | [日本語](./README.md) | French

<p align="center">
  <picture>
    <img height="300" alt="minishellImage" src="https://github.com/user-attachments/assets/96aab2ee-f9e3-4db8-ac33-61ad4aed5ad8">
  </picture>
</p>

<p align="center">
Minishell est un shell léger écrit en C, inspiré des fonctions essentielles des Bash comme l'exécution de commandes, la redirection, les pipes et l'expansion des variables d'environnement.<br>
Il gère différents mécanismes bas niveau du système, notamment la création de processus, la gestion des entrées/sorties via des descripteurs de fichiers, et les signaux,<br>
tout en cherchant à reproduire au mieux le comportement des Bash.
</p>


<p align="center">
  <a href="https://github.com/liqsuq/42-minishell/wiki">🐚 Voici un Wiki pour vous aider à comprendre le diagramme ER et la structure du projet</a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-213a70.svg?logo=C&style=flat">
  <img src="https://img.shields.io/badge/-Linux-ea5520.svg?logo=linux&style=flat">
</p>

<hr>

## Liste des commandes Make
| Catégorie de fonctionnalité | Description |
|-----------------------------|-------------|
| Invite de commande          | Affiche toujours l'invite `minish$` avec la gestion de l'historique grâce à `readline` |
| Exécution de commandes      | Exécute les commandes trouvées dans le `PATH` ou les codes binaires spécifiés via des chemins relatifs/absolus à l'aide de `execve(2)` |
| Redirections                | Gère correctement `<`, `>`, `>>` et `<<` (here-document), y compris les redirections imbriquées |
| Pipes                       | Développe et exécute récursivement des pipelines de longueur illimitée |
| Expansion des variables     | Développe `$VAR` et le code de retour `$?` jeton par jeton |
| Commandes intégrées         | `echo`・`cd`・`pwd`・`export`・`unset`・`env`・`exit` |
| Gestion des signaux         | `Ctrl-C`・`Ctrl-\`・`Ctrl-D` |
| Compatibilité des erreurs   | Renvoie les mêmes codes de sortie que Bash : commande introuvable (127), permission refusée (126), et erreur de syntaxe (2) |

## Liste des commandes Make
| Cible Make  | Description                                                                                     |
|-------------|-------------------------------------------------------------------------------------------------|
| all         | Compile tous les fichiers sources dépendants et crée le fichier exécutable.                    |
| clean       | Supprime les fichiers objets (*.o, etc.) générés lors de la compilation.                       |
| fclean      | Exécute `clean` et supprime en plus l'exécutable généré ainsi que les éventuelles bibliothèques.|
| re          | Lance `fclean` puis `all` pour reconstruire entièrement le projet.                             |




## Comment compiler
Installation des dépendances
- macOS (Homebrew)
```
$ brew install readline
```
- Ubuntu (APT)
```
$ sudo apt-get update && sudo apt-get install libreadline-dev
```
```
$ git clone <this repository>
$ cd 42-minishell
$ make
$ ./minishell
minish$
```

## Structure du répertoire
```
builtin/     … Implémentation des commandes intégrées  
execute/     … Logique de fork/exec et gestion des pipelines  
expand/      … Expansion des variables, paramètres et guillemets  
misc/        … Gestion des signaux, des erreurs et utilitaires pour les variables d’environnement  
parse/       … Analyse syntaxique récursive (recursive descent parser)  
redirect/    … Gestion des redirections et des here-documents  
tokenize/    … Analyse lexicale (tokeniseur)  
pipeline/    … Création et exécution des nœuds de pipeline  
tester.sh    … Script de test de compatibilité avec Bash  
```

## Conformité à la Norminette (en mai 2025)
Ce projet suit strictement les règles de la Norminette de 42 (version 3.3.58).  
[Norminette](https://github.com/42School/norminette) est un outil conçu pour faire respecter un style de code cohérent dans les projets en C à 42.  
Les principales règles incluent :

- Maximum de 25 lignes par fonction  
- Maximum de 80 caractères par ligne  
- Maximum de 5 fonctions par fichier  
- En-têtes de fonctions requis dans un format spécifique  
- Restrictions sur l'utilisation des fonctions de la bibliothèque standard  
- Règles strictes sur la déclaration et la dénomination des variables  
- Indentation obligatoire avec des tabulations  
- Interdiction d’utiliser `for`, `switch`, `do-while` et autres structures similaires  

## Tests
Après la compilation, vous pouvez exécuter `tester.sh` pour comparer automatiquement la sortie et les codes de retour entre Bash et Minishell.  
Cela permet de vérifier en un seul coup si toutes les fonctionnalités principales sont compatibles.
<p align="left">
  <img src="https://github.com/user-attachments/assets/acb01f2c-5a10-4465-86d0-332571e75438" height="500">
</p>

## Évaluation

Date de l'évaluation : 11-mai-2025

Partie obligatoire : 100 / 100

Bonus : 1 / 15

