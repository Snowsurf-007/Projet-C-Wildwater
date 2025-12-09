#!/bin/bash

#début mesure du temps
debut=$(date +%s.%N)

#verification bon nombre d'arguments
if [ $# -lt 3 ]
then 
	echo "ERREUR: commande icomplete, il manque des arguments !"
	fin=$(date +%s.%N)
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
    	exit 1
fi

if [ $# -gt 3 ]
then 
	echo "ERREUR: trop d'argument !"
	fin=$(date +%s.%N)
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
    	exit 1
fi

fichier="$1"

if [ ! -r "$fichier" ]
then
	echo "ERREUR: fichier d'entrée introuvable ou non lisible !"
	fin=$(date +%s.%N)
	time=$((fin-debut))
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
	exit 2
fi

#option="$2"

#case "$option" in
#	histo);;
#	leaks)make;;
#	*);;
#esac

#partie appel fonction histogramme
#bash histo.sh

#partie appel code C
#make
#./leaks

#verif retour code C



fin=$(date +%s.%N)
time=`echo "$fin-$debut" | bc`
time=`echo "$time*1000" | bc`
echo "Durée totale : $time ms"
