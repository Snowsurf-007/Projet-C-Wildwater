#!/bin/bash

echo "Compilation..."
make

echo "Exécution :"
./programme

if [ $# -ne 3 ]
then

fi

cat fuite.txt
# awk -F';' '$NF ~ /-/' fichier.csv > temp.txt #recupere les lignes contenant des usines
