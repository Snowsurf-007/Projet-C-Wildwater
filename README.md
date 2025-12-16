# 📘 Projet-C-Wildwater
Synthèse et analyse d’un réseau de distribution d’eau
CYTech – préING2 – 2025/2026

# 🎯 Description du projet

Ce projet a pour objectif de réaliser un outil d’analyse de données d’un système de distribution d’eau potable à partir d’un fichier CSV de grande taille (> 500 Mo).
L’application est composée :

- d’un script Shell servant de point d’entrée utilisateur,
- d’un programme en langage C chargé d’effectuer les calculs intensifs via des Arbres.

Les données représentent une topologie simplifiée de la distribution d’eau (sources, usines de traitement, stockages, jonctions, raccordements et usagers), avec des volumes annuels et des pourcentages de fuites.

# ⚙️ Fonctionnalités
1. Histogrammes des usines de traitement

Génération de fichiers de données et d’images (PNG) représentant les performances des usines selon l’un des critères suivants :
- max : capacité maximale annuelle de traitement.
- src : volume total capté depuis les sources.
- real : volume réellement traité (après fuites amont).

Les résultats incluent :
- un histogramme des 50 plus petites usines.
- un histogramme des 10 plus grandes usines.

2. Calcul des pertes d’eau (fuites)

- Calcul du volume total d’eau perdu sur l’ensemble du réseau aval d’une usine donnée.
- Le résultat est exprimé en millions de m³ par an (M.m³/an).
- Si l’identifiant de l’usine est inconnu, la valeur -1 est retournée.
- Les résultats sont historisés dans un fichier .dat.

# 🛠️ Exécution

Ouvrez votre terminal et entrez les commandes suivantes :

git clone https://github.com/Snowsurf-007/Projet-C-Wildwater
cd Projet-C-Wildwater

# ▶️ Utilisation

Le script Shell constitue le point d’entrée du projet.

Syntaxe générale
./myScript.sh <fichier_donnees.csv> <commande> [option]

Commandes disponibles
Histogrammes
./myScript.sh wildwater.dat histo max
./myScript.sh wildwater.dat histo src
./myScript.sh wildwater.dat histo real

Calcul des fuites
./myScript.sh wildwater.dat leaks "Facility complex #RH400057F"

# 📂 Fichiers de sortie

- 📄 Fichiers de données (.dat, .txt, .csv)
- 🖼️ Images PNG des histogrammes générés
- 🗃️ Fichier d’historique des fuites par usine (.dat)
- 🏷️ Noms de fichiers distincts selon le traitement effectué
