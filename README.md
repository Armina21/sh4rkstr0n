# Sh4rksTr0n

Jeu Sh4rksTr0n réalisé en **C++** avec la bibliothèque **SFML**.

## Présentation

**Sh4rksTr0n** est un jeu d'arcade classique où deux joueurs s'affrontent sur une grille dans une course à la survie. Chaque joueur contrôle un requin lumineux qui laisse une traînée derrière elle. Le but du jeu est de forcer l'adversaire à se heurter à un mur ou à une traînée, tout en évitant les obstacles soi-même. Attention cependant aux bonus qui trainent sur la carte qui pourraient changer le cours de la partie...

## Fonctionnalités

- Choix du **mode de jeu** (1 joueur contre l'ordinateur ou 2 joueurs)
- Choix du terrain de jeu (**Avec/Sans** Bordures)
- **Bonus** aléatoires qui apparaissent sur la carte et qui donnent des avantages temporaires
- Système de **scores** pour les joueurs
- Gestionnaire de **volume** ! (dans la rubrique A propos)

## Contrôles

- Navigation dans les menus: flèches directionnelles
- Joueur 1 : **Z, Q, S, D** pour se déplacer
- Joueur 2 : **O, K, L, M** pour se déplacer
- Quitter la partie : **Echap**

## Comment jouer

- Utilisez les touches pour déplacer votre requin lumineux.
- Essayez d'encercler votre adversaire en évitant de vous heurter à un mur ou à votre propre traînée.
- Collectez les bonus pour obtenir des avantages temporaires.
- Le premier joueur à atteindre 5 points gagne la partie.

## Installation

1. Clonez le repository: `git clone https://forge.univ-lyon1.fr/p2110993/sh4rkstr0n`
2. Assurez-vous que vous avez installé SFML (les fichiers sont disponibles dans le dossier 'extern' selon votre OS)
3. Construisez le jeu: 

Soyez sûr d'être au bon endroit dans le répertoire : `cd .`  
Construisez les 2 versions (txt & sfml) : `make`  
Lancez l'exécutable : `./bin/tron_sfml`  

## Auteurs

Ce jeu a été créé par :
- [**PEREZ Stella** : p2103226] 
- [**VANG Amanda** : p2104130] 
- [**MERZOUKI** Aghiles : p2110993]
