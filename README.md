# 📘 Projet-C-Wildwater
Synthèse et analyse d’un réseau de distribution d’eau
CYTech – préING2 – 2025/2026

# 🎯 Objectif général

Ce projet consiste à développer :
- Un script Shell : point d’entrée de l’application, gérant l’analyse d’un fichier massif de données (CSV ≥ 500 Mo, > 8 millions de lignes).
- Un programme en C : chargé de tous les calculs lourds (histogrammes, volumes, pertes).
- Une architecture modulaire et robuste, utilisant :
    AVL pour indexer efficacement les usines ou les nœuds
    Arbres généraux pour représenter la distribution en aval
