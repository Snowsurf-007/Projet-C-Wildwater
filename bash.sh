#!/bin/bash

#début mesure du temps
debut=$(date +%s.%N)

#verification bon nombre d'arguments
if [ $# -ne 3 ]
then 
	echo "ERREUR: le nombre d'argument donné n'est pas le bon !"
	fin=$(date +%s.%N)
	time=$(echo "($fin - $debut)*1000" | bc)
    	echo "Le programme a mis ${time} ms à être exécuté"
    	exit 1
fi



if [ ! -r "$DATAFILE" ]
then
	echo "ERREUR: fichier d'entrée introuvable ou non lisible !"
	fin=$(date +%s.%N)
	time=$(echo "($fin - $debut)*1000" | bc)
    	echo "Le programme a mis ${time} ms à être exécuté"
	exit 2
fi



#partie appel histogramme
bash 

#partie appel code C

#verif retour code C



fin=$(date +%s.%N)
time=$(echo "($fin - $debut)*1000" | bc)
echo "Durée totale : ${time} ms"
