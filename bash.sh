#!/bin/bash

echo "Compilation..."
make

echo "Exécution :"
./programme

if [ $# -ne 3 ]
then

fi

cat fuite.txt
# awk -F';' '$NF ~ /-/' fichier.csv > temp.csv  #recupere usine 
# cut -d';' -f2,4 temp.csv>temp2.csv #recupere donnée usine
